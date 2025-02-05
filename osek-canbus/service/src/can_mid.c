/*!*******************************************************************
*
* @defgroup can_stack_mid middle Layer between CAN and other modules
* @ingroup can_stack
* @{
*
*********************************************************************/

/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/
#include "can_defs.h"
#include "can_bcfg.h"
#include "CAN_app.h"
#include "can_dll_prv_par.h"

#include "can_il.h"
#include "can_il_prv.h"
#include "can_il_par.h"
#include "can_il_enum.h"
#include "can_il_prv_par.h"
#include "can_dll.h"

#include "VI_pub.h"
#include "fsl_debug_console.h"
#include "FreeRTOS.h"
#include "task.h"
#include <string.h>

#include "EEPM_pub.h"
#include "EW_pub.h"
#include "PM_pub.h"
#include "CAN_pub.h"
#include "BC_motocon_pub.h"

#include "can_mid.h"

/*--------------------------------------------------------------------
                            MACROS
--------------------------------------------------------------------*/
#define MID_MSG_RES_SHORT_TIMEOUT                       10   //!< 10  * 5ms = 50ms
#define MID_MSG_RES_SHORT_TIMEOUT_OFFSET                2    //!< 2  *  5ms = 10ms
#define MID_MSG_RES_MID_TIMEOUT                         30   //!< 30  * 5ms = 150ms

#define MID_MSG_RES_LONG_TIMEOUT                        1000 //!< 1000 * 5ms = 5000ms
#define MID_MSG_RE_SEND_TIME_LONG                       1    //!< 1 time,
#define MID_MSG_RE_SEND_TIME_SHORT                      3    //!< No response resending times

#define MID_MSG_CAN_ID_DEMO                             0xFFFFFFFF
#define MID_MSG_SVC_ID_DEMO                             0xFF

#define MID_MSG_TCFS_INIT                               0xFF
#define MID_MSG_BRZEGR_INIT                             0xFF

#define MID_FUEL_CONS_CALC_TIME                         200 //!< 200 * 5ms = 1000ms

#define MID_MSG_UPDATE_TO_BC_1000MS                     200 // !< 200 * 5ms = 1000ms
#define MID_MSG_UPDATE_TO_BC_100MS                      20  // !< 20 * 5ms = 100ms

#define MID_MSG_UPDATE_TO_BC_PERIOD_1000MS              1000 // 1000ms
#define MID_MSG_UPDATE_TO_BC_PERIOD_100MS               100  // 100ms

#define SUPP_MESSAGE_ID_CNT                             20
#define SUPP_1000MS_DATA_SIZE                           300
#define SUPP_100MS_DATA_SIZE                            300
#define SUPP_TIMEOUT_MAX                                1000    //5s timeout

/*--------------------------------------------------------------------
                            TYPES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                              VARIABLES
--------------------------------------------------------------------*/
/*------------------------------------------------------
Supported function list instances
------------------------------------------------------*/
mid_msg_supp_func_t supp_func_list      = { 0 };
boolean             supp_func_list_syc  = FALSE;
boolean             comm_err            = FALSE;

boolean             supp_send_result_flag = TRUE;

/*------------------------------------------------------
Supported function list instances
------------------------------------------------------*/
IdDataList can_supp_100ms_g_McCanResponse_dataList;
IdDataList can_supp_1000ms_g_McCanResponse_dataList;

/*------------------------------------------------------
Message list pointer
------------------------------------------------------*/
mid_msg_lst msg_lst_head = NULL;

/*------------------------------------------------------
Request message instances
------------------------------------------------------*/
mid_msg_t mid_msg_inst[] =
{
    { TX0_REQ_MT_FUNC_CNT_CAN0_ID, RX4_RES_MT_FUNC_CNT_CAN0_ID, MID_MSG_SID_VC_INFO_RST        , MID_RES_SID_VC_INFO_RST    },
    { TX0_REQ_MT_FUNC_CNT_CAN0_ID, RX4_RES_MT_FUNC_CNT_CAN0_ID, MID_MSG_SID_VC_INFO_CHNG_MT_LCD, MID_RES_SID_VC_INFO_CHNG   },
    { TX0_REQ_MT_FUNC_CNT_CAN0_ID, RX4_RES_MT_FUNC_CNT_CAN0_ID, MID_MSG_SID_UNIT_CHNG,           MID_RES_SID_UNIT           },
    { TX0_REQ_MT_FUNC_CNT_CAN0_ID, RX4_RES_MT_FUNC_CNT_CAN0_ID, MID_MSG_SID_TCS_SWITCH,          MID_RES_SID_TCS            },
    { TX4_REQ_REPRGRM_INFO_CAN0_ID,RX9_RES_RPRGRM_INFO_CAN0_ID, MID_MSG_SID_REPROG,              MID_RES_SID_REPROG         },
    { TX2_REQ_SUPPORT_CAN0_ID,     RX2_RES_SUPPORT_CAN0_ID,     MID_MSG_SID_SUPP_FUNC_LIST,      MID_RES_SID_SUPP_FUNC_LIST },
};

il_rx_frm_index_t supplement_messages[SUPP_MESSAGE_ID_CNT] =
{
    IL_CAN0_RX0_ECU_INDCT_STAT_IDX,
    IL_CAN0_RXH_VH_EG_SPD_IDX,
    IL_CAN0_RXJ_MT_SYS_MOD_IDX,
    IL_CAN0_RXK_GRIP_W_BTN_STAT_IDX,
    IL_CAN0_RXL_MT_GEAR_POS_IDX,
    IL_CAN0_RXM_ODO_TRIP_VAL_IDX,
    IL_CAN0_RXN_MT_SET_INFO_IDX,
    IL_CAN0_RXO_ECU_SYS_MOD_IDX,
    IL_CAN0_RXP_APS_ETV_IDX,
    IL_CAN0_RXQ_DIAG_EGMOD_IDX,
    IL_CAN0_RXR_EG_STAT_IDX,
    IL_CAN0_RXS_ECU_GEAR_POS_IDX,
    IL_CAN0_RXT_ECU_STAT_TCU_IDX,
    IL_CAN0_RXU_ECVT_STAT_TCU_IDX,
    IL_CAN0_RXV_ABS_PRESS_IDX,
    IL_CAN0_RXW_ABS_STAT_IDX,
    IL_CAN0_RXX_SMT_STAT_IDX,
    IL_CAN0_RXY_TLCU_COM_DATA_IDX,
    IL_CAN0_RXZ0_TLCU_SIG_IDX,
    IL_CAN0_RXZ1_TCU_STAT_ECU_IDX,
};

