// MR2301
//#include <windows.h>
#ifndef _WIN32_H
#define _WIN32_H

#include "doomtype.h"

#ifdef BORLAND31
#define GDI_ERROR               NULL
#define SYSPAL_ERROR    NULL
#endif


#ifdef WIN32_MAIN
        #define EXTERN
#else
        #define EXTERN extern
#endif

EXTERN boolean g_bIsMaster;
// MR260698
//EXTERN char g_cCurrentPlayer;
EXTERN char g_cCurrentPlayerForCmd;
EXTERN char g_cCurrentPlayerForDsp;
// MRSuit
EXTERN char g_cAMCurrentPlayer;
// MR280798
EXTERN char C_PLAYERNUMBER;
//#define C_PLAYERNUMBER                  2

#define DM_SLAVE                                WM_USER+0x100
#define DM_MASTER                               WM_USER+0x101
#define DM_SENDPACKET                   WM_USER+0x110

//void fn_vSlaveNotify();
void I_InitMaster();
//void fn_vSelectPlayer(char cPlayer);
void fn_vSelectPlayerForCmd(char cPlayer);
void fn_vSelectPlayerForDsp(char cPlayer);
void fn_vInitMultiPlayerVariables();

#endif //_WIN32_H
