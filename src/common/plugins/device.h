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

#ifndef cdvplugindevice_h__
#define cdvplugindevice_h__

#include "include/cef_base.h"
#include "cordovaplugin.h"

class DeviceBase : public CordovaPlugin
{
public:
  
  virtual ~DeviceBase();
  virtual bool execute(const std::string& action, const Json::Value& args, CallbackContext& callbackContext);
  virtual void initialize(CefRefPtr<Application> app);

protected:
  // serialize to user/appdata
  virtual std::string getUuid() = 0;
  virtual std::string getVersion() = 0;
  virtual std::string getPlatform() = 0;
  virtual std::string getModel() = 0;

private:
  std::string _uuid;
  std::string _version;
  std::string _platform;
  std::string _cordova;
  std::string _model;
};
#endif // cdvplugindevice_h__