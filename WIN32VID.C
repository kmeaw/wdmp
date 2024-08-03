/*      win32video.c
 *
 * Win32 DIB graphics routines for DOOM
 * 
 * Petteri Kangaslampi, pekangas@sci.fi
*/

/* Original file header: */
//-----------------------------------------------------------------------------
//
// $Id: win32video.c,v 1.7 1998/01/07 18:44:21 pekangas Exp $
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
// $Log: win32video.c,v $
// Revision 1.7  1998/01/07 18:44:21  pekangas
// Fixed a bunch of Visual C warnings, changed name to NTDOOM and
// made assembler optional
//
// Revision 1.6  1998/01/07 17:28:16  pekangas
// Improved mouse grab a little
//
// Revision 1.5  1998/01/05 14:46:35  pekangas
// Palette is now released when the window deactivates
//
// Revision 1.4  1998/01/05 13:40:58  pekangas
// Fixed I_ReadScreen for 16-bit modes
//
// Revision 1.3  1998/01/04 19:29:09  pekangas
// Added hicolor and multiresulution support from Chi Hoang's DOS port
//
// Revision 1.2  1997/12/29 21:17:17  pekangas
// Fixed to compile with Visual C
// Some Win95 fixes
//
// Revision 1.1  1997/12/29 19:49:10  pekangas
// Initial revision
//
// Revision 1.1.1.1  1997/12/28 12:59:03  pekangas
// Initial DOOM source release from id Software
//
//
// DESCRIPTION:
//      DOOM graphics stuff for X11, UNIX.
//
//-----------------------------------------------------------------------------

const char
win32video_rcsid[] = "$Id: win32video.c,v 1.7 1998/01/07 18:44:21 pekangas Exp $";

#define WIN32_LEAN_AND_MEAN
//#define BENCH

#include <windows.h>            // MR2301
#include <mmsystem.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

// MR2301
#define WIN32_MAIN
#include "win32.h"

#include "doomstat.h"
#include "i_system.h"

#include "multires.h"
#include "m_argv.h"
#include "d_main.h"

#include "doomdef.h"

// MR110798
#ifdef WATWIN31
UINT uiPeekMessageFlag;
boolean bIsPeekMsgYield;
char cKeyLastFrame[256];
#endif
#ifdef CHEATERMP
boolean bCheater[MAXPLAYERS];
extern player_t*        plyrMP[MAXPLAYERS]; 
#endif
//extern void (*fn_vTreatMessage)(MSG *msg);

/* Stuff for multiresolution support: */
int SCREENWIDTH;
int SCREENHEIGHT;
int BPP;
int weirdaspect;
byte *hicolortable;
short hicolortransmask1,hicolortransmask2;


#define POINTER_WARP_COUNTDOWN  1

// Fake mouse handling.
// This cannot work properly w/o DGA.
// Needs an invisible mouse cursor at least.
boolean         grabMouse;
int             doPointerWarp = POINTER_WARP_COUNTDOWN;

int             X_width;
int             X_height;


/* Multiplication - we'll let windows stretch instead */
static int      multiply=1;

int closed=0;

static int disableVerticalMouse = 0;

static int windowActive = 0;

HWND win[MAXPLAYERS];
static HINSTANCE inst;
static HDC dibDC[MAXPLAYERS];
static LOGPALETTE *palette[MAXPLAYERS];
static HPALETTE dibPal[MAXPLAYERS];
static BITMAPINFO *bminfo[MAXPLAYERS];
static unsigned char *dibData[MAXPLAYERS];
static int bits8;

extern doomdata_t *g_swMaster,*g_swSlave;
extern short *g_p_wMasterDataLength,*g_p_wSlaveDataLength;              // MR0698
extern short *g_p_wPacketReceiveFromMaster,*g_p_wPacketReceiveFromSlave;
extern HANDLE g_hMap;

#ifdef BENCH
extern HDC hDCMain;
#endif

HWND g_hSlaveWindow,g_hMasterWindow;

// MR Joy
UINT g_wXAmp,g_wYAmp,g_wXCenter,g_wYCenter;
/*#define C_X_SENSITIVITY 10
#define C_Y_SENSITIVITY 10*/
UINT C_X_SENSITIVITY=10;
UINT C_Y_SENSITIVITY=10;
extern int              usejoystick[MAXPLAYERS];    // MR250698

boolean g_bAutosize;	// MR280798

/* [Petteri] no-allegro-hacks: */
int makecol(int r, int g, int b)
{
    assert(BPP==2);
    return (b >> 3) | ((g >> 3) << 5) | ((r >> 3) << 10);
}
int palette_color[256];

// MR110798
boolean bOnePalette=false;

/*void fn_vTreatMessageNoYield(MSG *msg)
{
        TranslateMessage(msg);
        DispatchMessage(msg);
}*/

#ifdef WATWIN31
void fn_vTreatKey(UINT iKeyMsg,int vKey)
{ event_t event;
    
    switch(iKeyMsg)
    {
        case WM_KEYDOWN:
            event.type = ev_keydown;
            event.data1 = TranslateKey(vKey);
            if ( event.data1 != 0 )
                D_PostEvent(&event);
            break;

        case WM_KEYUP:
            event.type = ev_keyup;
            event.data1 = TranslateKey(vKey);
            if ( event.data1 != 0 )
                D_PostEvent(&event);
            break;
    }
}

void fn_vTreatKeysYield()
{ int i;
    for (i=0;i<256;i++)
        if (GetAsyncKeyState(i) & 0x80000000)
        {   fn_vTreatKey(WM_KEYDOWN,i);
            cKeyLastFrame[i]=1;
        }
        else
        if (cKeyLastFrame[i])
        {   fn_vTreatKey(WM_KEYUP,i);
            cKeyLastFrame[i]=0;
        }
        else
        if (GetAsyncKeyState(i) & 0x00000001)
        {   fn_vTreatKey(WM_KEYDOWN,i);
            fn_vTreatKey(WM_KEYUP,i);
        }
}
#endif