uint16 supplement_messages_period[SUPP_MESSAGE_ID_CNT] =
{
    100,100,1000,1000,100,1000,1000,100,100,100,
    1000,100,100,100,100,100,1000,1000,1000,100,
};

/*------------------------------------------------------
Fuel consumption
------------------------------------------------------*/
static uint32 fuel_cons_pre          = 0;
static uint32 fuel_cons_curr         = 0;
static bool   fuel_cons_read_status  = FALSE;
static bool   fuel_cons_write_status = FALSE;
static bool   ign_status             = PM_IGN_ON;


/*------------------------------------------------------
Init the message initial values in middle layer
------------------------------------------------------*/
void mid_sfl_init
    (
    void
    )
{
supp_func_list.tcfs                     = MID_MSG_TCFS_INIT;
supp_func_list.brzegr                   = MID_MSG_BRZEGR_INIT;

supp_func_list.sfl.bit.trip1            = 0;
supp_func_list.sfl.bit.trip2            = 0;
supp_func_list.sfl.bit.Ftrip            = 0;
supp_func_list.sfl.bit.mt_brgtnss_adj   = 0;
supp_func_list.sfl.bit.clk              = 0;
supp_func_list.sfl.bit.tcs              = 0;
supp_func_list.sfl.bit.grip_warmer      = 0;
supp_func_list.sfl.bit.seat_heater      = 0;

supp_func_list.sfl.bit.wind_scrn        = 0;
supp_func_list.sfl.bit.oil_trip         = 1;
supp_func_list.sfl.bit.Vbelt_trip       = 0;
supp_func_list.sfl.bit.Free1            = 0;
supp_func_list.sfl.bit.Free2            = 0;
supp_func_list.sfl.bit.avg_spd          = 0;
supp_func_list.sfl.bit.crt_fuel         = 1;
supp_func_list.sfl.bit.avg_fuel         = 1;

supp_func_list.sfl.bit.fuel_cons        = 0;
supp_func_list.sfl.bit.air              = 0;
supp_func_list.sfl.bit.bat              = 0;
supp_func_list.sfl.bit.coolant          = 0;
supp_func_list.sfl.bit.rng              = 0;
supp_func_list.sfl.bit.tire_frnt        = 0;
supp_func_list.sfl.bit.tire_frnt_r      = 0;
supp_func_list.sfl.bit.tire_frnt_l      = 0;

supp_func_list.sfl.bit.tire_rear        = 0;
supp_func_list.sfl.bit.tip_time         = 1;
supp_func_list.sfl.bit.cruise           = 0;
supp_func_list.sfl.bit.rsv              = 0;

supp_func_list.sfl.bit.unused           = 0;
}

/*------------------------------------------------------
Init the message list
------------------------------------------------------*/
static void mid_msg_list_init
    (
    void
    )
{
/*------------------------------------------------------
Get the head node memory space
------------------------------------------------------*/
msg_lst_head = pvPortMalloc( sizeof( mid_msg_node ) );

/*------------------------------------------------------
Init message para
------------------------------------------------------*/
msg_lst_head->next           = NULL;
msg_lst_head->req_msg_time   = 0;
msg_lst_head->req_msg_wait   = 0;
msg_lst_head->req_msg_status = MID_MSG_STAT_INITED;

/*------------------------------------------------------
Reset data field
------------------------------------------------------*/
memset( &msg_lst_head->req_msg,  0, sizeof(can_msg_t) );
memset( &msg_lst_head->pos_resp_msg,  0, sizeof(can_msg_t) );
memset( &msg_lst_head->neg_resp_msg,  0, sizeof(can_msg_t) );
}

/*------------------------------------------------------
Fill the node with the input request message
------------------------------------------------------*/
static can_ret_code_t
mid_msg_node_req_fill
    (
    can_msg_t   const *const req_msg_p,
    mid_msg_lst        const node_p
    )
{
can_ret_code_t  l_ret_code  = CAN_RC_NOT_AVAILABLE;
uint32 l_inst_can_id        = 0;
uint8  l_inst_svc_id        = 0;
uint32 l_req_can_id         = req_msg_p->id;
uint8  l_req_svc_id         = req_msg_p->data[MID_MSG_REQMFNC_IDX];
uint8  index = 0;

/*------------------------------------------------------
Find the para instance
------------------------------------------------------*/
for( index = 0; index < ( sizeof( mid_msg_inst ) / sizeof(mid_msg_t) ); index++ )
    {
    l_inst_can_id = mid_msg_inst[index].req_can_id;
    l_inst_svc_id = mid_msg_inst[index].req_svc_id;

    if( l_inst_can_id == l_req_can_id &&
        l_inst_svc_id == l_req_svc_id )
        {
        l_ret_code = CAN_RC_SUCCESS;
        break;
        }
    }

if( l_ret_code == CAN_RC_SUCCESS )
    {
    /*------------------------------------------------------
    Set these paras
    ------------------------------------------------------*/
    node_p->req_msg_wait   = 0;
    node_p->req_msg_time   = 0;
    node_p->req_msg_status = MID_MSG_STAT_WAIT_RES_SHORT;

    /*------------------------------------------------------
    Fill data field
    ------------------------------------------------------*/
    node_p->req_msg.id     = req_msg_p->id,
    node_p->req_msg.size   = req_msg_p->size;
    memcpy( node_p->req_msg.data, req_msg_p->data, req_msg_p->size );

    node_p->pos_resp_msg.id  = mid_msg_inst[index].resp_can_id;
    node_p->pos_resp_msg.data[MID_MSG_RESMFNC_IDX] = mid_msg_inst[index].pos_svc_id;

    node_p->neg_resp_msg.id  = mid_msg_inst[index].resp_can_id;
    node_p->neg_resp_msg.data[MID_MSG_NRES_NACK_IDX] = MID_MSG_NRES_NACK;
    node_p->neg_resp_msg.data[MID_MSG_NRES_SID_IDX]  = req_msg_p->data[MID_MSG_REQMFNC_IDX];
    }

return l_ret_code;
}

