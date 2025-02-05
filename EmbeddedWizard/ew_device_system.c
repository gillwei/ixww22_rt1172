/*********************************************************************
* @file
* ew_device_system.c
*
* @brief
* EW module - system related device interface implementation
*
* Copyright 2020 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "ewrte.h"
#include "ew_bsp_inout.h"
#include "ew_bsp_clock.h"
#include "ew_bsp_event.h"
#include "ew_priv.h"
#include "DeviceInterface.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "EEPM_pub.h"
#include "GRM_pub_prj.h"
#include "PERIPHERAL_pub.h"
#include "RTC_pub.h"
#include "PM_pub.h"
#include "QR_pub.h"
#include "VI_pub.h"
#include "OTA_pub.h"
#include "BC_motocon_pub.h"
#include "client_dcm_appl.h"
#include "display_support.h"
#include "ew_tacho.h"

/*--------------------------------------------------------------------
                           LITERAL CONSTANTS
--------------------------------------------------------------------*/
#ifdef _DeviceInterfaceSystemDeviceClass_
    typedef int system_device_function( void );
#endif

#ifdef _DeviceInterfaceSystemDeviceClass__NotifySystemEventReceived_
    static int notify_system_event_received( void );
#endif

#ifdef _DeviceInterfaceSystemDeviceClass__TestDisplayPattern_
    static int ew_sytem_test_display_pattern( void );
#endif

#ifdef _DeviceInterfaceSystemDeviceClass__QuitTest_
    static int ew_system_quit_test( void );
#endif

#ifdef _DeviceInterfaceSystemDeviceClass__NotifyEsnRead_
    static int ew_system_notify_esn( void );
#endif

#ifdef _DeviceInterfaceSystemDeviceClass__StartBurnInTest_
    static int ew_start_burn_in_test( void );
#endif

#ifdef _DeviceInterfaceSystemDeviceClass__UpdateBurnInTestTime_
    static int ew_update_burn_in_test_time( void );
#endif

#ifdef _DeviceInterfaceSystemDeviceClass__ShowBurnInTestResult_
    static int ew_show_burn_in_test_result( void );
#endif

#ifdef _DeviceInterfaceSystemDeviceClass__NotifyInspectionRequest_
    static int ew_notify_inspection_mode_request( void );
#endif

#ifdef _DeviceInterfaceSystemDeviceClass__NotifyLastPageRead_
    static int ew_notify_last_page_read( void );
#endif

#define UPDATE_TIME_TASK_PRIORITY       ( tskIDLE_PRIORITY )
#define UPDATE_TIME_TASK_NAME           "time_task"
#define UPDATE_TIME_TASK_STACK_SIZE     ( configMINIMAL_STACK_SIZE )

#define EW_STRING_LEN               ( 1024 )
#define SYSTEM_EVENT_QUEUE_SIZE     ( 32 )

#define UNIT_ID_CCUID_IDX           ( 0 )
#define UNIT_ID_PASSKEY_IDX         ( UNIT_ID_CCUID_IDX + CCUID_LENGTH )
#define UNIT_ID_DUMMY_IDX           ( UNIT_ID_PASSKEY_IDX + PASSKEY_LENGTH )
#define UNIT_ID_SEGMENT1_READ_OK    ( 1 << 0 )
#define UNIT_ID_SEGMENT2_READ_OK    ( 1 << 1 )
#define UNIT_ID_SEGMENT3_READ_OK    ( 1 << 2 )
#define UNIT_ID_READ_OK             ( 0x7 )

#define FACTORY_TEST_EVENT_DISP_PATTERN         ( 1 << 0 )
#define FACTORY_TEST_EVENT_DISP_QUIT            ( 1 << 1 )
#define FACTORY_TEST_EVENT_BURNIN_START         ( 1 << 2 )
#define FACTORY_TEST_EVENT_BURNIN_TIME_UPDATE   ( 1 << 3 )
#define FACTORY_TEST_EVENT_BURNIN_RESULT        ( 1 << 4 )

#define EEPROM_READ_STATUS_OP_MODE              ( 1 << 0 )
#define EEPROM_READ_STATUS_LANGUAGE             ( 1 << 1 )
#define EEPROM_READ_STATUS_LAST_PAGE            ( 1 << 2 )
#define EEPROM_READ_STATUS_ESN                  ( 1 << 3 )

/*--------------------------------------------------------------------
                                 TYPES
--------------------------------------------------------------------*/
static void update_time_task_main( void* arg );
static void ew_get_info_from_eeprom( void );

/*--------------------------------------------------------------------
                           PROJECT INCLUDES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                           MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                               VARIABLES
--------------------------------------------------------------------*/
#ifdef _DeviceInterfaceSystemDeviceClass_
    static DeviceInterfaceSystemDeviceClass device_object = 0;
    system_device_function* const system_function_lookup_table[] =
        {
        #ifdef _DeviceInterfaceSystemDeviceClass__NotifySystemEventReceived_
            notify_system_event_received,
        #endif
        #ifdef _DeviceInterfaceSystemDeviceClass__TestDisplayPattern_
            ew_sytem_test_display_pattern,
        #endif
        #ifdef _DeviceInterfaceSystemDeviceClass__QuitTest_
            ew_system_quit_test,
        #endif
        #ifdef _DeviceInterfaceSystemDeviceClass__NotifyEsnRead_
            ew_system_notify_esn,
        #endif
        #ifdef _DeviceInterfaceSystemDeviceClass__StartBurnInTest_
            ew_start_burn_in_test,
        #endif
        #ifdef _DeviceInterfaceSystemDeviceClass__UpdateBurnInTestTime_
            ew_update_burn_in_test_time,
        #endif
        #ifdef _DeviceInterfaceSystemDeviceClass__ShowBurnInTestResult_
            ew_show_burn_in_test_result,
        #endif
        #ifdef _DeviceInterfaceSystemDeviceClass__NotifyInspectionRequest_
            ew_notify_inspection_mode_request,
        #endif
        #ifdef _DeviceInterfaceSystemDeviceClass__NotifyLastPageRead_
            ew_notify_last_page_read
        #endif
        };
    const int num_of_system_func = sizeof( system_function_lookup_table )/sizeof( system_device_function* );
    static QueueHandle_t system_rx_event_queue;

    static EnumHomeGroup      home_group;
    static EnumMeterDisplay   meter_display_setting;
    static EnumNavigationView navigation_view_setting;
    static int      factory_test_event = 0;
    static int      factory_test_disp_pattern_idx = 0;
    static bool     factory_test_burn_in_result = false;
    static uint32_t factory_test_burn_in_time_sec = 0;
    static TickType_t update_time_period_ticks = pdMS_TO_TICKS( UPDATE_TIME_PERIOD_MS );

    static bool     is_inspection_request_received = false;
    static EnumInspectionMode inspection_mode = 0;
    static EnumInspectionDisplay inspection_display_pattern = 0;

    static int is_esn_read = 0;
    static int is_qrcode_ready = 0;
    static EnumOperationMode operation_mode = EnumOperationModeNORMAL;
    static EnumOperationMode operation_mode_in_eep = EnumOperationModeNORMAL;
    static bool     is_running_production_test;
    static bool     is_tft_backlight_on;
    static bool     is_op_mode_ready;
    static bool     is_last_page_read;
    static bool     clk_auto_adj_status;
    static uint8_t  clk_auto_adj_status_in_eep = 0;
    static uint32_t eeprom_read_status = 0;
    static EnumLanguage      ew_language;
    static language_src_prority_e ew_language_src = LANGUAGE_SRC_PRIORITY_EEPROM;
