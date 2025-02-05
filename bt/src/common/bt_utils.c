/*********************************************************************
* @file  bt_utils.c
* @brief Bluetooth Manager Utility interface definition.
*
* Copyright 2021 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

#ifdef __cplusplus
extern "C"{
#endif

/*--------------------------------------------------------------------
                        GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "bt_utils.h"

/*--------------------------------------------------------------------
                        Definitions
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                        LITERAL CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                        TYPES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                        PROJECT INCLUDES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                        MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                        VARIABLES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                        PROTOTYPES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                        PROCEDURES
--------------------------------------------------------------------*/
/*================================================================================================
@brief   Convert the Bluetooth profile connection status to string
@details Convert the Bluetooth profile connection status to string
@return  None
@retval  String of the Bluetooth profile connection status
================================================================================================*/
const char* BT_util_get_connection_status_string
    (
    const BT_connection_status_e connection_status
    )
{
switch( connection_status )
    {
    case BT_CONNECTION_DISCONNECTED:   return "Disconnected";
    case BT_CONNECTION_CONNECTING:     return "Connecting";
    case BT_CONNECTION_CONNECTED:      return "Connected";
    case BT_CONNECTION_DISCONNECTING:  return "Disconnecting";
    case BT_CONNECTION_STATUS_INVALID:
    default:                           return "Unknown";
    }
}

/*================================================================================================
@brief   Convert the device type to string
@details Convert the device type to string
@return  None
@retval  String of the device type
================================================================================================*/
const char* BT_util_get_device_type_string
    (
    const BT_device_type_e device_type
    )
{
switch( device_type )
    {
    case BT_DEVICE_BREDR:        return "BR/EDR";
    case BT_DEVICE_LE:           return "LE";
    case BT_DEVICE_BREDR_LE:     return "BR/EDR + LE";
    case BT_DEVICE_TYPE_INVALID:
    default:                     return "Unknown";
    }
}

/*================================================================================================
@brief   Convert the HCI role to string
@details Convert the HCI role to string
@return  None
@retval  String of the HCI role
================================================================================================*/
const char* BT_util_get_hci_role_string
    (
    const BT_hci_role_e hci_role
    )
{
switch( hci_role )
    {
    case BT_HCI_MASTER:       return "Master";
    case BT_HCI_SLAVE:        return "Slave";
    case BT_HCI_ROLE_INVALID:
    default:                  return "Unknown";
    }
}

/*================================================================================================
@brief   Convert the hardware mode to string
@details Convert the hardware mode to string
@return  None
@retval  String of the hardware mode
================================================================================================*/
const char* BT_util_get_hw_mode_string
    (
    const BT_hw_mode_e hw_mode
    )
{
switch( hw_mode )
    {
    case BT_HW_MODE_NORMAL:   return "Normal";
    case BT_HW_MODE_DOWNLOAD: return "Download";
    case BT_HW_MODE_INVALID:
    default:                  return "Unknown";
    }
}

/*================================================================================================
@brief   Convert the pairing status to string
@details Convert the pairing status to string
@return  None
@retval  String of the pairing status
================================================================================================*/
const char* BT_util_get_pairing_status_string
    (
    const BT_pairing_status_e pairing_status
    )
{
switch( pairing_status )
    {
    case BT_PAIRING_NONE:              return "None";
    case BT_PAIRING_USER_CONFIRMING:   return "User Confirming";
    case BT_PAIRING_CONFIRMED_WAITING: return "Confirmed Waiting";
    case BT_PAIRING_SUCCEEDED:         return "Succeeded";
    case BT_PAIRING_FAILED:            return "Failed";
    case BT_PAIRING_STATUS_INVALID:
    default:                           return "Unknown";
    }
}

/*================================================================================================
@brief   Convert the power status to string
@details Convert the power status to string
@return  None
@retval  String of the power status
================================================================================================*/
const char* BT_util_get_power_status_string
    (
    const BT_power_status_e power_status
    )
{
switch( power_status )
    {
    case BT_POWER_OFF:            return "Off";
    case BT_POWER_ON:             return "On";
    case BT_POWER_ON_UPDATING:    return "On Updating";
    case BT_POWER_ON_READY:       return "On Ready";
    case BT_POWER_STATUS_INVALID:
    default:                      return "Unknown";
    }
}

