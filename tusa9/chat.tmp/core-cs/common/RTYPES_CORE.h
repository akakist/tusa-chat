#ifndef RTYPE_CS_B___h
#define RTYPE_CS_B___h

/*#define CHANNEL_1 1
#define CHANNEL_2 2
#define CHANNEL_4 4
#define CHANNEL_5 5
*/

//#define FAM_B2CS_USER_MANAGE_10 0x10
    //#define TYPE_B2CS_USER_MANAGE_CREATE_USER_01 0x01
    //#define TYPE_B2CS_USER_MANAGE_DELETE_USER_02 0x02

//#define FAM_OTHER 0x06
    //#define TYPE_PING_09 0x09
    //#define TYPE_PONG_0A 0x0A
//#define FAM_LOGIN 0x01

    //#define TYPE_LOGIN_SEND_AUTH2_02 0x02	// C->CS

    //#define TYPE_NOTIFY_BOS_TO_DELETE_USER_03  0x03 //CS->B

    //#define TYPE_LOGIN_SET_SESSION_ID_05 0x05  //B->C
    //#define TYPE_BOS_LOGIN_RESULT_01 0x01  //CS->B
    //#define TYPE_FORCE_DISCONNECT_04 0x04 // CS->C
    
    //#define TYPE_AUTH_OK_06 0x06
    //#define TYPE_AUTH_FAILED_07 0x07
    

//#define FAM_DATA_EVENT_0 0
//#define FAM_REQUEST_2 2    

enum{
	UDP_SET_YOUR_EXTERNAL_SA	=1,
	UDP_PING					=2,
	UDP_PONG					=3,
	UDP_REQUEST_MM_CHANNEL		=4,
	UDP_DROP_MM_CHANNEL			=5,
	UDP_SLICE					=6,
	UDP_MMDATA					=9,
#ifdef CONTROL_DATA
	UDP_RESEND					=7,
	UDP_CANCELRESEND			=10,
	UDP_PACKETDELIVERED			=11,
#endif
};


#endif