int TranslateKey(unsigned k)
{
/*wtf?    if ( (k >= VK_0) && (k <= VK_9) )*/
    if ( (k >= 0x30) && (k <= 0x39) )
        return (k - 0x30 + '0');
/*    if ( (k >= 0x41) && (k <= 0x5a) )
        return (k - 0x41 + 'a');*/
// MR300698
/*    if ( (k >= 'a') && (k <= 'z') )
        return (k - 'a' + 'A');*/

#define K(a,b) case a: return b;    
    switch ( k )
    {
        K(VK_LEFT, KEY_LEFTARROW);
        K(VK_RIGHT, KEY_RIGHTARROW);
        K(VK_UP, KEY_UPARROW);
        K(VK_DOWN, KEY_DOWNARROW);
        K(VK_BACK, KEY_BACKSPACE);
        K(VK_TAB, KEY_TAB);
        K(VK_RETURN, KEY_ENTER);
        K(VK_SHIFT, KEY_RSHIFT);
        K(VK_CONTROL, KEY_RCTRL);
        K(VK_MENU, KEY_RALT);
        K(VK_PAUSE, KEY_PAUSE);
        K(VK_ESCAPE, KEY_ESCAPE);
        K(VK_SPACE, ' ');
        K(VK_DELETE, KEY_BACKSPACE);
        K(VK_ADD, '+');
        K(VK_SUBTRACT, KEY_MINUS);
        K(0xBC, ',');
        K(0xBE, '.');
        K(VK_F1, KEY_F1);
        K(VK_F2, KEY_F2);
        K(VK_F3, KEY_F3);
        K(VK_F4, KEY_F4);
        K(VK_F5, KEY_F5);
        K(VK_F6, KEY_F6);
        K(VK_F7, KEY_F7);
        K(VK_F8, KEY_F8);
        K(VK_F9, KEY_F9);
        K(VK_F10, KEY_F10);
        K(VK_F11, KEY_F11);
        K(VK_F12, KEY_F12);
    }

    // MR290698
        //return 0;
        return k;
}

// MR280798
#ifndef WATWIN31
DEVMODE dvmdOrig, dvmdRequested, dvmdCurrent;

void fn_vChangeScreenResolution()
{
  HDC hdc;

   // Initialize all the DEVMODE structures
   ZeroMemory(&dvmdOrig, sizeof(dvmdOrig));
   dvmdOrig.dmSize = sizeof(DEVMODE);
   dvmdOrig.dmDriverExtra = 0;
   dvmdOrig.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | 
      DM_BITSPERPEL | DM_DISPLAYFREQUENCY;
	dvmdRequested = dvmdCurrent = dvmdOrig;

   // Get the current screen settings and save them as
   // the "original" settings.
   hdc = GetDC(NULL);  // Screen DC used to get current display settings
	dvmdOrig.dmPelsWidth        = GetDeviceCaps(hdc, HORZRES);
	dvmdOrig.dmPelsHeight       = GetDeviceCaps(hdc, VERTRES);
	dvmdOrig.dmBitsPerPel       = GetDeviceCaps(hdc, BITSPIXEL);
   dvmdOrig.dmDisplayFrequency = GetDeviceCaps(hdc, VREFRESH);
	ReleaseDC(NULL, hdc);

   // Set the new  settings
   dvmdRequested.dmPelsWidth=640;
   dvmdRequested.dmPelsHeight=480;
   dvmdRequested.dmBitsPerPel=16;
   dvmdRequested.dmDisplayFrequency=60;

   // Attempt to chage the screen settings
   if (ChangeDisplaySettings(&dvmdRequested, 0)!= DISP_CHANGE_SUCCESSFUL)
   {
		fprintf(stderr,"Change screen resolution failed\n");
   }
}

void fn_vRestoreScreenResolution()
{
	HDC hdc;

	// Get the current screen settings
	hdc = GetDC(NULL);  // Screen DC used to get current resolution info
	dvmdCurrent.dmPelsWidth        = GetDeviceCaps(hdc, HORZRES);
	dvmdCurrent.dmPelsHeight       = GetDeviceCaps(hdc, VERTRES);
	dvmdCurrent.dmBitsPerPel       = GetDeviceCaps(hdc, BITSPIXEL);
	dvmdCurrent.dmDisplayFrequency = GetDeviceCaps(hdc, VREFRESH);
	ReleaseDC(NULL, hdc);

   // Windows 95 does not support getting/changing the display frequency
   // So, if we get a display frequency of 0, assume that we requested
   // a display frequency of 0.
   if (dvmdCurrent.dmDisplayFrequency == 0)
      dvmdRequested.dmDisplayFrequency = 0;

   // If the current settings match the requested settings,
   // restore the original settings
   if (memcmp(&dvmdCurrent, &dvmdRequested, sizeof(dvmdCurrent)) == 0) {
		ChangeDisplaySettings(&dvmdOrig, CDS_UPDATEREGISTRY);
	}
}

#endif	// WATWIN31


void WinError(char *msg)
{
#ifndef BORLAND31
        printf("Windows Error: %s, GetLastError(): %u\n", msg, GetLastError());
#endif
#ifndef WATWIN31
	if (g_bAutosize)
		fn_vRestoreScreenResolution();	// MR280798
#endif	
	exit(EXIT_FAILURE);
}

