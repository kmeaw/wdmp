// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id: g_game.c,v 1.3 1998/01/04 19:28:57 pekangas Exp $
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
// $Log: g_game.c,v $
// Revision 1.3  1998/01/04 19:28:57  pekangas
// Added hicolor and multiresulution support from Chi Hoang's DOS port
//
// Revision 1.2  1997/12/29 19:50:51  pekangas
// Ported to WinNT/95 environment using Watcom C 10.6.
// Everything expect joystick support is implemented, but networking is
// untested. Crashes way too often with problems in FixedDiv().
// Compiles with no warnings at warning level 3, uses MIDAS 1.1.1.
//
// Revision 1.1.1.1  1997/12/28 12:59:02  pekangas
// Initial DOOM source release from id Software
//
//
// DESCRIPTION:  none
//
//-----------------------------------------------------------------------------


const char
g_game_rcsid[] = "$Id: g_game.c,v 1.3 1998/01/04 19:28:57 pekangas Exp $";

#include <string.h>
#include <stdlib.h>

#include "doomdef.h" 
#include "doomstat.h"

#include "z_zone.h"
#include "f_finale.h"
#include "m_argv.h"
#include "m_misc.h"
#include "m_menu.h"
#include "m_random.h"
#include "i_system.h"

#include "p_setup.h"
#include "p_saveg.h"
#include "p_tick.h"

#include "d_main.h"

#include "wi_stuff.h"
#include "hu_stuff.h"
#include "st_stuff.h"
#include "am_map.h"

// Needs access to LFB.
#include "multires.h"

#include "w_wad.h"

#include "p_local.h" 

#include "s_sound.h"

// Data.
#include "dstrings.h"
#include "sounds.h"

// SKY handling - still the wrong place.
#include "r_data.h"
#include "r_sky.h"



#include "g_game.h"

// MR110798
#ifdef CHEATERMP
extern boolean bCheater[MAXPLAYERS];
#endif

#define SAVEGAMESIZE    0x2c000
#define SAVESTRINGSIZE  24



boolean G_CheckDemoStatus (void); 
void    G_ReadDemoTiccmd (ticcmd_t* cmd); 
void    G_WriteDemoTiccmd (ticcmd_t* cmd); 
void    G_PlayerReborn (int player); 
void    G_InitNew (skill_t skill, int episode, int map); 
 
void    G_DoReborn (int playernum); 
 
void    G_DoLoadLevel (void); 
void    G_DoNewGame (void); 
void    G_DoLoadGame (void); 
void    G_DoPlayDemo (void); 
void    G_DoCompleted (void); 
void    G_DoVictory (void); 
void    G_DoWorldDone (void); 
void    G_DoSaveGame (void); 
 
 
gameaction_t    gameaction; 
gamestate_t     gamestate; 
skill_t         gameskill; 
boolean         respawnmonsters;
int             gameepisode; 
int             gamemap; 
 
boolean         paused; 
boolean         sendpause;              // send a pause event next tic 
boolean         sendsave;               // send a save event next tic 
boolean         usergame;               // ok to save / end game 
 
boolean         timingdemo;             // if true, exit with report on completion 
boolean         nodrawers;              // for comparative timing purposes 
boolean         noblit;                 // for comparative timing purposes 
int             starttime;              // for comparative timing purposes       
 
boolean         viewactive; 
 
boolean         deathmatch;             // only if started as net death 
boolean         netgame;                // only true if packets are broadcast 
boolean         playeringame[MAXPLAYERS]; 
player_t        players[MAXPLAYERS]; 
 
// MR260698
//int             consoleplayer;          // player taking events and displaying 
int             displayplayer;          // view being displayed 
int             gametic; 
int             levelstarttic;          // gametic at level start 
int             totalkills, totalitems, totalsecret;    // for intermission 
 
char            demoname[32]; 
boolean         demorecording; 
boolean         demoplayback; 
boolean         netdemo; 
byte*           demobuffer;
byte*           demo_p;
byte*           demoend; 
boolean         singledemo;             // quit after playing a demo from cmdline 
 
boolean         precache = true;        // if true, load all graphics at start 
 
wbstartstruct_t wminfo[MAXPLAYERS];         // parms for world map / intermission 
 
short           consistancy[MAXPLAYERS][BACKUPTICS]; 
 
byte*           savebuffer;
 
 
// 
// controls (have defaults) 
// 
// MR250698
/*
int             key_right;
int             key_left;

int             key_up;
int             key_down; 
int             key_strafeleft;
int             key_straferight; 
int             key_fire;
int             key_use;
int             key_strafe;
int             key_speed; 
*/
int     key_right[MAXPLAYERS];
int             key_left[MAXPLAYERS];
int             key_up[MAXPLAYERS];
int             key_down[MAXPLAYERS]; 
int     key_strafeleft[MAXPLAYERS];
int             key_straferight[MAXPLAYERS]; 
int     key_fire[MAXPLAYERS];
int             key_use[MAXPLAYERS];
int             key_strafe[MAXPLAYERS];
int             key_speed[MAXPLAYERS]; 

int             key_map[MAXPLAYERS];                // MR300698

// MR290698
int             key_weapon0[MAXPLAYERS];
int             key_weapon1[MAXPLAYERS];
int             key_weapon2[MAXPLAYERS];
int             key_weapon3[MAXPLAYERS];
int             key_weapon4[MAXPLAYERS];
int             key_weapon5[MAXPLAYERS];
int             key_weapon6[MAXPLAYERS];
int             key_weapon7[MAXPLAYERS];
int             key_weapon8[MAXPLAYERS];
int             key_weapon[NUMWEAPONS];

// End MR250698 
int             mousebfire; 
int             mousebstrafe; 
int             mousebforward; 
 
int             joybfire; 
int             joybstrafe; 
int             joybuse; 
int             joybspeed; 
 
 
 
#define MAXPLMOVE               (forwardmove[1]) 
 
#define TURBOTHRESHOLD  0x32

fixed_t         forwardmove[2] = {0x19, 0x32}; 
fixed_t         sidemove[2] = {0x18, 0x28}; 
fixed_t         angleturn[3] = {640, 1280, 320};        // + slow turn 

#define SLOWTURNTICS    6 
 
#define NUMKEYS         256 

boolean         gamekeydown[NUMKEYS]; 
int             turnheld[MAXPLAYERS];                               // for accelerative turning 
 
boolean         mousearray[4]; 
boolean*        mousebuttons = &mousearray[1];          // allow [-1]

// mouse values are used once 
int             mousex;
int             mousey;         

int             dclicktime;
int             dclickstate;
int             dclicks; 
int             dclicktime2;
int             dclickstate2;
int             dclicks2;

// joystick values are repeated 
int             joyxmove;
int             joyymove;
boolean         joyarray[5]; 
boolean*        joybuttons = &joyarray[1];              // allow [-1] 
 