#endif

static uint32_t esn;

static uint8_t  unit_id_plaintext[UNIT_ID_LENGTH];
static uint8_t  unit_id_ciphertext[UNIT_ID_LENGTH];
static uint8_t  unit_id_read_status;
static const uint8_t unit_id_decryption_transposition_table[UNIT_ID_LENGTH] =
    {3, 11, 8, 19, 22, 17, 6, 0, 14, 20, 10, 23, 4, 9, 1, 18, 12, 5, 21, 13, 2, 15, 7, 16};

AT_BOARDSDRAM_SECTION_ALIGN( uint8_t ew_string[EW_STRING_LEN], 32 );

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

/*********************************************************************
*
* @private
* ew_system_int
*
* Embedded Wizard system initialization
*
*********************************************************************/
void ew_system_int
    (
    void
    )
{
if( NULL == system_rx_event_queue )
    {
    system_rx_event_queue = xQueueCreate( SYSTEM_EVENT_QUEUE_SIZE, sizeof( EnumSystemRxEvent ) );
    configASSERT( NULL != system_rx_event_queue );
    }
}

/*********************************************************************
*
* @private
* ew_device_system_init
*
* Embedded Wizard system device interface initialization
*
*********************************************************************/
void ew_device_system_init
    (
    void
    )
{
#ifdef _DeviceInterfaceSystemDeviceClass_
     /*
       Get access to the counterpart of this device driver: get access to the
       device class that is created as autoobject within your Embedded Wizard
       project. For this purpose you can call the function EwGetAutoObject().
       This function contains two parameters: The pointer to the autoobject and
       the class of the autoobject.
       Assuming you have implemented the class 'DeviceClass' within the unit
       'Application' and you have an autoobject with the name 'Device', make
       the following call:
       EwGetAutoObject( &ApplicationDevice, ApplicationDeviceClass );
    */
    device_object = EwGetAutoObject( &DeviceInterfaceSystemDevice, DeviceInterfaceSystemDeviceClass );
    /*
       Once you have the access to the autoobject, lock it as long as you need
       the access (typically, until your device driver is closed). By locking
       the autoobject, you can ensure that the object of the device class will
       be kept within the memory and not freed by the Garbage Collector.
       Once the device class is locked, you can easily store it within a static
       variable to access the driver class during the runtime.
    */
    EwLockObject( device_object );

    // In order to blink the colon mark in the clock of the status bar,
    // create a task to notify EW with the accurate period of 500ms.
    BaseType_t result = xTaskCreate( update_time_task_main, UPDATE_TIME_TASK_NAME, UPDATE_TIME_TASK_STACK_SIZE, NULL, UPDATE_TIME_TASK_PRIORITY, NULL );
    configASSERT( pdPASS == result );

    ew_get_info_from_eeprom();
#endif
}

/*********************************************************************
*
* @private
* ew_device_system_deinit
*
* Embedded Wizard system device interface de-initialization
*
*********************************************************************/
void ew_device_system_deinit
    (
    void
    )
{
#ifdef _DeviceInterfaceSystemDeviceClass_
    if( device_object )
        {
        EwUnlockObject( device_object );
        }
    device_object = 0;
#endif
}

/*********************************************************************
*
* @private
* ew_device_system_proc
*
* Select the function from system function table and execute it.
*
*********************************************************************/
int ew_device_system_proc
    (
    void
    )
{
int need_update = 0;

#ifdef _DeviceInterfaceSystemDeviceClass_
    if( device_object == 0 ||
        num_of_system_func == 0 )
        {
        return 0;
        }

    for( int i = 0; i < num_of_system_func; i++ )
        {
        if( system_function_lookup_table[i]() )
            {
            need_update = 1;
            }
        }
#endif
return need_update;
}

/*********************************************************************
*
* @private
* update_time_task_main
*
* Main loop of the update time task
*
*********************************************************************/
static void update_time_task_main
    (
    void* arg
    )
{
TickType_t last_wake_ticks = xTaskGetTickCount();
static bool is_one_second = false;

while( 1 )
    {
    /* count in 500ms */
    NTF_update_active_call_duration();

    /* count in 1s */
    if( is_one_second )
        {
        VI_trip_time_count();
        }
    is_one_second = !is_one_second;

    vTaskDelayUntil( &last_wake_ticks, update_time_period_ticks );
    }
vTaskDelete( NULL );
}

/*********************************************************************
*
* @private
* ew_get_software_version
*
* Get software version
*
* @param version The pointer to the char buffer storing software version
*
*********************************************************************/
void ew_get_software_version
    (
    char* version
    )
{
int i = 0;
if( ( SW_VERSION / 1000 ) > 0 )
    {
    version[i++] = '0' + ( SW_VERSION / 1000 );
    }
version[i++] = '0' + ( SW_VERSION / 100 % 10 );
version[i++] = '.';
version[i++] = '0' + ( SW_VERSION % 100 / 10 );
version[i++] = '0' + ( SW_VERSION % 100 % 10 );
version[i]   = 0;
}