void fn_vChangeGrabMouse()
{ RECT rect;
    
        grabMouse=!grabMouse;
        if (grabMouse)
        {
             ClipCursor(NULL); /* helps with Win95? */
             GetWindowRect(win[0], &rect);
             ClipCursor(&rect);
             ShowCursor(FALSE);            
        }
        else
        {
           ClipCursor(NULL);
           ShowCursor(TRUE);
        }
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT message,
                                WPARAM wparam, LPARAM lparam)
{
    event_t event;
    RECT rect;
    
    switch ( message )
    {        
            case WM_DESTROY:
            if ( grabMouse )
            {
                ClipCursor(NULL);
                ShowCursor(TRUE);
            }
            if ( bits8 )
            { char cPlayer;

                                for (cPlayer=0;cPlayer<C_PLAYERNUMBER;cPlayer++)
                                {
                                        if (dibPal[cPlayer])
                                        {
                                        if ( !UnrealizeObject(dibPal[cPlayer]) )
                                                WinError("UnrealizeObject failed");
                                        if ( SetSystemPaletteUse(dibDC[cPlayer], SYSPAL_STATIC) == SYSPAL_ERROR )
                                                WinError("SetSystemPaletteUse failed");
                                        }
                                }
            }
            fprintf(stderr, "WM_DESTROY\n");
            PostQuitMessage(0);
                        // MR (2 players)
/*                      UnmapViewOfFile((LPVOID)g_swMaster);
                        if (g_bIsMaster)
                                CloseHandle(g_hMap);*/
                        // End MR
            closed = 1;
            break;

/*        case WM_MOVE:
            GetWindowRect(win, &rect);
            fprintf(stderr, "%u,%u - %u, %u\n",
                    rect.left,rect.top,rect.right,rect.bottom);
            ClipCursor(&rect);
            break;*/

        case WM_ACTIVATE:
            fprintf(stderr, "WM_ACTIVATE %u\n", (unsigned) LOWORD(wparam));
            if ( LOWORD(wparam) )
            {
                if ( !windowActive )
                {
                    if ( grabMouse )
                    {
                        ClipCursor(NULL); /* helps with Win95? */
                        GetWindowRect(win[0], &rect);
                        fprintf(stderr, "%u,%u - %u, %u\n",
                                rect.left,rect.top,rect.right,rect.bottom);
                        ClipCursor(&rect);
                        ShowCursor(FALSE);
                    }                    
                }
                windowActive = 1;
                if ( bits8 )
                { char cPlayer;

                                        for (cPlayer=0;cPlayer<C_PLAYERNUMBER;cPlayer++)
                                        {
                                                if (dibDC[cPlayer])
                                                {
                                                if ( SetSystemPaletteUse(dibDC[cPlayer], SYSPAL_NOSTATIC) == SYSPAL_ERROR )
                                                        WinError("SetSystemPaletteUse failed");
                                                if ( SetPaletteEntries(dibPal[cPlayer], 0, 256, palette[cPlayer]->palPalEntry) != 256 )
                                                        WinError("SetPaletteEntries failed");
                                                if ( !UnrealizeObject(dibPal[cPlayer]) )
                                                        WinError("UnrealizeObject failed");
                                                if ( SelectPalette(dibDC[cPlayer], dibPal[cPlayer], FALSE) == NULL )
                                                        WinError("SelectPalette failed");
                                                if ( RealizePalette(dibDC[cPlayer]) == GDI_ERROR )
                                                        WinError("RealizePalette failed");
                                                }
                                        }
                }
            }
            else
            {
                if ( grabMouse )
                {
                    ClipCursor(NULL);
                    ShowCursor(TRUE);
                }
                windowActive = 0;
                if ( bits8 )
                { char cPlayer;

                                        for (cPlayer=0;cPlayer<C_PLAYERNUMBER;cPlayer++)
                                        {
                                                if (dibDC[cPlayer])
                                                {
                                                if ( !UnrealizeObject(dibPal[cPlayer]) )
                                                        WinError("UnrealizeObject failed");
                                                if ( SetSystemPaletteUse(dibDC[cPlayer], SYSPAL_STATIC) == SYSPAL_ERROR )
                                                        WinError("SetSystemPaletteUse failed");
                                                }
                                        }
                }
            }
            return DefWindowProc(hwnd, message, wparam, lparam);

        case WM_KEYDOWN:
            event.type = ev_keydown;
            event.data1 = TranslateKey(wparam);
            if ( event.data1 != 0 )
                D_PostEvent(&event);
            break;

        case WM_KEYUP:
            event.type = ev_keyup;
            event.data1 = TranslateKey(wparam);
            if ( event.data1 != 0 )
                D_PostEvent(&event);
            break;            

        default:
            return(DefWindowProc(hwnd, message, wparam, lparam));
    }

    return 0;
}


void BlitDIB(char cPlayer)
{
    RECT rect;
        char cPlayerNumber,cPlayerL,cPlayerF;

        if (cPlayer==-1)
        {       cPlayerF=displayplayer;
                cPlayerL=displayplayer+1;
        }
        /*{     cPlayerF=0;
                cPlayerL=C_PLAYERNUMBER;
        }*/
        else
        {       cPlayerF=cPlayer;
                cPlayerL=cPlayer+1;
        }

    for (cPlayerNumber=cPlayerF;cPlayerNumber<cPlayerL;cPlayerNumber++)
        {       //PAINTSTRUCT ps;

//                BeginPaint(win[cPlayerNumber],&ps);

//                printf("Display player : %d\n",cPlayerNumber);

                GetClientRect(win[cPlayerNumber], &rect);

/*        if (!cPlayerNumber)
            fn_vStartBench();*/

                if ( bits8 )
                {
#ifndef WATWIN31
                        if ( StretchDIBits(dibDC[cPlayerNumber], rect.left, rect.top, rect.right-rect.left,
                                                           rect.bottom-rect.top, 0, 0, SCREENWIDTH,
                                                           SCREENHEIGHT, dibData[cPlayerNumber], bminfo[cPlayerNumber], DIB_PAL_COLORS,
                                                           SRCCOPY)
                                 == GDI_ERROR )
#else
                        if ( SetDIBitsToDevice(dibDC[cPlayerNumber], rect.left, rect.top, rect.right-rect.left,
                                                           rect.bottom-rect.top, 0, 0, 0,
                                                           SCREENHEIGHT, dibData[cPlayerNumber], bminfo[cPlayerNumber], DIB_PAL_COLORS)
                                 == GDI_ERROR )
#endif
                                WinError("StrecthDIBits failed");
                }
                else
                {
// MR110798 (200 & -SCREENHEIGHT)
/*                        if ( StretchDIBits(dibDC[cPlayerNumber], rect.left, rect.top, rect.right-rect.left,
                                                           rect.bottom-rect.top, 0, 201, SCREENWIDTH,
                                                           -SCREENHEIGHT, dibData[cPlayerNumber], bminfo[cPlayerNumber], DIB_RGB_COLORS,
                                                           SRCCOPY)
                                 == GDI_ERROR )*/
#ifndef WATWIN31
                        if ( StretchDIBits(dibDC[cPlayerNumber], rect.left, rect.top, rect.right-rect.left,
                                                           rect.bottom-rect.top, 0, 0, SCREENWIDTH,
                                                           SCREENHEIGHT, dibData[cPlayerNumber], bminfo[cPlayerNumber], DIB_RGB_COLORS,
                                                           SRCCOPY)
                                 == GDI_ERROR )
#else
                        if ( SetDIBitsToDevice(dibDC[cPlayerNumber], rect.left, rect.top, rect.right-rect.left,
                                                           rect.bottom-rect.top, 0, 0, 0,
                                                           SCREENHEIGHT, dibData[cPlayerNumber], bminfo[cPlayerNumber], DIB_RGB_COLORS)
                                 == GDI_ERROR )
#endif
                                WinError("StrecthDIBits failed");
                }

/*        if (!cPlayerNumber)
           fn_vEndBench();        */

        #ifndef BORLAND31
                //GdiFlush();   // MR030798
        #endif    

//                RedrawWindow(win[cPlayerNumber],NULL,NULL,RDW_UPDATENOW);
//                EndPaint(win[cPlayerNumber],&ps);
        }
}