/*------------------------------------------------------
Search the message in the list by can id and service id
------------------------------------------------------*/
static mid_msg_lst
mid_msg_node_search
    (
    can_msg_t   const *const msg_p
    )
{
uint32 l_msg_can_id  = 0;
uint8  l_msg_svc_id  = 0;
uint32 l_can_id      = msg_p->id;
uint8  l_svc_id      = MID_MSG_SVC_ID_DEMO;
mid_msg_lst l_node_p = msg_lst_head;

/*------------------------------------------------------
Find the node whose element timer equals to the input
------------------------------------------------------*/
while( ( l_node_p != NULL ) &&
       ( l_msg_can_id != l_can_id || l_msg_svc_id != l_svc_id ) )
    {
    l_node_p = l_node_p->next;

    /*------------------------------------------------------
    Find the node by request CAN id and service id
    ------------------------------------------------------*/
    if( ( l_can_id == TX0_REQ_MT_FUNC_CNT_CAN0_ID  ) ||
        ( l_can_id == TX4_REQ_REPRGRM_INFO_CAN0_ID ) ||
        ( l_can_id == TX2_REQ_SUPPORT_CAN0_ID ) )
        {
        l_svc_id     = msg_p->data[MID_MSG_REQMFNC_IDX];

        l_msg_can_id = l_node_p->req_msg.id;
        l_msg_svc_id = l_node_p->req_msg.data[MID_MSG_REQMFNC_IDX];
        }
    /*------------------------------------------------------
    Find the node by response CAN id and service id
    ------------------------------------------------------*/
    else if( ( l_can_id == RX4_RES_MT_FUNC_CNT_CAN0_ID ) ||
             ( l_can_id == RX9_RES_RPRGRM_INFO_CAN0_ID ) ||
             ( l_can_id == RX2_RES_SUPPORT_CAN0_ID ) )
        {
        if( msg_p->data[MID_MSG_RESMFNC_IDX] == MID_MSG_NRES_NACK )
            {
            l_svc_id     = msg_p->data[MID_MSG_NRES_SID_IDX];

            l_msg_can_id = l_node_p->neg_resp_msg.id;
            l_msg_svc_id = l_node_p->neg_resp_msg.data[MID_MSG_NRES_SID_IDX];
            }
        else
            {
            l_svc_id     = msg_p->data[MID_MSG_REQMFNC_IDX];

            l_msg_can_id = l_node_p->pos_resp_msg.id;
            l_msg_svc_id = l_node_p->pos_resp_msg.data[MID_MSG_RESMFNC_IDX];
            }
        }
    }

return l_node_p;
}

/*------------------------------------------------------
Insert a request to the request message list
------------------------------------------------------*/
static can_ret_code_t
mid_msg_list_insert
    (
    can_msg_t   const *const req_msg_p
    )
{
can_ret_code_t  l_ret_code      = CAN_RC_NOT_AVAILABLE;
mid_msg_lst     l_node_pre_p    = msg_lst_head;
uint8           l_svc_staus     = 0;

/*------------------------------------------------------
Find if there is a same request message node
------------------------------------------------------*/
mid_msg_lst l_node_p = mid_msg_node_search( req_msg_p );

if( l_node_p != NULL )
    {
    /*------------------------------------------------------
    Client must not transmit next "Request A" message before
    "Response A" is received for previous "Request A".
    ------------------------------------------------------*/
    l_svc_staus = l_node_p->req_msg_status;
    if( l_svc_staus == MID_MSG_STAT_WAIT_RES_SHORT )
        {
        return l_ret_code;
        }
    else
        {
        l_ret_code = mid_msg_node_req_fill( req_msg_p, l_node_p );
        }
    }
else
    {
    /*------------------------------------------------------
    Get a node memory space
    ------------------------------------------------------*/
    l_node_p = pvPortMalloc( sizeof( mid_msg_node ) );
    if( l_node_p == NULL )
        {
        return l_ret_code;
        }

    /*------------------------------------------------------
    Find the message list tail
    ------------------------------------------------------*/
    while( l_node_pre_p->next != NULL )
        {
        l_node_pre_p = l_node_pre_p->next;
        }

    /*------------------------------------------------------
    Link new node to the tail node
    ------------------------------------------------------*/
    l_node_pre_p->next = l_node_p;

    /*------------------------------------------------------
    Set new node next pointer
    ------------------------------------------------------*/
    l_node_p->next = NULL;

    /*------------------------------------------------------
    Fill the node
    ------------------------------------------------------*/
    l_ret_code = mid_msg_node_req_fill( req_msg_p, l_node_p );
    }

return l_ret_code;
}

/*------------------------------------------------------
API for other module sending request
------------------------------------------------------*/
can_ret_code_t can_mid_req
    (
    uint32  can_id,
    uint8   msg_len,
    uint8   svc_id,
    uint8   svc_opt
    )
{
can_ret_code_t l_ret_code  = CAN_RC_NOT_AVAILABLE;
can_msg_t l_req_msg        = { 0 };

/*------------------------------------------------------
Set request message
------------------------------------------------------*/
l_req_msg.id   = can_id;
l_req_msg.size = msg_len;
l_req_msg.data[MID_MSG_REQMFNC_IDX]     = svc_id;
l_req_msg.data[MID_MSG_REQPROCDTL_IDX]  = svc_opt;
l_req_msg.data[MID_MSG_PADDING_IDX]     = MID_MSG_PADDING_DATA;

/*------------------------------------------------------
Add the message to message list for timing and response
waiting
------------------------------------------------------*/
l_ret_code = mid_msg_list_insert( &l_req_msg );

/*------------------------------------------------------
Add the message to message list for timing and response
waiting
------------------------------------------------------*/
if( l_ret_code == CAN_RC_SUCCESS )
    {
    l_ret_code = il_app_frm_put( &l_req_msg );
    }

return l_ret_code;
}

