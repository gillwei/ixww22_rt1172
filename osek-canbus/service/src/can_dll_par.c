/*!*******************************************************************
* @file can_dll_par.c
* @brief OSEK CAN Stack Dispatch Lower Layer Filter Vectors
*
*                         !!! WARNING !!!
*                 !!! COMPUTER GENERATED FILE !!!
*                    !!! DO NOT HAND MODIFY !!!
*
* The contents of this file were computer generated. Manual editing
* of this file is discouraged as it is likely to cause compilation
* errors and/or errors in run time functionalities that are dependent
* upon the contents of this file.
*
* The purpose of the functions and data structures in this file is to
* enable the dispatch of received CAN message frames and transmit
* complete notifications to the appropriate OSEK CAN stack layer,
* depending on the frame type.
*
* Copyright 2020 by Garmin Ltd. or its subsidiaries.
*********************************************************************/

/*!*******************************************************************
*
* @defgroup can_stack_dll_cfg Dispatch Lower Layer LYWW20 Application Configuration
* @ingroup can_stack_dll
* @{
*
*********************************************************************/

/*--------------------------------------------------------------------
                           GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "can_defs.h"
#include "can_cfg.h"
#include "can_dll.h"
#include "can_dll_par.h"
#include "can_dll_prv_par.h"

/*--------------------------------------------------------------------
                               VARIABLES
--------------------------------------------------------------------*/

/*------------------------------------------------------
CAN Hardware Receive Vector Qualification Data

This set of data structures defines the CAN Identifiers
that are received by each CAN receive filter/mask
combination (termed a receive "vector"). A specific
filter mask/combination may qualify multiple CAN
Identifiers, so this table is needed to further qualify
which CAN ID's that pass a specific filter/mask
combination are valid and therefore stored in the
software receive queue for further processing.
------------------------------------------------------*/

/*------------------------------------------------------
CAN0 Filter Vectors
------------------------------------------------------*/

