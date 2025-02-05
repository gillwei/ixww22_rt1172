/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.3 */

#ifndef PB_BLESERVICESTRUCTURE_PB_H_INCLUDED
#define PB_BLESERVICESTRUCTURE_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Enum definitions */
typedef enum _McMalfunctionStatus {
    McMalfunctionStatus_STATUS_UNKNOWN = 0,
    McMalfunctionStatus_X_MARK = 1,
    McMalfunctionStatus_TRIANGLE = 2,
    McMalfunctionStatus_FULL = 3,
    McMalfunctionStatus_TEMPORARY_MALFUNCTION = 4
} McMalfunctionStatus;

typedef enum _McNotificationDataV2_Category {
    McNotificationDataV2_Category_MESSAGE = 0,
    McNotificationDataV2_Category_CALL = 1
} McNotificationDataV2_Category;

/* Struct definitions */
typedef struct _McCanResponse {
    pb_callback_t data_list;
} McCanResponse;

typedef struct _McMalfunctionResponse {
    pb_callback_t list;
} McMalfunctionResponse;

typedef struct _McServerListResponse {
    pb_callback_t server_list;
} McServerListResponse;

typedef struct _McCanResponse_IdData {
    int32_t id;
    pb_callback_t data;
} McCanResponse_IdData;

typedef struct _McFfdResponse {
    int32_t server;
    pb_callback_t data_list;
} McFfdResponse;

typedef struct _McLocalRecordVehicleInformationIntervalRequest {
    int32_t server;
    pb_callback_t id_list;
    bool all_id;
    uint32_t interval;
} McLocalRecordVehicleInformationIntervalRequest;

typedef struct _McLocalRecordVehicleInformationRequest {
    int32_t server;
    pb_callback_t id_list;
    bool all_id;
} McLocalRecordVehicleInformationRequest;

typedef struct _McLocalRecordVehicleInformationResponse {
    int32_t server;
    pb_callback_t data_list;
} McLocalRecordVehicleInformationResponse;

typedef struct _McLocalRecordVehicleInformationResponse_IdData {
    int32_t id;
    pb_callback_t data;
} McLocalRecordVehicleInformationResponse_IdData;

typedef struct _McLocalRecordVehicleInformationSupportIdListResponse {
    int32_t server;
    pb_callback_t id_list;
} McLocalRecordVehicleInformationSupportIdListResponse;

typedef struct _McMalfunctionIntervalRequest {
    int32_t server;
    McMalfunctionStatus status;
    uint32_t interval;
} McMalfunctionIntervalRequest;

typedef struct _McMalfunctionRequest {
    int32_t server;
    McMalfunctionStatus status;
} McMalfunctionRequest;

typedef struct _McMalfunctionResponse_ServerCodeStatus {
    int32_t server;
    int32_t code;
    McMalfunctionStatus status;
} McMalfunctionResponse_ServerCodeStatus;

typedef struct _McMarketDataRequest {
    int32_t server;
    pb_callback_t id_list;
    bool all_id;
} McMarketDataRequest;

typedef struct _McMarketDataResponse {
    int32_t server;
    pb_callback_t data_list;
} McMarketDataResponse;

typedef struct _McMarketDataResponse_IdData {
    int32_t id;
    pb_callback_t data;
} McMarketDataResponse_IdData;

typedef struct _McNotificationDataV2 {
    uint32_t notification_id;
    McNotificationDataV2_Category category;
    int32_t year;
    int32_t month;
    int32_t day;
    int32_t hour;
    int32_t minutes;
    int32_t second;
    pb_callback_t title;
    pb_callback_t sub_title;
    pb_callback_t detail;
} McNotificationDataV2;

typedef struct _McVehicleIdentificationRequest {
    int32_t server;
    pb_callback_t id_list;
    bool all_id;
} McVehicleIdentificationRequest;

typedef struct _McVehicleIdentificationResponse {
    int32_t server;
    pb_callback_t data_list;
} McVehicleIdentificationResponse;

typedef struct _McVehicleIdentificationResponse_IdData {
    int32_t id;
    pb_callback_t data;
} McVehicleIdentificationResponse_IdData;


