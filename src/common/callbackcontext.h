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

#ifndef CallbackContext_h__
#define CallbackContext_h__

#include <string>
#include "pluginresult.h"

class Application;
namespace Json
{
  class Value;
}


class CallbackContext
{
public:
  CallbackContext(const std::string& callbackId, Application* app);
  virtual ~CallbackContext();

  void success(const Json::Value& json);
  void sendPluginresult(const PluginResult& result);

private:
  std::string _callbackId;
  Application* _app;
};

#endif // CallbackContext_h__