int             savegameslot; 
char            savedescription[32]; 
 
 
#define BODYQUESIZE     32

mobj_t*         bodyque[BODYQUESIZE]; 
int             bodyqueslot; 
 
void*           statcopy;                               // for statistics driver
 
extern int              usejoystick[MAXPLAYERS];    // MR250698 
extern int              usemouse[MAXPLAYERS];       // MRMouse

// MRSuit
void SetSTStuffForPlayer(char cPlayer);
void fn_vUpdateSTStuffForPlayer(char cPlayer);
 
int G_CmdChecksum (ticcmd_t* cmd) 
{ 
    int         i;
    int         sum = 0; 
         
    for (i=0 ; i< sizeof(*cmd)/4 - 1 ; i++) 
        sum += ((int *)cmd)[i]; 
                 
    return sum; 
} 
 

//
// G_BuildTiccmd
// Builds a ticcmd from all of the available inputs
// or reads it from the demo buffer. 
// If recording a demo, write it out 
// 
void G_BuildTiccmd (ticcmd_t* cmd) 
{ 
    int         i; 
    boolean     strafe;
    boolean     bstrafe; 
    int         speed;
    int         tspeed; 
    int         forward;
    int         side;
        boolean joybutton0,joybutton1,joybutton2,joybutton3;
        boolean mousebutton0,mousebutton1,mousebutton2; // MRMouse
    
    ticcmd_t*   base;

    base = I_BaseTiccmd ();             // empty, or external driver
    memcpy (cmd,base,sizeof(*cmd)); 
        
    cmd->consistancy = 
        consistancy[g_cCurrentPlayerForCmd][maketic%BACKUPTICS]; 

        if (!usejoystick[g_cCurrentPlayerForCmd])
        {       joyxmove = joyymove = 0; 

                joybutton0=joybuttons[0];
                joybutton1=joybuttons[1];
                joybutton2=joybuttons[2]; 
                joybutton3=joybuttons[3];

                joybuttons[0] = 0; 
                joybuttons[1] = 0; 
                joybuttons[2] = 0; 
                joybuttons[3] = 0;
        }

        // MRMouse
        if (!usemouse[g_cCurrentPlayerForCmd])
        {       mousex = mousey = 0; 

                mousebutton0=mousebuttons[0];
                mousebutton1=mousebuttons[1];
                mousebutton2=mousebuttons[2]; 

                mousebuttons[0] = 0; 
                mousebuttons[1] = 0; 
                mousebuttons[2] = 0; 
        }
 
    strafe = gamekeydown[key_strafe[g_cCurrentPlayerForCmd]] || mousebuttons[mousebstrafe] 
        || joybuttons[joybstrafe]; 
    speed = gamekeydown[key_speed[g_cCurrentPlayerForCmd]] || joybuttons[joybspeed];
 
    forward = side = 0;
    
    // use two stage accelerative turning
    // on the keyboard and joystick
    if (joyxmove < 0
        || joyxmove > 0  
        || gamekeydown[key_right[g_cCurrentPlayerForCmd]]               // MR250698
        || gamekeydown[key_left[g_cCurrentPlayerForCmd]]) 
        turnheld[g_cCurrentPlayerForCmd] += ticdup; 
    else 
        turnheld[g_cCurrentPlayerForCmd] = 0; 

    if (turnheld[g_cCurrentPlayerForCmd] < SLOWTURNTICS) 
        tspeed = 2;             // slow turn 
    else 
        tspeed = speed;
    
    // let movement keys cancel each other out
    if (strafe) 
    { 
        if (gamekeydown[key_right[g_cCurrentPlayerForCmd]]) 
        {
            // fprintf(stderr, "strafe right\n");
            side += sidemove[speed]; 
        }
        if (gamekeydown[key_left[g_cCurrentPlayerForCmd]]) 
        {
            //  fprintf(stderr, "strafe left\n");
            side -= sidemove[speed]; 
        }
        if (joyxmove > 0) 
            side += sidemove[speed]; 
        if (joyxmove < 0) 
            side -= sidemove[speed]; 
 
    } 
    else 
    { 
        if (gamekeydown[key_right[g_cCurrentPlayerForCmd]]) 
            cmd->angleturn -= angleturn[tspeed]; 
        if (gamekeydown[key_left[g_cCurrentPlayerForCmd]]) 
            cmd->angleturn += angleturn[tspeed]; 
        if (joyxmove > 0) 
            cmd->angleturn -= angleturn[tspeed]; 
        if (joyxmove < 0) 
            cmd->angleturn += angleturn[tspeed]; 
    } 
 
    if (gamekeydown[key_up[g_cCurrentPlayerForCmd]]) 
    {
        forward += forwardmove[speed]; 
    }
    if (gamekeydown[key_down[g_cCurrentPlayerForCmd]]) 
    {
        forward -= forwardmove[speed]; 
    }
    if (joyymove < 0) 
        forward += forwardmove[speed]; 
    if (joyymove > 0) 
        forward -= forwardmove[speed]; 
    if (gamekeydown[key_straferight[g_cCurrentPlayerForCmd]]) 
        side += sidemove[speed]; 
    if (gamekeydown[key_strafeleft[g_cCurrentPlayerForCmd]]) 
        side -= sidemove[speed];
    
    // buttons
    cmd->chatchar = HU_dequeueChatChar(); 
 
    if (gamekeydown[key_fire[g_cCurrentPlayerForCmd]] || mousebuttons[mousebfire] 
        || joybuttons[joybfire]) 
        cmd->buttons |= BT_ATTACK; 
 
    if (gamekeydown[key_use[g_cCurrentPlayerForCmd]] || joybuttons[joybuse] ) 
    { 
        cmd->buttons |= BT_USE;
        // clear double clicks if hit use button 
        dclicks = 0;                   
    } 

        // MR290698
        key_weapon[0]=key_weapon0[g_cCurrentPlayerForCmd];
        key_weapon[1]=key_weapon1[g_cCurrentPlayerForCmd];
        key_weapon[2]=key_weapon2[g_cCurrentPlayerForCmd];
        key_weapon[3]=key_weapon3[g_cCurrentPlayerForCmd];
        key_weapon[4]=key_weapon4[g_cCurrentPlayerForCmd];
        key_weapon[5]=key_weapon5[g_cCurrentPlayerForCmd];
        key_weapon[6]=key_weapon6[g_cCurrentPlayerForCmd];
        key_weapon[7]=key_weapon7[g_cCurrentPlayerForCmd];
        key_weapon[8]=key_weapon8[g_cCurrentPlayerForCmd];

    // chainsaw overrides 
    for (i=0 ; i<NUMWEAPONS-1 ; i++)        
        // MR290698
        //if (gamekeydown['1'+i]) 
        if (gamekeydown[key_weapon[i]]) 
        { 
            cmd->buttons |= BT_CHANGE; 
            cmd->buttons |= i<<BT_WEAPONSHIFT; 
            break; 
        }
    
    // mouse
    if (mousebuttons[mousebforward]) 
        forward += forwardmove[speed];
    
    // forward double click
    if (mousebuttons[mousebforward] != dclickstate && dclicktime > 1 ) 
    { 
        dclickstate = mousebuttons[mousebforward]; 
        if (dclickstate) 
            dclicks++; 
        if (dclicks == 2) 
        { 
            cmd->buttons |= BT_USE; 
            dclicks = 0; 
        } 
        else 
            dclicktime = 0; 
    } 
    else 
    { 
        dclicktime += ticdup; 
        if (dclicktime > 20) 
        { 
            dclicks = 0; 
            dclickstate = 0; 
        } 
    }
    
    // strafe double click
    bstrafe =
        mousebuttons[mousebstrafe] 
        || joybuttons[joybstrafe]; 
    if (bstrafe != dclickstate2 && dclicktime2 > 1 ) 
    { 
        dclickstate2 = bstrafe; 
        if (dclickstate2) 
            dclicks2++; 
        if (dclicks2 == 2) 
        { 
            cmd->buttons |= BT_USE; 
            dclicks2 = 0; 
        } 
        else 
            dclicktime2 = 0; 
    } 
    else 
    { 
        dclicktime2 += ticdup; 
        if (dclicktime2 > 20) 
        { 
            dclicks2 = 0; 
            dclickstate2 = 0; 
        } 
    } 
 
        if (usemouse[g_cCurrentPlayerForCmd])   // MRMouse
        {   forward += mousey; 
        if (strafe)
                side += mousex*2; 
                else 
                cmd->angleturn -= mousex*0x8; 
        }

    mousex = mousey = 0; 
         
    if (forward > MAXPLMOVE) 
        forward = MAXPLMOVE; 
    else if (forward < -MAXPLMOVE) 
        forward = -MAXPLMOVE; 
    if (side > MAXPLMOVE) 
        side = MAXPLMOVE; 
    else if (side < -MAXPLMOVE) 
        side = -MAXPLMOVE; 
 
    cmd->forwardmove += forward; 
    cmd->sidemove += side;
    
    // special buttons
    if (sendpause) 
    { 
        sendpause = false; 
        cmd->buttons = BT_SPECIAL | BTS_PAUSE; 
    } 
 
    if (sendsave) 
    { 
        sendsave = false; 
        cmd->buttons = BT_SPECIAL | BTS_SAVEGAME | (savegameslot<<BTS_SAVESHIFT); 
    } 

        // MR Joy
        joyxmove = joyymove = 0; 

        if (!usejoystick[g_cCurrentPlayerForCmd])
        {       joybuttons[0]=joybutton0;
                joybuttons[1]=joybutton1;
                joybuttons[2]=joybutton2; 
                joybuttons[3]=joybutton3;
        }

        // MRMouse
        mousex = mousey = 0; 

        if (!usemouse[g_cCurrentPlayerForCmd])
        {       mousebuttons[0]=mousebutton0;
                mousebuttons[1]=mousebutton1;
                mousebuttons[2]=mousebutton2; 
        }
} 
 

