/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
*/

#ifndef application_win_h__
#define application_win_h__

#include "common/application.h"

class Application_Win : public Application
{
public:
  Application_Win(HINSTANCE hInstance, std::shared_ptr<Helper::PathManager> pathManager);
  virtual ~Application_Win();
  virtual void createMainWindow();

  //virtual CefRefPtr<Client::RenderHandler> createOSRWindow(CefWindowHandle parent, OSRBrowserProvider* browser_provider, bool transparent);

private:
  static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);




  HINSTANCE _hInstance;

};
#endif // application_win_h__