/*------------------------------------------------------
Response callback
------------------------------------------------------*/
void can_mid_resp_cb
    (
    can_msg_t const * const mid_msg_p
    )
{
uint8            l_rs         = 0;
uint8            l_svc_id     = 0;
uint8*           l_svc_data_p = NULL;
uint32           l_can_id    = mid_msg_p->id;
uint32           l_msg_len   = mid_msg_p->size;
uint8            l_resp_type = mid_msg_p->data[MID_MSG_RESMFNC_IDX];

mid_msg_lst      l_node_p          = mid_msg_node_search( mid_msg_p );
uint8           *l_node_time_p     = &( l_node_p->req_msg_time );
uint16          *l_node_wait_p     = &( l_node_p->req_msg_wait );
mid_msg_stat_t  *l_node_status_p   = &( l_node_p->req_msg_status );
can_msg_t       *l_node_pos_resp_p = &( l_node_p->pos_resp_msg );

uint8            l_pos_resp_svc_id = mid_msg_p->data[MID_MSG_RESMFNC_IDX];
uint8            l_neg_resp_svc_id = mid_msg_p->data[MID_MSG_NRES_SID_IDX];

/*------------------------------------------------------
Can not find the response node in the message list
------------------------------------------------------*/
if( l_node_p == NULL )
    {
    return;
    }

/*------------------------------------------------------
Only when LC is in short wait(50ms) or long wait(5000ms),
response messages can be valid
------------------------------------------------------*/
if( ( ( *l_node_status_p ) != MID_MSG_STAT_WAIT_RES_SHORT ) &&
    ( ( *l_node_status_p ) != MID_MSG_STAT_WAIT_RES_LONG ) )
    {
    return;
    }

/*------------------------------------------------------
Handle resp date by different type(positive or negative)
------------------------------------------------------*/
if( l_resp_type == MID_MSG_NRES_NACK )
    {
    l_rs = mid_msg_p->data[MID_MSG_NRES_RS_IDX];
    l_svc_data_p = mid_msg_p->data[MID_MSG_NRES_RS_IDX];
    if( l_rs == MID_MSG_NRES_RS_WAIT_REQ )
        {
        *l_node_wait_p   = 0;
        *l_node_time_p   = 0;
        *l_node_status_p = MID_MSG_STAT_WAIT_RES_LONG;
         l_svc_id        = l_neg_resp_svc_id;

        //TBD nodity upper layer (resending is in the mid_task)
        }
    else if( l_rs == MID_MSG_NRES_RS_NOT_SUPP )
        {
        /*------------------------------------------------------
        Handle the response message
        If linkcard cannot receive positive response even though
        linkcard transmits the request 3 times, linkcard shall
        stop transmiting the request.
        ------------------------------------------------------*/
        if( ( *l_node_time_p ) < MID_MSG_RE_SEND_TIME_SHORT )
            {
             l_svc_id        = l_neg_resp_svc_id;
            }

        //TBD notity upper layer to handle no supported service ID
        }

    /*------------------------------------------------------
    Handle reprogram Negative response
    ------------------------------------------------------*/
    if( l_can_id == RX9_RES_RPRGRM_INFO_CAN0_ID )
        {
        VI_rx_reprogram_info_response( l_resp_type, l_svc_id, l_msg_len,l_svc_data_p );
        }
    }
else
    {
    /*------------------------------------------------------
    Data modify
    ------------------------------------------------------*/
    memcpy( l_node_pos_resp_p->data, mid_msg_p->data, l_msg_len );

    /*------------------------------------------------------
    Handle the positive response message
    ------------------------------------------------------*/
    *l_node_wait_p   = 0;
    *l_node_time_p   = 0;
    *l_node_status_p = MID_MSG_STAT_INITED;
     l_svc_id        = l_pos_resp_svc_id;
     l_svc_data_p    = &( l_node_pos_resp_p->data[MID_MSG_RESPROCDTL_IDX] );

    /*------------------------------------------------------
    Handle the function list positive response
    ------------------------------------------------------*/
    if( ( l_can_id == RX2_RES_SUPPORT_CAN0_ID ) &&
        ( supp_func_list_syc == FALSE ) &&
        ( comm_err == FALSE ) )
        {
        supp_func_list_syc = TRUE;
        memcpy( &supp_func_list, &( mid_msg_p->data[MID_MSG_TCFS_IDX] ), sizeof( supp_func_list ) );
        VI_rx_support_function_received( &supp_func_list );
        }

    /*------------------------------------------------------
    Handle reprogram positive response
    ------------------------------------------------------*/
    if( l_can_id == RX9_RES_RPRGRM_INFO_CAN0_ID )
        {
        VI_rx_reprogram_info_response( l_resp_type, l_svc_id, l_msg_len,l_svc_data_p );
        }

    /*------------------------------------------------------
    Handle positive response of Meter function control
    ------------------------------------------------------*/
    if( l_can_id == RX4_RES_MT_FUNC_CNT_CAN0_ID )
        {
        VI_rx_mt_func_cont_info_response( l_svc_id, l_msg_len,l_svc_data_p );
        }

#if( DEBUG_RX_CAN_SUPPORT )
    PRINTF( "Pos resp %x %x!\r\n", l_can_id, l_svc_id );
#endif
    }
}

/*------------------------------------------------------
Find the positive message node by response CAN ID and
service ID
------------------------------------------------------*/
mid_msg_lst
can_mid_resp_get
    (
    uint32  resp_can_id,
    uint8   resp_svc_id
    )
{
mid_msg_lst l_node_p      = msg_lst_head;
uint32      l_msg_can_id  = 0;
uint8       l_msg_svc_id  = 0;

/*------------------------------------------------------
Find the node whose element timer equals to the input
------------------------------------------------------*/
while( ( l_node_p != NULL ) &&
       ( l_msg_can_id != resp_can_id || l_msg_svc_id != resp_svc_id ) )
    {
    l_node_p = l_node_p->next;

    /*------------------------------------------------------
    Find the node by response CAN id and service id
    ------------------------------------------------------*/
    l_msg_can_id = l_node_p->pos_resp_msg.id;
    l_msg_svc_id = l_node_p->pos_resp_msg.data[MID_MSG_RESMFNC_IDX];
    }

return l_node_p;
}

