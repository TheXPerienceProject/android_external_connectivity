#ifndef CNE_SVC_H
#define CNE_SVC_H

/**----------------------------------------------------------------------------
  @file cne_svc.h

  This file provides the CNE interface/Service for the clients.
  It provides the info about all the commands that CNE can handle 
  and all the events that it can send to the clients.

-----------------------------------------------------------------------------*/

/**----------------------------------------------------------------------------
  @mainpage Connectivity Engine Interface.
    This documentation defines the interface for the Connectivity Engine(CNE).

    Connectivity Engine provides differenct services for its clients.

    Given the role the client wants to play, it will suggest the best network 
    that it can use for the best user experience.

    The suggestion are based of carrier profiles and user requirments.

    Clients can also specify its QOS requirments.

    Curently in this release clients can specify only band width requirements.

    Clients will get notified on loss of connectivity on their current rat.

    Clients can get notified if a better rat is availble based of its 
    requirments. 
    
-----------------------------------------------------------------------------*/

/*============================================================================= 
                Copyright (c) 2009 QUALCOMM Incorporated.
               All Rights Reserved.
               Qualcomm Confidential and Proprietary
============================================================================*/



/*=============================================================================  
  EDIT HISTORY FOR MODULE

  $Header: //depot/asic/sandbox/projects/cne/common/extern/inc/cne_svc.h#9 $
  $DateTime: 2009/12/03 19:27:03 $
  $Author: chinht $
  $Change: 1102974 $

  when        who  what, where, why
  ----------  ---  -------------------------------------------------------
  2009-07-15  ysk  First revision.

============================================================================*/