/* Helper constants for enums */
#define _McMalfunctionStatus_MIN McMalfunctionStatus_STATUS_UNKNOWN
#define _McMalfunctionStatus_MAX McMalfunctionStatus_TEMPORARY_MALFUNCTION
#define _McMalfunctionStatus_ARRAYSIZE ((McMalfunctionStatus)(McMalfunctionStatus_TEMPORARY_MALFUNCTION+1))

#define _McNotificationDataV2_Category_MIN McNotificationDataV2_Category_MESSAGE
#define _McNotificationDataV2_Category_MAX McNotificationDataV2_Category_CALL
#define _McNotificationDataV2_Category_ARRAYSIZE ((McNotificationDataV2_Category)(McNotificationDataV2_Category_CALL+1))


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define McServerListResponse_init_default        {{{NULL}, NULL}}
#define McMalfunctionRequest_init_default        {0, _McMalfunctionStatus_MIN}
#define McMalfunctionResponse_init_default       {{{NULL}, NULL}}
#define McMalfunctionResponse_ServerCodeStatus_init_default {0, 0, _McMalfunctionStatus_MIN}
#define McMalfunctionIntervalRequest_init_default {0, _McMalfunctionStatus_MIN, 0}
#define McVehicleIdentificationRequest_init_default {0, {{NULL}, NULL}, 0}
#define McVehicleIdentificationResponse_init_default {0, {{NULL}, NULL}}
#define McVehicleIdentificationResponse_IdData_init_default {0, {{NULL}, NULL}}
#define McMarketDataRequest_init_default         {0, {{NULL}, NULL}, 0}
#define McMarketDataResponse_init_default        {0, {{NULL}, NULL}}
#define McMarketDataResponse_IdData_init_default {0, {{NULL}, NULL}}
#define McLocalRecordVehicleInformationSupportIdListResponse_init_default {0, {{NULL}, NULL}}
#define McLocalRecordVehicleInformationRequest_init_default {0, {{NULL}, NULL}, 0}
#define McLocalRecordVehicleInformationResponse_init_default {0, {{NULL}, NULL}}
#define McLocalRecordVehicleInformationResponse_IdData_init_default {0, {{NULL}, NULL}}
#define McLocalRecordVehicleInformationIntervalRequest_init_default {0, {{NULL}, NULL}, 0, 0}
#define McFfdResponse_init_default               {0, {{NULL}, NULL}}
#define McCanResponse_init_default               {{{NULL}, NULL}}
#define McCanResponse_IdData_init_default        {0, {{NULL}, NULL}}
#define McNotificationDataV2_init_default        {0, _McNotificationDataV2_Category_MIN, 0, 0, 0, 0, 0, 0, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}}
#define McServerListResponse_init_zero           {{{NULL}, NULL}}
#define McMalfunctionRequest_init_zero           {0, _McMalfunctionStatus_MIN}
#define McMalfunctionResponse_init_zero          {{{NULL}, NULL}}
#define McMalfunctionResponse_ServerCodeStatus_init_zero {0, 0, _McMalfunctionStatus_MIN}
#define McMalfunctionIntervalRequest_init_zero   {0, _McMalfunctionStatus_MIN, 0}
#define McVehicleIdentificationRequest_init_zero {0, {{NULL}, NULL}, 0}
#define McVehicleIdentificationResponse_init_zero {0, {{NULL}, NULL}}
#define McVehicleIdentificationResponse_IdData_init_zero {0, {{NULL}, NULL}}
#define McMarketDataRequest_init_zero            {0, {{NULL}, NULL}, 0}
#define McMarketDataResponse_init_zero           {0, {{NULL}, NULL}}
#define McMarketDataResponse_IdData_init_zero    {0, {{NULL}, NULL}}
#define McLocalRecordVehicleInformationSupportIdListResponse_init_zero {0, {{NULL}, NULL}}
#define McLocalRecordVehicleInformationRequest_init_zero {0, {{NULL}, NULL}, 0}
#define McLocalRecordVehicleInformationResponse_init_zero {0, {{NULL}, NULL}}
#define McLocalRecordVehicleInformationResponse_IdData_init_zero {0, {{NULL}, NULL}}
#define McLocalRecordVehicleInformationIntervalRequest_init_zero {0, {{NULL}, NULL}, 0, 0}
#define McFfdResponse_init_zero                  {0, {{NULL}, NULL}}
#define McCanResponse_init_zero                  {{{NULL}, NULL}}
#define McCanResponse_IdData_init_zero           {0, {{NULL}, NULL}}
#define McNotificationDataV2_init_zero           {0, _McNotificationDataV2_Category_MIN, 0, 0, 0, 0, 0, 0, {{NULL}, NULL}, {{NULL}, NULL}, {{NULL}, NULL}}