void I_ShutdownGraphics(void)
{
    if ( grabMouse )
    {
        ClipCursor(NULL);
        ShowCursor(TRUE);
    }
// MR110798
    if ( bits8 )
    { char cPlayer;

       for (cPlayer=0;cPlayer<C_PLAYERNUMBER;cPlayer++)
       {
           if (dibPal[cPlayer])
           {
               if ( !UnrealizeObject(dibPal[cPlayer]) )
                     WinError("UnrealizeObject failed");
               if ( SetSystemPaletteUse(dibDC[cPlayer], SYSPAL_STATIC) == SYSPAL_ERROR )
                     WinError("SetSystemPaletteUse failed");
           }
        }
     }    
#ifndef WATWIN31
	if (g_bAutosize)
		fn_vRestoreScreenResolution();
#endif
}



//
// I_StartFrame
//
void I_StartFrame (void)
{
    // er?

}

/*static int    lastmousex = 0;
static int      lastmousey = 0;
boolean         mousemoved = false;
boolean         shmFinished;*/


void I_GetEvent(void)
{
    MSG msg;
        static JOYINFO xCurrentJoyStat,xPrevJoyStat;
    event_t event;
// MR2301
    static LONG prevX, prevY;
    static int hadMouse = 0;
    static int prevlb = 0, prevrb = 0;
    POINT point;
    RECT rect;
    int lb, rb;
    
#ifdef WATWIN31
    if (bIsPeekMsgYield)
        fn_vTreatKeysYield();
#endif

    /* Dispatch all messages: */
#ifdef WATWIN31
    while ( PeekMessage(&msg, NULL, 0, 0xFFFFFFFF, uiPeekMessageFlag) )
#else	
	while ( PeekMessage(&msg, NULL, 0, 0xFFFFFFFF, PM_REMOVE) )
#endif
    {
        TranslateMessage (&msg) ;
        DispatchMessage (&msg) ;
    }

    // Check Joy
        // MR260698
        //if (usejoystick[g_cCurrentPlayer]&&(joyGetPos(JOYSTICKID1,&xCurrentJoyStat)==JOYERR_NOERROR))
        if (joyGetPos(JOYSTICKID1,&xCurrentJoyStat)==JOYERR_NOERROR)
        {
/*              if (((UINT)abs(xCurrentJoyStat.wXpos-xPrevJoyStat.wXpos)>g_wXCenter+g_wXAmp)||
                        ((UINT)abs(xCurrentJoyStat.wYpos-xPrevJoyStat.wYpos)>g_wYCenter+g_wYAmp)||
                        (xCurrentJoyStat.wButtons!=xPrevJoyStat.wButtons))*/
                if (((UINT)abs(xCurrentJoyStat.wXpos-g_wXCenter)>g_wXAmp)||
                        ((UINT)abs(xCurrentJoyStat.wYpos-g_wYCenter)>g_wYAmp)||
                        (xCurrentJoyStat.wButtons!=xPrevJoyStat.wButtons))
                {
            event.type = ev_joystick;
                        event.data1 = xCurrentJoyStat.wButtons;
                        //if ((UINT)abs(xCurrentJoyStat.wXpos-xPrevJoyStat.wXpos)>g_wXCenter+g_wXAmp)
                        //      event.data2 = xCurrentJoyStat.wXpos-xPrevJoyStat.wXpos;
                        if ((UINT)abs(xCurrentJoyStat.wXpos-g_wXCenter)>g_wXAmp)
                                event.data2 = xCurrentJoyStat.wXpos-g_wXCenter;
                        else
                                event.data2 = 0;
                        //if ((UINT)abs(xCurrentJoyStat.wYpos-xPrevJoyStat.wYpos)>g_wYCenter+g_wYAmp)
                        //      event.data3 = xCurrentJoyStat.wYpos-xPrevJoyStat.wYpos;
                        if ((UINT)abs(xCurrentJoyStat.wYpos-g_wYCenter)>g_wYAmp)
                                event.data3 = xCurrentJoyStat.wYpos-g_wYCenter;
                        else
                                event.data3 = 0;
                        memcpy(&xPrevJoyStat,&xCurrentJoyStat,sizeof(JOYINFO));
                        D_PostEvent(&event);
                }
        }
        
        /* Check mouse and generate events if necessary: */
// MR2301
    if ( !GetCursorPos(&point) )
        WinError("GetCursorPos() failed");
    if ( hadMouse && windowActive)
    {
        lb = (GetAsyncKeyState(VK_LBUTTON) < 0);
        rb = (GetAsyncKeyState(VK_RBUTTON) < 0);
            
        if ( (prevX != point.x) || (prevY != point.y) ||
             (prevlb != lb) || (prevrb != rb) )
        {
            event.type = ev_mouse;
            event.data1 = lb | (rb << 1);
            event.data2 = (point.x - prevX) << 2;
            if ( disableVerticalMouse )
                event.data3 = 0;
            else
                event.data3 = (prevY - point.y) << 2;
            prevX = point.x;
            prevY = point.y;
            prevlb = lb;
            prevrb = rb;
            D_PostEvent(&event);
        }

        if ( grabMouse )
        {
            GetWindowRect(win[0], &rect);
            if ( !SetCursorPos((rect.left + rect.right) / 2,
                               (rect.top + rect.bottom) / 2) )
                WinError("SetCursorPos() failed");
            prevX = (rect.left + rect.right) / 2;
            prevY = (rect.top + rect.bottom) / 2;
        }
    }
    else
    {
        prevX = point.x;
        prevY = point.y;
        hadMouse = 1;
    }        

#if 0    
    event_t event;

    // put event-grabbing stuff in here
    XNextEvent(X_display, &X_event);
    switch (X_event.type)
    {
      case KeyPress:
        event.type = ev_keydown;
        event.data1 = xlatekey();
        D_PostEvent(&event);
        // fprintf(stderr, "k");
        break;
      case KeyRelease:
        event.type = ev_keyup;
        event.data1 = xlatekey();
        D_PostEvent(&event);
        // fprintf(stderr, "ku");
        break;
      case ButtonPress:
        event.type = ev_mouse;
        event.data1 =
            (X_event.xbutton.state & Button1Mask)
            | (X_event.xbutton.state & Button2Mask ? 2 : 0)
            | (X_event.xbutton.state & Button3Mask ? 4 : 0)
            | (X_event.xbutton.button == Button1)
            | (X_event.xbutton.button == Button2 ? 2 : 0)
            | (X_event.xbutton.button == Button3 ? 4 : 0);
        event.data2 = event.data3 = 0;
        D_PostEvent(&event);
        // fprintf(stderr, "b");
        break;
      case ButtonRelease:
        event.type = ev_mouse;
        event.data1 =
            (X_event.xbutton.state & Button1Mask)
            | (X_event.xbutton.state & Button2Mask ? 2 : 0)
            | (X_event.xbutton.state & Button3Mask ? 4 : 0);
        // suggest parentheses around arithmetic in operand of |
        event.data1 =
            event.data1
            ^ (X_event.xbutton.button == Button1 ? 1 : 0)
            ^ (X_event.xbutton.button == Button2 ? 2 : 0)
            ^ (X_event.xbutton.button == Button3 ? 4 : 0);
        event.data2 = event.data3 = 0;
        D_PostEvent(&event);
        // fprintf(stderr, "bu");
        break;
      case MotionNotify:
        event.type = ev_mouse;
        event.data1 =
            (X_event.xmotion.state & Button1Mask)
            | (X_event.xmotion.state & Button2Mask ? 2 : 0)
            | (X_event.xmotion.state & Button3Mask ? 4 : 0);
        event.data2 = (X_event.xmotion.x - lastmousex) << 2;
        event.data3 = (lastmousey - X_event.xmotion.y) << 2;

        if (event.data2 || event.data3)
        {
            lastmousex = X_event.xmotion.x;
            lastmousey = X_event.xmotion.y;
            if (X_event.xmotion.x != X_width/2 &&
                X_event.xmotion.y != X_height/2)
            {
                D_PostEvent(&event);
                // fprintf(stderr, "m");
                mousemoved = false;
            } else
            {
                mousemoved = true;
            }
        }
        break;
        
      case Expose:
      case ConfigureNotify:
        break;
        
      default:
        if (doShm && X_event.type == X_shmeventtype) shmFinished = true;
        break;
    }
#endif
}


