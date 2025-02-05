/*******************************************************************************
* @file
* navilite_prv_packframe.h
*
* @brief
* NAVILITE private pack frame integration header file
*
* Copyright 2021 by Garmin Ltd. or its subsidiaries.
********************************************************************************/
#ifndef NAVILITE_PRV_PACKFRAME_H
#define NAVILITE_PRV_PACKFRAME_H

#ifdef __cplusplus
extern "C" {
#endif

/*--------------------------------------------------------------------
                        GENERAL INCLUDES
--------------------------------------------------------------------*/
#if( NAVILITE_BUILD_ROLE == NAVILITE_TARGET_MCU )
#include "navilite_prv_packframe_mcu.h"
#endif

#if( NAVILITE_LOCAL_HMI_TEST_MODE || UNIT_TEST_NAVILITE )
#include "navilite_prv_packframe_mobile.h"
#endif

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
                        MACROS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                        PROCEDURES
--------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* NAVILITE_PRV_PACKFRAME_H */
