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

#ifndef device_win_h__
#define device_win_h__

#include "common/plugins/device.h"

class Device_Win : public DeviceBase
{
  DECLARE_PLUGIN(Device_Win);

public:
  virtual ~Device_Win();

  virtual std::string getVersion();
  virtual std::string getPlatform();
  virtual std::string getModel();
  virtual std::string getUuid();

};
#endif // device_win_h__