//
// I_StartTic
//
void I_StartTic (void)
{
    I_GetEvent();
#if 0
    if (!X_display)
        return;

    while (XPending(X_display))
        I_GetEvent();

    // Warp the pointer back to the middle of the window
    //  or it will wander off - that is, the game will
    //  loose input focus within X11.
    if (grabMouse)
    {
        if (!--doPointerWarp)
        {
            XWarpPointer( X_display,
                          None,
                          X_mainWindow,
                          0, 0,
                          0, 0,
                          X_width/2, X_height/2);

            doPointerWarp = POINTER_WARP_COUNTDOWN;
        }
    }

    mousemoved = false;
#endif
}


//
// I_UpdateNoBlit
//
void I_UpdateNoBlit (void)
{
    // what is this?
}

//
// I_FinishUpdate
//
void I_FinishUpdate (void)
{

    static int  lasttic;
    int         tics;
    int         i;
    // UNUSED static unsigned char *bigscreen=0;

    // draws little dots on the bottom of the screen
    if (devparm)
    {

        i = I_GetTime();
        tics = i - lasttic;
        lasttic = i;
        if (tics > 20) tics = 20;

        for (i=0 ; i<tics*2 ; i+=2)
        {
            screens[0][ ((SCREENHEIGHT-1)*SCREENWIDTH + i)*2] = 0xff;
            if (BPP==2)
                screens[0][ ((SCREENHEIGHT-1)*SCREENWIDTH + i)*2+1] = 0xff;
        }
        for ( ; i<20*2 ; i+=2)
        {
            screens[0][ ((SCREENHEIGHT-1)*SCREENWIDTH + i)*2] = 0x0;
            if (BPP==2)
                screens[0][ ((SCREENHEIGHT-1)*SCREENWIDTH + i)*2+1] = 0x0;
        }    
    }

    BlitDIB(-1);
}


//
// I_ReadScreen
//
void I_ReadScreen (byte* scr)
{
    memcpy (scr, screens[0], SCREENWIDTH*SCREENHEIGHT*BPP);
}


