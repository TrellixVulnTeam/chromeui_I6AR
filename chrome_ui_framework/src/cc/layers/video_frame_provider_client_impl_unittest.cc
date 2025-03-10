// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "cc/layers/video_frame_provider_client_impl.h"
#include "cc/layers/video_layer_impl.h"
#include "cc/output/begin_frame_args.h"
#include "cc/test/fake_video_frame_provider.h"
#include "cc/test/layer_test_common.h"
#include "cc/media/base/video_frame.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

using testing::_;

namespace cc {

// NOTE: We cannot use DebugScopedSetImplThreadAndMainThreadBlocked in these
// tests because it gets destroyed before the VideoLayerImpl is destroyed. This
// causes a DCHECK in VideoLayerImpl's destructor to fail.
static void DebugSetImplThreadAndMainThreadBlocked(Proxy* proxy) {
#if DCHECK_IS_ON()
  proxy->SetCurrentThreadIsImplThread(true);
  proxy->SetMainThreadBlocked(true);
#endif
}

class VideoFrameProviderClientImplTest : public testing::Test,
                                         public VideoFrameControllerClient {
 public:
  VideoFrameProviderClientImplTest()
      : client_impl_(VideoFrameProviderClientImpl::Create(&provider_, this)),
        video_layer_impl_(nullptr),
        test_frame_(media::VideoFrame::CreateFrame(media::PIXEL_FORMAT_YV12,
                                                   gfx::Size(10, 10),
                                                   gfx::Rect(10, 10),
                                                   gfx::Size(10, 10),
                                                   base::TimeDelta())) {
    DebugSetImplThreadAndMainThreadBlocked(impl_.proxy());
  }

  ~VideoFrameProviderClientImplTest() {
    if (!client_impl_->Stopped()) {
      client_impl_->Stop();
      DCHECK(client_impl_->Stopped());
      DCHECK(!client_impl_->ActiveVideoLayer());
    }

    provider_.SetVideoFrameProviderClient(nullptr);
  }

  void StartRendering() {
    EXPECT_CALL(*this, AddVideoFrameController(_));
    client_impl_->StartRendering();
  }

  void StopRendering() {
    EXPECT_CALL(*this, RemoveVideoFrameController(_));
    client_impl_->StopRendering();
  }

  void StartRenderingAndRenderFrame() {
    EXPECT_FALSE(client_impl_->HasCurrentFrame());
    provider_.set_frame(test_frame_);
    EXPECT_TRUE(client_impl_->HasCurrentFrame());

    // Start rendering and verify SetNeedsRedraw() was called for the new frame.
    StartRendering();
    EXPECT_EQ(gfx::Rect(), video_layer_impl_->update_rect());
    client_impl_->OnBeginFrame(BeginFrameArgs());
    EXPECT_NE(gfx::Rect(), video_layer_impl_->update_rect());
  }

  void CreateActiveVideoLayer() {
    gfx::Size layer_size(100, 100);
    video_layer_impl_ = impl_.AddChildToRoot<VideoLayerImpl>(
        &provider_, media::VIDEO_ROTATION_0);
    video_layer_impl_->SetBounds(layer_size);
    video_layer_impl_->SetDrawsContent(true);
    client_impl_->SetActiveVideoLayer(video_layer_impl_);
    ASSERT_TRUE(client_impl_->ActiveVideoLayer());
  }

  MOCK_METHOD1(AddVideoFrameController, void(VideoFrameController*));
  MOCK_METHOD1(RemoveVideoFrameController, void(VideoFrameController*));

 protected:
  FakeVideoFrameProvider provider_;
  LayerTestCommon::LayerImplTest impl_;
  scoped_refptr<VideoFrameProviderClientImpl> client_impl_;
  VideoLayerImpl* video_layer_impl_;
  scoped_refptr<media::VideoFrame> test_frame_;

 private:
  DISALLOW_COPY_AND_ASSIGN(VideoFrameProviderClientImplTest);
};

TEST_F(VideoFrameProviderClientImplTest, StartStopRendering) {
  StartRendering();
  StopRendering();
}

TEST_F(VideoFrameProviderClientImplTest, StopUsingProvider) {
  ASSERT_TRUE(client_impl_->get_provider_for_testing());
  StartRendering();
  EXPECT_CALL(*this, RemoveVideoFrameController(_));
  client_impl_->StopUsingProvider();
  ASSERT_FALSE(client_impl_->get_provider_for_testing());
}

TEST_F(VideoFrameProviderClientImplTest, FrameAcquisition) {
  CreateActiveVideoLayer();
  StartRenderingAndRenderFrame();

  // Verify GetCurrentFrame() and PutCurrentFrame() work correctly.
  EXPECT_EQ(test_frame_, client_impl_->AcquireLockAndCurrentFrame());
  EXPECT_EQ(0, provider_.put_current_frame_count());
  client_impl_->PutCurrentFrame();
  EXPECT_EQ(1, provider_.put_current_frame_count());

  client_impl_->ReleaseLock();
  StopRendering();
}

TEST_F(VideoFrameProviderClientImplTest, DidReceiveFrame) {
  CreateActiveVideoLayer();
  EXPECT_EQ(gfx::Rect(), video_layer_impl_->update_rect());
  client_impl_->DidReceiveFrame();
  EXPECT_NE(gfx::Rect(), video_layer_impl_->update_rect());
}

TEST_F(VideoFrameProviderClientImplTest, DidDrawFrameIssuesPutCurrentFrame) {
  CreateActiveVideoLayer();
  StartRenderingAndRenderFrame();
  EXPECT_EQ(0, provider_.put_current_frame_count());
  client_impl_->DidDrawFrame();
  EXPECT_EQ(1, provider_.put_current_frame_count());
  StopRendering();
}

TEST_F(VideoFrameProviderClientImplTest, StreamTextureMatrix) {
  const float kIdentityMatrix[] = {
      1.0,
      0.0,
      0.0,
      0.0,
      0.0,
      1.0,
      0.0,
      0.0,
      0.0,
      0.0,
      1.0,
      0.0,
      0.0,
      0.0,
      0.0,
      1.0,
  };

  EXPECT_FALSE(client_impl_->StreamTextureMatrix().IsIdentity());
  client_impl_->DidUpdateMatrix(kIdentityMatrix);
  EXPECT_TRUE(client_impl_->StreamTextureMatrix().IsIdentity());
}

}  // namespace cc