/*********************************************************************
*
* @private
* ew_system_set_language
*
* Set language
*
* @param lang_src_prority Language source priority
* @param language Language of EnumLanguage type
*
*********************************************************************/
void ew_system_set_language
    (
    const language_src_prority_e lang_src_prority,
    const EnumLanguage language
    )
{
/* To avoid the language setting from EEPROM overwriting the language setting from the smartphone,
   check priority before overwriting */
if( lang_src_prority >= ew_language_src )
    {
    if( ew_language != language )
        {
        ew_language = language;
        EW_notify_system_event_received( EnumSystemRxEventLANGUAGE_CHANGED );
        VI_set_tx_data( EnumVehicleTxTypeLANGUAGE, ew_language );
        }
    }
}

/*********************************************************************
*
* @private
* ew_set_last_page
*
* Set last page
*
* @param version The pointer to the char buffer storing software version
*
*********************************************************************/
void ew_set_last_page
    (
    const EnumHomeGroup      group,
    const EnumMeterDisplay   meter_disp_setting,
    const EnumNavigationView navi_view_setting
    )
{
PRINTF( "%s %d %d %d\r\n", __FUNCTION__, group, meter_disp_setting, navi_view_setting );
home_group = group;
meter_display_setting   = meter_disp_setting;
navigation_view_setting = navi_view_setting;
}

/*********************************************************************
*
* @private
* ew_get_last_home_group
*
* Get last home group
*
* @return Last page of uint8_t type
*
*********************************************************************/
EnumHomeGroup ew_get_last_home_group
    (
    void
    )
{
return home_group;
}

/*********************************************************************
*
* @private
* ew_get_meter_display_setting
*
* Get meter display setting
*
* @return Meter display setting
*
*********************************************************************/
EnumMeterDisplay ew_get_meter_display_setting
    (
    void
    )
{
return meter_display_setting;
}

/*********************************************************************
*
* @private
* ew_get_navigation_view_setting
*
* Get navigation view setting
*
* @return Navigation view setting
*
*********************************************************************/
EnumNavigationView ew_get_navigation_view_setting
    (
    void
    )
{
return navigation_view_setting;
}

/*********************************************************************
*
* @private
* decrypt_with_transposition_cipher
*
* Decrypt with transposition cipher.
*
* @param ciphertext  Pointer to the ciphertext buffer
* @param text_length Text length of plaintext and ciphertext
* @param plaintext   Pointer to the plaintext buffer
*
*********************************************************************/
static void decrypt_with_transposition_cipher
    (
    const uint8_t* ciphertext,
    const uint32_t start_idx,
    const uint32_t end_idx,
    uint8_t* plaintext
    )
{
for( int i = start_idx; i <= end_idx; i++ )
    {
    plaintext[unit_id_decryption_transposition_table[i]] = ciphertext[i - start_idx];
    }
}

/*********************************************************************
*
* @private
* generate_unit_id_qrcode
*
* Generate QR code of UNIT ID
*
*********************************************************************/
static void generate_unit_id_qrcode
    (
    void
    )
{
bool    is_unit_id_empty = true;
uint8_t qrcode_text[UNIT_ID_LENGTH + 1];

/* If the unit id is not written in EERPOM, it would be all 0xFF */
for( int32_t i = 0; i < UNIT_ID_LENGTH; i++ )
    {
    if( EEPROM_INVALID_VAL_1_BYTE != unit_id_plaintext[i] )
        {
        is_unit_id_empty = false;
        }
    }

if( !is_unit_id_empty )
    {
    memcpy( qrcode_text, unit_id_ciphertext, UNIT_ID_LENGTH );
    qrcode_text[UNIT_ID_LENGTH] = '\0';
    QR_generate( qrcode_text, UNIT_ID_LENGTH );
    }
else
    {
    PRINTF( "empty unit id\r\n" );
    }
}

/*********************************************************************
*
* @private
* EW_read_esn_callback
*
* Callback of reading ESN
*
* @param result True if read success. False if read fail.
* @param value The pointer to the ESN of uint32_t* type.
*
*********************************************************************/
void EW_read_esn_callback
    (
    bool  result,
    void* value
    )
{
esn = *(uint32_t*)value;
if( EEPROM_INVALID_VAL_4_BYTE != esn )
    {
    is_esn_read = 1;
    }
eeprom_read_status |= EEPROM_READ_STATUS_ESN;
}

/*********************************************************************
*
* @public
* EW_read_unit_id_segment1_callback
*
* Callback of reading UNIT ID from EEPROM
*
* @param result True if read success. False if read fail.
* @param value The pointer to the 1-8 digits of unit id
*
*********************************************************************/
void EW_read_unit_id_segment1_callback
    (
    bool  result,
    void* value
    )
{
if( result )
    {
    unit_id_read_status |= UNIT_ID_SEGMENT1_READ_OK;
    memcpy( &unit_id_ciphertext[0], (uint8_t*)value, 8 );
    decrypt_with_transposition_cipher( (uint8_t*)value, 0, 7, unit_id_plaintext );
    }
else
    {
    PRINTF( "rd unit id 1 fail\r\n" );
    }
}

/*********************************************************************
*
* @public
* EW_read_unit_id_segment2_callback
*
* Callback of reading UNIT ID from EEPROM
*
* @param result True if read success. False if read fail.
* @param value The pointer to the 9-16 digits of unit id
*
*********************************************************************/
void EW_read_unit_id_segment2_callback
    (
    bool  result,
    void* value
    )
{
if( result )
    {
    unit_id_read_status |= UNIT_ID_SEGMENT2_READ_OK;
    memcpy( &unit_id_ciphertext[8], (uint8_t*)value, 8 );
    decrypt_with_transposition_cipher( (uint8_t*)value, 8, 15, unit_id_plaintext );
    }
else
    {
    PRINTF( "rd unit id 2 fail\r\n" );
    }
}