//
// I_SetPalette
//
void I_SetPalette (byte* pal)
{
    unsigned i, j;
    RGBQUAD *rgb;
        char cPlayerNumber;
        byte *palIni=pal;

    for (cPlayerNumber=0;cPlayerNumber<C_PLAYERNUMBER;cPlayerNumber++)
        {       pal=palIni;
                if ( !bits8 )
                {
                        if ( BPP == 1 )
                        {
                                /* Just set the bitmap palette: */
                                rgb = bminfo[cPlayerNumber]->bmiColors;

                                for ( i = 0; i < 256; i++ )
                                {
                                        rgb->rgbRed = gammatable[usegamma][*pal++];
                                        rgb->rgbGreen = gammatable[usegamma][*pal++];
                                        rgb->rgbBlue = gammatable[usegamma][*pal++];
                                        rgb++;
                                }
                        }
                        else
                        {
                                /* Highcolor magic from Chi Choang's <cyhoang@acs.ucalgary.ca>
                                   DOS version: */
                                int tempr[256],tempg[256],tempb[256];
                                short *tempcolormap;
                                byte* tempptr;

                                tempcolormap=(short *)colormaps;
                                for (i=0;i<256;i++)
                                {
                                        tempr[i]=gammatable[usegamma][*pal++];
                                        tempg[i]=gammatable[usegamma][*pal++];
                                        tempb[i]=gammatable[usegamma][*pal++];
                                }
                                for (i=32;i>0;i--)
                                {
                                        tempptr=hicolortable+256*(i-1);
                                        for (j=0;j<256;j++)
                                        {
                                                *tempcolormap=makecol(tempptr[tempr[j]],tempptr[tempg[j]],tempptr[tempb[j]]);
                                                tempcolormap++;
                                        }
                                }
                                tempptr=hicolortable+256*32;
                                for (i=0;i<256;i++)
                                {
                                        j=tempr[i]*54+tempg[i]*183+tempb[i]*19;  //from the colorspace faq
                                        *tempcolormap=makecol(255-(j/256),255-(j/256),255-(j/256));  //lookup table?
                                        tempcolormap[256]=0;
                                        tempcolormap++;

                                        /* No allegro -hack: */
                                        palette_color[i] = makecol(tempr[i], tempg[i], tempb[i]);
                                }
                        }
        
                        // MRMP
                        //return;
                        continue;
                }

                //fprintf(stderr, "I_SetPalette\n");

                /* 8-bit display */
                assert(BPP == 1);
    
                for ( i = 0; i < 256; i++ )
                {
                        palette[cPlayerNumber]->palPalEntry[i].peRed = gammatable[usegamma][*pal++];
                        palette[cPlayerNumber]->palPalEntry[i].peGreen = gammatable[usegamma][*pal++];
                        palette[cPlayerNumber]->palPalEntry[i].peBlue = gammatable[usegamma][*pal++];
                        palette[cPlayerNumber]->palPalEntry[i].peFlags = PC_NOCOLLAPSE;
                }

                /* Make sure we'll get an identity palette */
                palette[cPlayerNumber]->palPalEntry[255].peRed = 255;
                palette[cPlayerNumber]->palPalEntry[255].peGreen = 255;
                palette[cPlayerNumber]->palPalEntry[255].peBlue = 255;
                palette[cPlayerNumber]->palPalEntry[255].peFlags = 0;

                palette[cPlayerNumber]->palPalEntry[0].peRed = 0;
                palette[cPlayerNumber]->palPalEntry[0].peGreen = 0;
                palette[cPlayerNumber]->palPalEntry[0].peBlue = 0;
                palette[cPlayerNumber]->palPalEntry[0].peFlags = 0;

// MRMP
/*              if ( !windowActive )
                        return;*/

                if ( SetPaletteEntries(dibPal[cPlayerNumber], 0, 256, palette[cPlayerNumber]->palPalEntry) != 256 )
                        WinError("SetPaletteEntries failed");
                if ( !UnrealizeObject(dibPal[cPlayerNumber]) )
                        WinError("UnrealizeObject failed");
                if ( SelectPalette(dibDC[cPlayerNumber], dibPal[cPlayerNumber], FALSE) == NULL )
                        WinError("SelectPalette failed");
                if ( RealizePalette(dibDC[cPlayerNumber]) == GDI_ERROR )
                        WinError("RealizePalette failed");
        }
}