/* Field tags (for use in manual encoding/decoding) */
#define McCanResponse_data_list_tag              3
#define McMalfunctionResponse_list_tag           3
#define McServerListResponse_server_list_tag     3
#define McCanResponse_IdData_id_tag              1
#define McCanResponse_IdData_data_tag            2
#define McFfdResponse_server_tag                 3
#define McFfdResponse_data_list_tag              4
#define McLocalRecordVehicleInformationIntervalRequest_server_tag 3
#define McLocalRecordVehicleInformationIntervalRequest_id_list_tag 4
#define McLocalRecordVehicleInformationIntervalRequest_all_id_tag 5
#define McLocalRecordVehicleInformationIntervalRequest_interval_tag 6
#define McLocalRecordVehicleInformationRequest_server_tag 3
#define McLocalRecordVehicleInformationRequest_id_list_tag 4
#define McLocalRecordVehicleInformationRequest_all_id_tag 5
#define McLocalRecordVehicleInformationResponse_server_tag 3
#define McLocalRecordVehicleInformationResponse_data_list_tag 4
#define McLocalRecordVehicleInformationResponse_IdData_id_tag 1
#define McLocalRecordVehicleInformationResponse_IdData_data_tag 2
#define McLocalRecordVehicleInformationSupportIdListResponse_server_tag 3
#define McLocalRecordVehicleInformationSupportIdListResponse_id_list_tag 4
#define McMalfunctionIntervalRequest_server_tag  3
#define McMalfunctionIntervalRequest_status_tag  4
#define McMalfunctionIntervalRequest_interval_tag 5
#define McMalfunctionRequest_server_tag          3
#define McMalfunctionRequest_status_tag          4
#define McMalfunctionResponse_ServerCodeStatus_server_tag 1
#define McMalfunctionResponse_ServerCodeStatus_code_tag 2
#define McMalfunctionResponse_ServerCodeStatus_status_tag 3
#define McMarketDataRequest_server_tag           3
#define McMarketDataRequest_id_list_tag          4
#define McMarketDataRequest_all_id_tag           5
#define McMarketDataResponse_server_tag          3
#define McMarketDataResponse_data_list_tag       4
#define McMarketDataResponse_IdData_id_tag       1
#define McMarketDataResponse_IdData_data_tag     2
#define McNotificationDataV2_notification_id_tag 3
#define McNotificationDataV2_category_tag        4
#define McNotificationDataV2_year_tag            5
#define McNotificationDataV2_month_tag           6
#define McNotificationDataV2_day_tag             7
#define McNotificationDataV2_hour_tag            8
#define McNotificationDataV2_minutes_tag         9
#define McNotificationDataV2_second_tag          10
#define McNotificationDataV2_title_tag           11
#define McNotificationDataV2_sub_title_tag       12
#define McNotificationDataV2_detail_tag          13
#define McVehicleIdentificationRequest_server_tag 3
#define McVehicleIdentificationRequest_id_list_tag 4
#define McVehicleIdentificationRequest_all_id_tag 5
#define McVehicleIdentificationResponse_server_tag 3
#define McVehicleIdentificationResponse_data_list_tag 4
#define McVehicleIdentificationResponse_IdData_id_tag 1
#define McVehicleIdentificationResponse_IdData_data_tag 2