//
// G_DoLoadLevel 
//
extern  gamestate_t     wipegamestate[MAXPLAYERS]; 
 
void G_DoLoadLevel (void) 
{ 
        char cPlayer;
    int             i; 

    // Set the sky map.
    // First thing, we have a dummy sky texture name,
    //  a flat. The data is in the WAD only because
    //  we look for an actual index, instead of simply
    //  setting one.
    skyflatnum = R_FlatNumForName ( SKYFLATNAME );


    // DOOM determines the sky texture to be used
    // depending on the current episode, and the game version.
    if ( (gamemode == commercial)
         || ( gamemode == pack_tnt )
         || ( gamemode == pack_plut ) )
    {
        skytexture = R_TextureNumForName ("SKY3");
        if (gamemap < 12)
            skytexture = R_TextureNumForName ("SKY1");
        else
            if (gamemap < 21)
                skytexture = R_TextureNumForName ("SKY2");
    }

    levelstarttic = gametic;        // for time calculation
    
        for (cPlayer=0;cPlayer<C_PLAYERNUMBER;cPlayer++)        // MRMP
                if (wipegamestate[cPlayer] == GS_LEVEL) 
                        wipegamestate[cPlayer] = -1;             // force a wipe 

    gamestate = GS_LEVEL; 

    for (i=0 ; i<MAXPLAYERS ; i++) 
    { 
        if (playeringame[i] && players[i].playerstate == PST_DEAD) 
            players[i].playerstate = PST_REBORN; 
        memset (players[i].frags,0,sizeof(players[i].frags)); 
    } 
                 
    P_SetupLevel (gameepisode, gamemap, 0, gameskill);    
    //displayplayer = consoleplayer;            // view the guy you are playing    
        displayplayer = g_cCurrentPlayerForCmd;         // view the guy you are playing    
    starttime = I_GetTime (); 
    gameaction = ga_nothing; 
    Z_CheckHeap ();
    
    // clear cmd building stuff
    memset (gamekeydown, 0, sizeof(gamekeydown)); 
    joyxmove = joyymove = 0; 
    mousex = mousey = 0; 
    sendpause = sendsave = paused = false; 
    memset (mousebuttons, 0, sizeof(mousebuttons)); 
    memset (joybuttons, 0, sizeof(joybuttons)); 
} 
 
 
// MR010798
extern char g_cSoundedPlayer;

