// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/message_center/views/notification_view.h"

#include "base/command_line.h"
#include "base/stl_util.h"
#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"
#include "components/url_formatter/elide_url.h"
#include "third_party/skia/include/core/SkPaint.h"
#include "third_party/skia/include/core/SkPath.h"
#include "ui/base/cursor/cursor.h"
#include "ui/base/layout.h"
#include "ui/gfx/canvas.h"
#include "ui/gfx/geometry/size.h"
#include "ui/gfx/skia_util.h"
#include "ui/gfx/text_elider.h"
#include "ui/message_center/message_center.h"
#include "ui/message_center/message_center_style.h"
#include "ui/message_center/notification.h"
#include "ui/message_center/notification_types.h"
#include "ui/message_center/views/bounded_label.h"
#include "ui/message_center/views/constants.h"
#include "ui/message_center/views/message_center_controller.h"
#include "ui/message_center/views/notification_button.h"
#include "ui/message_center/views/padded_button.h"
#include "ui/message_center/views/proportional_image_view.h"
#include "ui/native_theme/native_theme.h"
#include "ui/resources/grit/ui_resources.h"
#include "ui/strings/grit/ui_strings.h"
#include "ui/views/background.h"
#include "ui/views/border.h"
#include "ui/views/controls/button/image_button.h"
#include "ui/views/controls/image_view.h"
#include "ui/views/controls/label.h"
#include "ui/views/controls/progress_bar.h"
#include "ui/views/layout/box_layout.h"
#include "ui/views/layout/fill_layout.h"
#include "ui/views/native_cursor.h"
#include "ui/views/painter.h"
#include "ui/views/view_targeter.h"
#include "ui/views/widget/widget.h"
#include "url/gurl.h"

namespace {

// Dimensions.
const int kProgressBarWidth = message_center::kNotificationWidth -
    message_center::kTextLeftPadding - message_center::kTextRightPadding;
const int kProgressBarBottomPadding = 0;

// static
scoped_ptr<views::Border> MakeEmptyBorder(int top,
                                          int left,
                                          int bottom,
                                          int right) {
  return views::Border::CreateEmptyBorder(top, left, bottom, right);
}

// static
scoped_ptr<views::Border> MakeTextBorder(int padding, int top, int bottom) {
  // Split the padding between the top and the bottom, then add the extra space.
  return MakeEmptyBorder(padding / 2 + top,
                         message_center::kTextLeftPadding,
                         (padding + 1) / 2 + bottom,
                         message_center::kTextRightPadding);
}

// static
scoped_ptr<views::Border> MakeProgressBarBorder(int top, int bottom) {
  return MakeEmptyBorder(top,
                         message_center::kTextLeftPadding,
                         bottom,
                         message_center::kTextRightPadding);
}

// static
scoped_ptr<views::Border> MakeSeparatorBorder(int top,
                                              int left,
                                              SkColor color) {
  return views::Border::CreateSolidSidedBorder(top, left, 0, 0, color);
}

// static
// Return true if and only if the image is null or has alpha.
bool HasAlpha(gfx::ImageSkia& image, views::Widget* widget) {
  // Determine which bitmap to use.
  float factor = 1.0f;
  if (widget)
    factor = ui::GetScaleFactorForNativeView(widget->GetNativeView());

  // Extract that bitmap's alpha and look for a non-opaque pixel there.
  SkBitmap bitmap = image.GetRepresentation(factor).sk_bitmap();
  if (!bitmap.isNull()) {
    SkBitmap alpha;
    bitmap.extractAlpha(&alpha);
    for (int y = 0; y < bitmap.height(); ++y) {
      for (int x = 0; x < bitmap.width(); ++x) {
        if (alpha.getColor(x, y) != SK_ColorBLACK) {
          return true;
        }
      }
    }
  }

  // If no opaque pixel was found, return false unless the bitmap is empty.
  return bitmap.isNull();
}

// ItemView ////////////////////////////////////////////////////////////////////

// ItemViews are responsible for drawing each list notification item's title and
// message next to each other within a single column.
class ItemView : public views::View {
 public:
  ItemView(const message_center::NotificationItem& item);
  ~ItemView() override;

