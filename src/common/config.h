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

#include "include/cef_base.h"
#include "pugixml.hpp"
#include "pluginmanager.h"

namespace Helper
{
  class Path;
}

class Config
{
public:
  Config(const Helper::Path& configXMLFile, std::shared_ptr<PluginManager> pluginManager);
  virtual ~Config();

  std::string appName() const { return _appName;}
  std::string startDocument() const { return _startDocument; }

  bool getStringPreference(const std::string& prefName, std::string& value) const;
  bool getBoolPreference(const std::string& prefName, bool& value) const;
  bool getIntPreference(const std::string& prefName, int& value) const;
  bool getDoublePreference(const std::string& prefName, double& value) const;


private:
  
  std::string _appName;
  std::string _startDocument;  
  std::map<std::string, std::string> _preferences;

};