//
// G_Responder  
// Get info needed to make ticcmd_ts for the players.
// 
boolean G_Responder (event_t* ev) 
{ 
    // allow spy mode changes even during the demo
// MR260698
/*    if (gamestate == GS_LEVEL && ev->type == ev_keydown 
        && ev->data1 == KEY_F12 && (singledemo || !deathmatch) )
    {
        // spy mode 
        do 
        { 
            displayplayer++; 
            if (displayplayer == MAXPLAYERS) 
                displayplayer = 0; 
        } while (!playeringame[displayplayer] && displayplayer != consoleplayer); 
        return true; 
    }*/
// MR010798
    if (gamestate == GS_LEVEL && ev->type == ev_keydown 
        && ev->data1 == KEY_F5 && !g_cCurrentPlayerForCmd)
    {
        // Swap player sound
        g_cSoundedPlayer++;
        g_cSoundedPlayer%=C_PLAYERNUMBER;
        return true; 
    }
// End MR010798
    
    // any other key pops up menu if in demos
    if (gameaction == ga_nothing && !singledemo && 
        (demoplayback || gamestate == GS_DEMOSCREEN) 
        ) 
    { 
        if (ev->type == ev_keydown ||  
            (ev->type == ev_mouse && ev->data1) || 
            (ev->type == ev_joystick && ev->data1) ) 
        { 
            M_StartControlPanel (); 
            return true; 
        } 
        return false; 
    } 
 
    if (gamestate == GS_LEVEL) 
    { 
#if 0 
        if (devparm && ev->type == ev_keydown && ev->data1 == ';') 
        { 
            G_DeathMatchSpawnPlayer (0); 
            return true; 
        } 
#endif 
        if (HU_Responder (ev)) 
            return true;        // chat ate the event 
        if (ST_Responder (ev)) 
            return true;        // status window ate it 
        if (AM_Responder (ev)) 
            return true;        // automap ate it 
    } 
         
    if (gamestate == GS_FINALE) 
    { 
        if (F_Responder (ev)) 
            return true;        // finale ate the event 
    } 
         
    switch (ev->type) 
    { 
      case ev_keydown: 
        if (ev->data1 == KEY_PAUSE) 
        { 
            sendpause = true; 
            return true; 
        } 
        if (ev->data1 <NUMKEYS) 
            gamekeydown[ev->data1] = true; 
        return true;    // eat key down events 
 
      case ev_keyup: 
        if (ev->data1 <NUMKEYS) 
            gamekeydown[ev->data1] = false; 
        return false;   // always let key up events filter down 
                 
      case ev_mouse: 
        if (usemouse[g_cCurrentPlayerForCmd])   // MRMouse
        {       mousebuttons[0] = ev->data1 & 1; 
                mousebuttons[1] = ev->data1 & 2; 
                mousebuttons[2] = ev->data1 & 4; 
                mousex = ev->data2*(mouseSensitivity+5)/10; 
                mousey = ev->data3*(mouseSensitivity+5)/10; 
                return true;    // eat events 
        }
        else
                return false;
 
      case ev_joystick: 
// MR250698
        if (usejoystick[g_cCurrentPlayerForCmd])
        {       joybuttons[0] = ev->data1 & 1; 
                joybuttons[1] = ev->data1 & 2; 
                joybuttons[2] = ev->data1 & 4; 
                joybuttons[3] = ev->data1 & 8; 
                joyxmove = ev->data2; 
                joyymove = ev->data3; 
                return true;    // eat events 
        }
 
      default: 
        break; 
    } 
 
    return false; 
} 
 
 
 
//
// G_Ticker
// Make ticcmd_ts for the players.
//
void G_Ticker (void) 
{ 
    int         i;
    int         buf; 
    ticcmd_t*   cmd;
    
    // do player reborns if needed
    for (i=0 ; i<MAXPLAYERS ; i++) 
        if (playeringame[i] && players[i].playerstate == PST_REBORN) 
            G_DoReborn (i);
    
    // do things to change the game state
    while (gameaction != ga_nothing) 
    { 
        switch (gameaction) 
        { 
          case ga_loadlevel: 
            G_DoLoadLevel (); 
            break; 
          case ga_newgame: 
            G_DoNewGame (); 
            break; 
          case ga_loadgame: 
            G_DoLoadGame (); 
            break; 
          case ga_savegame: 
            G_DoSaveGame (); 
            break; 
          case ga_playdemo: 
            G_DoPlayDemo (); 
            break; 
          case ga_completed: 
            G_DoCompleted (); 
            break; 
          case ga_victory: 
            F_StartFinale (); 
            break; 
          case ga_worlddone: 
            G_DoWorldDone (); 
            break; 
          case ga_screenshot: 
            M_ScreenShot (); 
            gameaction = ga_nothing; 
            break; 
          case ga_nothing: 
            break; 
        } 
    }
    
    // get commands, check consistancy,
    // and build new consistancy check
    buf = (gametic/ticdup)%BACKUPTICS; 
 
    for (i=0 ; i<MAXPLAYERS ; i++)
    {
        if (playeringame[i]) 
        { 
            cmd = &players[i].cmd; 
 
            memcpy (cmd, &netcmds[i][buf], sizeof(ticcmd_t)); 
 
            if (demoplayback) 
                G_ReadDemoTiccmd (cmd); 
            if (demorecording) 
                G_WriteDemoTiccmd (cmd);
            
            // check for turbo cheats
            if (cmd->forwardmove > TURBOTHRESHOLD 
                && !(gametic&31) && ((gametic>>5)&3) == i )
            {
                static char turbomessage[80];
                extern char *player_names[4];
                sprintf (turbomessage, "%s is turbo!",player_names[i]);
                players[g_cCurrentPlayerForCmd].message = turbomessage;
            }
                        
            if (netgame && !netdemo && !(gametic%ticdup) ) 
            { 
                if (gametic > BACKUPTICS 
                    && consistancy[i][buf] != cmd->consistancy) 
                { 
// MRMP         !!! A voir
/*                  I_Error ("consistency failure (%i should be %i)",
                             cmd->consistancy, consistancy[i][buf]); */
                } 
                if (players[i].mo) 
                    consistancy[i][buf] = players[i].mo->x; 
                else 
                    consistancy[i][buf] = rndindex; 
            } 
        }
    }
    
    // check for special buttons
    for (i=0 ; i<MAXPLAYERS ; i++)
    {
        if (playeringame[i]) 
        { 
            if (players[i].cmd.buttons & BT_SPECIAL) 
            { 
                switch (players[i].cmd.buttons & BT_SPECIALMASK) 
                { 
                  case BTS_PAUSE: 
                    paused ^= 1; 
                    if (paused) 
                        S_PauseSound (); 
                    else 
                        S_ResumeSound (); 
                    break; 
                                         
                  case BTS_SAVEGAME: 
                    if (!savedescription[0]) 
                        strcpy (savedescription, "NET GAME"); 
                    savegameslot =  
                        (players[i].cmd.buttons & BTS_SAVEMASK)>>BTS_SAVESHIFT; 
                    gameaction = ga_savegame; 
                    break; 
                } 
            } 
        }
    }
    
    // do main actions
    switch (gamestate) 
    { 
      case GS_LEVEL: 
        P_Ticker (); 
        for (g_cCurrentPlayerForDsp=0;g_cCurrentPlayerForDsp<C_PLAYERNUMBER;g_cCurrentPlayerForDsp++)   // MR260698
        {       SetSTStuffForPlayer(g_cCurrentPlayerForDsp);
                ST_Ticker (); 
                fn_vUpdateSTStuffForPlayer(g_cCurrentPlayerForDsp);

                AM_Ticker (); 
                HU_Ticker ();            
        }
        break; 
         
      case GS_INTERMISSION: 
        WI_Ticker (); 
        break; 
                         
      case GS_FINALE: 
        F_Ticker (); 
        break; 
 
      case GS_DEMOSCREEN: 
        D_PageTicker (); 
        break; 
    }        
} 
 
 
//
// PLAYER STRUCTURE FUNCTIONS
// also see P_SpawnPlayer in P_Things
//