/*================================================================================================
@brief   Convert the SPP app type to string
@details Convert the SPP app type to string
@return  None
@retval  String of the SPP app type
================================================================================================*/
const char* BT_util_get_spp_app_type_string
    (
    const BT_spp_app_type_e app_type
    )
{
switch( app_type )
    {
    case BT_SPP_APP_NAVILITE:     return "Navilite";
    case BT_SPP_APP_MOTOCON:      return "Motocon";
    case BT_SPP_APP_TYPE_INVALID:
    default:                      return "Unknown";
    }
}

/*================================================================================================
@brief   Convert the SPP connection type to string
@details Convert the SPP connection type to string
@return  None
@retval  String of the SPP connection type
================================================================================================*/
const char* BT_util_get_spp_connection_type_string
    (
    const BT_spp_connection_type_e connection_type
    )
{
switch( connection_type )
    {
    case BT_SPP_CONNECTION_SPP:          return "SPP";
    case BT_SPP_CONNECTION_IAP:          return "iAP";
    case BT_SPP_CONNECTION_TYPE_INVALID:
    default:                             return "Unknown";
    }
}

/*================================================================================================
@brief   Convert the transport type to string
@details Convert the transport type to string
@return  None
@retval  String of the transport type
================================================================================================*/
const char* BT_util_get_transport_type_string
    (
    const BT_transport_type_e transport_type
    )
{
switch( transport_type )
    {
    case BT_TRANSPORT_BREDR:        return "BR/EDR";
    case BT_TRANSPORT_LE:           return "LE";
    case BT_TRANSPORT_TYPE_INVALID:
    default:                        return "Unknown";
    }
}

// LE

/*================================================================================================
@brief   Convert the LE advertising mode to string
@details Convert the LE advertising mode to string
@return  None
@retval  String of the LE advertising mode
================================================================================================*/
const char* BLE_util_get_advertising_mode_string
    (
    const BLE_advertising_mode_e advertising_mode
    )
{
switch( advertising_mode )
    {
    case BLE_ADVERTISING_OFF:             return "Off";
    case BLE_ADVERTISING_NON_CONNECTABLE: return "Non-Connectable Advertising";
    case BLE_ADVERTISING_CONNECTABLE:     return "Connectable Advertising";
    case BLE_ADVERTISING_MODE_INVALID:
    default:                              return "Unknown";
    }
}

/*================================================================================================
@brief   Convert the LE BD address type to string
@details Convert the LE BD address type to string
@return  None
@retval  String of the LE BD address type
================================================================================================*/
const char* BLE_util_get_bd_addr_type_string
    (
    const BLE_bd_addr_type_e bd_addr_type
    )
{
switch( bd_addr_type )
    {
    case BLE_BD_ADDR_PUBLIC:       return "Public";
    case BLE_BD_ADDR_RANDOM:       return "Random";
    case BLE_BD_ADDR_TYPE_INVALID:
    default:                       return "Unknown";
    }
}

/*================================================================================================
@brief   Convert the LE client type to string
@details Convert the LE client type to string
@return  None
@retval  String of the LE client type
================================================================================================*/
const char* BLE_util_get_client_type_string
    (
    const BLE_client_type_e client_type
    )
{
switch( client_type )
    {
    case BLE_CLIENT_ANCS:         return "ANCS";
    case BLE_CLIENT_AMS:          return "AMS";
    case BLE_CLIENT_TYPE_INVALID:
    default:                      return "Unknown";
    }
}

/*================================================================================================
@brief   Convert the LE server type to string
@details Convert the LE server type to string
@return  None
@retval  String of the LE server type
================================================================================================*/
const char* BLE_util_get_server_type_string
    (
    const BLE_server_type_e server_type
    )
{
switch( server_type )
    {
    case BLE_SERVER_MOTOCON:      return "Motocon";
    case BLE_SERVER_TYPE_INVALID:
    default:                      return "Unknown";
    }
}

#ifdef __cplusplus
}
#endif
