/*********************************************************************
* @file
* qr_main.c
*
* @brief
* QR code module
*
* Copyright 2020 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "event_groups.h"
#include "task.h"
#include "ewrte.h"
#include <stdio.h>
#include <string.h>
#include "semphr.h"
#include "fsl_debug_console.h"
#include "ricmoo_qrcode/qrcode.h"
#include "QR_pub.h"
#include "EW_pub.h"

/*--------------------------------------------------------------------
                           LITERAL CONSTANTS
--------------------------------------------------------------------*/
#define QRCODE_VERSION              ( 2 )   /* version 2 */
#define QRCODE_V2_MODULE_NUM        ( 25 )  /* number of modules for version 2 */
#define QRCODE_BUF_SIZE_BYTE        ( 640 ) /* (25*25) alignment 32 */

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
AT_BOARDSDRAM_SECTION( uint8_t qrcode_modules[QRCODE_BUF_SIZE_BYTE] );
static qrcode_buf_handle_struct qrcode_buf_handle;

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

/*********************************************************************
*
* @public
* QR_generate_qrcode
*
* Generate QR code of the text
*
* @param text Text to generate QR code
* @param text_size Text length not including NULL terminator
*
*********************************************************************/
void QR_generate
    (
    uint8_t* text,
    const uint32_t text_length
    )
{
QRCode  qrcode;
uint8_t modules[qrcode_getBufferSize( QRCODE_VERSION )];

qrcode_buf_handle.module_num = QRCODE_V2_MODULE_NUM;
qrcode_initText( &qrcode, modules, QRCODE_VERSION, ECC_QUARTILE, text );

if( qrcode.size > 0 )
    {
    /* set to full white */
    memset( qrcode_buf_handle.modules, 0xFF, QRCODE_BUF_SIZE_BYTE );

    for( int y = 0; y < QRCODE_V2_MODULE_NUM; y++ ) /* vertical direction */
        {
        for( int x = 0; x < QRCODE_V2_MODULE_NUM; x++ ) /* horizontal direction */
            {
            if( qrcode_getModule( &qrcode, x, y) )
                {
                qrcode_buf_handle.modules[y * QRCODE_V2_MODULE_NUM + x] = 0x00;
                }
            }
        }
    EW_notify_system_event_received( EnumSystemRxEventQRCODE_READY );
    }
}

/*********************************************************************
*
* @public
* QR_get_qrcode_buf
*
* Get the QR code buffer handle.
*
* @return The pointer to RGB buffer of QR code.
*
*********************************************************************/
qrcode_buf_handle_struct* QR_get_qrcode_buf
    (
    void
    )
{
return &qrcode_buf_handle;
}

/*********************************************************************
*
* @public
* QR_init
*
* Init QR code module.
*
*********************************************************************/
void QR_init
    (
    void
    )
{
qrcode_buf_handle.modules = qrcode_modules;
}