  // Overridden from views::View:
  void SetVisible(bool visible) override;

 private:
  DISALLOW_COPY_AND_ASSIGN(ItemView);
};

ItemView::ItemView(const message_center::NotificationItem& item) {
  SetLayoutManager(new views::BoxLayout(views::BoxLayout::kHorizontal,
      0, 0, message_center::kItemTitleToMessagePadding));

  views::Label* title = new views::Label(item.title);
  title->set_collapse_when_hidden(true);
  title->SetHorizontalAlignment(gfx::ALIGN_LEFT);
  title->SetEnabledColor(message_center::kRegularTextColor);
  title->SetBackgroundColor(message_center::kRegularTextBackgroundColor);
  AddChildView(title);

  views::Label* message = new views::Label(item.message);
  message->set_collapse_when_hidden(true);
  message->SetHorizontalAlignment(gfx::ALIGN_LEFT);
  message->SetEnabledColor(message_center::kDimTextColor);
  message->SetBackgroundColor(message_center::kDimTextBackgroundColor);
  AddChildView(message);

  PreferredSizeChanged();
  SchedulePaint();
}

ItemView::~ItemView() {
}

void ItemView::SetVisible(bool visible) {
  views::View::SetVisible(visible);
  for (int i = 0; i < child_count(); ++i)
    child_at(i)->SetVisible(visible);
}

// NotificationProgressBar /////////////////////////////////////////////////////

class NotificationProgressBar : public views::ProgressBar {
 public:
  NotificationProgressBar();
  ~NotificationProgressBar() override;

 private:
  // Overriden from View
  gfx::Size GetPreferredSize() const override;
  void OnPaint(gfx::Canvas* canvas) override;

  DISALLOW_COPY_AND_ASSIGN(NotificationProgressBar);
};

NotificationProgressBar::NotificationProgressBar() {
}

NotificationProgressBar::~NotificationProgressBar() {
}

gfx::Size NotificationProgressBar::GetPreferredSize() const {
  gfx::Size pref_size(kProgressBarWidth, message_center::kProgressBarThickness);
  gfx::Insets insets = GetInsets();
  pref_size.Enlarge(insets.width(), insets.height());
  return pref_size;
}

void NotificationProgressBar::OnPaint(gfx::Canvas* canvas) {
  gfx::Rect content_bounds = GetContentsBounds();

  // Draw background.
  SkPath background_path;
  background_path.addRoundRect(gfx::RectToSkRect(content_bounds),
                               message_center::kProgressBarCornerRadius,
                               message_center::kProgressBarCornerRadius);
  SkPaint background_paint;
  background_paint.setStyle(SkPaint::kFill_Style);
  background_paint.setFlags(SkPaint::kAntiAlias_Flag);
  background_paint.setColor(message_center::kProgressBarBackgroundColor);
  canvas->DrawPath(background_path, background_paint);

  // Draw slice.
  const int slice_width =
      static_cast<int>(content_bounds.width() * GetNormalizedValue() + 0.5);
  if (slice_width < 1)
    return;

  gfx::Rect slice_bounds = content_bounds;
  slice_bounds.set_width(slice_width);
  SkPath slice_path;
  slice_path.addRoundRect(gfx::RectToSkRect(slice_bounds),
                          message_center::kProgressBarCornerRadius,
                          message_center::kProgressBarCornerRadius);
  SkPaint slice_paint;
  slice_paint.setStyle(SkPaint::kFill_Style);
  slice_paint.setFlags(SkPaint::kAntiAlias_Flag);
  slice_paint.setColor(message_center::kProgressBarSliceColor);
  canvas->DrawPath(slice_path, slice_paint);
}

}  // namespace

