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

#ifndef COMPONENTS_CONFIG_PROFILE_PROFILE_H_
#define COMPONENTS_CONFIG_PROFILE_PROFILE_H_

#include <string>
#include "utils/macro.h"
#include "utils/types.h"

namespace profile {

/**
 * The Profile class
 */
class Profile {
 public:
  /**
   * @brief Returns the singleton of class
   */
  static Profile* Instance();

  /*
   * @brief Updates all related values from ini file
   */
  void UpdateValues();

  /**
   * @brief Sets the path to the config file
   */
  void config_file_name(const std::string& fileName);

  /**
   * @brief Returns the path to the config file
   */
  inline const std::string& config_file_name() const;

  /**
    * @brief Returns the desirable log file
    */
  inline const std::string& log_file_name() const;

  /**
    * @brief Returns the domain server address
    */
  inline const std::string& domain_server_address() const;

  /**
  * @brief Returns the proxy server address
  */
  inline const std::string& proxy_server_address() const;

  /**
    * @brief Returns the proxy server port
    */
  inline Int32 proxy_server_port() const;

  /**
    * @brief Returns the distributed service address
    */
  inline const std::string& distributed_service_address() const;

  /**
    * @brief Returns the distributed service port
    */
  inline Int32 distributed_service_port() const;

  std::string remote_network_service_host() const;

  Int32 remote_network_service_port() const;

  std::string board_type() const;

  /**
    * @brief Returns the interface name which will emulate cellular interface
    */
  inline const std::string& cellular_emulator_interface_name() const;

  /**
   * @brief Returns the interface name which will emulate WiFi interface
   */
  inline const std::string& wifi_emulator_interface_name() const;

  std::string network_service_host() const;

  Int32 network_service_port() const;

  /**
    * @brief Returns the sdl server address
    */
  inline std::string sdl_host() const;

  /**
    * @brief Returns the sdl server request port
    */
  inline Int32 sdl_port() const;

  /**
    * @brief Returns true if LLCM enabled, false otherwise
    */
  inline bool llcm_enabled() const;

  /**
    * @brief Returns the EnableDbus param
    */
  inline bool dbus_enabled() const;

  /**
    * @brief Returns true if NQM enabled, false otherwise
    */
  inline bool nqm_enabled() const;

  /**
    * @brief Returns the IVDCM dbus server name
    */
  inline const std::string& ivdcm_dbus_server_name() const;

  /**
    * @brief Returns the IVDCM dbus object path
    */
  inline const std::string& ivdcm_dbus_object_path() const;

  /**
    * @brief Returns the IVDCM dbus session rpc interface
    */
  inline const std::string& ivdcm_dbus_session_rpc_interface() const;

  /**
    * @brief Returns the IVDCM dbus proxy rpc interface
    */
  inline const std::string& ivdcm_dbus_proxy_rpc_interface() const;

  /**
    * @brief Returns the IVDCM dbus tcu sdk interface
    */
  inline const std::string& ivdcm_dbus_tcu_sdk_interface() const;

  /**
   * @brief Returns the IVDCM dbus introspect interface
   */
  inline const std::string& ivdcm_dbus_introspect_interface() const;

  /**
   * @brief Returns the IVDCM dbus properties interface
   */
  inline const std::string& ivdcm_dbus_properties_interface() const;

  /**
    * @brief Returns the DM dbus object path
    */
  inline const std::string& dm_dbus_object_path() const;

  /**
   * @brief Returns the DM dbus interface
   */
  inline const std::string& dm_dbus_interface() const;

  /**
    * @brief Returns the TCU dbus server name
    */
  inline const std::string& tcu_sdk_dbus_server_name() const;

  /**
    * @brief Returns the TCU dbus object path
    */
  inline const std::string& tcu_sdk_dbus_object_path() const;

  /**
    * @brief Returns the TCU dbus interface
    */
  inline const std::string& tcu_sdk_dbus_interface() const;