/* Struct field encoding specification for nanopb */
#define McServerListResponse_FIELDLIST(X, a) \
X(a, CALLBACK, REPEATED, INT32,    server_list,       3)
#define McServerListResponse_CALLBACK pb_default_field_callback
#define McServerListResponse_DEFAULT NULL

#define McMalfunctionRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    server,            3) \
X(a, STATIC,   SINGULAR, UENUM,    status,            4)
#define McMalfunctionRequest_CALLBACK NULL
#define McMalfunctionRequest_DEFAULT NULL

#define McMalfunctionResponse_FIELDLIST(X, a) \
X(a, CALLBACK, REPEATED, MESSAGE,  list,              3)
#define McMalfunctionResponse_CALLBACK pb_default_field_callback
#define McMalfunctionResponse_DEFAULT NULL
#define McMalfunctionResponse_list_MSGTYPE McMalfunctionResponse_ServerCodeStatus

#define McMalfunctionResponse_ServerCodeStatus_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    server,            1) \
X(a, STATIC,   SINGULAR, INT32,    code,              2) \
X(a, STATIC,   SINGULAR, UENUM,    status,            3)
#define McMalfunctionResponse_ServerCodeStatus_CALLBACK NULL
#define McMalfunctionResponse_ServerCodeStatus_DEFAULT NULL

#define McMalfunctionIntervalRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    server,            3) \
X(a, STATIC,   SINGULAR, UENUM,    status,            4) \
X(a, STATIC,   SINGULAR, UINT32,   interval,          5)
#define McMalfunctionIntervalRequest_CALLBACK NULL
#define McMalfunctionIntervalRequest_DEFAULT NULL

#define McVehicleIdentificationRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    server,            3) \
X(a, CALLBACK, REPEATED, INT32,    id_list,           4) \
X(a, STATIC,   SINGULAR, BOOL,     all_id,            5)
#define McVehicleIdentificationRequest_CALLBACK pb_default_field_callback
#define McVehicleIdentificationRequest_DEFAULT NULL

#define McVehicleIdentificationResponse_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    server,            3) \
X(a, CALLBACK, REPEATED, MESSAGE,  data_list,         4)
#define McVehicleIdentificationResponse_CALLBACK pb_default_field_callback
#define McVehicleIdentificationResponse_DEFAULT NULL
#define McVehicleIdentificationResponse_data_list_MSGTYPE McVehicleIdentificationResponse_IdData

#define McVehicleIdentificationResponse_IdData_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    id,                1) \
X(a, CALLBACK, SINGULAR, BYTES,    data,              2)
#define McVehicleIdentificationResponse_IdData_CALLBACK pb_default_field_callback
#define McVehicleIdentificationResponse_IdData_DEFAULT NULL

#define McMarketDataRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    server,            3) \
X(a, CALLBACK, REPEATED, INT32,    id_list,           4) \
X(a, STATIC,   SINGULAR, BOOL,     all_id,            5)
#define McMarketDataRequest_CALLBACK pb_default_field_callback
#define McMarketDataRequest_DEFAULT NULL

#define McMarketDataResponse_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    server,            3) \
X(a, CALLBACK, REPEATED, MESSAGE,  data_list,         4)
#define McMarketDataResponse_CALLBACK pb_default_field_callback
#define McMarketDataResponse_DEFAULT NULL
#define McMarketDataResponse_data_list_MSGTYPE McMarketDataResponse_IdData

#define McMarketDataResponse_IdData_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    id,                1) \
X(a, CALLBACK, SINGULAR, BYTES,    data,              2)
#define McMarketDataResponse_IdData_CALLBACK pb_default_field_callback
#define McMarketDataResponse_IdData_DEFAULT NULL

#define McLocalRecordVehicleInformationSupportIdListResponse_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    server,            3) \
X(a, CALLBACK, REPEATED, INT32,    id_list,           4)
#define McLocalRecordVehicleInformationSupportIdListResponse_CALLBACK pb_default_field_callback
#define McLocalRecordVehicleInformationSupportIdListResponse_DEFAULT NULL

#define McLocalRecordVehicleInformationRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    server,            3) \
X(a, CALLBACK, REPEATED, INT32,    id_list,           4) \
X(a, STATIC,   SINGULAR, BOOL,     all_id,            5)
#define McLocalRecordVehicleInformationRequest_CALLBACK pb_default_field_callback
#define McLocalRecordVehicleInformationRequest_DEFAULT NULL

#define McLocalRecordVehicleInformationResponse_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    server,            3) \
X(a, CALLBACK, REPEATED, MESSAGE,  data_list,         4)
#define McLocalRecordVehicleInformationResponse_CALLBACK pb_default_field_callback
#define McLocalRecordVehicleInformationResponse_DEFAULT NULL
#define McLocalRecordVehicleInformationResponse_data_list_MSGTYPE McLocalRecordVehicleInformationResponse_IdData

#define McLocalRecordVehicleInformationResponse_IdData_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    id,                1) \
X(a, CALLBACK, SINGULAR, BYTES,    data,              2)
#define McLocalRecordVehicleInformationResponse_IdData_CALLBACK pb_default_field_callback
#define McLocalRecordVehicleInformationResponse_IdData_DEFAULT NULL

#define McLocalRecordVehicleInformationIntervalRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    server,            3) \
X(a, CALLBACK, REPEATED, INT32,    id_list,           4) \
X(a, STATIC,   SINGULAR, BOOL,     all_id,            5) \
X(a, STATIC,   SINGULAR, UINT32,   interval,          6)
#define McLocalRecordVehicleInformationIntervalRequest_CALLBACK pb_default_field_callback
#define McLocalRecordVehicleInformationIntervalRequest_DEFAULT NULL

#define McFfdResponse_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    server,            3) \
X(a, CALLBACK, REPEATED, BYTES,    data_list,         4)
#define McFfdResponse_CALLBACK pb_default_field_callback
#define McFfdResponse_DEFAULT NULL

#define McCanResponse_FIELDLIST(X, a) \
X(a, CALLBACK, REPEATED, MESSAGE,  data_list,         3)
#define McCanResponse_CALLBACK pb_default_field_callback
#define McCanResponse_DEFAULT NULL
#define McCanResponse_data_list_MSGTYPE McCanResponse_IdData

#define McCanResponse_IdData_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, INT32,    id,                1) \
X(a, CALLBACK, SINGULAR, BYTES,    data,              2)
#define McCanResponse_IdData_CALLBACK pb_default_field_callback
#define McCanResponse_IdData_DEFAULT NULL

#define McNotificationDataV2_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   notification_id,   3) \
X(a, STATIC,   SINGULAR, UENUM,    category,          4) \
X(a, STATIC,   SINGULAR, INT32,    year,              5) \
X(a, STATIC,   SINGULAR, INT32,    month,             6) \
X(a, STATIC,   SINGULAR, INT32,    day,               7) \
X(a, STATIC,   SINGULAR, INT32,    hour,              8) \
X(a, STATIC,   SINGULAR, INT32,    minutes,           9) \
X(a, STATIC,   SINGULAR, INT32,    second,           10) \
X(a, CALLBACK, SINGULAR, STRING,   title,            11) \
X(a, CALLBACK, SINGULAR, STRING,   sub_title,        12) \
X(a, CALLBACK, SINGULAR, STRING,   detail,           13)
#define McNotificationDataV2_CALLBACK pb_default_field_callback
#define McNotificationDataV2_DEFAULT NULL