/*------------------------------------------------------
Middle layer signal value set for event type messages
------------------------------------------------------*/
boolean can_mid_sig_set
    (
    dll_frm_index_t          *frm_index_p, //!< [in] Frame index
    il_sig_handle_t     const sig_handle,  //!< [in] signal handle
    uint8               const num_bytes,   //!< [in] number of bytes in the signal
    uint8       const * const p_sig_data   //!< [in] pointer to signal data
    )
{
il_txsig_info_t     const * l_p_txsig_info;
il_txfrm_info_t     const * l_p_txfrm_info;
il_txsig_t          const * l_p_tx_sig;
il_txfrm_t          const * l_p_txfrm;
il_sig_index_t              l_sig_index;
il_sig_index_t              l_num_signals;
can_hw_inst_t               l_hw_inst;
boolean                     l_success;

/*------------------------------------------------------
Initialize the return value, then validate the signal
handle with respect to the range of CAN instances
------------------------------------------------------*/
l_success = FALSE;
l_hw_inst = IL_GET_HWINST_FROM_SIGNAL_HANDLE( sig_handle );

if( l_hw_inst < CAN_NUM_INSTANCES )
    {
    /*------------------------------------------------------
    Verify that the signal index is within a valid range and
    that the pointer to the data is not NULL
    ------------------------------------------------------*/
    l_p_txsig_info = il_get_txsig_info_ptr( l_hw_inst );
    l_num_signals  = l_p_txsig_info->num_signals;
    l_sig_index    = IL_GET_INDEX_FROM_SIGNAL_HANDLE( sig_handle );

    if( ( l_sig_index < l_num_signals ) && ( p_sig_data != NULL ) )
        {
        /*------------------------------------------------------
        Get the frame information for this signal index
        ------------------------------------------------------*/
        l_p_tx_sig     = &( l_p_txsig_info->p_il_txsig[l_sig_index] );
        *frm_index_p   = l_p_tx_sig->frame_index;
        l_p_txfrm_info = il_get_txfrm_info_ptr( l_hw_inst );
        l_p_txfrm      = &( l_p_txfrm_info->p_il_txfrm[*frm_index_p] );

        /*------------------------------------------------------
        Perform thread safe update of the frame signal data
        ------------------------------------------------------*/
        taskENTER_CRITICAL();

        l_success =  pack_frame_signal( l_p_tx_sig->start_bit,
                                        l_p_tx_sig->num_bits,
                                        p_sig_data,
                                        l_p_txfrm->p_data,
                                        num_bytes );
        taskEXIT_CRITICAL();
        }
    }

return l_success;
}

/*------------------------------------------------------
Middle layer frame send
------------------------------------------------------*/
void can_mid_frm_send
    (
    dll_frm_index_t frm_index
    )
{
transmit_frame( CAN_CONTROLLER_2, frm_index );
}

/*------------------------------------------------------
Handshake with Meter to get supported functions list
------------------------------------------------------*/
static can_ret_code_t
can_mid_hand_shake
    (
    void
    )
{
can_ret_code_t  l_ret_code  = CAN_RC_NOT_AVAILABLE;

/*------------------------------------------------------
Only one byte for function list request
------------------------------------------------------*/
l_ret_code = can_mid_req( TX2_REQ_SUPPORT_CAN0_ID,    IL_CAN0_TX2_REQ_SUPPORT_TXFRM_LEN,
                          MID_MSG_SID_SUPP_FUNC_LIST, MID_MSG_PADDING_DATA );
return l_ret_code;
}

#if( DEBUG_TX_CAN_SUPPORT )
/*------------------------------------------------------
Positive and negative test
------------------------------------------------------*/
static can_ret_code_t
can_mid_pos_neg_test
    (
    void
    )
{
can_ret_code_t  l_ret_code  = CAN_RC_NOT_AVAILABLE;

/*------------------------------------------------------
Positive test
------------------------------------------------------*/
l_ret_code = can_mid_req( TX0_REQ_MT_FUNC_CNT_CAN0_ID, IL_CAN0_TX0_REQ_MT_FUNC_CNT_TXFRM_LEN,
                          MID_MSG_SID_UNIT_CHNG, MID_MSG_PROCDTL_CHNG_DIST_UNIT_TO_MILE );

/*------------------------------------------------------
Negative test
------------------------------------------------------*/
l_ret_code = can_mid_req( TX4_REQ_REPRGRM_INFO_CAN0_ID, IL_CAN0_TX4_REQ_REPRGRM_INFO_TXFRM_LEN,
                          MID_MSG_SID_REPROG, MID_MSG_PROGSTS_START_REQ );

return l_ret_code;
}

/*------------------------------------------------------
No response test
------------------------------------------------------*/
static can_ret_code_t
can_mid_no_resp_test
    (
    void
    )
{
dll_frm_index_t  l_frm_index;

uint8  bnt_status = IL_VT_HEATER_LVL_BTN_STAT_HEATER_UP;
uint8  lvl_lv     = IL_VT_HEATER_LVL_LV_MID;
uint8  lvl_select = IL_VT_HEATER_LVL_SLECT_RIDER_SEAT_HEATER;

/*------------------------------------------------------
Fill the frame with different signals' values
------------------------------------------------------*/
can_mid_sig_set(
                &l_frm_index,
                 IL_CAN0_HEATER_LVL_BTN_STAT_HEATER_TXSIG_HANDLE,
                 IL_CAN0_HEATER_LVL_BTN_STAT_HEATER_TXSIG_NBYTES,
                &bnt_status
                );

can_mid_sig_set(
                &l_frm_index,
                IL_CAN0_HEATER_LVL_LV_TXSIG_HANDLE,
                IL_CAN0_HEATER_LVL_LV_TXSIG_NBYTES,
                &lvl_lv
                );

can_mid_sig_set(
                &l_frm_index,
                IL_CAN0_HEATER_LVL_SLECT_TXSIG_HANDLE,
                IL_CAN0_HEATER_LVL_SLECT_TXSIG_NBYTES,
                &lvl_select
                );

/*------------------------------------------------------
Send frame
------------------------------------------------------*/
can_mid_frm_send( l_frm_index );
}
#endif