/*------------------------------------------------------
CAN0 Receive Filter Vector 0
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr0_ids[DLL_CAN0_VCTR0_NUM_IDS] =
    {
        {
        RX_DAIG_SEG1_CAN0_ID,
        IL_CAN0_RX_DAIG_SEG1_RXFRM_HANDLE,
        DLL_RX_TP_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 1
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr1_ids[DLL_CAN0_VCTR1_NUM_IDS] =
    {
        {
        RX_DAIG_SEG2_CAN0_ID,
        IL_CAN0_RX_DAIG_SEG2_RXFRM_HANDLE,
        DLL_RX_TP_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 2
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr2_ids[DLL_CAN0_VCTR2_NUM_IDS] =
    {
        {
        RX_DAIG_SEG3_CAN0_ID,
        IL_CAN0_RX_DAIG_SEG3_RXFRM_HANDLE,
        DLL_RX_TP_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 3
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr3_ids[DLL_CAN0_VCTR3_NUM_IDS] =
    {
        {
        RX_DAIG_SEG4_CAN0_ID,
        IL_CAN0_RX_DAIG_SEG4_RXFRM_HANDLE,
        DLL_RX_TP_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 4
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr4_ids[DLL_CAN0_VCTR4_NUM_IDS] =
    {
        {
        RX_DAIG_SEG5_YDT_CAN0_ID,
        IL_CAN0_RX_DAIG_SEG5_YDT_RXFRM_HANDLE,
        DLL_RX_TP_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 5
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr5_ids[DLL_CAN0_VCTR5_NUM_IDS] =
    {
        {
        RX_DAIG_SEG6_YDT_CAN0_ID,
        IL_CAN0_RX_DAIG_SEG6_YDT_RXFRM_HANDLE,
        DLL_RX_TP_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 6
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr6_ids[DLL_CAN0_VCTR6_NUM_IDS] =
    {
        {
        RX_DAIG_SEG7_YDT_CAN0_ID,
        IL_CAN0_RX_DAIG_SEG7_YDT_RXFRM_HANDLE,
        DLL_RX_TP_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 7
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr7_ids[DLL_CAN0_VCTR7_NUM_IDS] =
    {
        {
        RX_NM_AND_LP_BK_CAN0_ID,
        IL_CAN0_RX_NM_AND_LP_BK_RXFRM_HANDLE,
        DLL_RX_NM_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 8
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr8_ids[DLL_CAN0_VCTR8_NUM_IDS] =
    {
        {
        RX0_ECU_INDCT_STAT_CAN0_ID,
        IL_CAN0_RX0_ECU_INDCT_STAT_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 9
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr9_ids[DLL_CAN0_VCTR9_NUM_IDS] =
    {
        {
        RX1_ECU_COM_DATA_CAN0_ID,
        IL_CAN0_RX1_ECU_COM_DATA_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 10
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr10_ids[DLL_CAN0_VCTR10_NUM_IDS] =
    {
        {
        RX2_RES_SUPPORT_CAN0_ID,
        IL_CAN0_RX2_RES_SUPPORT_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 11
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr11_ids[DLL_CAN0_VCTR11_NUM_IDS] =
    {
        {
        RX3_BRGTHNSS_CTRL_CAN0_ID,
        IL_CAN0_RX3_BRGTHNSS_CTRL_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 12
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr12_ids[DLL_CAN0_VCTR12_NUM_IDS] =
    {
        {
        RX4_RES_MT_FUNC_CNT_CAN0_ID,
        IL_CAN0_RX4_RES_MT_FUNC_CNT_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 13
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr13_ids[DLL_CAN0_VCTR13_NUM_IDS] =
    {
        {
        RX5_VEHICLE_INFO_CAN0_ID,
        IL_CAN0_RX5_VEHICLE_INFO_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 14
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr14_ids[DLL_CAN0_VCTR14_NUM_IDS] =
    {
        {
        RX6_FUNCSW_STAT_CAN0_ID,
        IL_CAN0_RX6_FUNCSW_STAT_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 15
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr15_ids[DLL_CAN0_VCTR15_NUM_IDS] =
    {
        {
        RX7_FUEL_RATE_CAN0_ID,
        IL_CAN0_RX7_FUEL_RATE_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 16
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr16_ids[DLL_CAN0_VCTR16_NUM_IDS] =
    {
        {
        RX8_ODO_TRIP_CAN0_ID,
        IL_CAN0_RX8_ODO_TRIP_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 17
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr17_ids[DLL_CAN0_VCTR17_NUM_IDS] =
    {
        {
        RX9_RES_RPRGRM_INFO_CAN0_ID,
        IL_CAN0_RX9_RES_RPRGRM_INFO_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 18
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr18_ids[DLL_CAN0_VCTR18_NUM_IDS] =
    {
        {
        RXA_VEHICLE_INFO_2_CAN0_ID,
        IL_CAN0_RXA_VEHICLE_INFO_2_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 19
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr19_ids[DLL_CAN0_VCTR19_NUM_IDS] =
    {
        {
        RXB_VEHICLE_INFO_3_CAN0_ID,
        IL_CAN0_RXB_VEHICLE_INFO_3_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 20
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr20_ids[DLL_CAN0_VCTR20_NUM_IDS] =
    {
        {
        RXC_VEHICLE_INFO_4_CAN0_ID,
        IL_CAN0_RXC_VEHICLE_INFO_4_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 21
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr21_ids[DLL_CAN0_VCTR21_NUM_IDS] =
    {
        {
        RXD_MAINT_TRIP_CAN0_ID,
        IL_CAN0_RXD_MAINT_TRIP_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 22
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr22_ids[DLL_CAN0_VCTR22_NUM_IDS] =
    {
        {
        RXE_HEATER_STAT_CAN0_ID,
        IL_CAN0_RXE_HEATER_STAT_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 23
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr23_ids[DLL_CAN0_VCTR23_NUM_IDS] =
    {
        {
        RXF_FACT_INSP_NS_CAN0_ID,
        IL_CAN0_RXF_FACT_INSP_NS_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 24
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr24_ids[DLL_CAN0_VCTR24_NUM_IDS] =
    {
        {
        RXG_FACT_INSP2_GA_CAN0_ID,
        IL_CAN0_RXG_FACT_INSP2_GA_RXFRM_HANDLE,
        DLL_RX_FT_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 25
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr25_ids[DLL_CAN0_VCTR25_NUM_IDS] =
    {
        {
        RXH_VH_EG_SPD_CAN0_ID,
        IL_CAN0_RXH_VH_EG_SPD_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 26
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr26_ids[DLL_CAN0_VCTR26_NUM_IDS] =
    {
        {
        RXI_TPMS_STAT_CAN0_ID,
        IL_CAN0_RXI_TPMS_STAT_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 27
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr27_ids[DLL_CAN0_VCTR27_NUM_IDS] =
    {
        {
        RXJ_MT_SYS_MOD_CAN0_ID,
        IL_CAN0_RXJ_MT_SYS_MOD_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 28
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr28_ids[DLL_CAN0_VCTR28_NUM_IDS] =
    {
        {
        RXK_GRIP_W_BTN_STAT_CAN0_ID,
        IL_CAN0_RXK_GRIP_W_BTN_STAT_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 29
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr29_ids[DLL_CAN0_VCTR29_NUM_IDS] =
    {
        {
        RXL_MT_GEAR_POS_CAN0_ID,
        IL_CAN0_RXL_MT_GEAR_POS_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 30
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr30_ids[DLL_CAN0_VCTR30_NUM_IDS] =
    {
        {
        RXM_ODO_TRIP_VAL_CAN0_ID,
        IL_CAN0_RXM_ODO_TRIP_VAL_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 31
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr31_ids[DLL_CAN0_VCTR31_NUM_IDS] =
    {
        {
        RXN_MT_SET_INFO_CAN0_ID,
        IL_CAN0_RXN_MT_SET_INFO_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 32
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr32_ids[DLL_CAN0_VCTR32_NUM_IDS] =
    {
        {
        RXO_ECU_SYS_MOD_CAN0_ID,
        IL_CAN0_RXO_ECU_SYS_MOD_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 33
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr33_ids[DLL_CAN0_VCTR33_NUM_IDS] =
    {
        {
        RXP_APS_ETV_CAN0_ID,
        IL_CAN0_RXP_APS_ETV_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 34
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr34_ids[DLL_CAN0_VCTR34_NUM_IDS] =
    {
        {
        RXQ_DIAG_EGMOD_CAN0_ID,
        IL_CAN0_RXQ_DIAG_EGMOD_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 35
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr35_ids[DLL_CAN0_VCTR35_NUM_IDS] =
    {
        {
        RXR_EG_STAT_CAN0_ID,
        IL_CAN0_RXR_EG_STAT_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 36
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr36_ids[DLL_CAN0_VCTR36_NUM_IDS] =
    {
        {
        RXS_ECU_GEAR_POS_CAN0_ID,
        IL_CAN0_RXS_ECU_GEAR_POS_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 37
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr37_ids[DLL_CAN0_VCTR37_NUM_IDS] =
    {
        {
        RXT_ECU_STAT_TCU_CAN0_ID,
        IL_CAN0_RXT_ECU_STAT_TCU_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 38
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr38_ids[DLL_CAN0_VCTR38_NUM_IDS] =
    {
        {
        RXU_ECVT_STAT_TCU_CAN0_ID,
        IL_CAN0_RXU_ECVT_STAT_TCU_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 39
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr39_ids[DLL_CAN0_VCTR39_NUM_IDS] =
    {
        {
        RXV_ABS_PRESS_CAN0_ID,
        IL_CAN0_RXV_ABS_PRESS_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 40
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr40_ids[DLL_CAN0_VCTR40_NUM_IDS] =
    {
        {
        RXW_ABS_STAT_CAN0_ID,
        IL_CAN0_RXW_ABS_STAT_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 41
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr41_ids[DLL_CAN0_VCTR41_NUM_IDS] =
    {
        {
        RXX_SMT_STAT_CAN0_ID,
        IL_CAN0_RXX_SMT_STAT_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 42
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr42_ids[DLL_CAN0_VCTR42_NUM_IDS] =
    {
        {
        RXY_TLCU_COM_DATA_CAN0_ID,
        IL_CAN0_RXY_TLCU_COM_DATA_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 43
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr43_ids[DLL_CAN0_VCTR43_NUM_IDS] =
    {
        {
        RXZ0_TLCU_SIG_CAN0_ID,
        IL_CAN0_RXZ0_TLCU_SIG_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Vector 44
------------------------------------------------------*/
static dll_rx_frm_dispatch_t const
dll_can0_vctr44_ids[DLL_CAN0_VCTR44_NUM_IDS] =
    {
        {
        RXZ1_TCU_STAT_ECU_CAN0_ID,
        IL_CAN0_RXZ1_TCU_STAT_ECU_RXFRM_HANDLE,
        DLL_RX_IL_FRAME
        }
    };

