// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_COMPOSITOR_TEST_IN_PROCESS_CONTEXT_PROVIDER_H_
#define UI_COMPOSITOR_TEST_IN_PROCESS_CONTEXT_PROVIDER_H_

#include <string>

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/synchronization/lock.h"
#include "base/threading/thread_checker.h"
#include "cc/output/context_provider.h"
#include "gpu/command_buffer/common/gles2_cmd_utils.h"
#include "skia/ext/refptr.h"
#include "ui/gfx/native_widget_types.h"

namespace gpu {
class GLInProcessContext;
class GpuMemoryBufferManager;
class ImageFactory;
}

namespace ui {

class InProcessContextProvider : public cc::ContextProvider {
 public:
  static scoped_refptr<InProcessContextProvider> Create(
      const gpu::gles2::ContextCreationAttribHelper& attribs,
      gpu::GpuMemoryBufferManager* gpu_memory_buffer_manager,
      gpu::ImageFactory* image_factory,
      gfx::AcceleratedWidget window,
      const std::string& debug_name);

  // Uses default attributes for creating an offscreen context.
  static scoped_refptr<InProcessContextProvider> CreateOffscreen(
      gpu::GpuMemoryBufferManager* gpu_memory_buffer_manager,
      gpu::ImageFactory* image_factory);

  // cc::ContextProvider:
  bool BindToCurrentThread() override;
  void DetachFromThread() override;
  Capabilities ContextCapabilities() override;
  gpu::gles2::GLES2Interface* ContextGL() override;
  gpu::ContextSupport* ContextSupport() override;
  class GrContext* GrContext() override;
  void InvalidateGrContext(uint32_t state) override;
  void SetupLock() override;
  base::Lock* GetLock() override;
  void VerifyContexts() override;
  void DeleteCachedResources() override;
  bool DestroyedOnMainThread() override;
  void SetLostContextCallback(
      const LostContextCallback& lost_context_callback) override;

 private:
  InProcessContextProvider(
      const gpu::gles2::ContextCreationAttribHelper& attribs,
      gpu::GpuMemoryBufferManager* gpu_memory_buffer_manager,
      gpu::ImageFactory* image_factory,
      gfx::AcceleratedWidget window,
      const std::string& debug_name);
  ~InProcessContextProvider() override;

  void OnLostContext();

  base::ThreadChecker main_thread_checker_;
  base::ThreadChecker context_thread_checker_;

  scoped_ptr<gpu::GLInProcessContext> context_;
  skia::RefPtr<class GrContext> gr_context_;

  gpu::gles2::ContextCreationAttribHelper attribs_;
  gpu::GpuMemoryBufferManager* gpu_memory_buffer_manager_;
  gpu::ImageFactory* image_factory_;
  gfx::AcceleratedWidget window_;
  std::string debug_name_;
  cc::ContextProvider::Capabilities capabilities_;

  LostContextCallback lost_context_callback_;

  base::Lock destroyed_lock_;
  bool destroyed_;

  base::Lock context_lock_;

  DISALLOW_COPY_AND_ASSIGN(InProcessContextProvider);
};

}  // namespace ui

#endif  // UI_COMPOSITOR_TEST_IN_PROCESS_CONTEXT_PROVIDER_H_