/*------------------------------------------------------
Get supported functions
------------------------------------------------------*/
mid_msg_supp_func_t*
can_mid_get_supp_func_list
    (
    void
    )
{
return ( &supp_func_list );
}

/*------------------------------------------------------
Get supplement information sending status
------------------------------------------------------*/
void
can_mid_get_supp_sending_sts
    (
    uint8 value
    )
{
supp_send_result_flag = TRUE;
}

/*------------------------------------------------------
Supplement CAN messages sending by Bluetooth
------------------------------------------------------*/
void can_mid_supplement_task
    (
    void
    )
{
uint8 l_supp_index  = 0;
uint8 l_frm_index   = 0;

il_rxfrm_info_t         const * l_p_rxfrm_info      = NULL;
il_rx_per_info_t        const * l_p_per_info        = NULL;
il_rxfrm_t              const * l_p_rxfrm           = NULL;

dll_rx_buf_dispatch_t   const * l_p_buf_dispatch    = NULL;
dll_rx_filt_dispatch_t  const * l_p_filt_dispatch   = NULL;
dll_rx_frm_dispatch_t   const * l_p_frm_dispatch    = NULL;
uint8                           l_num_filters       = 0;
uint8                           l_can_data_len      = 0;

static uint8                    timer = 0;
static uint16                   timeout_cnt = 0;
static can_supp_msg_t           l_supp_data         = { 0 };
uint16                          resp_100ms_data_len = 0;
uint16                          resp_1000ms_data_len = 0;

static uint8                    l_supp_1000ms_data[SUPP_1000MS_DATA_SIZE] = { 0 };
static uint8                    l_supp_100ms_data[SUPP_100MS_DATA_SIZE]  = { 0 };

#if(DEBUG_RX_CAN_SUPPORT)
static uint8                    i  = 0;
#endif
/*------------------------------------------------------
Check the connection status of Bluetooth
------------------------------------------------------*/
if( FALSE == BC_motocon_is_connected() )
    {
    timer = 0;
    #if(DEBUG_RX_CAN_SUPPORT)
    i++;
    if( i >= 200 )
        {
        PRINTF( "Bluetooth can not connected ---- \n\n\n");
        i = 0;
        }
    #endif
    return ;
    }

/*------------------------------------------------------
Get pointers to the frame information
------------------------------------------------------*/
l_p_rxfrm_info = il_get_rxfrm_info_ptr( CAN_CONTROLLER_2 );

/*------------------------------------------------------
Check every supplement messages' timers
------------------------------------------------------*/
can_supp_100ms_g_McCanResponse_dataList.count = 0;
can_supp_1000ms_g_McCanResponse_dataList.count = 0;
can_supp_100ms_g_McCanResponse_dataList.fields = McCanResponse_IdData_fields;
can_supp_1000ms_g_McCanResponse_dataList.fields = McCanResponse_IdData_fields;

for( l_supp_index = 0; l_supp_index < ( sizeof(supplement_messages) / sizeof(il_rx_frm_index_t) ); l_supp_index++ )
    {
    /*------------------------------------------------------
    Get the message's id from array
    ------------------------------------------------------*/
    l_frm_index = supplement_messages[l_supp_index];
    /*------------------------------------------------------
    Get the message's info( Status and period )
    ------------------------------------------------------*/
    l_p_rxfrm      = &( l_p_rxfrm_info->p_il_rxfrm[l_frm_index] );
    l_p_per_info   = l_p_rxfrm->p_per_info;

    l_num_filters = dll_get_rx_buf_dispatch_table( CAN_CONTROLLER_2, &l_p_buf_dispatch );

    if( l_frm_index < l_num_filters )
        {
        l_p_filt_dispatch = &( l_p_buf_dispatch->p_rx_filt_dispatch[l_frm_index] );
        l_p_frm_dispatch  = l_p_filt_dispatch->p_frame_dispatch;
        l_supp_data.id  = l_p_frm_dispatch->identifier;
        l_can_data_len = l_p_rxfrm->dlc;
        /*------------------------------------------------------
        Send supplement messages to APP by Bluetooth
        Maybe a Sending FIFO and another BT sending task
        could be added here for BT's Asynchrony
        ------------------------------------------------------*/
       if( ( MID_MSG_UPDATE_TO_BC_PERIOD_1000MS == supplement_messages_period[l_supp_index] ) || ( MID_MSG_UPDATE_TO_BC_PERIOD_100MS == supplement_messages_period[l_supp_index] ) )/*1000ms*/
            {
            IdDataList_add_IdData( &can_supp_1000ms_g_McCanResponse_dataList, ( uint32 )l_supp_data.id, ( uint8 * )( l_p_rxfrm->p_data ), ( uint32 )( l_can_data_len ) );
            }
       if( MID_MSG_UPDATE_TO_BC_PERIOD_100MS == supplement_messages_period[l_supp_index] ) /*100ms*/
            {
            IdDataList_add_IdData( &can_supp_100ms_g_McCanResponse_dataList, ( uint32 )l_supp_data.id, ( uint8 * )( l_p_rxfrm->p_data ), ( uint32 )( l_can_data_len ) );
            }
        }
    }
/*------------------------------------------------------
Send supplement messages to APP by 100ms and 1000ms
------------------------------------------------------*/
if( ( timer%MID_MSG_UPDATE_TO_BC_100MS ) == 0 )
{
    if( ( timer%MID_MSG_UPDATE_TO_BC_1000MS ) == 0)
        {
        timer = 0;
        if( supp_send_result_flag )
            {
            resp_1000ms_data_len = Gen_McCanResponse( &can_supp_1000ms_g_McCanResponse_dataList, l_supp_1000ms_data,sizeof( l_supp_1000ms_data ) );
            supp_send_result_flag = FALSE;
            BC_motocon_send_can_response( resp_1000ms_data_len, l_supp_1000ms_data, can_mid_get_supp_sending_sts );
            timeout_cnt = 0;
            }

        #if(DEBUG_RX_CAN_SUPPORT)
        PRINTF( "Supplement CAN LEN:%d \r\n", resp_1000ms_data_len );
        #endif
        }
    else
        {
        if( supp_send_result_flag )
            {
            resp_100ms_data_len = Gen_McCanResponse( &can_supp_100ms_g_McCanResponse_dataList, l_supp_100ms_data,sizeof( l_supp_100ms_data ) );
            supp_send_result_flag = FALSE;
            BC_motocon_send_can_response( resp_100ms_data_len, l_supp_100ms_data, can_mid_get_supp_sending_sts );
            timeout_cnt = 0;
            }

        #if(DEBUG_RX_CAN_SUPPORT)
        PRINTF( "Supplement CAN LEN:%d \r\n", resp_100ms_data_len );
        #endif
        }
}

if( supp_send_result_flag == FALSE )
    {
    if( timeout_cnt > SUPP_TIMEOUT_MAX )
        {
        supp_send_result_flag = TRUE;
        timeout_cnt = 0;
        }
    }
if( timer > MID_MSG_UPDATE_TO_BC_1000MS )
    {
    timer = 0;
    }
timer++;
timeout_cnt++;
}
/*------------------------------------------------------
Fuel consumption set call back
------------------------------------------------------*/
void can_mid_fuel_cons_set_cb
    (
    bool    status,
    void*   data
    )
{
uint8 fuel_cons[4] = { 0 };

if( status == TRUE )
    {
    fuel_cons_write_status = status;
    memcpy( fuel_cons, data, sizeof(fuel_cons) );

    fuel_cons_curr        = ( fuel_cons[3] << SHIFT_THREE_BYTES ) |
                            ( fuel_cons[2] << SHIFT_TWO_BYTES )   |
                            ( fuel_cons[1] << SHIFT_ONE_BYTE )    |
                            ( fuel_cons[0] );

#if( SYC_CAN_SUPPORT )
    PRINTF( "Set fuel consumption:%d\r\n", fuel_cons_curr );
#endif
    }
}

