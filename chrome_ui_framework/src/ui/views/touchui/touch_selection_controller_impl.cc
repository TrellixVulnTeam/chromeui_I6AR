// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/views/touchui/touch_selection_controller_impl.h"

#include "base/metrics/histogram_macros.h"
#include "base/time/time.h"
#include "ui/aura/client/cursor_client.h"
#include "ui/aura/env.h"
#include "ui/aura/window.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/gfx/canvas.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/gfx/geometry/size.h"
#include "ui/gfx/image/image.h"
#include "ui/gfx/path.h"
#include "ui/gfx/screen.h"
#include "ui/resources/grit/ui_resources.h"
#include "ui/strings/grit/ui_strings.h"
#include "ui/views/resources/grit/views_resources.h"
#include "ui/views/widget/widget.h"
#include "ui/views/widget/widget_delegate.h"
#include "ui/wm/core/coordinate_conversion.h"
#include "ui/wm/core/masked_window_targeter.h"

namespace {

// Constants defining the visual attributes of selection handles

// The distance by which a handle image is offset from the bottom of the
// selection/text baseline.
const int kSelectionHandleVerticalVisualOffset = 2;

// When a handle is dragged, the drag position reported to the client view is
// offset vertically to represent the cursor position. This constant specifies
// the offset in pixels above the bottom of the selection (see pic below). This
// is required because say if this is zero, that means the drag position we
// report is right on the text baseline. In that case, a vertical movement of
// even one pixel will make the handle jump to the line below it. So when the
// user just starts dragging, the handle will jump to the next line if the user
// makes any vertical movement. So we have this non-zero offset to prevent this
// jumping.
//
// Editing handle widget showing the padding and difference between the position
// of the ET_GESTURE_SCROLL_UPDATE event and the drag position reported to the
// client:
//                            ___________
//    Selection Highlight --->_____|__|<-|---- Drag position reported to client
//                              _  |  O  |
//          Vertical Padding __|   |   <-|---- ET_GESTURE_SCROLL_UPDATE position
//                             |_  |_____|<--- Editing handle widget
//
//                                 | |
//                                  T
//                          Horizontal Padding
//
const int kSelectionHandleVerticalDragOffset = 5;

// Padding around the selection handle defining the area that will be included
// in the touch target to make dragging the handle easier (see pic above).
const int kSelectionHandleHorizPadding = 10;
const int kSelectionHandleVertPadding = 20;

const int kQuickMenuTimoutMs = 200;

const int kSelectionHandleQuickFadeDurationMs = 50;

// Minimum height for selection handle bar. If the bar height is going to be
// less than this value, handle will not be shown.
const int kSelectionHandleBarMinHeight = 5;
// Maximum amount that selection handle bar can stick out of client view's
// boundaries.
const int kSelectionHandleBarBottomAllowance = 3;

// Creates a widget to host SelectionHandleView.
views::Widget* CreateTouchSelectionPopupWidget(
    gfx::NativeView context,
    views::WidgetDelegate* widget_delegate) {
  views::Widget* widget = new views::Widget;
  views::Widget::InitParams params(views::Widget::InitParams::TYPE_POPUP);
  params.opacity = views::Widget::InitParams::TRANSLUCENT_WINDOW;
  params.shadow_type = views::Widget::InitParams::SHADOW_TYPE_NONE;
  params.ownership = views::Widget::InitParams::WIDGET_OWNS_NATIVE_WIDGET;
  params.parent = context;
  params.delegate = widget_delegate;
  widget->Init(params);
  return widget;
}

gfx::Image* GetCenterHandleImage() {
  static gfx::Image* handle_image = nullptr;
  if (!handle_image) {
    handle_image = &ui::ResourceBundle::GetSharedInstance().GetImageNamed(
        IDR_TEXT_SELECTION_HANDLE_CENTER);
  }
  return handle_image;
}

gfx::Image* GetLeftHandleImage() {
  static gfx::Image* handle_image = nullptr;
  if (!handle_image) {
    handle_image = &ui::ResourceBundle::GetSharedInstance().GetImageNamed(
        IDR_TEXT_SELECTION_HANDLE_LEFT);
  }
  return handle_image;
}

gfx::Image* GetRightHandleImage() {
  static gfx::Image* handle_image = nullptr;
  if (!handle_image) {
    handle_image = &ui::ResourceBundle::GetSharedInstance().GetImageNamed(
        IDR_TEXT_SELECTION_HANDLE_RIGHT);
  }
  return handle_image;
}

// Return the appropriate handle image based on the bound's type
gfx::Image* GetHandleImage(ui::SelectionBound::Type bound_type) {
  switch(bound_type) {
    case ui::SelectionBound::LEFT:
      return GetLeftHandleImage();
    case ui::SelectionBound::CENTER:
      return GetCenterHandleImage();
    case ui::SelectionBound::RIGHT:
      return GetRightHandleImage();
    default:
      NOTREACHED() << "Invalid touch handle bound type.";
      return nullptr;
  };
}

// Calculates the bounds of the widget containing the selection handle based
// on the SelectionBound's type and location
gfx::Rect GetSelectionWidgetBounds(const ui::SelectionBound& bound) {
  gfx::Size image_size = GetHandleImage(bound.type())->Size();
  int widget_width = image_size.width() + 2 * kSelectionHandleHorizPadding;
  int widget_height = bound.GetHeight() + image_size.height() +
                      kSelectionHandleVerticalVisualOffset +
                      kSelectionHandleVertPadding;
  // Due to the shape of the handle images, the widget is aligned differently to
  // the selection bound depending on the type of the bound.
  int widget_left = 0;
  switch (bound.type()) {
    case ui::SelectionBound::LEFT:
      widget_left = bound.edge_top_rounded().x() - image_size.width() -
                    kSelectionHandleHorizPadding;
      break;
    case ui::SelectionBound::RIGHT:
      widget_left = bound.edge_top_rounded().x() - kSelectionHandleHorizPadding;
      break;
    case ui::SelectionBound::CENTER:
      widget_left = bound.edge_top_rounded().x() - widget_width / 2;
      break;
    default:
      NOTREACHED() << "Undefined bound type.";
      break;
  };
  return gfx::Rect(
      widget_left, bound.edge_top_rounded().y(), widget_width, widget_height);
}

gfx::Size GetMaxHandleImageSize() {
  gfx::Rect center_rect = gfx::Rect(GetCenterHandleImage()->Size());
  gfx::Rect left_rect = gfx::Rect(GetLeftHandleImage()->Size());
  gfx::Rect right_rect = gfx::Rect(GetRightHandleImage()->Size());
  gfx::Rect union_rect = center_rect;
  union_rect.Union(left_rect);
  union_rect.Union(right_rect);
  return union_rect.size();
}

// Convenience methods to convert a |bound| from screen to the |client|'s
// coordinate system and vice versa.
// Note that this is not quite correct because it does not take into account
// transforms such as rotation and scaling. This should be in TouchEditable.
// TODO(varunjain): Fix this.
ui::SelectionBound ConvertFromScreen(ui::TouchEditable* client,
                                     const ui::SelectionBound& bound) {
  ui::SelectionBound result = bound;
  gfx::Point edge_bottom = bound.edge_bottom_rounded();
  gfx::Point edge_top = bound.edge_top_rounded();
  client->ConvertPointFromScreen(&edge_bottom);
  client->ConvertPointFromScreen(&edge_top);
  result.SetEdge(edge_top, edge_bottom);
  return result;
}

ui::SelectionBound ConvertToScreen(ui::TouchEditable* client,
                                   const ui::SelectionBound& bound) {
  ui::SelectionBound result = bound;
  gfx::Point edge_bottom = bound.edge_bottom_rounded();
  gfx::Point edge_top = bound.edge_top_rounded();
  client->ConvertPointToScreen(&edge_bottom);
  client->ConvertPointToScreen(&edge_top);
  result.SetEdge(edge_top, edge_bottom);
  return result;
}

gfx::Rect BoundToRect(const ui::SelectionBound& bound) {
  return gfx::BoundingRect(bound.edge_top_rounded(),
                           bound.edge_bottom_rounded());
}

}  // namespace

