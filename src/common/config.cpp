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

#include "helper.h"
#include "config.h"
#include "humblelogging/api.h"
#include <sstream>

HUMBLE_LOGGER(logger, "Config");


Config::Config( const Helper::Path& configXMLFile, std::shared_ptr<PluginManager> pluginManager )
{
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(configXMLFile.filePath().c_str());
  if(result.status == pugi::status_ok)
  {
    // get name node
    pugi::xpath_node name_node =  doc.select_single_node(L"/widget/name");
    _appName = Helper::wideToUtf8(name_node.node().text().get());
    pugi::xpath_node content_node =  doc.select_single_node(L"/widget/content");
    _startDocument = Helper::wideToUtf8(content_node.node().attribute(L"src").value());

    // parse the preferences
    pugi::xpath_node_set preferences = doc.select_nodes(L"/widget/preference");
    for(pugi::xpath_node_set::const_iterator iter = preferences.begin() ; iter != preferences.end(); ++iter)
    {
      std::string preferenceName = Helper::wideToUtf8(iter->node().attribute(L"name").value());
      std::string preferenceValue = Helper::wideToUtf8(iter->node().attribute(L"value").value());
      _preferences[preferenceName] = preferenceValue;
    }

    // parse the plugins
    // get all feature nodes
    pugi::xpath_node_set features = doc.select_nodes(L"/widget/feature");
    
    for(pugi::xpath_node_set::const_iterator iter = features.begin() ; iter != features.end(); ++iter)
    {
      std::string servicename = Helper::wideToUtf8(iter->node().attribute(L"name").value());
      pugi::xpath_node param = iter->node().select_single_node(L"param");
      
      // check if name="cef-package"
      std::string param_name = Helper::wideToUtf8(param.node().attribute(L"name").value());
      if( param_name.compare("cef-package") == 0)
      {
        std::string classname = Helper::wideToUtf8(param.node().attribute(L"value").value());
        std::string onload_str = Helper::wideToUtf8(param.node().attribute(L"onload").value());
        bool onload = false;
        if(onload_str.compare("true") == 0)
          onload = true;
        pluginManager->addPlugin(servicename, classname, onload);
      }
    }
  }
  else
  {
    std::stringstream ss;
    ss << "failed to parse config xml '" << configXMLFile.filePath() << "' result=" << result.status;
    HL_ERROR(logger, ss.str());
    //TODO: error handling
  }
}

Config::~Config()
{

}

bool Config::getStringPreference( const std::string& prefName, std::string& value ) const
{
  bool ret = false;
  std::map<std::string, std::string>::const_iterator search = _preferences.find(prefName);
  if(search != _preferences.end())
  {
    value = search->second;
    return true;
  }
  return ret;
}

bool Config::getBoolPreference( const std::string& prefName, bool& value ) const
{
  bool ret = false;
  std::map<std::string, std::string>::const_iterator search = _preferences.find(prefName);
  if(search != _preferences.end())
  {
    std::string val = search->second;
    if(Helper::StringUtils::iequals(val, "true"))
      value = true;
    else
      value = false;
    return true;
  }
  return ret;
}

bool Config::getIntPreference( const std::string& prefName, int& value ) const
{
  bool ret = false;
  std::map<std::string, std::string>::const_iterator search = _preferences.find(prefName);
  if(search != _preferences.end())
  {
    try {
      value = std::stoi(search->second);
      return true;
    } catch(std::exception&) {
      return false;
    }
  }
  return ret;
}

bool Config::getDoublePreference( const std::string& prefName, double& value ) const
{
  bool ret = false;
  std::map<std::string, std::string>::const_iterator search = _preferences.find(prefName);
  if(search != _preferences.end())
  {
    try {
      value = std::stod(search->second);
      return true;
    } catch(std::exception&) {
      return false;
    }
  }
  return ret;
}