//
// G_InitPlayer 
// Called at the start.
// Called by the game initialization functions.
//
void G_InitPlayer (int player) 
{ 
    player_t*   p; 
 
    // set up the saved info         
    p = &players[player]; 
         
    // clear everything else to defaults 
    G_PlayerReborn (player); 
         
} 
 
 

//
// G_PlayerFinishLevel
// Can when a player completes a level.
//
void G_PlayerFinishLevel (int player) 
{ 
    player_t*   p; 
         
    p = &players[player]; 
         
    memset (p->powers, 0, sizeof (p->powers)); 
    memset (p->cards, 0, sizeof (p->cards)); 
    p->mo->flags &= ~MF_SHADOW;         // cancel invisibility 
    p->extralight = 0;                  // cancel gun flashes 
    p->fixedcolormap = 0;               // cancel ir gogles 
    p->damagecount = 0;                 // no palette changes 
    p->bonuscount = 0; 
} 
 

//
// G_PlayerReborn
// Called after a player dies 
// almost everything is cleared and initialized 
//
void G_PlayerReborn (int player) 
{ 
    player_t*   p; 
    int         i; 
    int         frags[MAXPLAYERS]; 
    int         killcount;
    int         itemcount;
    int         secretcount; 
         
    memcpy (frags,players[player].frags,sizeof(frags)); 
    killcount = players[player].killcount; 
    itemcount = players[player].itemcount; 
    secretcount = players[player].secretcount; 
         
    p = &players[player]; 
    memset (p, 0, sizeof(*p)); 
 
    memcpy (players[player].frags, frags, sizeof(players[player].frags)); 
    players[player].killcount = killcount; 
    players[player].itemcount = itemcount; 
    players[player].secretcount = secretcount; 
 
    p->usedown = p->attackdown = true;  // don't do anything immediately 
    p->playerstate = PST_LIVE;       
    p->health = MAXHEALTH; 
#ifdef CHEATERMP
    if (bCheater[player])      // MR110798
    {    for (i=0;i<NUMWEAPONS;i++)
          p->weaponowned[i] = true;
        
        for (i=0;i<NUMAMMO;i++)
          p->ammo[i] = maxammo[i];

        p->readyweapon = p->pendingweapon = wp_pistol; 
    }
    else
#endif
    {
        p->readyweapon = p->pendingweapon = wp_pistol; 
        p->weaponowned[wp_fist] = true; 
        p->weaponowned[wp_pistol] = true; 
        p->ammo[am_clip] = 50;
    }
         
    for (i=0 ; i<NUMAMMO ; i++) 
        p->maxammo[i] = maxammo[i]; 
                 
}

//
// G_CheckSpot  
// Returns false if the player cannot be respawned
// at the given mapthing_t spot  
// because something is occupying it 
//
void P_SpawnPlayer (mapthing_t* mthing); 
 
boolean
G_CheckSpot
( int           playernum,
  mapthing_t*   mthing ) 
{ 
    fixed_t             x;
    fixed_t             y; 
    subsector_t*        ss; 
    unsigned            an; 
    mobj_t*             mo; 
    int                 i;
        
    if (!players[playernum].mo)
    {
        // first spawn of level, before corpses
        for (i=0 ; i<playernum ; i++)
            if (players[i].mo->x == mthing->x << FRACBITS
                && players[i].mo->y == mthing->y << FRACBITS)
                return false;   
        return true;
    }
                
    x = mthing->x << FRACBITS; 
    y = mthing->y << FRACBITS; 
         
    if (!P_CheckPosition (players[playernum].mo, x, y) ) 
        return false; 
 
    // flush an old corpse if needed 
    if (bodyqueslot >= BODYQUESIZE) 
        P_RemoveMobj (bodyque[bodyqueslot%BODYQUESIZE]); 
    bodyque[bodyqueslot%BODYQUESIZE] = players[playernum].mo; 
    bodyqueslot++; 
        
    // spawn a teleport fog 
    ss = R_PointInSubsector (x,y); 
    an = ( ANG45 * (mthing->angle/45) ) >> ANGLETOFINESHIFT; 
 
    mo = P_SpawnMobj (x+20*finecosine[an], y+20*finesine[an] 
                      , ss->sector->floorheight 
                      , MT_TFOG); 
         
    if (players[g_cCurrentPlayerForCmd].viewz != 1) 
        S_StartSound (mo, sfx_telept);  // don't start sound on first frame 
 
    return true; 
} 


//
// G_DeathMatchSpawnPlayer 
// Spawns a player at one of the random death match spots 
// called at level load and each death 
//
void G_DeathMatchSpawnPlayer (int playernum) 
{ 
    int             i,j; 
    int                         selections; 
         
    selections = deathmatch_p - deathmatchstarts; 
    if (selections < 4) 
        I_Error ("Only %i deathmatch spots, 4 required", selections); 
 
    for (j=0 ; j<20 ; j++) 
    { 
        i = P_Random() % selections; 
        if (G_CheckSpot (playernum, &deathmatchstarts[i]) ) 
        { 
            deathmatchstarts[i].type = playernum+1; 
            P_SpawnPlayer (&deathmatchstarts[i]); 
            return; 
        } 
    } 
 
    // no good spot, so the player will probably get stuck 
    P_SpawnPlayer (&playerstarts[playernum]); 
} 

//
// G_DoReborn 
// 
void G_DoReborn (int playernum) 
{ 
    int                             i; 
         
    if (!netgame)
    {
        // reload the level from scratch
        gameaction = ga_loadlevel;  
    }
    else 
    {
        // respawn at the start

        // first dissasociate the corpse 
        players[playernum].mo->player = NULL;   
                 
        // spawn at random spot if in death match 
        if (deathmatch) 
        { 
            G_DeathMatchSpawnPlayer (playernum); 
            return; 
        } 
                 
        if (G_CheckSpot (playernum, &playerstarts[playernum]) ) 
        { 
            P_SpawnPlayer (&playerstarts[playernum]); 
            return; 
        }
        
        // try to spawn at one of the other players spots 
        for (i=0 ; i<MAXPLAYERS ; i++)
        {
            if (G_CheckSpot (playernum, &playerstarts[i]) ) 
            { 
                playerstarts[i].type = playernum+1;     // fake as other player 
                P_SpawnPlayer (&playerstarts[i]); 
                playerstarts[i].type = i+1;             // restore 
                return; 
            }       
            // he's going to be inside something.  Too bad.
        }
        P_SpawnPlayer (&playerstarts[playernum]); 
    } 
} 
 
 
void G_ScreenShot (void) 
{ 
    gameaction = ga_screenshot; 
} 
 


// DOOM Par Times
int pars[4][10] = 
{ 
    {0}, 
    {0,30,75,120,90,165,180,180,30,165}, 
    {0,90,90,90,120,90,360,240,30,170}, 
    {0,90,45,90,150,90,90,165,30,135} 
}; 

