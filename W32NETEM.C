#define WIN32_LEAN_AND_MEAN

#include <windows.h>		// MR2301

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

#include "doomstat.h"
#include "i_system.h"
#include "multires.h"
#include "m_argv.h"
#include "d_main.h"

#include "doomdef.h"

//#define WIN32_MAIN
#include "win32.h"

// MR070798
extern boolean     automapactive[MAXPLAYERS];
extern fixed_t scale_mtof[MAXPLAYERS];
extern  int markpointnum[MAXPLAYERS];
extern  int followplayer[MAXPLAYERS];
extern  boolean stopped[MAXPLAYERS];
extern  int lastlevel[MAXPLAYERS];
extern  int lastepisode[MAXPLAYERS];
extern  int nexttic[MAXPLAYERS];
extern  int litelevelscnt[MAXPLAYERS];
extern gamestate_t     wipegamestate[MAXPLAYERS];
extern   boolean  viewactivestate[MAXPLAYERS];
extern   boolean  menuactivestate[MAXPLAYERS];
extern   boolean  inhelpscreensstate[MAXPLAYERS];
extern   boolean  fullscreen[MAXPLAYERS];
extern   gamestate_t  oldgamestate[MAXPLAYERS];
extern   boolean  viewactivestate[MAXPLAYERS];
extern   boolean  menuactivestate[MAXPLAYERS];
extern   boolean  inhelpscreensstate[MAXPLAYERS];
extern   boolean  fullscreen[MAXPLAYERS];
extern   gamestate_t  oldgamestate[MAXPLAYERS];
extern  boolean  always_off[MAXPLAYERS];
extern  boolean  headsupactive[MAXPLAYERS];
extern  int head[MAXPLAYERS];
extern  int tail[MAXPLAYERS];
extern  boolean shiftdown[MAXPLAYERS];
extern  boolean altdown[MAXPLAYERS];
extern  int  num_nobrainers[MAXPLAYERS];
extern  int  st_msgcounterMP[MAXPLAYERS];
extern  int st_oldhealthMP[MAXPLAYERS];
extern  int st_facecountMP[MAXPLAYERS];
extern  int st_faceindexMP[MAXPLAYERS];
extern  boolean lastautomapactive[MAXPLAYERS];
#define INITSCALEMTOF (.2*FRACUNIT)
// End MR070798

// MR (2 players only)
extern HWND win[MAXPLAYERS];
extern int closed;
extern HWND g_hSlaveWindow,g_hMasterWindow;

//boolean g_bPacketReceived;
#ifdef BORLAND31		// Voir si ça marche avec Visual...
HGLOBAL g_hDDEMemory;
#endif
doomdata_t *g_swMaster,*g_swSlave;
short *g_p_wMasterDataLength,*g_p_wSlaveDataLength;		// MR0698
short *g_p_wPacketReceiveFromMaster,*g_p_wPacketReceiveFromSlave;
HANDLE g_hMap;

