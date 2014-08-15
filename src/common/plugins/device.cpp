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

#include "device.h"
#include "json/json.h"
#include "application.h"


DeviceBase::~DeviceBase()
{
}

bool DeviceBase::execute(const std::string& action, const Json::Value& args, CallbackContext& callbackContext)
{
  if(action == "getDeviceInfo")
  {
    Json::Value result;
    result["uuid"] = _uuid;
    result["version"] = _version;
    result["platform"] = _platform;
    result["cordova"] = _cordova;
    result["model"] = _model;

    callbackContext.success(result);
    return true;
  }
  return false;
}

void DeviceBase::initialize(CefRefPtr<Application> app)
{
  CordovaPlugin::initialize(app);
  _uuid = getUuid();
  _version = getVersion();
  _platform = getPlatform();
  _cordova = "dev";
  _model = getModel();
}


//REGISTER_PLUGIN(Device);