// DOOM II Par Times
int cpars[32] =
{
    30,90,120,120,90,150,120,120,270,90,        //  1-10
    210,150,150,150,210,150,420,150,210,150,    // 11-20
    240,150,180,150,150,300,330,420,300,180,    // 21-30
    120,30                                      // 31-32
};
 

//
// G_DoCompleted 
//
boolean         secretexit; 
extern char*    pagename; 
 
void G_ExitLevel (void) 
{ 
    secretexit = false; 
    gameaction = ga_completed; 
} 

// Here's for the german edition.
void G_SecretExitLevel (void) 
{ 
    // IF NO WOLF3D LEVELS, NO SECRET EXIT!
    if ( (gamemode == commercial)
      && (W_CheckNumForName("map31")<0))
        secretexit = false;
    else
        secretexit = true; 
    gameaction = ga_completed; 
} 
 
void G_DoCompleted (void) 
{ 
    int             i; 
         
    gameaction = ga_nothing; 
 
    for (i=0 ; i<MAXPLAYERS ; i++) 
        if (playeringame[i]) 
            G_PlayerFinishLevel (i);        // take away cards and stuff 
         
    for (i=0 ; i<C_PLAYERNUMBER ; i++) 
        if (automapactive[i]) 
        {       g_cAMCurrentPlayer=i;
                AM_Stop (); 
        }
        
    if ( gamemode != commercial)
        switch(gamemap)
        {
          case 8:
            gameaction = ga_victory;
            return;
          case 9: 
            for (i=0 ; i<MAXPLAYERS ; i++) 
                players[i].didsecret = true; 
            break;
        }
                
//#if 0  Hmmm - why?
    if ( (gamemap == 8)
         && (gamemode != commercial) ) 
    {
        // victory 
        gameaction = ga_victory; 
        return; 
    } 
         
    if ( (gamemap == 9)
         && (gamemode != commercial) ) 
    {
        // exit secret level 
        for (i=0 ; i<MAXPLAYERS ; i++) 
            players[i].didsecret = true; 
    } 
//#endif
    
         
    for (g_cCurrentPlayerForDsp=0;g_cCurrentPlayerForDsp<C_PLAYERNUMBER;g_cCurrentPlayerForDsp++)
        {
                wminfo[g_cCurrentPlayerForDsp].didsecret = players[g_cCurrentPlayerForDsp].didsecret; 
                wminfo[g_cCurrentPlayerForDsp].epsd = gameepisode -1; 
                wminfo[g_cCurrentPlayerForDsp].last = gamemap -1;
    
                // wminfo[g_cCurrentPlayerForDsp].next is 0 biased, unlike gamemap
                if ( gamemode == commercial)
                {
                if (secretexit)
                        switch(gamemap)
                        {
                          case 15: wminfo[g_cCurrentPlayerForDsp].next = 30; break;
                          case 31: wminfo[g_cCurrentPlayerForDsp].next = 31; break;
                        }
                else
                        switch(gamemap)
                        {
                          case 31:
                          case 32: wminfo[g_cCurrentPlayerForDsp].next = 15; break;
                          default: wminfo[g_cCurrentPlayerForDsp].next = gamemap;
                        }
                }
                else
                {
                if (secretexit) 
                        wminfo[g_cCurrentPlayerForDsp].next = 8;        // go to secret level 
                else if (gamemap == 9) 
                {
                        // returning from secret level 
                        switch (gameepisode) 
                        { 
                          case 1: 
                        wminfo[g_cCurrentPlayerForDsp].next = 3; 
                        break; 
                          case 2: 
                        wminfo[g_cCurrentPlayerForDsp].next = 5; 
                        break; 
                          case 3: 
                        wminfo[g_cCurrentPlayerForDsp].next = 6; 
                        break; 
                          case 4:
                        wminfo[g_cCurrentPlayerForDsp].next = 2;
                        break;
                        }                
                } 
                else 
                        wminfo[g_cCurrentPlayerForDsp].next = gamemap;          // go to next level 
                }
                         
                wminfo[g_cCurrentPlayerForDsp].maxkills = totalkills; 
                wminfo[g_cCurrentPlayerForDsp].maxitems = totalitems; 
                wminfo[g_cCurrentPlayerForDsp].maxsecret = totalsecret; 
                wminfo[g_cCurrentPlayerForDsp].maxfrags = 0; 
                if ( gamemode == commercial )
                wminfo[g_cCurrentPlayerForDsp].partime = 35*cpars[gamemap-1]; 
                else
                wminfo[g_cCurrentPlayerForDsp].partime = 35*pars[gameepisode][gamemap]; 
                wminfo[g_cCurrentPlayerForDsp].pnum = g_cCurrentPlayerForDsp; 
 
                for (i=0 ; i<MAXPLAYERS ; i++) 
                { 
                wminfo[g_cCurrentPlayerForDsp].plyr[i].in = playeringame[i]; 
                wminfo[g_cCurrentPlayerForDsp].plyr[i].skills = players[i].killcount; 
                wminfo[g_cCurrentPlayerForDsp].plyr[i].sitems = players[i].itemcount; 
                wminfo[g_cCurrentPlayerForDsp].plyr[i].ssecret = players[i].secretcount; 
                wminfo[g_cCurrentPlayerForDsp].plyr[i].stime = leveltime; 
                memcpy (wminfo[g_cCurrentPlayerForDsp].plyr[i].frags, players[i].frags 
                        , sizeof(wminfo[g_cCurrentPlayerForDsp].plyr[i].frags)); 
                } 
 
                gamestate = GS_INTERMISSION; 
                viewactive = false; 
                // MRSuit
                for (i=0 ; i<C_PLAYERNUMBER ; i++) 
                        automapactive[i] = false; 
 
                if (statcopy)
                memcpy (statcopy, &wminfo[g_cCurrentPlayerForDsp], sizeof(wminfo[g_cCurrentPlayerForDsp]));
                
                WI_Start (&wminfo[g_cCurrentPlayerForDsp]); 
        }
} 


//
// G_WorldDone 
//
void G_WorldDone (void) 
{ 
    gameaction = ga_worlddone; 

    if (secretexit) 
        players[g_cCurrentPlayerForCmd].didsecret = true; 

    if ( gamemode == commercial )
    {
        switch (gamemap)
        {
          case 15:
          case 31:
            if (!secretexit)
                break;
          case 6:
          case 11:
          case 20:
          case 30:
            F_StartFinale ();
            break;
        }
    }
} 
 
void G_DoWorldDone (void) 
{        
    gamestate = GS_LEVEL; 
    gamemap = wminfo[0].next+1; // MRFin
    G_DoLoadLevel (); 
    gameaction = ga_nothing; 
    viewactive = true; 
} 
 


//
// G_InitFromSavegame
// Can be called by the startup code or the menu task. 
//
extern boolean setsizeneeded;
void R_ExecuteSetViewSize (void);

char    savename[256];