namespace views {

typedef TouchSelectionControllerImpl::EditingHandleView EditingHandleView;

class TouchHandleWindowTargeter : public wm::MaskedWindowTargeter {
 public:
  TouchHandleWindowTargeter(aura::Window* window,
                            EditingHandleView* handle_view);

  ~TouchHandleWindowTargeter() override {}

 private:
  // wm::MaskedWindowTargeter:
  bool GetHitTestMask(aura::Window* window, gfx::Path* mask) const override;

  EditingHandleView* handle_view_;

  DISALLOW_COPY_AND_ASSIGN(TouchHandleWindowTargeter);
};

// A View that displays the text selection handle.
class TouchSelectionControllerImpl::EditingHandleView
    : public views::WidgetDelegateView {
 public:
  EditingHandleView(TouchSelectionControllerImpl* controller,
                    gfx::NativeView context,
                    bool is_cursor_handle)
      : controller_(controller),
        image_(GetCenterHandleImage()),
        is_cursor_handle_(is_cursor_handle),
        draw_invisible_(false),
        weak_ptr_factory_(this) {
    widget_.reset(CreateTouchSelectionPopupWidget(context, this));
    widget_->SetContentsView(this);

    aura::Window* window = widget_->GetNativeWindow();
    window->SetEventTargeter(scoped_ptr<ui::EventTargeter>(
        new TouchHandleWindowTargeter(window, this)));

    // We are owned by the TouchSelectionControllerImpl.
    set_owned_by_client();
  }

  ~EditingHandleView() override { SetWidgetVisible(false, false); }

  // Overridden from views::WidgetDelegateView:
  bool WidgetHasHitTestMask() const override { return true; }

  void GetWidgetHitTestMask(gfx::Path* mask) const override {
    gfx::Size image_size = image_->Size();
    mask->addRect(
        SkIntToScalar(0),
        SkIntToScalar(selection_bound_.GetHeight() +
                      kSelectionHandleVerticalVisualOffset),
        SkIntToScalar(image_size.width()) + 2 * kSelectionHandleHorizPadding,
        SkIntToScalar(selection_bound_.GetHeight() +
                      kSelectionHandleVerticalVisualOffset +
                      image_size.height() + kSelectionHandleVertPadding));
  }

  void DeleteDelegate() override {
    // We are owned and deleted by TouchSelectionControllerImpl.
  }

  // Overridden from views::View:
  void OnPaint(gfx::Canvas* canvas) override {
    if (draw_invisible_)
      return;

    // Draw the handle image.
    canvas->DrawImageInt(
        *image_->ToImageSkia(),
        kSelectionHandleHorizPadding,
        selection_bound_.GetHeight() + kSelectionHandleVerticalVisualOffset);
  }

  void OnGestureEvent(ui::GestureEvent* event) override {
    event->SetHandled();
    switch (event->type()) {
      case ui::ET_GESTURE_SCROLL_BEGIN: {
        widget_->SetCapture(this);
        controller_->SetDraggingHandle(this);
        // Distance from the point which is |kSelectionHandleVerticalDragOffset|
        // pixels above the bottom of the selection bound edge to the event
        // location (aka the touch-drag point).
        drag_offset_ = selection_bound_.edge_bottom_rounded() -
                       gfx::Vector2d(0, kSelectionHandleVerticalDragOffset) -
                       event->location();
        break;
      }
      case ui::ET_GESTURE_SCROLL_UPDATE: {
        controller_->SelectionHandleDragged(event->location() + drag_offset_);
        break;
      }
      case ui::ET_GESTURE_SCROLL_END:
      case ui::ET_SCROLL_FLING_START: {
        // Use a weak pointer to the handle to make sure the handle and its
        // owning selection controller is not destroyed by the capture release
        // to diagnose a crash on Windows (see crbug.com/459423)
        // TODO(mohsen): Delete the diagnostics code when the crash is fixed.
        base::WeakPtr<EditingHandleView> weak_ptr =
            weak_ptr_factory_.GetWeakPtr();
        widget_->ReleaseCapture();
        CHECK(weak_ptr);
        controller_->SetDraggingHandle(nullptr);
        break;
      }
      default:
        break;
    }
  }

  gfx::Size GetPreferredSize() const override {
    return GetSelectionWidgetBounds(selection_bound_).size();
  }

  bool IsWidgetVisible() const {
    return widget_->IsVisible();
  }

  void SetWidgetVisible(bool visible, bool quick) {
    if (widget_->IsVisible() == visible)
      return;
    widget_->SetVisibilityAnimationDuration(
        base::TimeDelta::FromMilliseconds(
            quick ? kSelectionHandleQuickFadeDurationMs : 0));
    if (visible)
      widget_->Show();
    else
      widget_->Hide();
  }

  void SetBoundInScreen(const ui::SelectionBound& bound) {
    bool update_bound_type = false;
    // Cursor handle should always have the bound type CENTER
    DCHECK(!is_cursor_handle_ || bound.type() == ui::SelectionBound::CENTER);

    if (bound.type() != selection_bound_.type()) {
      // Unless this is a cursor handle, do not set the type to CENTER -
      // selection handles corresponding to a selection should always use left
      // or right handle image. If selection handles are dragged to be located
      // at the same spot, the |bound|'s type here will be CENTER for both of
      // them. In this case do not update the type of the |selection_bound_|.
      if (bound.type() != ui::SelectionBound::CENTER || is_cursor_handle_)
        update_bound_type = true;
    }
    if (update_bound_type) {
      selection_bound_.set_type(bound.type());
      image_ = GetHandleImage(bound.type());
      SchedulePaint();
    }
    selection_bound_.SetEdge(bound.edge_top(), bound.edge_bottom());

    widget_->SetBounds(GetSelectionWidgetBounds(selection_bound_));

    aura::Window* window = widget_->GetNativeView();
    gfx::Point edge_top = selection_bound_.edge_top_rounded();
    gfx::Point edge_bottom = selection_bound_.edge_bottom_rounded();
    wm::ConvertPointFromScreen(window, &edge_top);
    wm::ConvertPointFromScreen(window, &edge_bottom);
    selection_bound_.SetEdge(edge_top, edge_bottom);
  }

  void SetDrawInvisible(bool draw_invisible) {
    if (draw_invisible_ == draw_invisible)
      return;
    draw_invisible_ = draw_invisible;
    SchedulePaint();
  }

 private:
  scoped_ptr<Widget> widget_;
  TouchSelectionControllerImpl* controller_;

  // In local coordinates
  ui::SelectionBound selection_bound_;
  gfx::Image* image_;

  // If true, this is a handle corresponding to the single cursor, otherwise it
  // is a handle corresponding to one of the two selection bounds.
  bool is_cursor_handle_;

  // Offset applied to the scroll events location when calling
  // TouchSelectionControllerImpl::SelectionHandleDragged while dragging the
  // handle.
  gfx::Vector2d drag_offset_;

  // If set to true, the handle will not draw anything, hence providing an empty
  // widget. We need this because we may want to stop showing the handle while
  // it is being dragged. Since it is being dragged, we cannot destroy the
  // handle.
  bool draw_invisible_;

  base::WeakPtrFactory<EditingHandleView> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(EditingHandleView);
};

TouchHandleWindowTargeter::TouchHandleWindowTargeter(
    aura::Window* window,
    EditingHandleView* handle_view)
    : wm::MaskedWindowTargeter(window),
      handle_view_(handle_view) {
}

bool TouchHandleWindowTargeter::GetHitTestMask(aura::Window* window,
                                               gfx::Path* mask) const {
  handle_view_->GetWidgetHitTestMask(mask);
  return true;
}

TouchSelectionControllerImpl::TouchSelectionControllerImpl(
    ui::TouchEditable* client_view)
    : client_view_(client_view),
      client_widget_(nullptr),
      selection_handle_1_(new EditingHandleView(this,
                                                client_view->GetNativeView(),
                                                false)),
      selection_handle_2_(new EditingHandleView(this,
                                                client_view->GetNativeView(),
                                                false)),
      cursor_handle_(new EditingHandleView(this,
                                           client_view->GetNativeView(),
                                           true)),
      command_executed_(false),
      dragging_handle_(nullptr) {
  selection_start_time_ = base::TimeTicks::Now();
  aura::Window* client_window = client_view_->GetNativeView();
  client_window->AddObserver(this);
  client_widget_ = Widget::GetTopLevelWidgetForNativeView(client_window);
  if (client_widget_)
    client_widget_->AddObserver(this);
  aura::Env::GetInstance()->AddPreTargetHandler(this);
}

TouchSelectionControllerImpl::~TouchSelectionControllerImpl() {
  UMA_HISTOGRAM_BOOLEAN("Event.TouchSelection.EndedWithAction",
                        command_executed_);
  HideQuickMenu();
  aura::Env::GetInstance()->RemovePreTargetHandler(this);
  if (client_widget_)
    client_widget_->RemoveObserver(this);
  client_view_->GetNativeView()->RemoveObserver(this);
}

void TouchSelectionControllerImpl::SelectionChanged() {
  ui::SelectionBound anchor, focus;
  client_view_->GetSelectionEndPoints(&anchor, &focus);
  ui::SelectionBound screen_bound_anchor =
      ConvertToScreen(client_view_, anchor);
  ui::SelectionBound screen_bound_focus = ConvertToScreen(client_view_, focus);
  gfx::Rect client_bounds = client_view_->GetBounds();
  if (anchor.edge_top().y() < client_bounds.y()) {
    gfx::Point anchor_edge_top = anchor.edge_top_rounded();
    anchor_edge_top.set_y(client_bounds.y());
    anchor.SetEdgeTop(anchor_edge_top);
  }
  if (focus.edge_top().y() < client_bounds.y()) {
    gfx::Point focus_edge_top = focus.edge_top_rounded();
    focus_edge_top.set_y(client_bounds.y());
    focus.SetEdgeTop(focus_edge_top);
  }
  ui::SelectionBound screen_bound_anchor_clipped =
      ConvertToScreen(client_view_, anchor);
  ui::SelectionBound screen_bound_focus_clipped =
      ConvertToScreen(client_view_, focus);
  if (screen_bound_anchor_clipped == selection_bound_1_clipped_ &&
      screen_bound_focus_clipped == selection_bound_2_clipped_)
    return;

  selection_bound_1_ = screen_bound_anchor;
  selection_bound_2_ = screen_bound_focus;
  selection_bound_1_clipped_ = screen_bound_anchor_clipped;
  selection_bound_2_clipped_ = screen_bound_focus_clipped;

  if (client_view_->DrawsHandles()) {
    UpdateQuickMenu();
    return;
  }

  if (dragging_handle_) {
    // We need to reposition only the selection handle that is being dragged.
    // The other handle stays the same. Also, the selection handle being dragged
    // will always be at the end of selection, while the other handle will be at
    // the start.
    // If the new location of this handle is out of client view, its widget
    // should not get hidden, since it should still receive touch events.
    // Hence, we are not using |SetHandleBound()| method here.
    dragging_handle_->SetBoundInScreen(screen_bound_focus_clipped);

    // Temporary fix for selection handle going outside a window. On a webpage,
    // the page should scroll if the selection handle is dragged outside the
    // window. That does not happen currently. So we just hide the handle for
    // now.
    // TODO(varunjain): Fix this: crbug.com/269003
    dragging_handle_->SetDrawInvisible(!ShouldShowHandleFor(focus));

    if (dragging_handle_ != cursor_handle_.get()) {
      // The non-dragging-handle might have recently become visible.
      EditingHandleView* non_dragging_handle = selection_handle_1_.get();
      if (dragging_handle_ == selection_handle_1_) {
        non_dragging_handle = selection_handle_2_.get();
        // if handle 1 is being dragged, it is corresponding to the end of
        // selection and the other handle to the start of selection.
        selection_bound_1_ = screen_bound_focus;
        selection_bound_2_ = screen_bound_anchor;
        selection_bound_1_clipped_ = screen_bound_focus_clipped;
        selection_bound_2_clipped_ = screen_bound_anchor_clipped;
      }
      SetHandleBound(non_dragging_handle, anchor, screen_bound_anchor_clipped);
    }
  } else {
    UpdateQuickMenu();

    // Check if there is any selection at all.
    if (screen_bound_anchor.edge_top() == screen_bound_focus.edge_top() &&
        screen_bound_anchor.edge_bottom() == screen_bound_focus.edge_bottom()) {
      selection_handle_1_->SetWidgetVisible(false, false);
      selection_handle_2_->SetWidgetVisible(false, false);
      SetHandleBound(cursor_handle_.get(), anchor, screen_bound_anchor_clipped);
      return;
    }

    cursor_handle_->SetWidgetVisible(false, false);
    SetHandleBound(
        selection_handle_1_.get(), anchor, screen_bound_anchor_clipped);
    SetHandleBound(
        selection_handle_2_.get(), focus, screen_bound_focus_clipped);
  }
}

bool TouchSelectionControllerImpl::IsHandleDragInProgress() {
  return !!dragging_handle_;
}

void TouchSelectionControllerImpl::HideHandles(bool quick) {
  selection_handle_1_->SetWidgetVisible(false, quick);
  selection_handle_2_->SetWidgetVisible(false, quick);
  cursor_handle_->SetWidgetVisible(false, quick);
}

void TouchSelectionControllerImpl::SetDraggingHandle(
    EditingHandleView* handle) {
  dragging_handle_ = handle;
  if (dragging_handle_)
    HideQuickMenu();
  else
    StartQuickMenuTimer();
}

void TouchSelectionControllerImpl::SelectionHandleDragged(
    const gfx::Point& drag_pos) {
  DCHECK(dragging_handle_);
  gfx::Point drag_pos_in_client = drag_pos;
  ConvertPointToClientView(dragging_handle_, &drag_pos_in_client);

  if (dragging_handle_ == cursor_handle_.get()) {
    client_view_->MoveCaretTo(drag_pos_in_client);
    return;
  }

  // Find the stationary selection handle.
  ui::SelectionBound anchor_bound =
      selection_handle_1_ == dragging_handle_ ? selection_bound_2_
                                              : selection_bound_1_;

  // Find selection end points in client_view's coordinate system.
  gfx::Point p2 = anchor_bound.edge_top_rounded();
  p2.Offset(0, anchor_bound.GetHeight() / 2);
  client_view_->ConvertPointFromScreen(&p2);

  // Instruct client_view to select the region between p1 and p2. The position
  // of |fixed_handle| is the start and that of |dragging_handle| is the end
  // of selection.
  client_view_->SelectRect(p2, drag_pos_in_client);
}

void TouchSelectionControllerImpl::ConvertPointToClientView(
    EditingHandleView* source, gfx::Point* point) {
  View::ConvertPointToScreen(source, point);
  client_view_->ConvertPointFromScreen(point);
}

void TouchSelectionControllerImpl::SetHandleBound(
    EditingHandleView* handle,
    const ui::SelectionBound& bound,
    const ui::SelectionBound& bound_in_screen) {
  handle->SetWidgetVisible(ShouldShowHandleFor(bound), false);
  if (handle->IsWidgetVisible())
    handle->SetBoundInScreen(bound_in_screen);
}

bool TouchSelectionControllerImpl::ShouldShowHandleFor(
    const ui::SelectionBound& bound) const {
  if (bound.GetHeight() < kSelectionHandleBarMinHeight)
    return false;
  gfx::Rect client_bounds = client_view_->GetBounds();
  client_bounds.Inset(0, 0, 0, -kSelectionHandleBarBottomAllowance);
  return client_bounds.Contains(BoundToRect(bound));
}

bool TouchSelectionControllerImpl::IsCommandIdEnabled(int command_id) const {
  return client_view_->IsCommandIdEnabled(command_id);
}

void TouchSelectionControllerImpl::ExecuteCommand(int command_id,
                                                  int event_flags) {
  command_executed_ = true;
  base::TimeDelta duration = base::TimeTicks::Now() - selection_start_time_;
  // Note that we only log the duration stats for the 'successful' selections,
  // i.e. selections ending with the execution of a command.
  UMA_HISTOGRAM_CUSTOM_TIMES("Event.TouchSelection.Duration",
                             duration,
                             base::TimeDelta::FromMilliseconds(500),
                             base::TimeDelta::FromSeconds(60),
                             60);
  client_view_->ExecuteCommand(command_id, event_flags);
}

void TouchSelectionControllerImpl::RunContextMenu() {
  // Context menu should appear centered on top of the selected region.
  const gfx::Rect rect = GetQuickMenuAnchorRect();
  const gfx::Point anchor(rect.CenterPoint().x(), rect.y());
  client_view_->OpenContextMenu(anchor);
}

void TouchSelectionControllerImpl::OnAncestorWindowTransformed(
    aura::Window* window,
    aura::Window* ancestor) {
  client_view_->DestroyTouchSelection();
}

void TouchSelectionControllerImpl::OnWidgetClosing(Widget* widget) {
  DCHECK_EQ(client_widget_, widget);
  client_widget_->RemoveObserver(this);
  client_widget_ = nullptr;
}

void TouchSelectionControllerImpl::OnWidgetBoundsChanged(
    Widget* widget,
    const gfx::Rect& new_bounds) {
  DCHECK_EQ(client_widget_, widget);
  SelectionChanged();
}

void TouchSelectionControllerImpl::OnKeyEvent(ui::KeyEvent* event) {
  client_view_->DestroyTouchSelection();
}

void TouchSelectionControllerImpl::OnMouseEvent(ui::MouseEvent* event) {
  aura::client::CursorClient* cursor_client = aura::client::GetCursorClient(
      client_view_->GetNativeView()->GetRootWindow());
  if (cursor_client && !cursor_client->IsMouseEventsEnabled())
    return;

  // Do not hide handles on mouse-capture-changed event which might occur when a
  // selection handle is released. Normally, cursor client should report mouse
  // events as disabled (the above check), but there are crashes on Windows
  // devices suggesting it is not always the case (see crbug.com/459423).
  if (event->type() == ui::ET_MOUSE_CAPTURE_CHANGED)
    return;

  client_view_->DestroyTouchSelection();
}

void TouchSelectionControllerImpl::OnScrollEvent(ui::ScrollEvent* event) {
  client_view_->DestroyTouchSelection();
}

void TouchSelectionControllerImpl::QuickMenuTimerFired() {
  gfx::Rect menu_anchor = GetQuickMenuAnchorRect();
  if (menu_anchor == gfx::Rect())
    return;

  ui::TouchSelectionMenuRunner::GetInstance()->OpenMenu(
      this, menu_anchor, GetMaxHandleImageSize(),
      client_view_->GetNativeView());
}

void TouchSelectionControllerImpl::StartQuickMenuTimer() {
  if (quick_menu_timer_.IsRunning())
    return;
  quick_menu_timer_.Start(
      FROM_HERE,
      base::TimeDelta::FromMilliseconds(kQuickMenuTimoutMs),
      this,
      &TouchSelectionControllerImpl::QuickMenuTimerFired);
}

void TouchSelectionControllerImpl::UpdateQuickMenu() {
  // Hide quick menu to be shown when the timer fires.
  HideQuickMenu();
  StartQuickMenuTimer();
}

void TouchSelectionControllerImpl::HideQuickMenu() {
  if (ui::TouchSelectionMenuRunner::GetInstance()->IsRunning())
    ui::TouchSelectionMenuRunner::GetInstance()->CloseMenu();
  quick_menu_timer_.Stop();
}

gfx::Rect TouchSelectionControllerImpl::GetQuickMenuAnchorRect() const {
  // Get selection end points in client_view's space.
  ui::SelectionBound b1_in_screen = selection_bound_1_clipped_;
  ui::SelectionBound b2_in_screen = cursor_handle_->IsWidgetVisible()
                                        ? b1_in_screen
                                        : selection_bound_2_clipped_;
  // Convert from screen to client.
  ui::SelectionBound b1 = ConvertFromScreen(client_view_, b1_in_screen);
  ui::SelectionBound b2 = ConvertFromScreen(client_view_, b2_in_screen);

  // if selection is completely inside the view, we display the quick menu in
  // the middle of the end points on the top. Else, we show it above the visible
  // handle. If no handle is visible, we do not show the menu.
  gfx::Rect menu_anchor;
  if (ShouldShowHandleFor(b1) && ShouldShowHandleFor(b2))
    menu_anchor = ui::RectBetweenSelectionBounds(b1_in_screen, b2_in_screen);
  else if (ShouldShowHandleFor(b1))
    menu_anchor = BoundToRect(b1_in_screen);
  else if (ShouldShowHandleFor(b2))
    menu_anchor = BoundToRect(b2_in_screen);
  else
    return menu_anchor;

  // Enlarge the anchor rect so that the menu is offset from the text at least
  // by the same distance the handles are offset from the text.
  menu_anchor.Inset(0, -kSelectionHandleVerticalVisualOffset);

  return menu_anchor;
}

gfx::NativeView TouchSelectionControllerImpl::GetCursorHandleNativeView() {
  return cursor_handle_->GetWidget()->GetNativeView();
}

gfx::Rect TouchSelectionControllerImpl::GetSelectionHandle1Bounds() {
  return selection_handle_1_->GetBoundsInScreen();
}

gfx::Rect TouchSelectionControllerImpl::GetSelectionHandle2Bounds() {
  return selection_handle_2_->GetBoundsInScreen();
}

gfx::Rect TouchSelectionControllerImpl::GetCursorHandleBounds() {
  return cursor_handle_->GetBoundsInScreen();
}

bool TouchSelectionControllerImpl::IsSelectionHandle1Visible() {
  return selection_handle_1_->IsWidgetVisible();
}

bool TouchSelectionControllerImpl::IsSelectionHandle2Visible() {
  return selection_handle_2_->IsWidgetVisible();
}

bool TouchSelectionControllerImpl::IsCursorHandleVisible() {
  return cursor_handle_->IsWidgetVisible();
}

gfx::Rect TouchSelectionControllerImpl::GetExpectedHandleBounds(
    const ui::SelectionBound& bound) {
  return GetSelectionWidgetBounds(bound);
}

views::WidgetDelegateView* TouchSelectionControllerImpl::GetHandle1View() {
  return selection_handle_1_.get();
}

views::WidgetDelegateView* TouchSelectionControllerImpl::GetHandle2View() {
  return selection_handle_2_.get();
}

}  // namespace views