/*********************************************************************
*
* @public
* EW_read_unit_id_segment3_callback
*
* Callback of reading UNIT ID from EEPROM
*
* @param result True if read success. False if read fail.
* @param value The pointer to the 17-24 digits of unit id
*
*********************************************************************/
void EW_read_unit_id_segment3_callback
    (
    bool  result,
    void* value
    )
{
if( result )
    {
    unit_id_read_status |= UNIT_ID_SEGMENT3_READ_OK;
    memcpy( &unit_id_ciphertext[16], (uint8_t*)value, 8 );
    decrypt_with_transposition_cipher( (uint8_t*)value, 16, 23, unit_id_plaintext );

    if( UNIT_ID_READ_OK == unit_id_read_status )
        {
        EW_notify_system_event_received( EnumSystemRxEventUNIT_ID_READ_OK );
        }
    }
else
    {
    PRINTF( "rd unit id 3 fail\r\n" );
    }
}

/*********************************************************************
*
* @public
* EW_get_last_page_callback
*
* Callback of reading last page from EEPROM
*
* @param result True if read success. False if read fail.
* @param value Pointer to the last page of uint8_t* type
*
*********************************************************************/
void EW_get_last_page_callback
    (
    bool  result,
    void* value
    )
{
if( result )
    {
    uint8_t last_page = *(uint8_t*)value;
    PRINTF( "rd last page 0x%x\r\n", last_page );
    if( EEPROM_INVALID_VAL_1_BYTE != last_page )
        {
        home_group = ( last_page >> LAST_PAGE_HOME_GROUP_SHIFT ) & LAST_PAGE_HOME_GROUP_MASK;
        navigation_view_setting = ( last_page >> LAST_PAGE_NAVI_SETTING_SHIFT ) & LAST_PAGE_NAVIGATION_SETTING_MASK;
        meter_display_setting   = last_page & LAST_PAGE_METER_DISP_SETTING_MASK;
        is_last_page_read = true;
        }
    }
else
    {
    PRINTF( "rd last page fail\r\n" );
    }
}

/*********************************************************************
*
* @public
* EW_get_language_callback
*
* Callback of reading language setting from EEPROM
*
* @param result True if read success. False if read fail.
* @param value Pointer to the last page of uint8_t* type
*
*********************************************************************/
void EW_get_language_callback
    (
    bool  result,
    void* value
    )
{
if( result )
    {
    uint8_t language = *(uint8_t*)value;
    PRINTF( "rd lang %d\r\n", language );
    if( EnumLanguageTOTAL > language )
        {
        ew_system_set_language( LANGUAGE_SRC_PRIORITY_EEPROM, language );
        }
    eeprom_read_status |= EEPROM_READ_STATUS_LANGUAGE;
    }
else
    {
    PRINTF( "rd last page fail\r\n" );
    }
}

/*********************************************************************
*
* @public
* EW_read_operation_mode_callback
*
* Callback of reading operation mode from EEPROM
*
* @param result True if read success. False if read fail.
* @param value The pointer to the operation of uint8_t* type
*
*********************************************************************/
void EW_read_operation_mode_callback
    (
    bool  result,
    void* value
    )
{
if( result )
    {
    operation_mode_in_eep = *(uint8_t*)value;
    PRINTF( "rd op mode 0x%x\r\n", operation_mode_in_eep );

    if( EEPROM_INVALID_VAL_1_BYTE == operation_mode_in_eep )
        {
        operation_mode_in_eep = EnumOperationModeFACTORY;
        }
    else if( EnumOperationModeTOTAL <= operation_mode_in_eep )
        {
        operation_mode_in_eep = EnumOperationModeNORMAL;
        }
    else
        {
        // empty
        }
    }
else
    {
    PRINTF( "rd op mode fail\r\n" );
    }

ew_set_operation_mode( operation_mode_in_eep );
is_op_mode_ready = true;
eeprom_read_status |= EEPROM_READ_STATUS_OP_MODE;
}

/*********************************************************************
*
* @public
* EW_get_clock_auto_adj_callback
*
* Callback of reading clock auto adjustment status from EEPROM
*
* @param result True if read success. False if read fail.
* @param value Pointer to the clock auto adjustment status of uint8_t* type
*
*********************************************************************/
void EW_get_clock_auto_adj_callback
    (
    bool  result,
    void* value
    )
{
if( result )
    {
    clk_auto_adj_status_in_eep = *(uint8_t*)value;
    PRINTF( "rd clk auto adj 0x%x\r\n", clk_auto_adj_status_in_eep );
    if( EEPROM_INVALID_VAL_1_BYTE == clk_auto_adj_status_in_eep )
        {
        clk_auto_adj_status_in_eep = DEFAULT_CLK_AUTO_ADJUSTMENT;
        }
    clk_auto_adj_status = (bool)clk_auto_adj_status_in_eep;
    }
else
    {
    PRINTF( "rd clock auto status fail\r\n" );
    }
}

/*********************************************************************
*
* @private
* ew_get_esn
*
* Get ESN from EEPROM.
*
*********************************************************************/
void ew_get_esn
    (
    void
    )
{
#ifdef _DeviceInterfaceSystemDeviceClass_
if( pdFALSE == EEPM_get_ESN( &EW_read_esn_callback ) )
    {
    EwPrint( "%s false\r\n", __FUNCTION__ );
    }
#endif
}

/*********************************************************************
*
* @private
* ew_get_info_from_eeprom
*
* Get info from EEPROM
*
*********************************************************************/
static void read_unit_id_from_eeprom
    (
    void
    )
{
unit_id_read_status = 0;

if( pdFALSE == EEPM_get_qrcode_fused_data_1( &EW_read_unit_id_segment1_callback ) ||
    pdFALSE == EEPM_get_qrcode_fused_data_2( &EW_read_unit_id_segment2_callback ) ||
    pdFALSE == EEPM_get_qrcode_fused_data_3( &EW_read_unit_id_segment3_callback ) )
    {
    EwPrint( "rd unit id fail\r\n" );
    }
}