extern const pb_msgdesc_t McServerListResponse_msg;
extern const pb_msgdesc_t McMalfunctionRequest_msg;
extern const pb_msgdesc_t McMalfunctionResponse_msg;
extern const pb_msgdesc_t McMalfunctionResponse_ServerCodeStatus_msg;
extern const pb_msgdesc_t McMalfunctionIntervalRequest_msg;
extern const pb_msgdesc_t McVehicleIdentificationRequest_msg;
extern const pb_msgdesc_t McVehicleIdentificationResponse_msg;
extern const pb_msgdesc_t McVehicleIdentificationResponse_IdData_msg;
extern const pb_msgdesc_t McMarketDataRequest_msg;
extern const pb_msgdesc_t McMarketDataResponse_msg;
extern const pb_msgdesc_t McMarketDataResponse_IdData_msg;
extern const pb_msgdesc_t McLocalRecordVehicleInformationSupportIdListResponse_msg;
extern const pb_msgdesc_t McLocalRecordVehicleInformationRequest_msg;
extern const pb_msgdesc_t McLocalRecordVehicleInformationResponse_msg;
extern const pb_msgdesc_t McLocalRecordVehicleInformationResponse_IdData_msg;
extern const pb_msgdesc_t McLocalRecordVehicleInformationIntervalRequest_msg;
extern const pb_msgdesc_t McFfdResponse_msg;
extern const pb_msgdesc_t McCanResponse_msg;
extern const pb_msgdesc_t McCanResponse_IdData_msg;
extern const pb_msgdesc_t McNotificationDataV2_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define McServerListResponse_fields &McServerListResponse_msg
#define McMalfunctionRequest_fields &McMalfunctionRequest_msg
#define McMalfunctionResponse_fields &McMalfunctionResponse_msg
#define McMalfunctionResponse_ServerCodeStatus_fields &McMalfunctionResponse_ServerCodeStatus_msg
#define McMalfunctionIntervalRequest_fields &McMalfunctionIntervalRequest_msg
#define McVehicleIdentificationRequest_fields &McVehicleIdentificationRequest_msg
#define McVehicleIdentificationResponse_fields &McVehicleIdentificationResponse_msg
#define McVehicleIdentificationResponse_IdData_fields &McVehicleIdentificationResponse_IdData_msg
#define McMarketDataRequest_fields &McMarketDataRequest_msg
#define McMarketDataResponse_fields &McMarketDataResponse_msg
#define McMarketDataResponse_IdData_fields &McMarketDataResponse_IdData_msg
#define McLocalRecordVehicleInformationSupportIdListResponse_fields &McLocalRecordVehicleInformationSupportIdListResponse_msg
#define McLocalRecordVehicleInformationRequest_fields &McLocalRecordVehicleInformationRequest_msg
#define McLocalRecordVehicleInformationResponse_fields &McLocalRecordVehicleInformationResponse_msg
#define McLocalRecordVehicleInformationResponse_IdData_fields &McLocalRecordVehicleInformationResponse_IdData_msg
#define McLocalRecordVehicleInformationIntervalRequest_fields &McLocalRecordVehicleInformationIntervalRequest_msg
#define McFfdResponse_fields &McFfdResponse_msg
#define McCanResponse_fields &McCanResponse_msg
#define McCanResponse_IdData_fields &McCanResponse_IdData_msg
#define McNotificationDataV2_fields &McNotificationDataV2_msg

/* Maximum encoded size of messages (where known) */
/* McServerListResponse_size depends on runtime parameters */
#define McMalfunctionRequest_size                13
/* McMalfunctionResponse_size depends on runtime parameters */
#define McMalfunctionResponse_ServerCodeStatus_size 24
#define McMalfunctionIntervalRequest_size        19
/* McVehicleIdentificationRequest_size depends on runtime parameters */
/* McVehicleIdentificationResponse_size depends on runtime parameters */
/* McVehicleIdentificationResponse_IdData_size depends on runtime parameters */
/* McMarketDataRequest_size depends on runtime parameters */
/* McMarketDataResponse_size depends on runtime parameters */
/* McMarketDataResponse_IdData_size depends on runtime parameters */
/* McLocalRecordVehicleInformationSupportIdListResponse_size depends on runtime parameters */
/* McLocalRecordVehicleInformationRequest_size depends on runtime parameters */
/* McLocalRecordVehicleInformationResponse_size depends on runtime parameters */
/* McLocalRecordVehicleInformationResponse_IdData_size depends on runtime parameters */
/* McLocalRecordVehicleInformationIntervalRequest_size depends on runtime parameters */
/* McFfdResponse_size depends on runtime parameters */
/* McCanResponse_size depends on runtime parameters */
/* McCanResponse_IdData_size depends on runtime parameters */
/* McNotificationDataV2_size depends on runtime parameters */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
