// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/ozone/platform/drm/gpu/drm_window.h"

#include <drm_fourcc.h>

#include "base/time/time.h"
#include "base/trace_event/trace_event.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "third_party/skia/include/core/SkDevice.h"
#include "third_party/skia/include/core/SkSurface.h"
#include "ui/ozone/common/gpu/ozone_gpu_message_params.h"
#include "ui/ozone/platform/drm/common/drm_util.h"
#include "ui/ozone/platform/drm/gpu/crtc_controller.h"
#include "ui/ozone/platform/drm/gpu/drm_buffer.h"
#include "ui/ozone/platform/drm/gpu/drm_device.h"
#include "ui/ozone/platform/drm/gpu/drm_device_manager.h"
#include "ui/ozone/platform/drm/gpu/scanout_buffer.h"
#include "ui/ozone/platform/drm/gpu/screen_manager.h"

namespace ui {

namespace {

#ifndef DRM_CAP_CURSOR_WIDTH
#define DRM_CAP_CURSOR_WIDTH 0x8
#endif

#ifndef DRM_CAP_CURSOR_HEIGHT
#define DRM_CAP_CURSOR_HEIGHT 0x9
#endif

void EmptyFlipCallback(gfx::SwapResult) {
}

void UpdateCursorImage(DrmBuffer* cursor, const SkBitmap& image) {
  SkRect damage;
  image.getBounds(&damage);

  // Clear to transparent in case |image| is smaller than the canvas.
  SkCanvas* canvas = cursor->GetCanvas();
  canvas->clear(SK_ColorTRANSPARENT);

  SkRect clip;
  clip.set(0, 0, canvas->getDeviceSize().width(),
           canvas->getDeviceSize().height());
  canvas->clipRect(clip, SkRegion::kReplace_Op);
  canvas->drawBitmapRect(image, damage, NULL);
}

}  // namespace

DrmWindow::DrmWindow(gfx::AcceleratedWidget widget,
                     DrmDeviceManager* device_manager,
                     ScreenManager* screen_manager)
    : widget_(widget),
      device_manager_(device_manager),
      screen_manager_(screen_manager) {
}

DrmWindow::~DrmWindow() {
}

void DrmWindow::Initialize() {
  TRACE_EVENT1("drm", "DrmWindow::Initialize", "widget", widget_);

  device_manager_->UpdateDrmDevice(widget_, nullptr);
}

void DrmWindow::Shutdown() {
  TRACE_EVENT1("drm", "DrmWindow::Shutdown", "widget", widget_);
  device_manager_->RemoveDrmDevice(widget_);
}

gfx::AcceleratedWidget DrmWindow::GetAcceleratedWidget() {
  return widget_;
}

HardwareDisplayController* DrmWindow::GetController() {
  return controller_;
}

void DrmWindow::SetBounds(const gfx::Rect& bounds) {
  TRACE_EVENT2("drm", "DrmWindow::SetBounds", "widget", widget_, "bounds",
               bounds.ToString());
  if (bounds_.size() != bounds.size())
    last_submitted_planes_.clear();

  bounds_ = bounds;
  screen_manager_->UpdateControllerToWindowMapping();
}

void DrmWindow::SetCursor(const std::vector<SkBitmap>& bitmaps,
                          const gfx::Point& location,
                          int frame_delay_ms) {
  cursor_bitmaps_ = bitmaps;
  cursor_location_ = location;
  cursor_frame_ = 0;
  cursor_frame_delay_ms_ = frame_delay_ms;
  cursor_timer_.Stop();

  if (cursor_frame_delay_ms_)
    cursor_timer_.Start(
        FROM_HERE, base::TimeDelta::FromMilliseconds(cursor_frame_delay_ms_),
        this, &DrmWindow::OnCursorAnimationTimeout);

  ResetCursor(false);
}

void DrmWindow::SetCursorWithoutAnimations(const std::vector<SkBitmap>& bitmaps,
                                           const gfx::Point& location) {
  cursor_bitmaps_ = bitmaps;
  cursor_location_ = location;
  cursor_frame_ = 0;
  cursor_frame_delay_ms_ = 0;
  ResetCursor(false);
}

void DrmWindow::MoveCursor(const gfx::Point& location) {
  cursor_location_ = location;

  if (controller_)
    controller_->MoveCursor(location);
}

void DrmWindow::SchedulePageFlip(const std::vector<OverlayPlane>& planes,
                                 const SwapCompletionCallback& callback) {
  if (force_buffer_reallocation_) {
    force_buffer_reallocation_ = false;
    callback.Run(gfx::SwapResult::SWAP_NAK_RECREATE_BUFFERS);
    return;
  }

  last_submitted_planes_ = planes;

  if (!controller_) {
    callback.Run(gfx::SwapResult::SWAP_ACK);
    return;
  }

  if (!controller_->SchedulePageFlip(last_submitted_planes_,
                                     false /* test_only */, callback)) {
    callback.Run(gfx::SwapResult::SWAP_FAILED);
  }
}

std::vector<OverlayCheck_Params> DrmWindow::TestPageFlip(
    const std::vector<OverlayCheck_Params>& overlays,
    ScanoutBufferGenerator* buffer_generator) {
  std::vector<OverlayCheck_Params> params;
  if (!controller_) {
    // Nothing much we can do here.
    return params;
  }

  OverlayPlaneList compatible_test_list;
  scoped_refptr<DrmDevice> drm = controller_->GetAllocationDrmDevice();
  for (const auto& overlay : overlays) {
    OverlayCheck_Params overlay_params(overlay);
    gfx::Size size =
        (overlay.plane_z_order == 0) ? bounds().size() : overlay.buffer_size;
    scoped_refptr<ScanoutBuffer> buffer;
    // Check if we can re-use existing buffers.
    for (const auto& plane : last_submitted_planes_) {
      uint32_t format = GetFourCCFormatFromBufferFormat(overlay.format);
      // We always use a storage type of XRGB, even if the pixel format
      // is ARGB.
      if (format == DRM_FORMAT_ARGB8888)
        format = DRM_FORMAT_XRGB8888;

      if (plane.buffer->GetFramebufferPixelFormat() == format &&
          plane.z_order == overlay.plane_z_order &&
          plane.display_bounds == overlay.display_rect &&
          plane.buffer->GetSize() == size) {
        buffer = plane.buffer;
        break;
      }
    }

    if (!buffer)
      buffer = buffer_generator->Create(drm, overlay.format, size);

    if (!buffer)
      continue;

    OverlayPlane plane(buffer, overlay.plane_z_order, overlay.transform,
                       overlay.display_rect, overlay.crop_rect);

    // Buffer for Primary plane should always be present for compatibility test.
    if (!compatible_test_list.size() && overlay.plane_z_order != 0) {
      compatible_test_list.push_back(
          *OverlayPlane::GetPrimaryPlane(last_submitted_planes_));
    }

    compatible_test_list.push_back(plane);

    bool page_flip_succeeded = controller_->SchedulePageFlip(
        compatible_test_list, true /* test_only */,
        base::Bind(&EmptyFlipCallback));

    if (page_flip_succeeded) {
      overlay_params.plane_ids =
          controller_->GetCompatibleHardwarePlaneIds(plane);
      params.push_back(overlay_params);
    }

    if (compatible_test_list.size() > 1)
      compatible_test_list.pop_back();
  }

  return params;
}

const OverlayPlane* DrmWindow::GetLastModesetBuffer() {
  return OverlayPlane::GetPrimaryPlane(last_submitted_planes_);
}

void DrmWindow::GetVSyncParameters(
    const gfx::VSyncProvider::UpdateVSyncCallback& callback) const {
  if (!controller_)
    return;

  // If we're in mirror mode the 2 CRTCs should have similar modes with the same
  // refresh rates.
  CrtcController* crtc = controller_->crtc_controllers()[0];
  // The value is invalid, so we can't update the parameters.
  if (controller_->GetTimeOfLastFlip() == 0 || crtc->mode().vrefresh == 0)
    return;

  // Stores the time of the last refresh.
  base::TimeTicks timebase =
      base::TimeTicks::FromInternalValue(controller_->GetTimeOfLastFlip());
  // Stores the refresh rate.
  base::TimeDelta interval =
      base::TimeDelta::FromSeconds(1) / crtc->mode().vrefresh;

  callback.Run(timebase, interval);
}

void DrmWindow::ResetCursor(bool bitmap_only) {
  if (!controller_)
    return;

  if (cursor_bitmaps_.size()) {
    // Draw new cursor into backbuffer.
    UpdateCursorImage(cursor_buffers_[cursor_frontbuffer_ ^ 1].get(),
                      cursor_bitmaps_[cursor_frame_]);

    // Reset location & buffer.
    if (!bitmap_only)
      controller_->MoveCursor(cursor_location_);
    controller_->SetCursor(cursor_buffers_[cursor_frontbuffer_ ^ 1]);
    cursor_frontbuffer_ ^= 1;
  } else {
    // No cursor set.
    controller_->UnsetCursor();
  }
}

void DrmWindow::OnCursorAnimationTimeout() {
  cursor_frame_++;
  cursor_frame_ %= cursor_bitmaps_.size();

  ResetCursor(true);
}

void DrmWindow::SetController(HardwareDisplayController* controller) {
  if (controller_ == controller)
    return;

  // Force buffer reallocation since the window moved to a different controller.
  // This is required otherwise the GPU will eventually try to render into the
  // buffer currently showing on the old controller (there is no guarantee that
  // the old controller has been updated in the meantime).
  force_buffer_reallocation_ = true;

  controller_ = controller;
  device_manager_->UpdateDrmDevice(
      widget_, controller ? controller->GetAllocationDrmDevice() : nullptr);

  UpdateCursorBuffers();
  // We changed displays, so we want to update the cursor as well.
  ResetCursor(false /* bitmap_only */);
}

void DrmWindow::UpdateCursorBuffers() {
  if (!controller_) {
    for (size_t i = 0; i < arraysize(cursor_buffers_); ++i) {
      cursor_buffers_[i] = nullptr;
    }
  } else {
    scoped_refptr<DrmDevice> drm = controller_->GetAllocationDrmDevice();

    uint64_t cursor_width = 64;
    uint64_t cursor_height = 64;
    drm->GetCapability(DRM_CAP_CURSOR_WIDTH, &cursor_width);
    drm->GetCapability(DRM_CAP_CURSOR_HEIGHT, &cursor_height);

    SkImageInfo info = SkImageInfo::MakeN32Premul(cursor_width, cursor_height);
    for (size_t i = 0; i < arraysize(cursor_buffers_); ++i) {
      cursor_buffers_[i] = new DrmBuffer(drm);
      // Don't register a framebuffer for cursors since they are special (they
      // aren't modesetting buffers and drivers may fail to register them due to
      // their small sizes).
      if (!cursor_buffers_[i]->Initialize(
              info, false /* should_register_framebuffer */)) {
        LOG(FATAL) << "Failed to initialize cursor buffer";
        return;
      }
    }
  }
}

}  // namespace ui