void G_LoadGame (char* name) 
{ 
    strcpy (savename, name); 
    gameaction = ga_loadgame; 
} 
 
#define VERSIONSIZE             16 


void G_DoLoadGame (void) 
{ 
    int         length; 
    int         i; 
    int         a,b,c; 
    char        vcheck[VERSIONSIZE]; 
         
    gameaction = ga_nothing; 
         
    length = M_ReadFile (savename, &savebuffer); 
    save_p = savebuffer + SAVESTRINGSIZE;
    
    // skip the description field 
    memset (vcheck,0,sizeof(vcheck)); 
    sprintf (vcheck,"version %i",VERSION); 
    if (strcmp (save_p, vcheck)) 
        return;                         // bad version 
    save_p += VERSIONSIZE; 
                         
    gameskill = *save_p++; 
    gameepisode = *save_p++; 
    gamemap = *save_p++; 
    for (i=0 ; i<MAXPLAYERS ; i++) 
        playeringame[i] = *save_p++; 

    // load a base level 
    G_InitNew (gameskill, gameepisode, gamemap); 
 
    // get the times 
    a = *save_p++; 
    b = *save_p++; 
    c = *save_p++; 
    leveltime = (a<<16) + (b<<8) + c; 
         
    // dearchive all the modifications
    P_UnArchivePlayers (); 
    P_UnArchiveWorld (); 
    P_UnArchiveThinkers (); 
    P_UnArchiveSpecials (); 
 
    if (*save_p != 0x1d) 
        I_Error ("Bad savegame");
    
    // done 
    Z_Free (savebuffer); 
 
    if (setsizeneeded)
        R_ExecuteSetViewSize ();
    
    // draw the pattern into the back screen
    R_FillBackScreen ();   
} 
 

//
// G_SaveGame
// Called by the menu task.
// Description is a 24 byte text string 
//
void
G_SaveGame
( int   slot,
  char* description ) 
{ 
    savegameslot = slot; 
    strcpy (savedescription, description); 
    sendsave = true; 
} 
 
void G_DoSaveGame (void) 
{ 
    char        name[100]; 
    char        name2[VERSIONSIZE]; 
    char*       description; 
    int         length; 
    int         i; 
        
    if (M_CheckParm("-cdrom"))
        sprintf(name,"c:\\doomdata\\"SAVEGAMENAME"%d.dsg",savegameslot);
    else
        sprintf (name,SAVEGAMENAME"%d.dsg",savegameslot); 
    description = savedescription; 
         
    save_p = savebuffer = screens[1]+0x4000; 
         
    memcpy (save_p, description, SAVESTRINGSIZE); 
    save_p += SAVESTRINGSIZE; 
    memset (name2,0,sizeof(name2)); 
    sprintf (name2,"version %i",VERSION); 
    memcpy (save_p, name2, VERSIONSIZE); 
    save_p += VERSIONSIZE; 
         
    *save_p++ = gameskill; 
    *save_p++ = gameepisode; 
    *save_p++ = gamemap; 
    for (i=0 ; i<MAXPLAYERS ; i++) 
        *save_p++ = playeringame[i]; 
    *save_p++ = leveltime>>16; 
    *save_p++ = leveltime>>8; 
    *save_p++ = leveltime; 
 
    P_ArchivePlayers (); 
    P_ArchiveWorld (); 
    P_ArchiveThinkers (); 
    P_ArchiveSpecials (); 
         
    *save_p++ = 0x1d;           // consistancy marker 
         
    length = save_p - savebuffer; 
    if (length > SAVEGAMESIZE) 
        I_Error ("Savegame buffer overrun"); 
    M_WriteFile (name, savebuffer, length); 
    gameaction = ga_nothing; 
    savedescription[0] = 0;              
         
    players[g_cCurrentPlayerForCmd].message = GGSAVED; 

    // draw the pattern into the back screen
    R_FillBackScreen ();        
} 
 

//
// G_InitNew
// Can be called by the startup code or the menu task,
// consoleplayer, displayplayer, playeringame[] should be set. 
//
skill_t d_skill; 
int     d_episode; 
int     d_map; 
 
void
G_DeferedInitNew
( skill_t       skill,
  int           episode,
  int           map) 
{ 
    d_skill = skill; 
    d_episode = episode; 
    d_map = map; 
    gameaction = ga_newgame; 
} 


void G_DoNewGame (void) 
{
    demoplayback = false; 
    netdemo = false;
    netgame = false;
    deathmatch = false;
    playeringame[1] = playeringame[2] = playeringame[3] = 0;
    respawnparm = false;
    fastparm = false;
    nomonsters = false;
    //consoleplayer = 0;        // MR260698
    G_InitNew (d_skill, d_episode, d_map); 
    gameaction = ga_nothing; 
} 

// The sky texture to be used instead of the F_SKY1 dummy.
extern  int     skytexture; 


void
G_InitNew
( skill_t       skill,
  int           episode,
  int           map ) 
{ 
    int             i; 
         
    if (paused) 
    { 
        paused = false; 
        S_ResumeSound (); 
    } 
        

    if (skill > sk_nightmare) 
        skill = sk_nightmare;


    // This was quite messy with SPECIAL and commented parts.
    // Supposedly hacks to make the latest edition work.
    // It might not work properly.
    if (episode < 1)
      episode = 1; 

    if ( gamemode == retail )
    {
      if (episode > 4)
        episode = 4;
    }
    else if ( gamemode == shareware )
    {
      if (episode > 1) 
           episode = 1; // only start episode 1 on shareware
    }  
    else
    {
      if (episode > 3)
        episode = 3;
    }
    

  
    if (map < 1) 
        map = 1;
    
    if ( (map > 9)
         && ( gamemode != commercial) )
      map = 9; 
                 
    M_ClearRandom (); 
         
    if (skill == sk_nightmare || respawnparm )
        respawnmonsters = true;
    else
        respawnmonsters = false;
                
    if (fastparm || (skill == sk_nightmare && gameskill != sk_nightmare) )
    { 
        for (i=S_SARG_RUN1 ; i<=S_SARG_PAIN2 ; i++) 
            states[i].tics >>= 1; 
        mobjinfo[MT_BRUISERSHOT].speed = 20*FRACUNIT; 
        mobjinfo[MT_HEADSHOT].speed = 20*FRACUNIT; 
        mobjinfo[MT_TROOPSHOT].speed = 20*FRACUNIT; 
    } 
    else if (skill != sk_nightmare && gameskill == sk_nightmare) 
    { 
        for (i=S_SARG_RUN1 ; i<=S_SARG_PAIN2 ; i++) 
            states[i].tics <<= 1; 
        mobjinfo[MT_BRUISERSHOT].speed = 15*FRACUNIT; 
        mobjinfo[MT_HEADSHOT].speed = 10*FRACUNIT; 
        mobjinfo[MT_TROOPSHOT].speed = 10*FRACUNIT; 
    } 
         
                         
    // force players to be initialized upon first level load         
    for (i=0 ; i<MAXPLAYERS ; i++) 
        players[i].playerstate = PST_REBORN; 
 
    usergame = true;                // will be set false if a demo 
    paused = false; 
    demoplayback = false; 
        for (i=0 ; i<C_PLAYERNUMBER ; i++) 
                automapactive[i] = false; 
    viewactive = true; 
    gameepisode = episode; 
    gamemap = map; 
    gameskill = skill; 
 
    viewactive = true;
    
    // set the sky map for the episode
    if ( gamemode == commercial)
    {
        skytexture = R_TextureNumForName ("SKY3");
        if (gamemap < 12)
            skytexture = R_TextureNumForName ("SKY1");
        else
            if (gamemap < 21)
                skytexture = R_TextureNumForName ("SKY2");
    }
    else
        switch (episode) 
        { 
          case 1: 
            skytexture = R_TextureNumForName ("SKY1"); 
            break; 
          case 2: 
            skytexture = R_TextureNumForName ("SKY2"); 
            break; 
          case 3: 
            skytexture = R_TextureNumForName ("SKY3"); 
            break; 
          case 4:       // Special Edition sky
            skytexture = R_TextureNumForName ("SKY4");
            break;
        } 
 
    G_DoLoadLevel (); 
} 
 

