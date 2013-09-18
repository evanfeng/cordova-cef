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

#ifndef pluginresult_h__
#define pluginresult_h__
#include <string>
namespace Json
{
  class Value;
}

class PluginResult
{
public:
  
  enum Status
  {
    NO_RESULT,
    OK,
    CLASS_NOT_FOUND_EXCEPTION,
    ILLEGAL_ACCESS_EXCEPTION,
    INSTANTIATION_EXCEPTION,
    MALFORMED_URL_EXCEPTION,
    IO_EXCEPTION,
    INVALID_ACTION,
    JSON_EXCEPTION,
    ERROR_ // ERROR give compiler errors so use ERROR_ instead
  };

  enum MessageType
  {
    MESSAGE_TYPE_STRING,
    MESSAGE_TYPE_JSON,
    MESSAGE_TYPE_NUMBER,
    MESSAGE_TYPE_BOOLEAN,
    MESSAGE_TYPE_NULL,
    MESSAGE_TYPE_ARRAYBUFFER,
    MESSAGE_TYPE_BINARYSTRING
  };

  PluginResult(PluginResult::Status status);
  PluginResult(PluginResult::Status status, const Json::Value& json);
  virtual ~PluginResult();

private:
  Status _status;
  MessageType _messageType;
  std::string _strMessage;
  std::string _encodedMessage;

  static const char* _statusMessages[];
};
#endif // pluginresult_h__