namespace message_center {

// NotificationView ////////////////////////////////////////////////////////////

// static
NotificationView* NotificationView::Create(MessageCenterController* controller,
                                           const Notification& notification,
                                           bool top_level) {
  switch (notification.type()) {
    case NOTIFICATION_TYPE_BASE_FORMAT:
    case NOTIFICATION_TYPE_IMAGE:
    case NOTIFICATION_TYPE_MULTIPLE:
    case NOTIFICATION_TYPE_SIMPLE:
    case NOTIFICATION_TYPE_PROGRESS:
      break;
    default:
      // If the caller asks for an unrecognized kind of view (entirely possible
      // if an application is running on an older version of this code that
      // doesn't have the requested kind of notification template), we'll fall
      // back to a notification instance that will provide at least basic
      // functionality.
      LOG(WARNING) << "Unable to fulfill request for unrecognized "
                   << "notification type " << notification.type() << ". "
                   << "Falling back to simple notification type.";
  }

  // Currently all roads lead to the generic NotificationView.
  NotificationView* notification_view =
      new NotificationView(controller, notification);

#if defined(OS_LINUX) && !defined(OS_CHROMEOS)
  // Don't create shadows for notification toasts on linux wih aura.
  if (top_level)
    return notification_view;
#endif

  notification_view->CreateShadowBorder();
  return notification_view;
}

views::View* NotificationView::TargetForRect(views::View* root,
                                             const gfx::Rect& rect) {
  CHECK_EQ(root, this);

  // TODO(tdanderson): Modify this function to support rect-based event
  // targeting. Using the center point of |rect| preserves this function's
  // expected behavior for the time being.
  gfx::Point point = rect.CenterPoint();

  // Want to return this for underlying views, otherwise GetCursor is not
  // called. But buttons are exceptions, they'll have their own event handlings.
  std::vector<views::View*> buttons(action_buttons_.begin(),
                                    action_buttons_.end());
  buttons.push_back(close_button());

  for (size_t i = 0; i < buttons.size(); ++i) {
    gfx::Point point_in_child = point;
    ConvertPointToTarget(this, buttons[i], &point_in_child);
    if (buttons[i]->HitTestPoint(point_in_child))
      return buttons[i]->GetEventHandlerForPoint(point_in_child);
  }

  return root;
}

void NotificationView::CreateOrUpdateViews(const Notification& notification) {
  CreateOrUpdateTitleView(notification);
  CreateOrUpdateMessageView(notification);
  CreateOrUpdateProgressBarView(notification);
  CreateOrUpdateListItemViews(notification);
  CreateOrUpdateIconView(notification);
  CreateOrUpdateImageView(notification);
  CreateOrUpdateContextMessageView(notification);
  CreateOrUpdateActionButtonViews(notification);
}

void NotificationView::SetAccessibleName(const Notification& notification) {
  std::vector<base::string16> accessible_lines;
  accessible_lines.push_back(notification.title());
  accessible_lines.push_back(notification.message());
  accessible_lines.push_back(notification.context_message());
  std::vector<NotificationItem> items = notification.items();
  for (size_t i = 0; i < items.size() && i < kNotificationMaximumItems; ++i) {
    accessible_lines.push_back(items[i].title + base::ASCIIToUTF16(" ") +
                               items[i].message);
  }
  set_accessible_name(
      base::JoinString(accessible_lines, base::ASCIIToUTF16("\n")));
}

NotificationView::NotificationView(MessageCenterController* controller,
                                   const Notification& notification)
    : MessageView(this,
                  notification.id(),
                  notification.notifier_id(),
                  notification.small_image().AsImageSkia(),
                  notification.display_source()),
      controller_(controller),
      clickable_(notification.clickable()),
      top_view_(NULL),
      title_view_(NULL),
      message_view_(NULL),
      context_message_view_(NULL),
      icon_view_(NULL),
      bottom_view_(NULL),
      image_container_(NULL),
      image_view_(NULL),
      progress_bar_view_(NULL) {
  // Create the top_view_, which collects into a vertical box all content
  // at the top of the notification (to the right of the icon) except for the
  // close button.
  top_view_ = new views::View();
  top_view_->SetLayoutManager(
      new views::BoxLayout(views::BoxLayout::kVertical, 0, 0, 0));
  top_view_->SetBorder(
      MakeEmptyBorder(kTextTopPadding - 8, 0, kTextBottomPadding - 5, 0));
  AddChildView(top_view_);
  // Create the bottom_view_, which collects into a vertical box all content
  // below the notification icon.
  bottom_view_ = new views::View();
  bottom_view_->SetLayoutManager(
      new views::BoxLayout(views::BoxLayout::kVertical, 0, 0, 0));
  AddChildView(bottom_view_);

  CreateOrUpdateViews(notification);

  // Put together the different content and control views. Layering those allows
  // for proper layout logic and it also allows the close button and small
  // image to overlap the content as needed to provide large enough click and
  // touch areas (<http://crbug.com/168822> and <http://crbug.com/168856>).
  AddChildView(small_image());
  AddChildView(close_button());
  SetAccessibleName(notification);

  SetEventTargeter(
      scoped_ptr<views::ViewTargeter>(new views::ViewTargeter(this)));
}

NotificationView::~NotificationView() {
}

gfx::Size NotificationView::GetPreferredSize() const {
  int top_width = top_view_->GetPreferredSize().width() +
                  icon_view_->GetPreferredSize().width();
  int bottom_width = bottom_view_->GetPreferredSize().width();
  int preferred_width = std::max(top_width, bottom_width) + GetInsets().width();
  return gfx::Size(preferred_width, GetHeightForWidth(preferred_width));
}

int NotificationView::GetHeightForWidth(int width) const {
  // Get the height assuming no line limit changes.
  int content_width = width - GetInsets().width();
  int top_height = top_view_->GetHeightForWidth(content_width);
  int bottom_height = bottom_view_->GetHeightForWidth(content_width);

  // <http://crbug.com/230448> Fix: Adjust the height when the message_view's
  // line limit would be different for the specified width than it currently is.
  // TODO(dharcourt): Avoid BoxLayout and directly compute the correct height.
  if (message_view_) {
    int title_lines = 0;
    if (title_view_) {
      title_lines = title_view_->GetLinesForWidthAndLimit(width,
                                                          kMaxTitleLines);
    }
    int used_limit = message_view_->GetLineLimit();
    int correct_limit = GetMessageLineLimit(title_lines, width);
    if (used_limit != correct_limit) {
      top_height -= GetMessageHeight(content_width, used_limit);
      top_height += GetMessageHeight(content_width, correct_limit);
    }
  }

  int content_height = std::max(top_height, kIconSize) + bottom_height;

  // Adjust the height to make sure there is at least 16px of space below the
  // icon if there is any space there (<http://crbug.com/232966>).
  if (content_height > kIconSize)
    content_height = std::max(content_height,
                              kIconSize + message_center::kIconBottomPadding);

  return content_height + GetInsets().height();
}

void NotificationView::Layout() {
  MessageView::Layout();
  gfx::Insets insets = GetInsets();
  int content_width = width() - insets.width();

  // Before any resizing, set or adjust the number of message lines.
  int title_lines = 0;
  if (title_view_) {
    title_lines =
        title_view_->GetLinesForWidthAndLimit(width(), kMaxTitleLines);
  }
  if (message_view_)
    message_view_->SetLineLimit(GetMessageLineLimit(title_lines, width()));

  // Top views.
  int top_height = top_view_->GetHeightForWidth(content_width);
  top_view_->SetBounds(insets.left(), insets.top(), content_width, top_height);

  // Icon.
  icon_view_->SetBounds(insets.left(), insets.top(), kIconSize, kIconSize);

  // Bottom views.
  int bottom_y = insets.top() + std::max(top_height, kIconSize);
  int bottom_height = bottom_view_->GetHeightForWidth(content_width);
  bottom_view_->SetBounds(insets.left(), bottom_y,
                          content_width, bottom_height);
}

void NotificationView::OnFocus() {
  MessageView::OnFocus();
  ScrollRectToVisible(GetLocalBounds());
}

void NotificationView::ScrollRectToVisible(const gfx::Rect& rect) {
  // Notification want to show the whole notification when a part of it (like
  // a button) gets focused.
  views::View::ScrollRectToVisible(GetLocalBounds());
}

gfx::NativeCursor NotificationView::GetCursor(const ui::MouseEvent& event) {
  if (!clickable_ || !controller_->HasClickedListener(notification_id()))
    return views::View::GetCursor(event);

  return views::GetNativeHandCursor();
}

void NotificationView::UpdateWithNotification(
    const Notification& notification) {
  MessageView::UpdateWithNotification(notification);

  CreateOrUpdateViews(notification);
  SetAccessibleName(notification);
  Layout();
  SchedulePaint();
}

void NotificationView::ButtonPressed(views::Button* sender,
                                     const ui::Event& event) {
  // Certain operations can cause |this| to be destructed, so copy the members
  // we send to other parts of the code.
  // TODO(dewittj): Remove this hack.
  std::string id(notification_id());
  // See if the button pressed was an action button.
  for (size_t i = 0; i < action_buttons_.size(); ++i) {
    if (sender == action_buttons_[i]) {
      controller_->ClickOnNotificationButton(id, i);
      return;
    }
  }

  // Let the superclass handled anything other than action buttons.
  // Warning: This may cause the NotificationView itself to be deleted,
  // so don't do anything afterwards.
  MessageView::ButtonPressed(sender, event);
}

void NotificationView::ClickOnNotification(const std::string& notification_id) {
  controller_->ClickOnNotification(notification_id);
}

void NotificationView::RemoveNotification(const std::string& notification_id,
                                          bool by_user) {
  controller_->RemoveNotification(notification_id, by_user);
}

void NotificationView::CreateOrUpdateTitleView(
    const Notification& notification) {
  if (notification.title().empty()) {
    if (title_view_) {
      // Deletion will also remove |title_view_| from its parent.
      delete title_view_;
      title_view_ = NULL;
    }
    return;
  }

  DCHECK(top_view_ != NULL);

  const gfx::FontList& font_list =
      views::Label().font_list().DeriveWithSizeDelta(2);

  int title_character_limit =
      kNotificationWidth * kMaxTitleLines / kMinPixelsPerTitleCharacter;

  base::string16 title = gfx::TruncateString(notification.title(),
                                             title_character_limit,
                                             gfx::WORD_BREAK);
  if (!title_view_) {
    int padding = kTitleLineHeight - font_list.GetHeight();

    title_view_ = new BoundedLabel(title, font_list);
    title_view_->SetLineHeight(kTitleLineHeight);
    title_view_->SetLineLimit(kMaxTitleLines);
    title_view_->SetColors(message_center::kRegularTextColor,
                           kRegularTextBackgroundColor);
    title_view_->SetBorder(MakeTextBorder(padding, 3, 0));
    top_view_->AddChildView(title_view_);
  } else {
    title_view_->SetText(title);
  }
}

void NotificationView::CreateOrUpdateMessageView(
    const Notification& notification) {
  if (notification.message().empty()) {
    if (message_view_) {
      // Deletion will also remove |message_view_| from its parent.
      delete message_view_;
      message_view_ = NULL;
    }
    return;
  }

  DCHECK(top_view_ != NULL);

  base::string16 text = gfx::TruncateString(notification.message(),
                                            kMessageCharacterLimit,
                                            gfx::WORD_BREAK);
  if (!message_view_) {
    int padding = kMessageLineHeight - views::Label().font_list().GetHeight();
    message_view_ = new BoundedLabel(text);
    message_view_->SetLineHeight(kMessageLineHeight);
    message_view_->SetColors(message_center::kRegularTextColor,
                             kDimTextBackgroundColor);
    message_view_->SetBorder(MakeTextBorder(padding, 4, 0));
    top_view_->AddChildView(message_view_);
  } else {
    message_view_->SetText(text);
  }

  message_view_->SetVisible(!notification.items().size());
}

base::string16 NotificationView::FormatContextMessage(
    const Notification& notification) const {
  if (notification.UseOriginAsContextMessage()) {
    const GURL url = notification.origin_url();
    DCHECK(url.is_valid());
    // TODO(palmer): Find a way to get the Profile's real languages.
    // crbug.com/496965.
    return gfx::ElideText(url_formatter::FormatUrlForSecurityDisplayOmitScheme(
                              url, std::string()),
                          views::Label().font_list(), kContextMessageViewWidth,
                          gfx::ELIDE_HEAD);
  }

  return gfx::TruncateString(notification.context_message(),
                             kContextMessageCharacterLimit, gfx::WORD_BREAK);
}

void NotificationView::CreateOrUpdateContextMessageView(
    const Notification& notification) {
  if (notification.context_message().empty() &&
      !notification.UseOriginAsContextMessage()) {
    if (context_message_view_) {
      // Deletion will also remove |context_message_view_| from its parent.
      delete context_message_view_;
      context_message_view_ = NULL;
    }
    return;
  }

  DCHECK(top_view_ != NULL);

  base::string16 message = FormatContextMessage(notification);

  if (!context_message_view_) {
    int padding = kMessageLineHeight - views::Label().font_list().GetHeight();
    context_message_view_ = new BoundedLabel(message);
    context_message_view_->SetLineLimit(
        message_center::kContextMessageLineLimit);
    context_message_view_->SetLineHeight(kMessageLineHeight);
    context_message_view_->SetColors(message_center::kDimTextColor,
                                     kContextTextBackgroundColor);
    context_message_view_->SetBorder(MakeTextBorder(padding, 4, 0));
    top_view_->AddChildView(context_message_view_);
  } else {
    context_message_view_->SetText(message);
  }
}

void NotificationView::CreateOrUpdateProgressBarView(
    const Notification& notification) {
  if (notification.type() != NOTIFICATION_TYPE_PROGRESS) {
    if (progress_bar_view_) {
      // Deletion will also remove |progress_bar_view_| from its parent.
      delete progress_bar_view_;
      progress_bar_view_ = NULL;
    }
    return;
  }

  DCHECK(top_view_ != NULL);

  if (!progress_bar_view_) {
    progress_bar_view_ = new NotificationProgressBar();
    progress_bar_view_->SetBorder(MakeProgressBarBorder(
        message_center::kProgressBarTopPadding, kProgressBarBottomPadding));
    top_view_->AddChildView(progress_bar_view_);
  }

  progress_bar_view_->SetValue(notification.progress() / 100.0);
  progress_bar_view_->SetVisible(!notification.items().size());
}

void NotificationView::CreateOrUpdateListItemViews(
    const Notification& notification) {
  for (size_t i = 0; i < item_views_.size(); ++i)
    delete item_views_[i];
  item_views_.clear();

  int padding = kMessageLineHeight - views::Label().font_list().GetHeight();
  std::vector<NotificationItem> items = notification.items();

  if (items.size() == 0)
    return;

  DCHECK(top_view_);
  for (size_t i = 0; i < items.size() && i < kNotificationMaximumItems; ++i) {
    ItemView* item_view = new ItemView(items[i]);
    item_view->SetBorder(MakeTextBorder(padding, i ? 0 : 4, 0));
    item_views_.push_back(item_view);
    top_view_->AddChildView(item_view);
  }
}

void NotificationView::CreateOrUpdateIconView(
    const Notification& notification) {
  if (!icon_view_) {
    icon_view_ = new ProportionalImageView(gfx::Size(kIconSize, kIconSize));
    AddChildView(icon_view_);
  }

  gfx::ImageSkia icon = notification.icon().AsImageSkia();
  if (notification.adjust_icon()) {
    icon_view_->set_background(
        views::Background::CreateSolidBackground(kIconBackgroundColor));
    gfx::Size max_image_size =
        notification.type() == NOTIFICATION_TYPE_SIMPLE &&
                (icon.width() < kIconSize || icon.height() < kIconSize ||
                 HasAlpha(icon, GetWidget()))
            ? gfx::Size(kLegacyIconSize, kLegacyIconSize)
            : gfx::Size(kIconSize, kIconSize);
    icon_view_->SetImage(icon, max_image_size);
  } else {
    icon_view_->SetImage(icon, icon.size());
    icon_view_->set_background(nullptr);
  }
}

void NotificationView::CreateOrUpdateImageView(
    const Notification& notification) {
  // |image_view_| is the view representing the area covered by the
  // notification's image, including background and border.  Its size can be
  // specified in advance and images will be scaled to fit including a border if
  // necessary.
  if (notification.image().IsEmpty()) {
    delete image_container_;
    image_container_ = NULL;
    image_view_ = NULL;
    return;
  }

  gfx::Size ideal_size(kNotificationPreferredImageWidth,
                       kNotificationPreferredImageHeight);

  if (!image_container_) {
    DCHECK(!image_view_);
    DCHECK(bottom_view_);
    DCHECK_EQ(this, bottom_view_->parent());

    image_container_ = new views::View();
    image_container_->SetLayoutManager(new views::FillLayout());
    image_container_->set_background(views::Background::CreateSolidBackground(
        message_center::kImageBackgroundColor));

    image_view_ = new message_center::ProportionalImageView(ideal_size);
    image_container_->AddChildView(image_view_);
    bottom_view_->AddChildViewAt(image_container_, 0);
  }

  DCHECK(image_view_);
  image_view_->SetImage(notification.image().AsImageSkia(), ideal_size);

  gfx::Size scaled_size = message_center::GetImageSizeForContainerSize(
      ideal_size, notification.image().Size());
  image_view_->SetBorder(ideal_size != scaled_size
                             ? views::Border::CreateSolidBorder(
                                   message_center::kNotificationImageBorderSize,
                                   SK_ColorTRANSPARENT)
                             : NULL);
}

void NotificationView::CreateOrUpdateActionButtonViews(
    const Notification& notification) {
  std::vector<ButtonInfo> buttons = notification.buttons();
  bool new_buttons = action_buttons_.size() != buttons.size();

  if (new_buttons || buttons.size() == 0) {
    // STLDeleteElements also clears the container.
    STLDeleteElements(&separators_);
    STLDeleteElements(&action_buttons_);
  }

  DCHECK(bottom_view_);
  DCHECK_EQ(this, bottom_view_->parent());

  for (size_t i = 0; i < buttons.size(); ++i) {
    ButtonInfo button_info = buttons[i];
    if (new_buttons) {
      views::View* separator = new views::ImageView();
      separator->SetBorder(MakeSeparatorBorder(1, 0, kButtonSeparatorColor));
      separators_.push_back(separator);
      bottom_view_->AddChildView(separator);
      NotificationButton* button = new NotificationButton(this);
      button->SetTitle(button_info.title);
      button->SetIcon(button_info.icon.AsImageSkia());
      action_buttons_.push_back(button);
      bottom_view_->AddChildView(button);
    } else {
      action_buttons_[i]->SetTitle(button_info.title);
      action_buttons_[i]->SetIcon(button_info.icon.AsImageSkia());
      action_buttons_[i]->SchedulePaint();
      action_buttons_[i]->Layout();
    }
  }

  if (new_buttons) {
    Layout();
    views::Widget* widget = GetWidget();
    if (widget != NULL) {
      widget->SetSize(widget->GetContentsView()->GetPreferredSize());
      GetWidget()->SynthesizeMouseMoveEvent();
    }
  }
}

int NotificationView::GetMessageLineLimit(int title_lines, int width) const {
  // Image notifications require that the image must be kept flush against
  // their icons, but we can allow more text if no image.
  int effective_title_lines = std::max(0, title_lines - 1);
  int line_reduction_from_title = (image_view_ ? 1 : 2) * effective_title_lines;
  if (!image_view_) {
    // Title lines are counted as twice as big as message lines for the purpose
    // of this calculation.
    // The effect from the title reduction here should be:
    //   * 0 title lines: 5 max lines message.
    //   * 1 title line:  5 max lines message.
    //   * 2 title lines: 3 max lines message.
    return std::max(
        0,
        message_center::kMessageExpandedLineLimit - line_reduction_from_title);
  }

  int message_line_limit = message_center::kMessageCollapsedLineLimit;

  // Subtract any lines taken by the context message.
  if (context_message_view_) {
    message_line_limit -= context_message_view_->GetLinesForWidthAndLimit(
        width,
        message_center::kContextMessageLineLimit);
  }

  // The effect from the title reduction here should be:
  //   * 0 title lines: 2 max lines message + context message.
  //   * 1 title line:  2 max lines message + context message.
  //   * 2 title lines: 1 max lines message + context message.
  message_line_limit =
      std::max(0, message_line_limit - line_reduction_from_title);

  return message_line_limit;
}

int NotificationView::GetMessageHeight(int width, int limit) const {
  return message_view_ ?
         message_view_->GetSizeForWidthAndLines(width, limit).height() : 0;
}

}  // namespace message_center