  /**
    * @brief Returns address of local MQTT server
    */
  inline const std::string& mqtt_server_address() const;

  /**
    * @brief Returns port of local MQTT server
    */
  inline const Int32 mqtt_server_port() const;

  /**
    * @brief Returns the sdl server notification port
    */
  inline Int32 sdl_notification_port() const;

  /**
    * @brief Returns the GRE Tunnel local address
    */
  inline const std::string& gre_tunnel_local_address() const;

  /**
   * @brief Returns the IP Alias address generator base
   */
  inline const std::string& ip_alias_address_generator_base() const;

  /**
   * @brief Returns the pravala network manager address
   */
  inline const std::string& pravala_netmgr_address() const;

  /**
   * @brief Returns the pravala most prefered interface
   */
  inline const std::string& pravala_most_prefered_interface() const;

  /**
   * @brief Returns path of folder with SSL certificates
   */
  inline const std::string& ssl_certificates_path() const;

 private:
  /**
   * Default constructor
   *
   * Unimplemented to avoid misusing
   *
   */
  Profile();

  /**
    * Destructor
    *
    * Unimplemented to avoid misusing
    *
    */
  ~Profile();

  /**
   * @brief Reads a string value from the profile
   *
   * @param param_name    The key whose value needs to be read out
   * @param value         Result value
   *
   * @return FALSE if could not read the value out of the profile
   * (then the value is equal \c default_value)
   */
  bool ReadStringValue(const char* const param_name, std::string* value) const;

  /**
   * @brief Reads an int32_t value from the profile
   *
   * @param param_name    The key whose value needs to be read out
   * @param value         Result value
   *
   * @return FALSE if could not read the value out of the profile
   * (then the value is equal \c default_value)
   */
  bool ReadIntValue(const char* const param_name, Int32* value) const;

  /**
   * @brief Reads an bool value from the profile
   *
   * @param param_name    The key whose value needs to be read out
   * @param value         Result value
   *
   * @return FALSE if could not read the value out of the profile
   * (then the value is equal \c default_value)
   */
  bool ReadBoolValue(const char* const param_name, bool* value) const;

  /**
   * @brief Reads a string value from the profile and interpret it
   * as \c true on "true" value or as \c false on any other value
   *
   * @param pSection   The section to read the value in
   * @param pKey       The key whose value needs to be read out
   * @param value      The value to return
   *
   * @return FALSE if could not read the value out of the profile
   * (then the value is not changed)
   */
  bool ReadValue(const char* const pSection, const char* const pKey,
                 std::string* value) const;

 private:
  std::string config_file_name_;
  std::string log_file_name_;
  std::string domain_server_address_;
  std::string proxy_server_address_;
  Int32 proxy_server_port_;
  std::string distributed_service_address_;
  Int32 distributed_service_port_;
  std::string board_type_;
  std::string cellular_emulator_interface_name_;
  std::string wifi_emulator_interface_name_;
  std::string network_service_host_;
  Int32 network_service_port_;
  std::string remote_network_service_host_;
  Int32 remote_network_service_port_;

  std::string sdl_host_;
  Int32 sdl_port_;
  Int32 sdl_notification_port_;

  bool llcm_enabled_;
  bool dbus_enabled_;
  bool nqm_enabled_;

  std::string ivdcm_dbus_server_name_;
  std::string ivdcm_dbus_object_path_;
  std::string ivdcm_dbus_session_rpc_interface_;
  std::string ivdcm_dbus_proxy_rpc_interface_;
  std::string ivdcm_dbus_tcu_sdk_interface_;
  std::string ivdcm_dbus_introspect_interface_;
  std::string ivdcm_dbus_properties_interface_;

  std::string dm_dbus_object_path_;
  std::string dm_dbus_interface_;

  std::string tcu_sdk_dbus_server_name_;
  std::string tcu_sdk_dbus_object_path_;
  std::string tcu_sdk_dbus_interface_;