//
// DEMO RECORDING 
// 
#define DEMOMARKER              0x80


void G_ReadDemoTiccmd (ticcmd_t* cmd) 
{ 
    if (*demo_p == DEMOMARKER) 
    {
        // end of demo data stream 
        G_CheckDemoStatus (); 
        return; 
    } 
    cmd->forwardmove = ((signed char)*demo_p++); 
    cmd->sidemove = ((signed char)*demo_p++); 
    cmd->angleturn = ((unsigned char)*demo_p++)<<8; 
    cmd->buttons = (unsigned char)*demo_p++; 
} 


void G_WriteDemoTiccmd (ticcmd_t* cmd) 
{ 
    if (gamekeydown['q'])           // press q to end demo recording 
        G_CheckDemoStatus (); 
    *demo_p++ = cmd->forwardmove; 
    *demo_p++ = cmd->sidemove; 
    *demo_p++ = (cmd->angleturn+128)>>8; 
    *demo_p++ = cmd->buttons; 
    demo_p -= 4; 
    if (demo_p > demoend - 16)
    {
        // no more space 
        G_CheckDemoStatus (); 
        return; 
    } 
        
    G_ReadDemoTiccmd (cmd);         // make SURE it is exactly the same 
} 
 
 
 
//
// G_RecordDemo 
// 
void G_RecordDemo (char* name) 
{ 
    int             i; 
    int                         maxsize;
        
    usergame = false; 
    strcpy (demoname, name); 
    strcat (demoname, ".lmp"); 
    maxsize = 0x20000;
    i = M_CheckParm ("-maxdemo");
    if (i && i<myargc-1)
        maxsize = atoi(myargv[i+1])*1024;
    demobuffer = Z_Malloc (maxsize,PU_STATIC,NULL); 
    demoend = demobuffer + maxsize;
        
    demorecording = true; 
} 
 
 
void G_BeginRecording (void) 
{ 
    int             i; 
                
    demo_p = demobuffer;
        
    *demo_p++ = VERSION;
    *demo_p++ = gameskill; 
    *demo_p++ = gameepisode; 
    *demo_p++ = gamemap; 
    *demo_p++ = deathmatch; 
    *demo_p++ = respawnparm;
    *demo_p++ = fastparm;
    *demo_p++ = nomonsters;
    *demo_p++ = g_cCurrentPlayerForCmd;
         
    for (i=0 ; i<MAXPLAYERS ; i++) 
        *demo_p++ = playeringame[i];             
} 
 

//
// G_PlayDemo 
//

char*   defdemoname; 
 
void G_DeferedPlayDemo (char* name) 
{ 
    defdemoname = name; 
    gameaction = ga_playdemo; 
} 
 
void G_DoPlayDemo (void) 
{ 
    skill_t skill; 
    int             i, episode, map; 
         
    gameaction = ga_nothing; 
    demobuffer = demo_p = W_CacheLumpName (defdemoname, PU_STATIC); 
    if ( *demo_p++ != VERSION)
    {
      fprintf( stderr, "Demo is from a different game version!\n");
      gameaction = ga_nothing;
      return;
    }
    
    skill = *demo_p++; 
    episode = *demo_p++; 
    map = *demo_p++; 
    deathmatch = *demo_p++;
    respawnparm = *demo_p++;
    fastparm = *demo_p++;
    nomonsters = *demo_p++;
    //consoleplayer = *demo_p++;
        g_cCurrentPlayerForCmd = *demo_p++;
        
    for (i=0 ; i<MAXPLAYERS ; i++) 
        playeringame[i] = *demo_p++; 
    if (playeringame[1]) 
    { 
        netgame = true; 
        netdemo = true; 
    }

    // don't spend a lot of time in loadlevel 
    precache = false;
    G_InitNew (skill, episode, map); 
    precache = true; 

    usergame = false; 
    demoplayback = true; 
} 

//
// G_TimeDemo 
//
void G_TimeDemo (char* name) 
{        
    nodrawers = M_CheckParm ("-nodraw"); 
    noblit = M_CheckParm ("-noblit"); 
    timingdemo = true; 
    singletics = true; 

    defdemoname = name; 
    gameaction = ga_playdemo; 
} 
 
 
/* 
=================== 
= 
= G_CheckDemoStatus 
= 
= Called after a death or level completion to allow demos to be cleaned up 
= Returns true if a new demo loop action will take place 
=================== 
*/ 
 
boolean G_CheckDemoStatus (void) 
{ 
    int             endtime; 
         
    if (timingdemo) 
    { 
        endtime = I_GetTime (); 
        I_Error ("timed %i gametics in %i realtics",gametic 
                 , endtime-starttime); 
    } 
         
    if (demoplayback) 
    { 
        if (singledemo) 
            I_Quit (); 
                         
        Z_ChangeTag (demobuffer, PU_CACHE); 
        demoplayback = false; 
        netdemo = false;
        netgame = false;
        deathmatch = false;
        playeringame[1] = playeringame[2] = playeringame[3] = 0;
        respawnparm = false;
        fastparm = false;
        nomonsters = false;
        // MR260698
        //consoleplayer = 0;
        g_cCurrentPlayerForCmd = 0;

        D_AdvanceDemo (); 
        return true; 
    } 
 
    if (demorecording) 
    { 
        *demo_p++ = DEMOMARKER; 
        M_WriteFile (demoname, demobuffer, demo_p - demobuffer); 
        Z_Free (demobuffer); 
        demorecording = false; 
        I_Error ("Demo %s recorded",demoname); 
    } 
         
    return false; 
} 
 
 
 
