// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GL_GL_IMAGE_SHARED_MEMORY_H_
#define UI_GL_GL_IMAGE_SHARED_MEMORY_H_

#include "base/memory/scoped_ptr.h"
#include "base/memory/shared_memory_handle.h"
#include "ui/gl/gl_image_memory.h"

namespace gfx {

class GL_EXPORT GLImageSharedMemory : public GLImageMemory {
 public:
  GLImageSharedMemory(const gfx::Size& size, unsigned internalformat);

  bool Initialize(const base::SharedMemoryHandle& handle,
                  gfx::GenericSharedMemoryId shared_memory_id,
                  BufferFormat format);

  // Overridden from GLImage:
  void Destroy(bool have_context) override;
  void OnMemoryDump(base::trace_event::ProcessMemoryDump* pmd,
                    uint64_t process_tracing_id,
                    const std::string& dump_name) override;

 protected:
  ~GLImageSharedMemory() override;

 private:
  scoped_ptr<base::SharedMemory> shared_memory_;
  GenericSharedMemoryId shared_memory_id_;

  DISALLOW_COPY_AND_ASSIGN(GLImageSharedMemory);
};

}  // namespace gfx

#endif  // UI_GL_GL_IMAGE_SHARED_MEMORY_H_