/*********************************************************************
*
* @private
* ew_get_info_from_eeprom
*
* Get info from EEPROM
*
*********************************************************************/
static void ew_get_info_from_eeprom
    (
    void
    )
{
if( pdFALSE == EEPM_get_operation_mode( &EW_read_operation_mode_callback ) )
    {
    EwPrint( "get op mode fail\r\n" );
    }
if( pdFALSE == EEPM_get_ESN( &EW_read_esn_callback ) )
    {
    EwPrint( "get esn fail\r\n" );
    }

read_unit_id_from_eeprom();

if( pdFALSE == EEPM_get_last_page( &EW_get_last_page_callback ) )
    {
    EwPrint( "get last page err\r\n" );
    }
if( pdFALSE == EEPM_get_language( &EW_get_language_callback ) )
    {
    EwPrint( "get lang err\r\n" );
    }
if( pdFALSE == EEPM_get_clk_auto_adjustment( &EW_get_clock_auto_adj_callback ) )
    {
    EwPrint( "get clk auto adj err\r\n" );
    }
}

/*********************************************************************
*
* @private
* ew_get_rtc_time
*
* Get RTC time
*
* @param srtc_datetime The pointer to the rtc datetime
*
*********************************************************************/
void ew_get_rtc_time
    (
    snvs_lp_srtc_datetime_t* srtc_datetime
    )
{
RTC_get_datetime( srtc_datetime );
}

/*********************************************************************
*
* @private
* ew_set_rtc_time
*
* Set RTC time
*
* @param srtc_datetime The pointer to the rtc datetime
*
*********************************************************************/
void ew_set_rtc_time
    (
    snvs_lp_srtc_datetime_t* srtc_datetime
    )
{
RTC_set_dateTime( srtc_datetime );
}

/*********************************************************************
*
* @private
* EW_get_clk_auto_adj
*
* Get clock auto adjustment status
*
* @return status of clock auto adjustment setting
*
*********************************************************************/
bool EW_get_clk_auto_adj
    (
    void
    )
{
PRINTF( "%s %d\r\n", __FUNCTION__, clk_auto_adj_status );
return clk_auto_adj_status ? true : false;
}

/*********************************************************************
*
* @private
* ew_set_clk_auto_adj
*
* Set clock auto adjustment status
*
* @param is_clk_auto_adj clock auto adjustment status
*
*********************************************************************/
void ew_set_clk_auto_adj
    (
    bool is_clk_auto_adj
    )
{
PRINTF( "%s %d\r\n", __FUNCTION__, is_clk_auto_adj );
uint8_t auto_adj = 0;

if( is_clk_auto_adj )
    {
    auto_adj = 1;
    }

if( pdFALSE == EEPM_set_clk_auto_adjustment( auto_adj, NULL ) )
    {
    EwPrint( "set clk auto adjustment err\r\n" );
    }
else
    {
    clk_auto_adj_status = auto_adj;
    }
}

/*********************************************************************
*
* @private
* ew_is_debug_build
*
* Return if the current build is debug build
*
* @retVal true if debug build; false if release build
*
*********************************************************************/
XBool ew_is_debug_build
    (
    void
    )
{
#ifdef NDEBUG
    return false;
#else
    return true;
#endif
}

/*********************************************************************
*
* @private
* ew_handle_special_characters
*
* Stuff '%' before '%', '^', '~'
*
* @param in_str Pointer to input string
* @param out Pointer to output string
* @return Length of the output string
*
*********************************************************************/
int ew_handle_special_characters
    (
    const uint8_t* in_str,
    uint8_t**      out_str
    )
{
int i = 0;
int ew_str_idx = 0;

while( 1 )
    {
    if( '\0' == in_str[i] )
        {
        break;
        }

    if( ( '%' == in_str[i] ) ||
        ( '^' == in_str[i] ) ||
        ( '~' == in_str[i] ) )
        {
        ew_string[ew_str_idx++] = '%';
        }
    ew_string[ew_str_idx++] = in_str[i++];

    if( EW_STRING_LEN == ew_str_idx )
        {
        ew_string[EW_STRING_LEN - 1] = '\0';
        break;
        }
    }

if( 0 < ew_str_idx )
    {
    *out_str = ew_string;
    }

return ew_str_idx;
}

/*********************************************************************
*
* @private
* set_language_from_phone
*
* Set language from the smartphone
*
*********************************************************************/
static void set_language_from_phone
    (
    void
    )
{
uint8_t phone_language = BC_motocon_get_language_type();
EnumLanguage language;

switch( phone_language )
    {
    case BC_MOTOCON_LANGUAGE_ENGLISH_US:
        language = EnumLanguageENGLISH;
        break;
    case BC_MOTOCON_LANGUAGE_FRENCH_FRA:
        language = EnumLanguageFRENCH;
        break;
    case BC_MOTOCON_LANGUAGE_GERMAN:
        language = EnumLanguageGERMAN;
        break;
    case BC_MOTOCON_LANGUAGE_ITALIAN:
        language = EnumLanguageITALIAN;
        break;
    case BC_MOTOCON_LANGUAGE_JAPANESE:
        language = EnumLanguageJAPANESE;
        break;
    case BC_MOTOCON_LANGUAGE_SPANISH_INTL:
        language = EnumLanguageSPANISH;
        break;
    case BC_MOTOCON_LANGUAGE_TRADITIONAL_CHINESE:
        language = EnumLanguageTRADITIONAL_CHINESE;
        break;
    case BC_MOTOCON_LANGUAGE_SIMPLIFIED_CHINESE:
        language = EnumLanguageSIMPLIFIED_CHINESE;
        break;
    case BC_MOTOCON_LANGUAGE_GREEK:
        language = EnumLanguageGREEK;
        break;
    case BC_MOTOCON_LANGUAGE_FINNISH:
        language = EnumLanguageFINNISH;
        break;
    case BC_MOTOCON_LANGUAGE_HINDI:
        language = EnumLanguageHINDI;
        break;
    case BC_MOTOCON_LANGUAGE_INDONESIAN:
        language = EnumLanguageINDONESIAN;
        break;
    case BC_MOTOCON_LANGUAGE_POLISH:
        language = EnumLanguagePOLISH;
        break;
    case BC_MOTOCON_LANGUAGE_PORTUGUESE:
        language = EnumLanguagePORTUGUESE_BRAZIL;
        break;
    case BC_MOTOCON_LANGUAGE_THAI:
        language = EnumLanguageTHAI;
        break;
    case BC_MOTOCON_LANGUAGE_VIETNAMESE:
        language = EnumLanguageVIETNAMESE;
        break;
    case BC_MOTOCON_LANGUAGE_KOREAN:
        language = EnumLanguageKOREAN;
        break;
    case BC_MOTOCON_LANGUAGE_MALAY:
        language = EnumLanguageMALAY;
        break;
    default:
        language = EnumLanguageENGLISH;
        break;
    }

    ew_system_set_language( LANGUAGE_SRC_PRIORITY_PHONE, language );
}