void fn_vCreateWindow(char cPlayer,int frameX,int frameY,int capY)
{
    unsigned i, x, y;
    WORD *d;
    unsigned char *b;
    int bits;
    RECT rect;
    int width, height;
    RGBQUAD *rgb;

    width = X_width + 2*frameX;
    height = X_height + 2*frameY + capY;

        // MR110798: height-1 (2 lignes ci-dessous)
#ifndef WATWIN31
	if ((C_PLAYERNUMBER>2)||(!g_bAutosize))	// MR280798
    win[cPlayer] = CreateWindow("DoomWindowClass", "WDMP",
                       WS_THICKFRAME | WS_CAPTION | WS_OVERLAPPED/*WINDOW*/ | WS_VISIBLE, width*(cPlayer%2)-5, height*(cPlayer>1), width, height,
                       NULL, NULL, inst, NULL);
	else
    win[cPlayer] = CreateWindow("DoomWindowClass", "WDMP",
                       WS_THICKFRAME | WS_CAPTION | WS_VISIBLE, 0, height*(cPlayer%2), width, height,
                       NULL, NULL, inst, NULL);
#else
    win[cPlayer] = CreateWindow("DoomWindowClass", "WDMP",
                       //WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, width, height-1,
                                           WS_OVERLAPPEDWINDOW | WS_VISIBLE, width*(cPlayer%2), height*(cPlayer>1), width, height-1,
                       NULL, NULL, inst, NULL);
#endif
    /* Display the window: */
    ShowWindow(win[cPlayer], SW_SHOW);
    UpdateWindow(win[cPlayer]);

    GetClientRect(win[cPlayer], &rect);
    fprintf(stderr, "I_InitGraphics: Client area: %ux%u\n",
            rect.right-rect.left, rect.bottom-rect.top);

    if ( (rect.right-rect.left) != X_width )
    {
        fprintf(stderr, "I_InitGraphics: Fixing width\n");
        width += X_width - (rect.right-rect.left);
        MoveWindow(win[cPlayer], 0, 0, width, height, TRUE);
    }
    if ( (rect.bottom-rect.top) != X_height )
    {
        fprintf(stderr, "I_InitGraphics: Fixing height\n");
        height += X_height - (rect.bottom-rect.top);
        MoveWindow(win[cPlayer], 0, 0, width, height, TRUE);
    }

    GetClientRect(win[cPlayer], &rect);
    fprintf(stderr, "I_InitGraphics: Client area: %ux%u\n",
            rect.right-rect.left, rect.bottom-rect.top);    
        
    dibDC[cPlayer] = GetDC(win[cPlayer]);

    bits = GetDeviceCaps(dibDC[cPlayer], BITSPIXEL);
    fprintf(stderr, "I_InitGraphics: %i bpp screen\n", bits);
    if ( bits == 8 )
    {
        bits8 = 1;
        if ( BPP != 1 )
        {
            fprintf(stderr, "I_InitGraphics: Forcing 8-bit display for "
                    "8-bit screen\n");
            BPP = 1;
        }
    }
    else
    {
        bits8 = 0;
    }

    if ( bits8 )
        if ( SetSystemPaletteUse(dibDC[cPlayer], SYSPAL_NOSTATIC) == SYSPAL_ERROR )
            WinError("SetSystemPaletteUse failed");

    if ( bits8 )
    {
// MR110798
        if (M_CheckParm("-1pal"))
            bOnePalette=true;

        palette[cPlayer] = malloc(sizeof(LOGPALETTE) + 256 * sizeof(PALETTEENTRY));
        palette[cPlayer]->palVersion = 0x300;
        palette[cPlayer]->palNumEntries = 256;
        
        for ( i = 0; i < 256; i++ )
        {
            palette[cPlayer]->palPalEntry[i].peRed = i;
            palette[cPlayer]->palPalEntry[i].peGreen = i;
            palette[cPlayer]->palPalEntry[i].peBlue = i;
            palette[cPlayer]->palPalEntry[i].peFlags = PC_NOCOLLAPSE;
        }


        if ( bits8 )
        {
            /* Make sure we'll get an identity palette */
            palette[cPlayer]->palPalEntry[255].peRed = 255;
            palette[cPlayer]->palPalEntry[255].peGreen = 255;
            palette[cPlayer]->palPalEntry[255].peBlue = 255;
            palette[cPlayer]->palPalEntry[255].peFlags = 0;
            
            palette[cPlayer]->palPalEntry[0].peRed = 0;
            palette[cPlayer]->palPalEntry[0].peGreen = 0;
            palette[cPlayer]->palPalEntry[0].peBlue = 0;
            palette[cPlayer]->palPalEntry[0].peFlags = 0;
        }

        if ( (dibPal[cPlayer] = CreatePalette(palette[cPlayer])) == NULL )
            WinError("CreatePalette failed");
        if ( SelectPalette(dibDC[cPlayer], dibPal[cPlayer], FALSE) == NULL )
            WinError("SelectPalette failed");
        if ( RealizePalette(dibDC[cPlayer]) == GDI_ERROR )
            WinError("RealizePalette failed");
    }

    if ( BPP == 1 )
        bminfo[cPlayer] = malloc(sizeof(BITMAPINFOHEADER) + 4*256);
    else
        bminfo[cPlayer] = malloc(sizeof(BITMAPINFOHEADER));
        

    if ( bits8 )
    {
        d = (WORD*) bminfo[cPlayer]->bmiColors;
        for ( i = 0; i < 256; i++ )
            *(d++) = i;
    }
    else
    {
        if ( BPP == 1 )
        {
            rgb = bminfo[cPlayer]->bmiColors;
            for ( i = 0; i < 256; i++ )
            {
                rgb->rgbRed = i;
                rgb->rgbGreen = i;
                rgb->rgbBlue = i;
                rgb->rgbReserved = 0;
                rgb++;
            }
        }
    }
    
    bminfo[cPlayer]->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bminfo[cPlayer]->bmiHeader.biWidth = SCREENWIDTH;
    bminfo[cPlayer]->bmiHeader.biHeight = -SCREENHEIGHT;
    bminfo[cPlayer]->bmiHeader.biPlanes = 1;
    if ( BPP == 1 )
        bminfo[cPlayer]->bmiHeader.biBitCount = 8;
    else
        bminfo[cPlayer]->bmiHeader.biBitCount = 16;
    bminfo[cPlayer]->bmiHeader.biCompression = BI_RGB;
    bminfo[cPlayer]->bmiHeader.biSizeImage = 0;
    bminfo[cPlayer]->bmiHeader.biXPelsPerMeter = 0;
    bminfo[cPlayer]->bmiHeader.biYPelsPerMeter = 0;
    bminfo[cPlayer]->bmiHeader.biClrUsed = 0;
    bminfo[cPlayer]->bmiHeader.biClrImportant = 0;
    
    dibData[cPlayer] = malloc(SCREENWIDTH*SCREENHEIGHT*BPP);
    if ( BPP == 1 )
    {
        b = dibData[cPlayer];
        for ( y = 0; y < (unsigned)SCREENHEIGHT; y++ )
            for ( x = 0; x < (unsigned)SCREENWIDTH; x++ )
                *(b++) = y;
    }
    else
    {
        d = (WORD*) dibData[cPlayer];
        for ( y = 0; y < (unsigned)SCREENHEIGHT; y++ )
            for ( x = 0; x < (unsigned)SCREENWIDTH; x++ )                
                *(d++) = (WORD) makecol(x, 0, y);
    }

// MR110798
#ifdef WATWIN31
    bminfo[cPlayer]->bmiHeader.biHeight= -bminfo[cPlayer]->bmiHeader.biHeight;
#endif
    BlitDIB(cPlayer);

    screensMP[0+5*cPlayer] = (unsigned char *) (dibData[cPlayer]);
}