  std::string mqtt_server_address_;
  Int32 mqtt_server_port_;

  std::string gre_tunnel_local_address_;
  std::string ip_alias_address_generator_base_;

  std::string pravala_netmgr_address_;
  std::string pravala_most_prefered_interface_;

  std::string ssl_certificates_path_;

  DISALLOW_COPY_AND_ASSIGN(Profile);
};

const std::string& Profile::config_file_name() const {
  return config_file_name_;
}

const std::string& Profile::log_file_name() const { return log_file_name_; }

const std::string& Profile::domain_server_address() const {
  return domain_server_address_;
}

const std::string& Profile::proxy_server_address() const {
  return proxy_server_address_;
}

Int32 Profile::proxy_server_port() const { return proxy_server_port_; }

const std::string& Profile::distributed_service_address() const {
  return distributed_service_address_;
}

Int32 Profile::distributed_service_port() const {
  return distributed_service_port_;
}

const std::string& Profile::cellular_emulator_interface_name() const {
  return cellular_emulator_interface_name_;
}

const std::string& Profile::wifi_emulator_interface_name() const {
  return wifi_emulator_interface_name_;
}

std::string Profile::sdl_host() const { return sdl_host_; }

Int32 Profile::sdl_port() const { return sdl_port_; }

Int32 Profile::sdl_notification_port() const { return sdl_notification_port_; }

bool Profile::llcm_enabled() const { return llcm_enabled_; }

bool Profile::dbus_enabled() const { return dbus_enabled_; }

bool Profile::nqm_enabled() const { return nqm_enabled_; }

const std::string& Profile::ivdcm_dbus_server_name() const {
  return ivdcm_dbus_server_name_;
}

const std::string& Profile::ivdcm_dbus_object_path() const {
  return ivdcm_dbus_object_path_;
}

const std::string& Profile::ivdcm_dbus_session_rpc_interface() const {
  return ivdcm_dbus_session_rpc_interface_;
}

const std::string& Profile::ivdcm_dbus_proxy_rpc_interface() const {
  return ivdcm_dbus_proxy_rpc_interface_;
}

const std::string& Profile::ivdcm_dbus_tcu_sdk_interface() const {
  return ivdcm_dbus_tcu_sdk_interface_;
}

const std::string& Profile::ivdcm_dbus_introspect_interface() const {
  return ivdcm_dbus_introspect_interface_;
}

const std::string& Profile::ivdcm_dbus_properties_interface() const {
  return ivdcm_dbus_properties_interface_;
}

const std::string& Profile::dm_dbus_object_path() const {
  return dm_dbus_object_path_;
}

const std::string& Profile::dm_dbus_interface() const {
  return dm_dbus_interface_;
}

const std::string& Profile::tcu_sdk_dbus_server_name() const {
  return tcu_sdk_dbus_server_name_;
}

const std::string& Profile::tcu_sdk_dbus_object_path() const {
  return tcu_sdk_dbus_object_path_;
}

const std::string& Profile::tcu_sdk_dbus_interface() const {
  return tcu_sdk_dbus_interface_;
}

const std::string& Profile::mqtt_server_address() const {
  return mqtt_server_address_;
}

const Int32 Profile::mqtt_server_port() const { return mqtt_server_port_; }

const std::string& Profile::gre_tunnel_local_address() const {
  return gre_tunnel_local_address_;
}

const std::string& Profile::ip_alias_address_generator_base() const {
  return ip_alias_address_generator_base_;
}

const std::string& Profile::pravala_netmgr_address() const {
  return pravala_netmgr_address_;
}

const std::string& Profile::pravala_most_prefered_interface() const {
  return pravala_most_prefered_interface_;
}

const std::string& Profile::ssl_certificates_path() const {
  return ssl_certificates_path_;
}

}  //  namespace profile

#endif  // SRC_COMPONENTS_CONFIG_PROFILE_PROFILE_H_