// MRMP
void SetSTStuffForPlayer(char cPlayer);
// MR260698
/*
// MR (2 players only)
void fn_vCreateSharedMemory()
{ LPVOID lpMapAddress;

	g_hMap= CreateFileMapping(	(HANDLE)0xFFFFFFFF,
								NULL,
								PAGE_READWRITE,
								0,
								2*sizeof(doomdata_t)+4*sizeof(short),
								"DoomNet");

	lpMapAddress = MapViewOfFile(g_hMap,  // handle to map. object 
		FILE_MAP_ALL_ACCESS,               // read-write access 
		0,                                 // max. object size 
		0,                                 // size of hFile 
		2*sizeof(doomdata_t)+4*sizeof(short));             // map size	// MR0698

	g_swMaster=(doomdata_t *)lpMapAddress;
	g_swSlave=(doomdata_t *)((char *)lpMapAddress+sizeof(doomdata_t));
	// MR0698
	g_p_wMasterDataLength=(short *)((char *)lpMapAddress+2*sizeof(doomdata_t));
	g_p_wSlaveDataLength=(short *)((char *)lpMapAddress+2*sizeof(doomdata_t)+sizeof(short));
	g_p_wPacketReceiveFromMaster=(short *)((char *)lpMapAddress+2*sizeof(doomdata_t)+2*sizeof(short));
	g_p_wPacketReceiveFromSlave=(short *)((char *)lpMapAddress+2*sizeof(doomdata_t)+3*sizeof(short));
}

void fn_vRecoverSharedMemory()
{ LPVOID lpMapAddress;

	g_hMap=OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE,
                   FALSE,
                   "DoomNet");

	lpMapAddress = MapViewOfFile(g_hMap,  // handle to map. object 
		FILE_MAP_ALL_ACCESS,               // read-write access 
		0,                                 // max. object size 
		0,                                 // size of hFile 
		2*sizeof(doomdata_t)+4*sizeof(short));             // map size

	g_swMaster=(doomdata_t *)lpMapAddress;
	g_swSlave=(doomdata_t *)((char *)lpMapAddress+sizeof(doomdata_t));
	// MR0698
	g_p_wMasterDataLength=(short *)((char *)lpMapAddress+2*sizeof(doomdata_t));
	g_p_wSlaveDataLength=(short *)((char *)lpMapAddress+2*sizeof(doomdata_t)+sizeof(short));
	g_p_wPacketReceiveFromMaster=(short *)((char *)lpMapAddress+2*sizeof(doomdata_t)+2*sizeof(short));
	g_p_wPacketReceiveFromSlave=(short *)((char *)lpMapAddress+2*sizeof(doomdata_t)+3*sizeof(short));
}

//void fn_vSlaveNotify()
//{
//	SendMessage(HWND_BROADCAST,DM_SLAVE,0,(long)win[0]);
//	g_hSlaveWindow=win[0];
//	fn_vRecoverSharedMemory();
//}

void I_InitMaster()
{
	fn_vCreateSharedMemory();
	//g_hMasterWindow=win[0];
}


void fn_vWriteSMswMaster(doomdata_t	*sw,short wDataLength)
{
	if (!closed)
	{	memcpy(g_swMaster,sw,sizeof(doomdata_t));
		*g_p_wMasterDataLength=wDataLength;
		*g_p_wPacketReceiveFromMaster=1;
	}
}

void fn_vWriteSMswSlave(doomdata_t	*sw,short wDataLength)
{
	if (!closed)
	{	memcpy(g_swSlave,sw,sizeof(doomdata_t));
		*g_p_wSlaveDataLength=wDataLength;
		*g_p_wPacketReceiveFromSlave=1;
	}
}

short fn_vReadSMswMaster(doomdata_t	*sw)
{
	if (!closed)
	{	memcpy(sw,g_swMaster,sizeof(doomdata_t));
		return *g_p_wMasterDataLength;
	}
	else
		return -1;
}

short fn_vReadSMswSlave(doomdata_t	*sw)
{
	if (!closed)
	{	memcpy(sw,g_swSlave,sizeof(doomdata_t));
		return *g_p_wSlaveDataLength;
	}
	else
		return -1;
}


//void fn_vCreateDDEMemory()
//{
//#ifdef BORLAND31		// Voir si ça marche avec Visual...
//  void FAR *vPtr;
//	g_hDDEMemory=GlobalAlloc(GMEM_DDESHARE,2*sizeof(doomdata_t));	
//	vPtr=GlobalLock(g_hDDEMemory);
//	g_swMaster=(doomdata_t *)vPtr;
//	g_swSlave=(doomdata_t *)((char *)vPtr+sizeof(doomdata_t));
//#endif
//}


void fn_vSendPacket(doomdata_t	*sw,short wDataLength)	// MR0698
{
	// !!!! ATTENTION !!!
	// sw doit être alloué dans une partie de la mem accessible par les 2 dooms
	// Voir GlobalAlloc et DDE
    // Créer un swMaster et swSlave dans une mem DDE
//
//	if (g_bIsMaster)
//	{	SendMessage(g_hSlaveWindow,DM_SENDPACKET,0,(long)sw);
//		WriteDDEswMaster(sw);	// fct à écrire
//	}
//	else
//	{	SendMessage(g_hMasterWindow,DM_SENDPACKET,0,(long)sw);
//		WriteDDEswSlave(sw);	// fct à écrire
//	}

	if (g_bIsMaster)
	{	
		fn_vWriteSMswMaster(sw,wDataLength);
		//PostMessage(g_hSlaveWindow,DM_SENDPACKET,0,(long)sw);
	}
	else
	{	
		fn_vWriteSMswSlave(sw,wDataLength);
		//PostMessage(g_hMasterWindow,DM_SENDPACKET,0,(long)sw);
	}

}

short fn_wGetPacket(doomdata_t	*sw)
{ boolean bPacketR;
  short wDataLength;

	//bPacketR=g_bPacketReceived;
	bPacketR=g_bIsMaster ? *g_p_wPacketReceiveFromSlave : *g_p_wPacketReceiveFromMaster;
	
	if (bPacketR)
	{	if (g_bIsMaster)
		{	wDataLength=fn_vReadSMswSlave(sw);
			*g_p_wPacketReceiveFromSlave=0;
		}
		else
		{	wDataLength=fn_vReadSMswMaster(sw);
			*g_p_wPacketReceiveFromMaster=0;
		}
	}

	//g_bPacketReceived=false;
    
	if (!bPacketR)
		return -1;
	else
		return wDataLength;
}
// End MR
*/
/*
void fn_vSelectPlayer(char cPlayer)	// MRMP
{
	g_cCurrentPlayer=cPlayer;
// MR260698
//	doomcom=&doomcomMP[g_cCurrentPlayer];
//	netbuffer=&netbufferMP[g_cCurrentPlayer];
//	consoleplayer = doomcom->consoleplayer;
//	localcmds=localcmdsMP[g_cCurrentPlayer]
	consoleplayer = g_cCurrentPlayer;
// End MR260698
	if (g_cCurrentPlayer==0)		// 2 players only
		g_bIsMaster=true;
	else
		g_bIsMaster=false;
	fn_vSetCurrentScreen(g_cCurrentPlayer);
	SetSTStuffForPlayer(g_cCurrentPlayer);
}*/