/*------------------------------------------------------
CAN0 Receive Filter Dispatch Table
------------------------------------------------------*/
static dll_rx_filt_dispatch_t const
dll_can0_dispatch_filters[DLL_CAN0_NUM_FILT_VCTRS] =
    {
        {
        DLL_CAN0_VCTR0_NUM_IDS,
        dll_can0_vctr0_ids
        },
        {
        DLL_CAN0_VCTR1_NUM_IDS,
        dll_can0_vctr1_ids
        },
        {
        DLL_CAN0_VCTR2_NUM_IDS,
        dll_can0_vctr2_ids
        },
        {
        DLL_CAN0_VCTR3_NUM_IDS,
        dll_can0_vctr3_ids
        },
        {
        DLL_CAN0_VCTR4_NUM_IDS,
        dll_can0_vctr4_ids
        },
        {
        DLL_CAN0_VCTR5_NUM_IDS,
        dll_can0_vctr5_ids
        },
        {
        DLL_CAN0_VCTR6_NUM_IDS,
        dll_can0_vctr6_ids
        },
        {
        DLL_CAN0_VCTR7_NUM_IDS,
        dll_can0_vctr7_ids
        },
        {
        DLL_CAN0_VCTR8_NUM_IDS,
        dll_can0_vctr8_ids
        },
        {
        DLL_CAN0_VCTR9_NUM_IDS,
        dll_can0_vctr9_ids
        },
        {
        DLL_CAN0_VCTR10_NUM_IDS,
        dll_can0_vctr10_ids
        },
        {
        DLL_CAN0_VCTR11_NUM_IDS,
        dll_can0_vctr11_ids
        },
        {
        DLL_CAN0_VCTR12_NUM_IDS,
        dll_can0_vctr12_ids
        },
        {
        DLL_CAN0_VCTR13_NUM_IDS,
        dll_can0_vctr13_ids
        },
        {
        DLL_CAN0_VCTR14_NUM_IDS,
        dll_can0_vctr14_ids
        },
        {
        DLL_CAN0_VCTR15_NUM_IDS,
        dll_can0_vctr15_ids
        },
        {
        DLL_CAN0_VCTR16_NUM_IDS,
        dll_can0_vctr16_ids
        },
        {
        DLL_CAN0_VCTR17_NUM_IDS,
        dll_can0_vctr17_ids
        },
        {
        DLL_CAN0_VCTR18_NUM_IDS,
        dll_can0_vctr18_ids
        },
        {
        DLL_CAN0_VCTR19_NUM_IDS,
        dll_can0_vctr19_ids
        },
        {
        DLL_CAN0_VCTR20_NUM_IDS,
        dll_can0_vctr20_ids
        },
        {
        DLL_CAN0_VCTR21_NUM_IDS,
        dll_can0_vctr21_ids
        },
        {
        DLL_CAN0_VCTR22_NUM_IDS,
        dll_can0_vctr22_ids
        },
        {
        DLL_CAN0_VCTR23_NUM_IDS,
        dll_can0_vctr23_ids
        },
        {
        DLL_CAN0_VCTR24_NUM_IDS,
        dll_can0_vctr24_ids
        },
        {
        DLL_CAN0_VCTR25_NUM_IDS,
        dll_can0_vctr25_ids
        },
        {
        DLL_CAN0_VCTR26_NUM_IDS,
        dll_can0_vctr26_ids
        },
        {
        DLL_CAN0_VCTR27_NUM_IDS,
        dll_can0_vctr27_ids
        },
        {
        DLL_CAN0_VCTR28_NUM_IDS,
        dll_can0_vctr28_ids
        },
        {
        DLL_CAN0_VCTR29_NUM_IDS,
        dll_can0_vctr29_ids
        },
        {
        DLL_CAN0_VCTR30_NUM_IDS,
        dll_can0_vctr30_ids
        },
        {
        DLL_CAN0_VCTR31_NUM_IDS,
        dll_can0_vctr31_ids
        },
        {
        DLL_CAN0_VCTR32_NUM_IDS,
        dll_can0_vctr32_ids
        },
        {
        DLL_CAN0_VCTR33_NUM_IDS,
        dll_can0_vctr33_ids
        },
        {
        DLL_CAN0_VCTR34_NUM_IDS,
        dll_can0_vctr34_ids
        },
        {
        DLL_CAN0_VCTR35_NUM_IDS,
        dll_can0_vctr35_ids
        },
        {
        DLL_CAN0_VCTR36_NUM_IDS,
        dll_can0_vctr36_ids
        },
        {
        DLL_CAN0_VCTR37_NUM_IDS,
        dll_can0_vctr37_ids
        },
        {
        DLL_CAN0_VCTR38_NUM_IDS,
        dll_can0_vctr38_ids
        },
        {
        DLL_CAN0_VCTR39_NUM_IDS,
        dll_can0_vctr39_ids
        },
        {
        DLL_CAN0_VCTR40_NUM_IDS,
        dll_can0_vctr40_ids
        },
        {
        DLL_CAN0_VCTR41_NUM_IDS,
        dll_can0_vctr41_ids
        },
        {
        DLL_CAN0_VCTR42_NUM_IDS,
        dll_can0_vctr42_ids
        },
        {
        DLL_CAN0_VCTR43_NUM_IDS,
        dll_can0_vctr43_ids
        },
        {
        DLL_CAN0_VCTR44_NUM_IDS,
        dll_can0_vctr44_ids
        }
    };


