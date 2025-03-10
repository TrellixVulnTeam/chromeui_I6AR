// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/views/examples/webview_example.h"

#include "content/public/browser/browser_context.h"
#include "content/public/browser/web_contents.h"
#include "ui/views/controls/webview/webview.h"
#include "ui/views/layout/fill_layout.h"

namespace views {
namespace examples {

WebViewExample::WebViewExample(content::BrowserContext* browser_context)
    : ExampleBase("WebView"),
      webview_(NULL),
      browser_context_(browser_context) {
}

WebViewExample::~WebViewExample() {
}

void WebViewExample::CreateExampleView(View* container) {
  webview_ = new WebView(browser_context_);
  webview_->GetWebContents()->SetDelegate(this);
  container->SetLayoutManager(new FillLayout);
  container->AddChildView(webview_);

  webview_->LoadInitialURL(GURL("http://www.baidu.com/"));
  webview_->GetWebContents()->Focus();
}

void WebViewExample::HandleKeyboardEvent(
    content::WebContents* source,
    const content::NativeWebKeyboardEvent& event) {
  unhandled_keyboard_event_handler_.HandleKeyboardEvent(
      event, webview_->GetFocusManager());
}

}  // namespace examples
}  // namespace views