#ifdef __cplusplus
  extern "C" {
#endif /* __cplusplus */

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#ifndef TRUE
/** Boolean true value. */
  #define TRUE   1   
#endif /* TRUE */

#ifndef FALSE
/** Boolean false value. */
  #define FALSE  0   
#endif /* FALSE */

#ifndef NULL
/** NULL */
  #define NULL  0
#endif /* NULL */

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
#define CNE_MAX_SSID_LEN 32
#define CNE_MAX_SCANLIST_SIZE 20

/**
  This is a type for representing the Requests, Notifications that could be
  sent to the CNE.
 */
typedef enum
{
  CNE_REQUEST_INIT_CMD=1,
    /**< Command to initialise the internal CNE modules.*/
  CNE_REQUEST_REG_ROLE_CMD,
    /**< Command for registering a role that the clients wants to play. */
  CNE_REQUEST_GET_COMPATIBLE_NWS_CMD,
    /**< Command to request a list of Nws for a registered role. */
  CNE_REQUEST_CONFIRM_NW_CMD,
    /**< Command to confirm whether the given networks list is ok. */
  CNE_REQUEST_DEREG_ROLE_CMD,
    /**< Command to deregister the role, once the client is done with it. */
  CNE_REQUEST_REG_NOTIFICATIONS_CMD,
    /**< Command to register a notifications call back, if the client does 
         does not want to get notified via the default mechanism for that 
         platform
     */
  CNE_REQUEST_UPDATE_BATTERY_INFO_CMD,
  CNE_REQUEST_UPDATE_WLAN_INFO_CMD,
  CNE_REQUEST_UPDATE_WWAN_INFO_CMD,
  CNE_NOTIFY_RAT_CONNECT_STATUS_CMD,
  CNE_NOTIFY_DEFAULT_NW_PREF_CMD,
    /**< Command to notify CNE about the uppper layer default nw preference. */
  CNE_REQUEST_UPDATE_WLAN_SCAN_RESULTS_CMD,

  CNE_NOTIFY_SENSOR_EVENT_CMD,
  CNE_REQUEST_CONFIG_IPROUTE2_CMD

  /*  Add other commands here, note these should match with the ones in the
   *  java layer.
   */

} cne_cmd_enum_type;

/**
  This is a type for representing the expected events/responses, requests that 
  the CNE can send to the clients and the upperlayer connectionManager.
 */
typedef enum
{

  CNE_RESPONSE_REG_ROLE_MSG = 1,
    /**< Response for the register role command. */
  CNE_RESPONSE_GET_COMPATIBLE_NWS_MSG,
    /**< Response for the get compatible nws command. */
  CNE_RESPONSE_CONFIRM_NW_MSG,
    /**< Response for the confirm Nw command. */
  CNE_RESPONSE_DEREG_ROLE_MSG,
    /**< Response for the deregister role command. */
  CNE_REQUEST_BRING_RAT_DOWN_MSG,
  CNE_REQUEST_BRING_RAT_UP_MSG,
  CNE_NOTIFY_MORE_PREFERED_RAT_AVAIL_MSG,
    /**< Notifications sent to the registered clients about a more prefered NW
         availability.
     */
  CNE_NOTIFY_RAT_LOST_MSG,
    /**< Notification sent to clients when the RAT they are using is lost.*/
  CNE_REQUEST_START_SCAN_WLAN_MSG,
  CNE_NOTIFY_INFLIGHT_STATUS_MSG
 

} cne_msg_enum_type;

/** Unsigned 32 bit value */
typedef  unsigned long int  uint32;      
/** Unsigned 16 bit value */
typedef  unsigned short     uint16;      
/** Unsigned 8  bit value */
typedef  unsigned char      uint8;       
/** Unsigned 8  bit value */
typedef  unsigned char      byte;       

/** boolean value can be TRUE or FALSE */
typedef  unsigned char      boolean;

/** Signed 32 bit value */
typedef  signed long int    int32;       
/** Signed 16 bit value */
typedef  signed short       int16;       
/** Signed 8  bit value */
typedef  signed char        int8;        


typedef enum // correspond to network State defined in NetworkInfo.java
{
  CNE_NETWORK_STATE_CONNECTING = 0,
  CNE_NETWORK_STATE_CONNECTED,
  CNE_NETWORK_SUSPENDED,
  CNE_NETWORK_DISCONNECTING,
  CNE_NETWORK_DISCONNECTED,
  CNE_NETWORK_UNKNOWN
 
} cne_network_state_enum_type;


/** Role Id Type. */
typedef int32 cne_role_id_type;
/** Registration Id Type. */
typedef int32 cne_reg_id_type;
/** BandWidth type */
typedef uint32 cne_link_bw_type;

/** 
  A call back funtion type that the clients would register with CNE if they 
  do not want to be notified via the default mechanisim used for that platform.
 */
typedef void (*cne_event_notif_cb_type)
(
  cne_msg_enum_type event,
  void *event_data_ptr,
  void *cb_data_ptr 
);

/** 
* A call back funtion type that cnd register with CNE to be
* called by CNE when it wants to send unsolicited message.
  */
typedef void (*cne_messageCbType)
(
  int targetFd, 
  int msgType, 
  int dataLen, 
  void *data
);

/** 
  This is a type representing the list of possible RATs 
 */
typedef enum
{
  CNE_RAT_MIN = 0, //For tagging only
  CNE_RAT_WWAN = CNE_RAT_MIN,
  CNE_RAT_WLAN,
  /* any new rats should be added here */
  CNE_RAT_ANY,
  /**< Any of the above RATs */
  CNE_RAT_NONE,
  /**< None of the abvoe RATs */
  CNE_RAT_MAX, //For tagging only
  /** @internal */
  CNE_RAT_INVALID = CNE_RAT_MAX,
  /**< INVALID RAT */

}cne_rat_type;

/**
 This is a type representing the list of possible subRATs
 */
typedef enum
{

  CNE_NET_SUBTYPE_UNKNOWN = 0, 
  /* Sub type GPRS */
  CNE_NET_SUBTYPE_GPRS, 
  /* Sub type EDGE */
  CNE_NET_SUBTYPE_EDGE,
  /* Sub type UMTS */
  CNE_NET_SUBTYPE_UMTS,
  /* Sub type CDMA IS-95 */
  CNE_NET_SUBTYPE_CDMA,
  /* Sub type EVDO Rev 0 */
  CNE_NET_SUBTYPE_EVDO_0,
  /* Sub type EVDO Rev A */
  CNE_NET_SUBTYPE_EVDO_A,
  /* Sub type 1x RTT */
  CNE_NET_SUBTYPE_1xRTT,
  /* Sub type HSDPA */
  CNE_NET_SUBTYPE_HSDPA,
  /* Sub type HSUPA */
  CNE_NET_SUBTYPE_HSUPA,
  /* Sub type HSPA */
  CNE_NET_SUBTYPE_HSPA,
  /* Sub type 802.11 B */
  CNE_NET_SUBTYPE_WLAN_B,
  /* Sub type 802.11 G */
  CNE_NET_SUBTYPE_WLAN_G

}cne_rat_subtype;


/* cmd handlers will pass the cmd data as raw bytes.
 * the bytes specified below are for a 32 bit machine
 */
/** @note 
   BooleanNote: the daemon will receive the boolean as a 4 byte integer 
   cne may treat it as a 1 byte internally
 */
/**
  Command data structure to be passed for the CNE_REQUEST_REG_ROLE_CMD
 */
typedef struct
{
  cne_role_id_type role_id;            
  /**< role Id 4 bytes */
  cne_reg_id_type reg_id;             
  /**< regestration  Id 4 bytes */
  cne_link_bw_type fwd_link_bw;
  /**< forward link band width 4 bytes */
  cne_link_bw_type rev_link_bw;
  /**< reverse link band width 4 bytes */
} cne_reg_role_cmd_args_type;

/**
  Command data structure to be passed for the CNE_REQUEST_DEREG_ROLE_CMD
 */
typedef struct
{
  cne_reg_id_type reg_id;
  /**< regestration  Id 4 bytes */
} cne_dereg_role_cmd_args_type;

/**
  Command data structure to be passed for the CNE_REQUEST_GET_COMPATIBLE_NWS_CMD
 */
typedef struct
{
  cne_reg_id_type reg_id;
  /**< regestration  Id 4 bytes */
} cne_get_compatible_nws_cmd_args_type;

/**
  Command data structure to be passed for the CNE_REQUEST_REG_NOTIFICATIONS_CMD
 */
typedef struct
{
  cne_reg_id_type reg_id; 
  /**< regestration  Id 4 bytes */
  cne_event_notif_cb_type cb_fn_ptr;
  /**< notification call back function pointer 4 bytes */
  void* cb_data_ptr;
  /**< call back data pointer 4 bytes */
} cne_reg_notifs_cmd_args_type;

/**
  Command data structure to be passed for the CNE_REQUEST_CONFIRM_NW_CMD
 */
typedef struct
{
  cne_reg_id_type reg_id;
  /**< regestration  Id 4 bytes */
  cne_rat_type rat;
  /**< rat to confirmed 4 bytes */
  boolean is_rat_ok;
  /**< was the rat given ok TRUE if satisfied else FALSE 1 byte see BooleanNote
   */
  boolean is_notif_if_better_rat_avail;
  /**< TRUE if notifications be sent on better rat availability 1 bye 
       see BooleanNote
   */
  cne_rat_type new_rat;
  /**< if not satisfied with the given rat what is the new rat that you would
       like. 4 bytes 
   */
} cne_confirm_nw_cmd_args_type;



/** 
  Response info structure returned for the response CNE_RESPONSE_REG_ROLE_MSG
 */
typedef struct
{
  cne_reg_id_type reg_id;
  /**< regestration  Id 4 bytes */
  boolean is_success;
  /**< TRUE if the request was successful. 1 byte see BooleanNote */
} cne_reg_role_rsp_evt_data_type;


/** 
  Response info structure returned for the response CNE_RESPONSE_GET_COMPATIBLE_NWS_MSG
 */
typedef struct
{
  cne_reg_id_type reg_id;
  /**< regestration  Id 4 bytes */
  boolean is_success;
  /**< TRUE if the request was successful. 1 byte see BooleanNote */
  /* if success send the rat info */
  cne_rat_type best_rat;
  /**< this is the best rat for this registration/role. 4 bytes */
  /* to do other ratInfo */
  cne_rat_type rat_pref_order[CNE_RAT_MAX]; 
  /**< Other Compatible RATs. CNE_RAT_MAX*4 bytes */
} cne_get_compatible_nws_evt_rsp_data_type;


/** 
  Response info structure returned for the response CNE_RESPONSE_CONFIRM_NW_MSG
 */
typedef struct
{
  cne_reg_id_type reg_id;
  /**< regestration  Id 4 bytes */
  boolean is_success;
  /**< TRUE if the request was successful. 1 byte see BooleanNote */
} cne_confirm_nw_evt_rsp_data_type;


/** 
  Response info structure returned for the response CNE_RESPONSE_DEREG_ROLE_MSG
 */
typedef struct
{
  cne_reg_id_type reg_id;
  /**< regestration  Id 4 bytes */
  boolean is_success;
  /**< TRUE if the request was successful. 1 byte see BooleanNote */
} cne_dereg_role_evt_rsp_data_type;


/** 
  Response info structure returned for the event CNE_NOTIFY_RAT_LOST_MSG
 */
typedef struct
{
  cne_reg_id_type reg_id;
  /**< regestration  Id 4 bytes */
  cne_rat_type rat;
  /**< Rat type which has lost the connectivity. 4 bytes */
} cne_rat_lost_evt_data_type;


/** 
  Response info structure returned for the event
  CNE_NOTIFY_MORE_PREFERED_RAT_AVAIL_MSG
 */
typedef struct
{
  cne_reg_id_type reg_id;
  /**< regestration  Id 4 bytes */
  cne_rat_type rat;
  /**< Rat type which is better for this registration/role 4 bytes */
  /* to do other ratInfo */
} cne_pref_rat_avail_evt_data_type;

/** 
  Response info structure returned for the event
  CNE_NOTIFY_INFLIGHT_STATUS_MSG
 */
typedef struct
{
  boolean is_flying;
  /**< true if in flight else false */
} cne_inflight_status_change_evt_data_type;

typedef union {
    cne_rat_type rat;
    struct {
        cne_rat_type rat;
        char ssid[CNE_MAX_SSID_LEN];
    } wlan;
    struct {
        cne_rat_type rat;
    } wwan;
    
} CneRatInfoType;


typedef struct  {
    int32 status; 
    int32 rssi; 
    char *ssid;
} CneWlanInfoType;

typedef struct {
    int32 level; 
    int32 frequency; 
    char *ssid;
    char *bssid;
    char *capabilities;
}CneWlanScanListInfoType;

typedef struct  {
    int numItems;
    CneWlanScanListInfoType scanList[CNE_MAX_SCANLIST_SIZE];
} CneWlanScanResultsType;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

/**
 @brief cne_svc_init creates the internal cne sub modules.
        This functions needs to be called only once at the power up.
 @param  None
 @see    None
 @return None

*/
void cne_svc_init();



#ifdef __cplusplus
  }
#endif /* __cplusplus */

#endif /* CNE_SVC_H */