/*------------------------------------------------------
Fuel consumption get call back
------------------------------------------------------*/
void can_mid_fuel_cons_get_cb
    (
    bool    status,
    void*   data
    )
{
uint8 fuel_cons[4] = { 0 };

/*------------------------------------------------------
Get the fuel consumption in the eeprom successfully
------------------------------------------------------*/
if( status == TRUE )
    {
    fuel_cons_read_status = status;
    memcpy( fuel_cons, data, sizeof(fuel_cons) );

    fuel_cons_pre         = ( fuel_cons[3] << SHIFT_THREE_BYTES ) |
                            ( fuel_cons[2] << SHIFT_TWO_BYTES )   |
                            ( fuel_cons[1] << SHIFT_ONE_BYTE )    |
                            ( fuel_cons[0] );

    /*------------------------------------------------------
    If this is the first time to read fuel consumption,reset
    fuel_cons_pre
    ------------------------------------------------------*/
    if( fuel_cons[3] == 0xFF &&
        fuel_cons[2] == 0xFF &&
        fuel_cons[1] == 0xFF &&
        fuel_cons[0] == 0xFF )
        {
        fuel_cons_pre = 0;
        }

#if( SYC_CAN_SUPPORT )
    PRINTF( "Get fuel consumption:%d\r\n", fuel_cons_pre );
#endif
    }
}

/*------------------------------------------------------
Read the current fuel consumption
------------------------------------------------------*/
uint32 can_mid_fuel_cons_get
    (
    void
    )
{
return fuel_cons_curr;
}

/*------------------------------------------------------
Read the previous consumption eeprom every IGN ON
------------------------------------------------------*/
void can_mid_fuel_cons_init
    (
    void
    )
{
EEPM_get_fuel_consumption( can_mid_fuel_cons_get_cb );
}

/*------------------------------------------------------
Write the current consumption to eeprom every IGN OFF
------------------------------------------------------*/
void can_mid_fuel_cons_deinit
    (
    uint32 fuel_cons
    )
{
EEPM_set_fuel_consumption( fuel_cons, can_mid_fuel_cons_set_cb );
}

/*------------------------------------------------------
Send fuel consumption when Bt connected after IGN ON
------------------------------------------------------*/
void can_mid_send_fuel_cons
    (
    void
    )
{
static bool fuel_cons_syned = FALSE;

/*------------------------------------------------------
Send Fuel consumption to APP once after getting the value
successfully, IGN ON, and BT connetcted
------------------------------------------------------*/
if( fuel_cons_syned == FALSE      &&
    fuel_cons_read_status == TRUE &&
    BC_motocon_is_connected() )
    {
    fuel_cons_syned = TRUE;

    /*------------------------------------------------------
    Send to APP
    ------------------------------------------------------*/
    BC_motocon_send_injection_quantity( (uint8*)&fuel_cons_pre );
    }
}

/*------------------------------------------------------
Fuel consumption power manager status call back
------------------------------------------------------*/
void can_mid_fuel_cons_pm_cb
    (
    bool status
    )
{
ign_status = status;

if( ign_status == PM_IGN_OFF )
    {
    fuel_cons_pre = fuel_cons_curr;
    can_mid_fuel_cons_deinit( fuel_cons_pre );
    }
}

/*------------------------------------------------------
Calculate the fuel consumption by EG_status(0x23E) every
1000ms and store it when IGN OFF
------------------------------------------------------*/
void can_mid_fuel_cons_calc_task
    (
    void
    )
{
static uint32 fuel_cons_calc_tick = 0;
uint32 fuel_cons_instans          = 0;

/*------------------------------------------------------
Injection value effects after IGN on
------------------------------------------------------*/
if( ign_status == PM_IGN_ON )
    {
    /*------------------------------------------------------
    Send fuel consumption to APP one time
    ------------------------------------------------------*/
    can_mid_send_fuel_cons();

    /*------------------------------------------------------
    Get the injection value from ram in EG_status every 1000ms
    ------------------------------------------------------*/
    if( fuel_cons_calc_tick < MID_FUEL_CONS_CALC_TIME )
        {
        fuel_cons_calc_tick++;
        if( fuel_cons_calc_tick >= MID_FUEL_CONS_CALC_TIME )
            {
            fuel_cons_calc_tick = 0;

            nim_app_sig_get( IL_CAN0_EG_STAT_INJECT_RXSIG_HANDLE, IL_CAN0_EG_STAT_INJECT_RXSIG_NBYTES, &fuel_cons_instans );
            fuel_cons_curr += fuel_cons_instans;
            }
        }
    }
}

