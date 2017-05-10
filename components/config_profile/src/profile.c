/*
 * Copyright (c) 2016, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "config_profile/profile.h"

#include <string.h>
#include <stdlib.h>
#include <map>

#include "config_profile/ini_file.h"
#include "logger/logger.h"

namespace {

// default ini file name
std::string kDefaultConfigFileName = "ivdcm.ini";

// Sections name
std::string kMainSection = "Main";
std::string kDomainServerSection = "DomainServer";
std::string kProxyServerSection = "ProxyServer";
std::string kDistributedServiceSection = "DistributedService";
std::string kRemoteNetworkProvider = "RemoteNetworkProvider";
std::string kSDLSection = "SDL";
std::string kPravalaNetworkManagerSection = "PravalaNetworkManager";
std::string kDBusSection = "DBus";

// Params name
std::string kLogFile = "LogFile";
std::string kDomainServerAddress = "DomainServerAddress";
std::string kProxyServerAddress = "ProxyServerAddress";
std::string kProxyServerPort = "ProxyServerPort";
std::string kDistributedServiceAddress = "DistributedServiceAddress";
std::string kDistributedServicePort = "DistributedServicePort";
std::string kBoardType = "BoardType";
std::string kCellularEmulatorInterfaceName = "CellularEmulatorInterfaceName";
std::string kWifiEmulatorInterfaceName = "WifiEmulatorInterfaceName";
std::string kNetworkServiceHost = "NetworkServiceHost";
std::string kNetworkServicePort = "NetworkServicePort";
std::string kRemoteNetworkServiceHost = "RemoteNetworkServiceHost";
std::string kRemoteNetworkServicePort = "RemoteNetworkServicePort";
std::string kSDLServerAddress = "SDLServerAddress";
std::string kSDLServerPort = "SDLServerPort";
std::string kSDLServerNotificationPort = "SDLServerNotificationPort";
std::string kSSLCertificatesPath = "SSLCertificatesPath";

std::string kEnableNQM = "EnableNQM";
std::string kEnableLLCM = "EnableLLCM";
std::string kEnableDBus = "EnableDBus";
std::string kIVDCMDBusServerName = "IVDCMDBusServerName";
std::string kIVDCMDBusObjectPath = "IVDCMDBusObjectPath";
std::string kIVDCMDBusSessionRPCInterface = "IVDCMDBusSessionRPCInterface";
std::string kIVDCMDBusProxyRPCInterface = "IVDCMDBusProxyRPCInterface";
std::string kIVDCMDBusTCUSDKInterface = "IVDCMDBusTCUSDKInterface";
std::string kIVDCMDBusIntrospectInterface = "IVDCMDBusIntrospectInterface";
std::string kIVDCMDBusPropertiesInterface = "IVDCMDBusPropertiesInterface";
std::string kTCUSDKDBusServerName = "TCUSDKDBusServerName";
std::string kTCUSDKDbusObjectPath = "TCUSDKDbusObjectPath";
std::string kTCUSDKDBusInterface = "TCUSDKDBusInterface";
std::string kMQTTServerAddress = "MQTTServerAddress";
std::string kMQTTServerPort = "MQTTServerPort";

std::string kDMDBusInterface = "DMDBusInterface";
std::string kDMDBusObjectPath = "DMDBusObjectPath";

std::string kGRETunnelLocalAddress = "GRETunnelLocalAddress";
std::string kIPAliasAddressGeneratorBase = "IPAliasAddressGeneratorBase";

std::string kPravalaNetWorkManagerAddress = "PravalaNetWorkManagerAddress";
std::string kPravalaMostPreferedInterface = "PravalaMostPreferedInterface";

// maps with default values
// <param name, < param section, param default value> >
static std::map<std::string, std::pair<std::string, std::string> >
    default_values;
typedef std::map<std::string, std::pair<std::string, std::string> >::iterator
    DefValueIt;

void InitDefaultParamsValues() {
  // <param name, < param section, param default value> >
  default_values[kLogFile] = std::make_pair(kMainSection, "ivdcm.log");
  default_values[kDomainServerAddress] =
      std::make_pair(kDomainServerSection, "/tmp/ivdcm_socket");
  default_values[kProxyServerAddress] =
      std::make_pair(kProxyServerSection, "127.0.0.1");
  default_values[kProxyServerPort] =
      std::make_pair(kProxyServerSection, "4051");
  default_values[kDistributedServiceAddress] =
      std::make_pair(kDistributedServiceSection, "127.0.0.1");
  default_values[kDistributedServicePort] =
      std::make_pair(kDistributedServiceSection, "4050");
  default_values[kBoardType] = std::make_pair(kMainSection, "TCU");  // or SYNC
  default_values[kCellularEmulatorInterfaceName] =
      std::make_pair(kMainSection, "cellular");
  default_values[kWifiEmulatorInterfaceName] = std::make_pair(kMainSection, "");
  default_values[kSSLCertificatesPath] =
      std::make_pair(kMainSection, "/opt/conti/etc/cert/");

  default_values[kNetworkServiceHost] =
      std::make_pair(kRemoteNetworkProvider, "127.0.0.1");
  default_values[kNetworkServicePort] =
      std::make_pair(kRemoteNetworkProvider, "4060");

  default_values[kRemoteNetworkServiceHost] =
      std::make_pair(kRemoteNetworkProvider, "127.0.0.1");
  default_values[kRemoteNetworkServicePort] =
      std::make_pair(kRemoteNetworkProvider, "4060");

  default_values[kSDLServerAddress] = std::make_pair(kSDLSection, "127.0.0.1");
  default_values[kSDLServerPort] = std::make_pair(kSDLSection, "5445");
  default_values[kSDLServerNotificationPort] =
      std::make_pair(kSDLSection, "5446");

  default_values[kEnableLLCM] =
      std::make_pair(kPravalaNetworkManagerSection, "false");
  default_values[kEnableNQM] =
      std::make_pair(kPravalaNetworkManagerSection, "false");
  default_values[kPravalaNetWorkManagerAddress] =
      std::make_pair(kPravalaNetworkManagerSection, "/tmp/ivdcm.sock");
  default_values[kPravalaMostPreferedInterface] =
        std::make_pair(kPravalaNetworkManagerSection, "wifi");

  default_values[kEnableDBus] = std::make_pair(kDBusSection, "false");

  default_values[kIVDCMDBusServerName] =
      std::make_pair(kDBusSection, "ivdcm.cm");

  default_values[kIVDCMDBusObjectPath] =
      std::make_pair(kDBusSection, "/ivdcm/cm");

  default_values[kIVDCMDBusSessionRPCInterface] =
      std::make_pair(kDBusSection, "ivdcm.cm.sessionrpc");

  default_values[kIVDCMDBusProxyRPCInterface] =
      std::make_pair(kDBusSection, "ivdcm.cm.proxyrpc");

  default_values[kIVDCMDBusTCUSDKInterface] =
      std::make_pair(kDBusSection, "ivdcm.cm");

  default_values[kIVDCMDBusIntrospectInterface] =
      std::make_pair(kDBusSection, "org.freedesktop.DBus.Introspectable");

  default_values[kIVDCMDBusPropertiesInterface] =
      std::make_pair(kDBusSection, "org.freedesktop.DBus.Properties");

  default_values[kDMDBusObjectPath] =
      std::make_pair(kDBusSection, "/dm/general");

  default_values[kDMDBusInterface] = std::make_pair(kDBusSection, "dm.general");

  default_values[kTCUSDKDBusServerName] =
      std::make_pair(kDBusSection, "conti.sdk.common");

  default_values[kTCUSDKDbusObjectPath] =
      std::make_pair(kDBusSection, "/conti/sdk/common");

  default_values[kTCUSDKDBusInterface] =
      std::make_pair(kDBusSection, "conti.sdk.common");

  default_values[kMQTTServerAddress] =
      std::make_pair(kDBusSection, "127.0.0.1");

  default_values[kMQTTServerPort] = std::make_pair(kDBusSection, "7777");

  default_values[kGRETunnelLocalAddress] =
      std::make_pair(kMainSection, "10.1.0.1");

  default_values[kIPAliasAddressGeneratorBase] =
      std::make_pair(kMainSection, "10.11.0.1");
}

}  // namespace

namespace profile {

Profile::Profile()
    : config_file_name_(kDefaultConfigFileName),
      log_file_name_(),
      domain_server_address_(),
      distributed_service_address_(),
      distributed_service_port_() {
  InitDefaultParamsValues();
}

Profile::~Profile() {}

Profile* Profile::Instance() {
  static Profile instance;
  return &instance;
}

void Profile::config_file_name(const std::string& fileName) {
  if (!fileName.empty()) {
    config_file_name_ = fileName;
    UpdateValues();
  }
}

void Profile::UpdateValues() {
  ReadStringValue(kLogFile.c_str(), &log_file_name_);
  ReadStringValue(kDomainServerAddress.c_str(), &domain_server_address_);

  ReadStringValue(kProxyServerAddress.c_str(), &proxy_server_address_);
  ReadIntValue(kProxyServerPort.c_str(), &proxy_server_port_);

  ReadStringValue(kDistributedServiceAddress.c_str(),
                  &distributed_service_address_);
  ReadIntValue(kDistributedServicePort.c_str(), &distributed_service_port_);
  ReadStringValue(kBoardType.c_str(), &board_type_);
  ReadStringValue(kCellularEmulatorInterfaceName.c_str(),
                  &cellular_emulator_interface_name_);
  ReadStringValue(kWifiEmulatorInterfaceName.c_str(),
                  &wifi_emulator_interface_name_);
  ReadStringValue(kSSLCertificatesPath.c_str(),
                  &ssl_certificates_path_);
  ReadStringValue(kNetworkServiceHost.c_str(), &network_service_host_);
  ReadIntValue(kNetworkServicePort.c_str(), &network_service_port_);
  ReadStringValue(kRemoteNetworkServiceHost.c_str(),
                  &remote_network_service_host_);
  ReadIntValue(kRemoteNetworkServicePort.c_str(),
               &remote_network_service_port_);

  ReadStringValue(kSDLServerAddress.c_str(), &sdl_host_);
  ReadIntValue(kSDLServerPort.c_str(), &sdl_port_);
  ReadIntValue(kSDLServerNotificationPort.c_str(), &sdl_notification_port_);

  ReadBoolValue(kEnableLLCM.c_str(), &llcm_enabled_);
  ReadBoolValue(kEnableDBus.c_str(), &dbus_enabled_);
  ReadBoolValue(kEnableNQM.c_str(), &nqm_enabled_);

  ReadStringValue(kIVDCMDBusServerName.c_str(), &ivdcm_dbus_server_name_);
  ReadStringValue(kIVDCMDBusObjectPath.c_str(), &ivdcm_dbus_object_path_);
  ReadStringValue(kIVDCMDBusSessionRPCInterface.c_str(),
                  &ivdcm_dbus_session_rpc_interface_);
  ReadStringValue(kIVDCMDBusProxyRPCInterface.c_str(),
                  &ivdcm_dbus_proxy_rpc_interface_);
  ReadStringValue(kIVDCMDBusTCUSDKInterface.c_str(),
                  &ivdcm_dbus_tcu_sdk_interface_);
  ReadStringValue(kIVDCMDBusIntrospectInterface.c_str(),
                  &ivdcm_dbus_introspect_interface_);
  ReadStringValue(kIVDCMDBusPropertiesInterface.c_str(),
                  &ivdcm_dbus_properties_interface_);
  ReadStringValue(kTCUSDKDBusServerName.c_str(), &tcu_sdk_dbus_server_name_);
  ReadStringValue(kTCUSDKDbusObjectPath.c_str(), &tcu_sdk_dbus_object_path_);
  ReadStringValue(kTCUSDKDBusInterface.c_str(), &tcu_sdk_dbus_interface_);
  ReadStringValue(kMQTTServerAddress.c_str(), &mqtt_server_address_);
  ReadIntValue(kMQTTServerPort.c_str(), &mqtt_server_port_);

  ReadStringValue(kDMDBusObjectPath.c_str(), &dm_dbus_object_path_);
  ReadStringValue(kDMDBusInterface.c_str(), &dm_dbus_interface_);

  ReadStringValue(kGRETunnelLocalAddress.c_str(), &gre_tunnel_local_address_);
  ReadStringValue(kIPAliasAddressGeneratorBase.c_str(),
                  &ip_alias_address_generator_base_);
  ReadStringValue(kPravalaNetWorkManagerAddress.c_str(),
                  &pravala_netmgr_address_);
  ReadStringValue(kPravalaMostPreferedInterface.c_str(),
                  &pravala_most_prefered_interface_);
}

bool Profile::ReadStringValue(const char* const param_name,
                              std::string* value) const {
  DCHECK_OR_RETURN(value, false);

  bool result = false;
  DefValueIt it = default_values.find(param_name);
  if (default_values.end() == it) {
    DBG_FATAL("No default value for %s", param_name);
    return result;
  }

  if (!ReadValue(it->second.first.c_str(), it->first.c_str(), value)) {
    *value = it->second.second;
  } else {
    result = true;
  }

  DBG_MSG("Parameter name %s from section %s was set to %s", param_name,
          it->second.first.c_str(), value->c_str());
  return result;
}

bool Profile::ReadIntValue(const char* const param_name, Int32* value) const {
  DCHECK_OR_RETURN(value, false);

  bool result = false;
  DefValueIt it = default_values.find(param_name);
  if (default_values.end() == it) {
    return result;
  }

  std::string string_value;
  if (ReadValue(it->second.first.c_str(), it->first.c_str(), &string_value)) {
    result = true;
  } else {
    string_value = it->second.second;
  }

  *value = atoi(string_value.c_str());
  DBG_MSG("Parameter name %s from section %s was set to %d", param_name,
          it->second.first.c_str(), *value);
  return result;
}

bool Profile::ReadBoolValue(const char* const param_name, bool* value) const {
  DCHECK_OR_RETURN(value, false);

  bool result = false;
  DefValueIt it = default_values.find(param_name);
  if (default_values.end() == it) {
    return result;
  }

  std::string string_value;
  if (ReadValue(it->second.first.c_str(), it->first.c_str(), &string_value)) {
    result = true;
  } else {
    string_value = it->second.second;
  }

  const int32_t tmpVal = atoi(string_value.c_str());
  if ((0 == strcmp("true", string_value.c_str())) || (0 != tmpVal)) {
    *value = true;
  } else {
    *value = false;
  }
  DBG_MSG("Parameter name %s from section %s was set to %s", param_name,
          it->second.first.c_str(), (*value) ? "true" : "false");

  return result;
}

bool Profile::ReadValue(const char* const pSection, const char* const pKey,
                        std::string* value) const {
  DCHECK_OR_RETURN(value, false);
  bool ret = false;

  char buf[INI_LINE_LEN + 1];
  *buf = '\0';
  if ((0 != ini_read_value(config_file_name_.c_str(), pSection, pKey, buf)) &&
      ('\0' != *buf)) {
    *value = buf;
    ret = true;
  }
  return ret;
}
Int32 Profile::network_service_port() const { return network_service_port_; }

std::string Profile::network_service_host() const {
  return network_service_host_;
}

std::string Profile::board_type() const { return board_type_; }

Int32 Profile::remote_network_service_port() const {
  return remote_network_service_port_;
}

std::string Profile::remote_network_service_host() const {
  return remote_network_service_host_;
}

}  //  namespace profile