/*********************************************************************
*
* @private
* notify_system_event_received
*
* Notify EW GUI the received system event
*
*********************************************************************/
#ifdef _DeviceInterfaceSystemDeviceClass__NotifySystemEventReceived_
static int notify_system_event_received
    (
    void
    )
{
int need_update = 0;

EnumSystemRxEvent system_rx_event;
while( pdPASS == xQueueReceive( system_rx_event_queue, &system_rx_event, 0 ) )
    {
    switch( system_rx_event )
        {
        case EnumSystemRxEventPHONE_LANGUAGE_RECEIVED:
            set_language_from_phone();
            break;
        case EnumSystemRxEventUNIT_ID_UPDATED:
            read_unit_id_from_eeprom();
            break;
        case EnumSystemRxEventUNIT_ID_READ_OK:
            generate_unit_id_qrcode();
            break;
        default:
            DeviceInterfaceSystemDeviceClass__NotifySystemEventReceived( device_object, system_rx_event );
            need_update = 1;
            break;
        }
    }
return need_update;
}
#endif

/*********************************************************************
*
* @private
* ew_sytem_test_display_pattern
*
* Notify EW GUI to show display test pattern
*
*********************************************************************/
#ifdef _DeviceInterfaceSystemDeviceClass__TestDisplayPattern_
    static int ew_sytem_test_display_pattern
        (
        void
        )
    {
    int need_update = 0;
    if( factory_test_event & FACTORY_TEST_EVENT_DISP_PATTERN )
        {
        factory_test_event &= ~FACTORY_TEST_EVENT_DISP_PATTERN;
        DeviceInterfaceSystemDeviceClass__TestDisplayPattern( device_object, factory_test_disp_pattern_idx );
        need_update = 1;
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_system_quit_test
*
* Notify EW GUI to quit test
*
*********************************************************************/
#ifdef _DeviceInterfaceSystemDeviceClass__QuitTest_
    static int ew_system_quit_test
        (
        void
        )
    {
    int need_update = 0;
    if( factory_test_event & FACTORY_TEST_EVENT_DISP_QUIT )
        {
        factory_test_event &= ~FACTORY_TEST_EVENT_DISP_QUIT;
        DeviceInterfaceSystemDeviceClass_QuitTest( device_object );

        is_running_production_test = false;
        ew_set_operation_mode( operation_mode_in_eep );

        need_update = 1;
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_start_burn_in_test
*
* Notify EW GUI to start burn in test
*
*********************************************************************/
#ifdef _DeviceInterfaceSystemDeviceClass__StartBurnInTest_
    static int ew_start_burn_in_test
        (
        void
        )
    {
    int need_update = 0;
    if( factory_test_event & FACTORY_TEST_EVENT_BURNIN_START )
        {
        factory_test_event &= ~FACTORY_TEST_EVENT_BURNIN_START;
        DeviceInterfaceSystemDeviceClass_StartBurnInTest( device_object );
        need_update = 1;
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_start_burn_in_test
*
* Notify EW GUI to update burn in test time
*
*********************************************************************/
#ifdef _DeviceInterfaceSystemDeviceClass__UpdateBurnInTestTime_
    static int ew_update_burn_in_test_time
        (
        void
        )
    {
    int need_update = 0;
    if( factory_test_event & FACTORY_TEST_EVENT_BURNIN_TIME_UPDATE )
        {
        factory_test_event &= ~FACTORY_TEST_EVENT_BURNIN_TIME_UPDATE;
        DeviceInterfaceSystemDeviceClass_UpdateBurnInTestTime( device_object, factory_test_burn_in_time_sec );
        need_update = 1;
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_start_burn_in_test
*
* Notify EW GUI to update burn in test time
*
*********************************************************************/
#ifdef _DeviceInterfaceSystemDeviceClass__ShowBurnInTestResult_
    static int ew_show_burn_in_test_result
        (
        void
        )
    {
    int need_update = 0;
    if( factory_test_event & FACTORY_TEST_EVENT_BURNIN_RESULT )
        {
        factory_test_event &= ~FACTORY_TEST_EVENT_BURNIN_RESULT;
        DeviceInterfaceSystemDeviceClass_ShowBurnInTestResult( device_object, factory_test_burn_in_result );
        need_update = 1;
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_system_notify_esn
*
* Notify EW GUI to quit test
*
*********************************************************************/
#ifdef _DeviceInterfaceSystemDeviceClass__NotifyEsnRead_
    static int ew_system_notify_esn
        (
        void
        )
    {
    int need_update = 0;
    if( is_esn_read )
        {
        is_esn_read = 0;
        char esn_decimal[ESN_STR_MAX_LEN + 1];
        sprintf( esn_decimal, "%u", esn );
        XString esn_str = EwNewStringAnsi( esn_decimal );
        DeviceInterfaceSystemDeviceClass__NotifyEsnRead( device_object, esn_str );
        need_update = 1;
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_reboot_system
*
* Device interface to trigger system reboot
*
*********************************************************************/
void ew_reboot_system
    (
    void
    )
{
PM_system_reset();
}

/*********************************************************************
*
* @private
* ew_set_operation_mode
*
* Set operation mode
*
* @param mode Operation mode of EnumOperationMode type
*
*********************************************************************/
void ew_set_operation_mode
    (
    EnumOperationMode mode
    )
{
PRINTF( "%s %d\r\n", __FUNCTION__, mode );
EnumOperationMode last_operation_mode = operation_mode;

switch( mode )
    {
    case EnumOperationModeNORMAL:
    case EnumOperationModeFACTORY:
        if( operation_mode_in_eep != mode )
            {
            EEPM_set_operation_mode( mode, NULL );
            }

        if( !is_running_production_test )
            {
            operation_mode = mode;
            if( EnumOperationModePRODUCTION_TEST == last_operation_mode )
                {
                EW_notify_opening_event( OPENING_EVENT_OP_MODE_READY );
                }

            if( EnumOperationModeFACTORY == last_operation_mode &&
                EnumOperationModeNORMAL == mode )
                {
                uint32_t tft_duty;
                VI_get_rx_data_uint( EnumVehicleRxTypeTFT_DUTY, &tft_duty );
                DISP_update_tft_brightness( (uint8_t)( tft_duty * TFT_DUTY_FACTOR ) );
                }
            }
        break;

    case EnumOperationModeINSPECTION:
        if( EnumOperationModeFACTORY == operation_mode )
            {
            operation_mode = mode;
            }
        break;

    case EnumOperationModePRODUCTION_TEST:
        is_running_production_test = true;
        operation_mode = mode;
        break;

    default:
        PRINTF( "%s invalid %d\r\n", __FUNCTION__, mode );
        break;
    }

if( last_operation_mode != operation_mode )
    {
    client_appl_operation_mode_switch();
    }
}

/*********************************************************************
*
* @private
* EW_get_operation_mode
*
* Get current operation mode
*
* @param mode Pointer to operation mode
* @return True if operation mode from EEPROM is ready
*
*********************************************************************/
bool EW_get_operation_mode
    (
    EnumOperationMode* mode
    )
{
*mode = operation_mode;
return is_op_mode_ready;
}

/*********************************************************************
*
* @private
* ew_is_operation_mode_ready
*
* Check if the operation mode is read from EEPROM
*
* @return True if the operation mode is read from EEPROM
*
*********************************************************************/
bool ew_is_operation_mode_ready
    (
    void
    )
{
PRINTF( "%s %d\r\n", __FUNCTION__, operation_mode );
return is_op_mode_ready;
}

/*********************************************************************
*
* @public
* EW_get_esn
*
* Get ESN
*
* @return ESN
*
*********************************************************************/
uint32_t EW_get_esn
    (
    void
    )
{
PRINTF( "%s\r\n", __FUNCTION__ );
return esn;
}

/*********************************************************************
*
* @private
* is_eeprom_data_valid
*
* Check if data read from EEPROM is valid
*
* @param data Pointer to data
* @param length Data length
*
*********************************************************************/
static bool is_eeprom_data_valid
    (
    const uint8_t* data,
    const uint32_t length
    )
{
bool valid = false;
for( int32_t i = 0; i < length; i++ )
    {
    if( EEPROM_INVALID_VAL_1_BYTE != data[i] )
        {
        valid = true;
        }
    }
return valid;
}

/*********************************************************************
*
* @private
* EW_get_unit_id_ccuid
*
* Get CCUID
*
* @param Pointer to CCUID
* @return CCUID valid status
*
*********************************************************************/
bool EW_get_unit_id_ccuid
    (
    uint8_t** ccuid
    )
{
bool valid = false;
if( UNIT_ID_READ_OK == unit_id_read_status )
    {
    *ccuid = &unit_id_plaintext[UNIT_ID_CCUID_IDX];
    valid = is_eeprom_data_valid( &unit_id_plaintext[UNIT_ID_CCUID_IDX], CCUID_LENGTH );
    }
return valid;
}

/*********************************************************************
*
* @private
* EW_get_unit_id_passkey
*
* Get UNIT ID passkey
*
* @param Pointer to passkey
* @return Passkey valid status
*
*********************************************************************/
bool EW_get_unit_id_passkey
    (
    uint8_t** passkey
    )
{
bool valid = false;
if( UNIT_ID_READ_OK == unit_id_read_status )
    {
    *passkey = &unit_id_plaintext[UNIT_ID_PASSKEY_IDX];
    valid = is_eeprom_data_valid( &unit_id_plaintext[UNIT_ID_PASSKEY_IDX], PASSKEY_LENGTH );
    }
return valid;
}

/*********************************************************************
*
* @private
* EW_get_unit_id_dummy
*
* Get UNIT ID dummy
*
* @param Pointer to dummy
* @return dummy valid status
*
*********************************************************************/
bool EW_get_unit_id_dummy
    (
    uint8_t** dummy
    )
{
bool result = false;
if( UNIT_ID_READ_OK == unit_id_read_status )
    {
    *dummy = &unit_id_plaintext[UNIT_ID_DUMMY_IDX];
    result = true;
    }
return result;
}

/*********************************************************************
*
* @private
* ew_notify_vi_dd_mode_state_changed
*
* Notify EW GUI the inspection mode request
*
*********************************************************************/
#ifdef _DeviceInterfaceSystemDeviceClass__NotifyInspectionRequest_
    static int ew_notify_inspection_mode_request
        (
        void
        )
    {
    int need_update = 0;
    if( is_inspection_request_received )
        {
        is_inspection_request_received = false;
        DeviceInterfaceSystemDeviceClass__NotifyInspectionRequest( device_object, inspection_mode, inspection_display_pattern );
        need_update = 1;
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @private
* ew_notify_last_page_read
*
* Notify EW UI the last page has been read from EEPROM
*
*********************************************************************/
#ifdef _DeviceInterfaceSystemDeviceClass__NotifyLastPageRead_
    static int ew_notify_last_page_read
        (
        void
        )
    {
    int need_update = 0;
    if( is_last_page_read )
        {
        is_last_page_read = false;
        DeviceInterfaceSystemDeviceClass__NotifyLastPageRead( device_object );
        need_update = 1;
        }
    return need_update;
    }
#endif

/*********************************************************************
*
* @public
* EW_test_display_pattern
*
* Request Embedded Wizard to show display pattern
*
* @param index The display test pattern index
*
*********************************************************************/
void EW_test_display_pattern
    (
    int index
    )
{
#ifdef _DeviceInterfaceSystemDeviceClass_
    ew_set_operation_mode( EnumOperationModePRODUCTION_TEST );
    factory_test_disp_pattern_idx = index;
    factory_test_event |= FACTORY_TEST_EVENT_DISP_PATTERN;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_quit_test
*
* Request Embedded Wizard to quit test
*
*********************************************************************/
void EW_quit_test
    (
    void
    )
{
#ifdef _DeviceInterfaceSystemDeviceClass_
    factory_test_event |= FACTORY_TEST_EVENT_DISP_QUIT;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_start_burn_in
*
* Start Embedded Wizard burn-in UI
*
*********************************************************************/
void EW_start_burn_in
    (
    void
    )
{
#ifdef _DeviceInterfaceSystemDeviceClass_
    PRINTF( "%s\r\n", __FUNCTION__ );
    ew_set_operation_mode( EnumOperationModePRODUCTION_TEST );
    factory_test_event |= FACTORY_TEST_EVENT_BURNIN_START;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_update_burn_in_time
*
* Update burn in test time
*
* @param time_sec The burn-in time in second
*
*********************************************************************/
void EW_update_burn_in_time
    (
    const uint32_t time_sec
    )
{
#ifdef _DeviceInterfaceSystemDeviceClass_
    factory_test_burn_in_time_sec = time_sec;
    factory_test_event |= FACTORY_TEST_EVENT_BURNIN_TIME_UPDATE;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_show_burn_in_result
*
* Show burn-in test result
*
* @param result The burn-in test result
*
*********************************************************************/
void EW_show_burn_in_result
    (
    const bool result
    )
{
#ifdef _DeviceInterfaceSystemDeviceClass_
    factory_test_burn_in_result = result;
    factory_test_event |= FACTORY_TEST_EVENT_BURNIN_RESULT;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @private
* start_opening
*
* Start opening
*
*********************************************************************/
static void start_opening
    (
    void
    )
{
PRINTF( "%s\r\n", __FUNCTION__ );
#ifdef _DeviceInterfaceSystemDeviceClass__StartOpening_
    DeviceInterfaceSystemDeviceClass__StartOpening( device_object );
#endif
}

/*********************************************************************
*
* @private
* ew_start_ota
*
* Start OTA
*
*********************************************************************/
void ew_start_ota
    (
    void
    )
{
PRINTF( "%s\r\n", __FUNCTION__ );

bc_motocon_ota_update_info_t* ota_info = BC_motocon_get_ota_update_info();
OTA_set_update_packet( ota_info->enable, ota_info->new_firmware_ver, ota_info->total_size, ota_info->number_of_packages );
OTA_jump_to_bootloader();
}

/*********************************************************************
*
* @public
* EW_notify_opening_event
*
* Start opening if both TFT backlight is on and operation mode is ready
*
* @param event TFT backlight on or operation mode ready event
*
*********************************************************************/
void EW_notify_opening_event
    (
    const opening_event event
    )
{
PRINTF( "%s %d\r\n", __FUNCTION__, event );
if( OPENING_EVENT_TFT_BACKLIGHT_ON == event )
    {
    is_tft_backlight_on = true;
    }

if( is_tft_backlight_on && is_op_mode_ready )
    {
    start_opening();
    VI_set_tx_data( EnumVehicleTxTypeSYSTEM_STATUS_READY, 0 );
    }
}

/*********************************************************************
*
* @public
* EW_notify_inspection_request
*
* Notify Embedded Wizard inspection request
* @param mode Inspection mode
* @param display_pattern Inspection display pattern
*
*********************************************************************/
void EW_notify_inspection_request
    (
    EnumInspectionMode    mode,
    EnumInspectionDisplay display_pattern
    )
{
#ifdef _DeviceInterfaceSystemDeviceClass_
    inspection_mode = mode;
    inspection_display_pattern = display_pattern;
    is_inspection_request_received = true;
    EwBspEventTrigger();
#endif
}

/*********************************************************************
*
* @public
* EW_notify_software_event_received
*
* Enqueue the received system event
*
* @param system_rx_event Received system event
*
*********************************************************************/
void EW_notify_system_event_received
    (
    const EnumSystemRxEvent system_rx_event
    )
{
if( EnumSystemRxEventQRCODE_READY == system_rx_event )
    {
    is_qrcode_ready = true;
    }

if( pdTRUE == xQueueSend( system_rx_event_queue, &system_rx_event, 0 ) )
    {
    EwBspEventTrigger();
    }
else
    {
    EwPrint( "%s err\r\n", __FUNCTION__ );
    }
}

/*********************************************************************
*
* @private
* ew_send_system_command
*
* Enqueue the received system event
*
* @param system_rx_event Received system event
*
*********************************************************************/
void ew_send_system_command
    (
    const EnumSystemTxCmd command
    )
{
switch( command )
    {
    case EnumSystemTxCmdENABLE_TFT_BRIGHTNESS_MANUAL_ADJ:
        DISP_set_tft_brightness_manual_adjustment( true );
        break;
    case EnumSystemTxCmdDISABLE_TFT_BRIGHTNESS_MANUAL_ADJ:
        DISP_set_tft_brightness_manual_adjustment( false );
        break;
    case EnumSystemTxCmdADJ_TFT_BRIGHTNESS_LEVEL_UP:
        DISP_adjust_tft_brightness_level_up();
        break;
    case EnumSystemTxCmdADJ_TFT_BRIGHTNESS_LEVEL_DOWN:
        DISP_adjust_tft_brightness_level_down();
        break;
    default:
        break;
    }
}

/*********************************************************************
*
* @private
* ew_system_get_status
*
* Return the system status
*
* @param status_type System status type
*
*********************************************************************/
int32_t ew_system_get_status
    (
    const EnumSystemStatus status_type
    )
{
int32_t status;

switch( status_type )
    {
    case EnumSystemStatusLANGUAGE:
        status = ew_language;
        break;
    case EnumSystemStatusIS_TFT_BRIGHTNESS_LEVEL_MAX:
        status = DISP_is_current_tft_brighness_level_max();
        break;
    case EnumSystemStatusIS_TFT_BRIGHTNESS_LEVEL_MIN:
        status = DISP_is_current_tft_brighness_level_min();
        break;
    case EnumSystemStatusIS_TFT_DERATING_ON:
        status = DISP_is_tft_derating_on();
        break;
    case EnumSystemStatusIS_QRCODE_READY:
        status = is_qrcode_ready;
    case EnumSystemStatusTACHO_FULLSCALE:
        status = ew_tacho_get_fullscale();
        break;
    case EnumSystemStatusTACHO_REDZONE_BEGIN:
        status = ew_tacho_get_readzone_begin();
        break;
    default:
        break;
    }

return status;
}
