// Copyright (c) 2012 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file.

#include <limits.h>
#include "osrenderer.h"

#if defined(OS_WIN)
#include <gl/gl.h>
#include <gl/glu.h>
#elif defined(OS_MACOSX)
#include <OpenGL/gl.h>
#elif defined(OS_LINUX)
#include <GL/gl.h>
#include <GL/glu.h>
#else
#error Platform is not supported.
#endif

#include "cefclient/util.h"

#ifndef GL_BGR
#define GL_BGR 0x80E0
#endif
#ifndef GL_BGRA
#define GL_BGRA 0x80E1
#endif
#ifndef GL_UNSIGNED_INT_8_8_8_8_REV
#define GL_UNSIGNED_INT_8_8_8_8_REV 0x8367
#endif

//#include <fstream>


ClientOSRenderer::ClientOSRenderer(bool transparent)
    : transparent_(transparent),
      initialized_(false),     
      view_width_(0),
      view_height_(0),
      spin_x_(0),
      spin_y_(0) {
}

ClientOSRenderer::~ClientOSRenderer() {
  Cleanup();
}

void ClientOSRenderer::Initialize() {
  if (initialized_)
    return;

  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // Necessary for non-power-of-2 textures to render correctly.
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  // Create the texture.
  TexLayer tex;
  glGenTextures(1, &tex.id);
  ASSERT(tex.id != 0);

  glBindTexture(GL_TEXTURE_2D, tex.id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  initialized_ = true;

  // insert int texture map
  
  
  texture_ids_[WEB_CONTENT_TEXTURE_PRIORITY] = tex;
}

void ClientOSRenderer::Cleanup() {

  if (texture_ids_.find(WEB_CONTENT_TEXTURE_PRIORITY) != texture_ids_.end() && texture_ids_[WEB_CONTENT_TEXTURE_PRIORITY].id != 0)
    glDeleteTextures(1, &texture_ids_[WEB_CONTENT_TEXTURE_PRIORITY].id);
}

void ClientOSRenderer::Render() {
  if (view_width_ == 0 || view_height_ == 0)
    return;

  ASSERT(initialized_);

  

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Match GL units to screen coordinates.
  glViewport(0, 0, view_width_, view_height_);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 0, view_width_, view_height_, 0.1, 100.0);

  std::map<int, TexLayer>::iterator iter;
  for(iter = texture_ids_.begin(); iter != texture_ids_.end(); ++iter) 
  {

    const TexLayer& tex = (*iter).second;

    float tex_coordinate_S = 1.0f;
    float tex_coordinate_T = 1.0f;

    if(tex.bRepeatableS)
      tex_coordinate_S = (float)view_width_ / (float)tex.width;

    if(tex.bRepeatableT)
      tex_coordinate_T = (float)view_height_ / (float)tex.height;
    

    /*
    struct {
      float tu, tv;
      float x, y, z;
    } static vertices[] = {
      {0.0f,             tex_coordinate_T, -1.0f, -1.0f, 0.0f},
      {tex_coordinate_S, tex_coordinate_T,  1.0f, -1.0f, 0.0f},
      {tex_coordinate_S, 0.0f,          1.0f,  1.0f, 0.0f},
      {0.0f,             0.0f,         -1.0f,  1.0f, 0.0f}
    };
    */

    // Draw the background gradient.

    if (transparent_) {
      // Alpha blending style. Texture values have premultiplied alpha.
      glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

      // Enable alpha blending.
      glEnable(GL_BLEND);
    }

    // Enable 2D textures.
    glEnable(GL_TEXTURE_2D);

    // Draw the facets with the texture.


    ASSERT(tex.id != 0);
    glBindTexture(GL_TEXTURE_2D, tex.id);


    
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glBegin(GL_QUADS);

    // flipped h
    if(tex.bFlippedh) 
    {
      glTexCoord2f(0.0f, 0.0f);
      glVertex2f(-1.0, -1.0); // bottom left
      glTexCoord2f(tex_coordinate_S, 0.0f);
      glVertex2f(1.0, -1.0); // bottom right

    
      glTexCoord2f(tex_coordinate_S, tex_coordinate_T);
      glVertex2f(1.0, 1.0); // top right
      glTexCoord2f(0.0f, tex_coordinate_T);
      glVertex2f(-1.0, 1.0); // top left
    }
    else
    {
      glTexCoord2f(0.0f, tex_coordinate_T);
      glVertex2f(-1.0, -1.0); // bottom left    
      glTexCoord2f(tex_coordinate_S, tex_coordinate_T);
      glVertex2f(1.0, -1.0); // bottom right

      glTexCoord2f(tex_coordinate_S, 0.0f);
      glVertex2f(1.0, 1.0); // top right
      glTexCoord2f(0.0f, 0.0f);
      glVertex2f(-1.0, 1.0); // top left
    }
    
    glEnd();
    glPopAttrib();
    

    // Rotate the view based on the mouse spin.
    if (spin_x_ != 0)
      glRotatef(-spin_x_, 1.0f, 0.0f, 0.0f);
    if (spin_y_ != 0)
      glRotatef(-spin_y_, 0.0f, 1.0f, 0.0f);

    
    /*
    glInterleavedArrays(GL_T2F_V3F, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 4);
    */
  }

  

  // Disable 2D textures.
  glDisable(GL_TEXTURE_2D);

  if (transparent_) {
    // Disable alpha blending.
    glDisable(GL_BLEND);
  }
  
  /*
  int size = view_width_ * view_height_ * 4;
  char* pbuffer = new char[size];
  glReadPixels(0, 0, view_width_, view_height_, GL_RGBA, GL_UNSIGNED_BYTE, (void*)pbuffer);

  std::ofstream ofile("raw.rgba", std::ofstream::binary);
  ofile.write(pbuffer, size);
  ofile.close();
  delete[] pbuffer;
  */
}