void I_InitGraphics(void)
{
    static int firsttime=1;
    
    unsigned i,j;
        WNDCLASS wc;
    int frameX, frameY, capY;
        JOYCAPS xJoyCaps;
    

    if (!firsttime)
        return;
    firsttime = 0;

	// MR280798
#ifndef WATWIN31
	if (g_bAutosize)
		fn_vChangeScreenResolution();
#endif
	
        // MRMP
        fn_vSetCurrentScreen(0);

    if (M_CheckParm("-2"))
        multiply = 2;

    if (M_CheckParm("-3"))
        multiply = 3;

    if (M_CheckParm("-4"))
        multiply = 4;

// MR110798
#ifdef WATWIN31
    if (M_CheckParm("-exclusive"))
    {    uiPeekMessageFlag=PM_REMOVE | PM_NOYIELD;
         bIsPeekMsgYield=true;
    }
    else
    {    uiPeekMessageFlag=PM_REMOVE;
         bIsPeekMsgYield=false;
    }
    for (i=0;i<256;i++)
        cKeyLastFrame[i]=0;
#endif

    if ((i=M_CheckParm("-joysty")))
    {
        C_X_SENSITIVITY=C_Y_SENSITIVITY=atoi(myargv[i+1]);
    }

#ifdef CHEATERMP
    for (i=0;i<C_PLAYERNUMBER;i++)
        bCheater[i]=false;

    if ((i=M_CheckParm("-allweapons")))
    {
        j=atoi(myargv[i+1]);
        
        bCheater[j]=true;
        
        plyrMP[j]->armorpoints = 200;
        plyrMP[j]->armortype = 2;
        
        for (i=0;i<NUMWEAPONS;i++)
          plyrMP[j]->weaponowned[i] = true;
        
        for (i=0;i<NUMAMMO;i++)
          plyrMP[j]->ammo[i] = plyrMP[j]->maxammo[i];
    }
#endif    
// End MR110798

    X_width = SCREENWIDTH * multiply;
    X_height = SCREENHEIGHT * multiply;

    // check if the user wants to grab the mouse (quite unnice)
    grabMouse = !!M_CheckParm("-grabmouse");

    /* [Petteri] New: Option to disable mouse vertical movement - useful
       for players used to Quake: */
    disableVerticalMouse = !!M_CheckParm("-novertmouse");

        // MR250698
        //if (usejoystick&&(joyGetDevCaps(JOYSTICKID1,&xJoyCaps,sizeof(JOYCAPS))==JOYERR_NOERROR))
        { boolean joy=false; 
          char cPlayer;

                for (cPlayer=0;cPlayer<C_PLAYERNUMBER;cPlayer++)
                        joy|=usejoystick[cPlayer];

                if (joy&&(joyGetDevCaps(JOYSTICKID1,&xJoyCaps,sizeof(JOYCAPS))==JOYERR_NOERROR))
                {
                        g_wXAmp=(C_X_SENSITIVITY*(xJoyCaps.wXmax-xJoyCaps.wXmin))/100;
                        g_wYAmp=(C_Y_SENSITIVITY*(xJoyCaps.wYmax-xJoyCaps.wYmin))/100;
                        g_wXCenter=(xJoyCaps.wXmax-xJoyCaps.wXmin)/2;
                        g_wYCenter=(xJoyCaps.wYmax-xJoyCaps.wYmin)/2;
                }
        }

    /* Build and initialize the window: */
    
    inst = (HINSTANCE) GetModuleHandle(NULL);

    frameX = GetSystemMetrics(SM_CXFRAME);
    frameY = GetSystemMetrics(SM_CYFRAME);
    capY = GetSystemMetrics(SM_CYCAPTION);

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = inst;
    wc.hIcon = NULL;
    if ( grabMouse )
        wc.hCursor = LoadCursor( 0, IDC_ARROW );
    else
        wc.hCursor = LoadCursor( 0, IDC_ARROW );
    /*wc.hbrBackground = GetStockObject( WHITE_BRUSH );*/
    wc.hbrBackground = NULL;    
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "DoomWindowClass";

    RegisterClass(&wc);

        for (i=0;i<C_PLAYERNUMBER;i++)
                fn_vCreateWindow(i,frameX,frameY,capY);

		SetActiveWindow(win[0]);
    // MRBench
#ifdef BENCH
    hDCMain=dibDC[0];
#endif

    /* Build magic highcolor table: */
    if (BPP==2)
    {
        byte *tempptr;

        tempptr=hicolortable=(byte *)malloc(256*32);
        for (i=0;i<32;i++)
        {
            for (j=0;j<256;j++)
            {
                *tempptr=j*gammatable[0][i*(256/32)]/256;
                tempptr++;
            }
        }
        hicolortransmask1=makecol(127,127,127);
        hicolortransmask2=makecol(63,63,63);
    }    
}



/*
 * $Log: win32video.c,v $
 * Revision 1.7  1998/01/07 18:44:21  pekangas
 * Fixed a bunch of Visual C warnings, changed name to NTDOOM and
 * made assembler optional
 *
 * Revision 1.6  1998/01/07 17:28:16  pekangas
 * Improved mouse grab a little
 *
 * Revision 1.5  1998/01/05 14:46:35  pekangas
 * Palette is now released when the window deactivates
 *
 * Revision 1.4  1998/01/05 13:40:58  pekangas
 * Fixed I_ReadScreen for 16-bit modes
 *
 * Revision 1.3  1998/01/04 19:29:09  pekangas
 * Added hicolor and multiresulution support from Chi Hoang's DOS port
 *
 * Revision 1.2  1997/12/29 21:17:17  pekangas
 * Fixed to compile with Visual C
 * Some Win95 fixes
 *
 * Revision 1.1  1997/12/29 19:49:10  pekangas
 * Initial revision
 *
*/