/*------------------------------------------------------
Init CAN middle layer module
------------------------------------------------------*/
void can_mid_init
    (
    void
    )
{
EnumOperationMode mode = EnumOperationModeNORMAL;

/*------------------------------------------------------
Regiter the power manager call back for CAN middle layer
------------------------------------------------------*/
PM_register_callback( "CANbus",  can_mid_fuel_cons_pm_cb );

/*------------------------------------------------------
Read the fuel consumption from eeprom
------------------------------------------------------*/
can_mid_fuel_cons_init();

/*------------------------------------------------------
Init the supported function list
------------------------------------------------------*/
mid_sfl_init();

/*------------------------------------------------------
Init message list
------------------------------------------------------*/
mid_msg_list_init();

/*------------------------------------------------------
Get Operation Mode
------------------------------------------------------*/
if( EW_get_operation_mode( &mode ) )
    {
    /*------------------------------------------------------
    Handshake request(0x581) should not be sended when the
    operation mode is Factory or Inspection
    ------------------------------------------------------*/
    if( EnumOperationModeNORMAL == mode )
        {
        /*------------------------------------------------------
        Handshake with Meter to check out those functions
        it supports
        ------------------------------------------------------*/
        can_mid_hand_shake();
        }
    }
else
    {
    /*------------------------------------------------------
    Handshake with Meter to check out those functions
    it supports
    ------------------------------------------------------*/
    can_mid_hand_shake();
    }

#if( DEBUG_TX_CAN_SUPPORT )
/*------------------------------------------------------
No response test case
------------------------------------------------------*/
can_mid_no_resp_test();

/*------------------------------------------------------
Positive and negative test case
------------------------------------------------------*/
can_mid_pos_neg_test();
#endif
}

/*------------------------------------------------------
Middle layer request  and response message task
------------------------------------------------------*/
void can_mid_task
    (
    void
    )
{
can_ret_code_t   l_ret_code       = CAN_RC_NOT_AVAILABLE;
uint8           *l_node_time_p    = NULL;
uint16          *l_node_wait_p    = NULL;
mid_msg_stat_t  *l_node_status_p  = NULL;
can_msg_t       *l_node_req_p     = NULL;
mid_msg_lst      l_node_p         = msg_lst_head;

/*------------------------------------------------------
Fuel consumption task
------------------------------------------------------*/
can_mid_fuel_cons_calc_task();

/*------------------------------------------------------
There is no request message in the list
------------------------------------------------------*/
if( l_node_p == NULL )
    {
    return;
    }

/*------------------------------------------------------
Handle all the nodes in the list
------------------------------------------------------*/
while( l_node_p->next != NULL )
    {
    l_node_p = l_node_p->next;

    /*------------------------------------------------------
    Get the message node status and request message
    ------------------------------------------------------*/
    l_node_wait_p    = &( l_node_p->req_msg_wait );
    l_node_time_p    = &( l_node_p->req_msg_time );
    l_node_status_p  = &( l_node_p->req_msg_status );
    l_node_req_p     = &( l_node_p->req_msg );

    /*------------------------------------------------------
    Handle message node with different status
    ------------------------------------------------------*/
    switch( *l_node_status_p )
        {
        case MID_MSG_STAT_INITED :

            break;

        case MID_MSG_STAT_WAIT_RES_SHORT :
            /*------------------------------------------------------
            Ticker increases
            ------------------------------------------------------*/
            ( *l_node_wait_p )++;
            if( ( *l_node_wait_p ) > MID_MSG_RES_SHORT_TIMEOUT )
                {
                ( *l_node_wait_p ) = 0;
                ( *l_node_time_p )++;
                if( ( *l_node_time_p ) >= MID_MSG_RE_SEND_TIME_SHORT )
                    {
                    ( *l_node_status_p ) = MID_MSG_STAT_COMM_ERR;

                    /*------------------------------------------------------
                    Notify the communication error
                    ------------------------------------------------------*/
                    PRINTF( "Comm error %x!\r\n", l_node_req_p->id );
                    comm_err = TRUE;
                    }
                else
                    {
                    ( *l_node_status_p ) = MID_MSG_STAT_WAIT_RES_MID;
                    }
                }
            break;

        case MID_MSG_STAT_WAIT_RES_MID :
            /*------------------------------------------------------
            Ticker increases
            ------------------------------------------------------*/
            ( *l_node_wait_p )++;
            if( ( *l_node_wait_p ) > MID_MSG_RES_MID_TIMEOUT )
                {
                ( *l_node_wait_p ) = 0;
                ( *l_node_status_p ) = MID_MSG_STAT_WAIT_RES_SHORT;

                /*------------------------------------------------------
                Re-send the request message 50ms after the first sending
                without response
                ------------------------------------------------------*/
                l_ret_code = il_app_frm_put( l_node_req_p );
                }
            break;

        case MID_MSG_STAT_WAIT_RES_LONG :
            /*------------------------------------------------------
            Ticker increases
            ------------------------------------------------------*/
            ( *l_node_wait_p )++;
            if( ( *l_node_wait_p ) > MID_MSG_RES_LONG_TIMEOUT )
                {
                ( *l_node_wait_p ) = 0;
                ( *l_node_time_p )++;

                /*------------------------------------------------------
                Client judge as communication error if there is no response
                even though Client send the request message for 3 times.
                ------------------------------------------------------*/
                if( ( *l_node_time_p ) >= MID_MSG_RE_SEND_TIME_LONG )
                    {
                    ( *l_node_status_p ) = MID_MSG_STAT_COMM_ERR;

                    /*------------------------------------------------------
                    Notify the communication error
                    ------------------------------------------------------*/
                    PRINTF( "Comm error %x!\r\n", l_node_req_p->id );
                    comm_err = TRUE;
                    }
                }
            break;

        case MID_MSG_STAT_RES_SUCCESS :

            break;


        case MID_MSG_STAT_COMM_ERR :
            //TBD communication error handle.
            break;
        }
    }
}