void ClientOSRenderer::OnPopupShow(CefRefPtr<CefBrowser> browser,
                                   bool show) {
  if (!show) {
    // Clear the popup rectangle.
    ClearPopupRects();
  }
}

void ClientOSRenderer::OnPopupSize(CefRefPtr<CefBrowser> browser,
                                   const CefRect& rect) {
  if (rect.width <= 0 || rect.height <= 0)
    return;
  original_popup_rect_ = rect;
  popup_rect_ = GetPopupRectInWebView(original_popup_rect_);
}

CefRect ClientOSRenderer::GetPopupRectInWebView(const CefRect& original_rect) {
  CefRect rc(original_rect);
  // if x or y are negative, move them to 0.
  if (rc.x < 0)
    rc.x = 0;
  if (rc.y < 0)
    rc.y = 0;
  // if popup goes outside the view, try to reposition origin
  if (rc.x + rc.width > view_width_)
    rc.x = view_width_ - rc.width;
  if (rc.y + rc.height > view_height_)
    rc.y = view_height_ - rc.height;
  // if x or y became negative, move them to 0 again.
  if (rc.x < 0)
    rc.x = 0;
  if (rc.y < 0)
    rc.y = 0;
  return rc;
}

void ClientOSRenderer::ClearPopupRects() {
  popup_rect_.Set(0, 0, 0, 0);
  original_popup_rect_.Set(0, 0, 0, 0);
}

void ClientOSRenderer::OnPaint(CefRefPtr<CefBrowser> browser,
                               CefRenderHandler::PaintElementType type,
                               const CefRenderHandler::RectList& dirtyRects,
                               const void* buffer, int width, int height) {
  if (!initialized_)
    Initialize();

  if (transparent_) {
    // Enable alpha blending.
    glEnable(GL_BLEND);
  }

  // Enable 2D textures.
  glEnable(GL_TEXTURE_2D);

  unsigned int texture_id = texture_ids_[WEB_CONTENT_TEXTURE_PRIORITY].id;

  texture_ids_[WEB_CONTENT_TEXTURE_PRIORITY].width = width;
  texture_ids_[WEB_CONTENT_TEXTURE_PRIORITY].height = height;

  ASSERT(texture_id != 0);
  glBindTexture(GL_TEXTURE_2D, texture_id);

  if (type == PET_VIEW) {
    int old_width = view_width_;
    int old_height = view_height_;

    view_width_ = width;
    view_height_ = height;

    glPixelStorei(GL_UNPACK_ROW_LENGTH, view_width_);

    if (old_width != view_width_ || old_height != view_height_) {
      // Update/resize the whole texture.
      glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
      glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, view_width_, view_height_, 0,
                   GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, buffer);
    } else {
      // Update just the dirty rectangles.
      CefRenderHandler::RectList::const_iterator i = dirtyRects.begin();
      for (; i != dirtyRects.end(); ++i) {
        const CefRect& rect = *i;
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, rect.x);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, rect.y);
        glTexSubImage2D(GL_TEXTURE_2D, 0, rect.x, rect.y, rect.width,
                        rect.height, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV,
                        buffer);
      }
    }
  } else if (type == PET_POPUP && popup_rect_.width > 0 &&
             popup_rect_.height > 0) {
    int skip_pixels = 0, x = popup_rect_.x;
    int skip_rows = 0, y = popup_rect_.y;
    int w = width;
    int h = height;

    // Adjust the popup to fit inside the view.
    if (x < 0) {
      skip_pixels = -x;
      x = 0;
    }
    if (y < 0) {
      skip_rows = -y;
      y = 0;
    }
    if (x + w > view_width_)
      w -= x + w - view_width_;
    if (y + h > view_height_)
      h -= y + h - view_height_;

    // Update the popup rectangle.
    glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, skip_pixels);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, skip_rows);
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_BGRA,
                    GL_UNSIGNED_INT_8_8_8_8_REV, buffer);
  }

  // Disable 2D textures.
  glDisable(GL_TEXTURE_2D);

  if (transparent_) {
    // Disable alpha blending.
    glDisable(GL_BLEND);
  }
}

void ClientOSRenderer::SetSpin(float spinX, float spinY) {
  spin_x_ = spinX;
  spin_y_ = spinY;
}

void ClientOSRenderer::IncrementSpin(float spinDX, float spinDY) {
  spin_x_ -= spinDX;
  spin_y_ -= spinDY;
}

void ClientOSRenderer::addTextureWithPrio(int priority, TexLayer tex)
{
  texture_ids_[priority] = tex;
}

void ClientOSRenderer::removeTextureWithPrio(int priority)
{
  texture_ids_.erase(priority);
}
