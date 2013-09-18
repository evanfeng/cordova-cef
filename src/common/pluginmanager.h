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

#ifndef pluginmanager_h__
#define pluginmanager_h__

#include "include/cef_base.h"
#include <string>
#include <map>
#include "cordovaplugin.h"
#include "logging.h"
#include "pluginregistry.h"

class Application;
class PluginEntry;

class PluginManager
{
public:
  PluginManager(Application* app);
  virtual ~PluginManager();
  void init();
  void addPlugin(const std::string& servicename, const std::string& classname, bool onload=false);
  void exec(const std::string& service, const std::string& action, const std::string& callbackId, const std::string& rawArgs);

private:
  

  void clearPluginObjects();
  void startupPlugins();
  CordovaPlugin* getPlugin(const std::string service);
  

  
  bool _firstRun;
  Application* _app;
  typedef std::map<std::string, PluginEntry*> PluginMap;
  PluginMap _pluginEntries;

  IMPLEMENT_REFCOUNTING(PluginManager);
  DECLARE_LOGGER(PluginManager);
};

#endif // pluginmanager_h__