/*------------------------------------------------------
Pointers to Hardware Receive Filter Tables
------------------------------------------------------*/
static dll_rx_buf_dispatch_t const
dll_rx_buf_dispatch_table[CAN_NUM_INSTANCES] =
    {
        {
        DLL_CAN0_NUM_FILT_VCTRS,
        dll_can0_dispatch_filters
        }
    };


/*--------------------------------------------------------------------
                              PROCEDURES
--------------------------------------------------------------------*/

/*!*******************************************************************
*
* @private
* get Dispatch Lower Layer receive buffer dispatch table
*
* This function gets the dispatch table associated with a specific
* FCAN controller hardware instance. Using filter masks it is possible
* for multiple messages (i.e. multiple CAN Identifiers) to be
* qualified by a given filter, including unwanted messages that should
* be discarded. The dispatch tables identify the specific CAN
* Identifiers that are qualified by a given filter vector. Any received
* message that does not have its unique CAN Identifier in the dispatch
* table for a specific filter vector is discarded.
*
* @return uint8
* number of filter vectors in the dispatch table
*
*********************************************************************/

uint8
dll_get_rx_buf_dispatch_table
    (
    can_hw_inst_t                     const hw_inst,               //!< [in] CAN hardware instance
    dll_rx_buf_dispatch_t   const * * const pp_buf_dispatch_table  //!< [in,out] pointer to dispatch table
    )
{
uint8   l_num_filters;

/*------------------------------------------------------
Check for a valid CAN instance
------------------------------------------------------*/
if( hw_inst < CAN_NUM_INSTANCES )
    {
    /*------------------------------------------------------
    Return pointer to dispatch table and number of filters
    ------------------------------------------------------*/
    *( pp_buf_dispatch_table ) =  &( dll_rx_buf_dispatch_table[hw_inst] );
    l_num_filters              =  dll_rx_buf_dispatch_table[hw_inst].num_filters;
    }
else
    {
    *( pp_buf_dispatch_table ) = NULL;
    l_num_filters              = 0;
    }

return l_num_filters;
}

/*!*******************************************************************
*
* @}
*
*********************************************************************/