void fn_vSelectPlayerForCmd(char cPlayer)
{
	g_cCurrentPlayerForCmd=cPlayer;
	//consoleplayer = g_cCurrentPlayer;

//	fn_vSetCurrentScreen(g_cCurrentPlayer);
	//SetSTStuffForPlayer(g_cCurrentPlayerForCmd);
}

void fn_vSelectPlayerForDsp(char cPlayer)
{
	g_cCurrentPlayerForDsp=cPlayer;
	//consoleplayer = g_cCurrentPlayer;

	fn_vSetCurrentScreen(g_cCurrentPlayerForDsp);
	SetSTStuffForPlayer(g_cCurrentPlayerForDsp);
}

void fn_vInitMultiPlayerVariables()
{ char cPlayer;

	for (cPlayer=0;cPlayer<C_PLAYERNUMBER;cPlayer++)
	{	automapactive[cPlayer]=false;
		scale_mtof[cPlayer]=INITSCALEMTOF;
		markpointnum[cPlayer]=0;
		followplayer[cPlayer]=1;
		stopped[cPlayer]=true;
		lastlevel[cPlayer]=-1;
		nexttic[cPlayer]=0;
		litelevelscnt[cPlayer]=0;
		wipegamestate[cPlayer]=GS_DEMOSCREEN;
		viewactivestate[cPlayer]=false;
		menuactivestate[cPlayer]=false;
		inhelpscreensstate[cPlayer]=false;
		fullscreen[cPlayer]=false;
		oldgamestate[cPlayer]=-1;
		viewactivestate[cPlayer]=false;
		menuactivestate[cPlayer]=false;
		inhelpscreensstate[cPlayer]=false;
		fullscreen[cPlayer]=false;
		oldgamestate[cPlayer]=-1;
		lastautomapactive[cPlayer]=true;
		always_off[cPlayer]=false;
		headsupactive[cPlayer]=false;
		head[cPlayer]=0;
		tail[cPlayer]=0;
		shiftdown[cPlayer]=false;
		altdown[cPlayer]=false;
		num_nobrainers[cPlayer]=0;
		st_msgcounterMP[cPlayer]=0;
		st_oldhealthMP[cPlayer]=-1;
		st_facecountMP[cPlayer]=0;
		st_faceindexMP[cPlayer]=0;
		
	}
}