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

#include "application_win.h"
#include "client_win.h"

#include <Shlwapi.h>
#include <algorithm>

Application_Win::Application_Win()
  : Application(new Client_Win)
{
}

Application_Win::~Application_Win()
{
}

std::wstring Application_Win::getAppDirectory()
{
  if(!_appDirFetched)
  {
    TCHAR path[MAX_PATH];
    DWORD length = GetModuleFileName( NULL, path, MAX_PATH );
    PathRemoveFileSpec(path);
    TCHAR path_canonicalized[MAX_PATH];
    PathCanonicalize(path_canonicalized, path);
    _applicationDir = path_canonicalized;
    std::replace(_applicationDir.begin(), _applicationDir.end(), '\\', '/');
    _appDirFetched = true;
  }
  return _applicationDir;
}

