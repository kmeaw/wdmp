// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id: am_map.c,v 1.4 1998/01/04 19:28:52 pekangas Exp $
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
//
// $Log: am_map.c,v $
// Revision 1.4  1998/01/04 19:28:52  pekangas
// Added hicolor and multiresulution support from Chi Hoang's DOS port
//
//
// DESCRIPTION:  the automap code
//
//-----------------------------------------------------------------------------

const char am_map_rcsid[] = "$Id: am_map.c,v 1.4 1998/01/04 19:28:52 pekangas Exp $";

#include <stdio.h>

#include "z_zone.h"
#include "doomdef.h"
#include "st_stuff.h"
#include "p_local.h"
#include "w_wad.h"

#include "m_cheat.h"
#include "i_system.h"

// Needs access to LFB.
#include "multires.h"

// State.
#include "doomstat.h"
#include "r_state.h"

// Data.
#include "dstrings.h"

#include "am_map.h"

/* [Petteri] no-allegro-hack: */
#ifndef palette_color
extern int palette_color[256];
#endif

// MR110798
#ifdef WATWIN31
#define REAL_Y(x) (SCREENHEIGHT-1-x)
#define SBARHEIGHT 32
#endif

/* [Petteri] Disable warning C4244: 'initializing' : conversion from
   'const double ' to 'int ', possible loss of data */
#ifdef _MSC_VER
#   pragma warning(disable:4244)
#endif

// MR300698
extern int              key_map[MAXPLAYERS];
extern int     key_right[MAXPLAYERS];
extern int              key_left[MAXPLAYERS];
extern int              key_up[MAXPLAYERS];
extern int              key_down[MAXPLAYERS]; 

// MR110798
extern void fn_vChangeGrabMouse();

// For use if I do walls with outsides/insides
#define REDS            (256-5*16)
#define REDRANGE        16
#define BLUES           (256-4*16+8)
#define BLUERANGE       8
#define GREENS          (7*16)
#define GREENRANGE      16
#define GRAYS           (6*16)
#define GRAYSRANGE      16
#define BROWNS          (4*16)
#define BROWNRANGE      16
#define YELLOWS         (256-32+7)
#define YELLOWRANGE     1
#define BLACK           0
#define WHITE           (256-47)

// Automap colors
#define BACKGROUND      BLACK
#define YOURCOLORS      WHITE
#define YOURRANGE       0
#define WALLCOLORS      REDS
#define WALLRANGE       REDRANGE
#define TSWALLCOLORS    GRAYS
#define TSWALLRANGE     GRAYSRANGE
#define FDWALLCOLORS    BROWNS
#define FDWALLRANGE     BROWNRANGE
#define CDWALLCOLORS    YELLOWS
#define CDWALLRANGE     YELLOWRANGE
#define THINGCOLORS     GREENS
#define THINGRANGE      GREENRANGE
#define SECRETWALLCOLORS WALLCOLORS
#define SECRETWALLRANGE WALLRANGE
#define GRIDCOLORS      (GRAYS + GRAYSRANGE/2)
#define GRIDRANGE       0
#define XHAIRCOLORS     GRAYS

// drawing stuff
#define FB              0

// MR300698
#define AM_PANDOWNKEY   KEY_DOWNARROW
#define AM_PANUPKEY     KEY_UPARROW
#define AM_PANRIGHTKEY  KEY_RIGHTARROW
#define AM_PANLEFTKEY   KEY_LEFTARROW
/*#define AM_PANDOWNKEY key_down[g_cCurrentPlayerForCmd]
#define AM_PANUPKEY             key_up[g_cCurrentPlayerForCmd]
#define AM_PANRIGHTKEY  key_right[g_cCurrentPlayerForCmd]
#define AM_PANLEFTKEY   key_left[g_cCurrentPlayerForCmd]*/

/*#define AM_ZOOMINKEY  '='
#define AM_ZOOMOUTKEY   '-'
#define AM_STARTKEY     KEY_TAB
#define AM_ENDKEY       KEY_TAB*/
#define AM_ZOOMINKEY    43
#define AM_ZOOMOUTKEY   45
#define AM_STARTKEY     key_map[g_cCurrentPlayerForCmd]
#define AM_ENDKEY       key_map[g_cCurrentPlayerForCmd]
#define AM_GRABMOUSEKEY 222     // Petit 2 en haut à gauche du clavier
#define AM_NEXTLVL      13     // Petit Enter

#define AM_GOBIGKEY     '0'
// MR300698
/*#define AM_FOLLOWKEY  'f'
#define AM_GRIDKEY      'g'
#define AM_MARKKEY      'm'
#define AM_CLEARMARKKEY 'c'*/
#define AM_FOLLOWKEY    'F'
#define AM_GRIDKEY      'G'
#define AM_MARKKEY      'M'
#define AM_CLEARMARKKEY 'C'

#define AM_NUMMARKPOINTS 10

// scale on entry
#define INITSCALEMTOF (.2*FRACUNIT)
// how much the automap moves window per tic in frame-buffer coordinates
// moves 140 pixels in 1 second
#define F_PANINC        4
// how much zoom-in per tic
// goes to 2x in 1 second
#define M_ZOOMIN        ((int) (1.02*FRACUNIT))
// how much zoom-out per tic
// pulls out to 0.5x in 1 second
#define M_ZOOMOUT       ((int) (FRACUNIT/1.02))

// translates between frame-buffer and map distances
#define FTOM(x) FixedMul(((x)<<16),scale_ftom[g_cAMCurrentPlayer])
#define MTOF(x) (FixedMul((x),scale_mtof[g_cAMCurrentPlayer])>>16)
// translates between frame-buffer and map coordinates
#define CXMTOF(x)  (f_x + MTOF((x)-m_x[g_cAMCurrentPlayer]))
#define CYMTOF(y)  (f_y + (f_h - MTOF((y)-m_y[g_cAMCurrentPlayer])))

// the following is crap
#define LINE_NEVERSEE ML_DONTDRAW

typedef struct
{
    int x, y;
} fpoint_t;

typedef struct
{
    fpoint_t a, b;
} fline_t;

typedef struct
{
    fixed_t             x,y;
} mpoint_t;

typedef struct
{
    mpoint_t a, b;
} mline_t;

typedef struct
{
    fixed_t slp, islp;
} islope_t;



//
// The vector graphics for the automap.
//  A line drawing of the player pointing right,
//   starting from the middle.
//
#define R ((8*PLAYERRADIUS)/7)
mline_t player_arrow[] = {
    { { -R+R/8, 0 }, { R, 0 } }, // -----
    { { R, 0 }, { R-R/2, R/4 } },  // ----->
    { { R, 0 }, { R-R/2, -R/4 } },
    { { -R+R/8, 0 }, { -R-R/8, R/4 } }, // >---->
    { { -R+R/8, 0 }, { -R-R/8, -R/4 } },
    { { -R+3*R/8, 0 }, { -R+R/8, R/4 } }, // >>--->
    { { -R+3*R/8, 0 }, { -R+R/8, -R/4 } }
};
#undef R
#define NUMPLYRLINES (sizeof(player_arrow)/sizeof(mline_t))

#define R ((8*PLAYERRADIUS)/7)
mline_t cheat_player_arrow[] = {
    { { -R+R/8, 0 }, { R, 0 } }, // -----
    { { R, 0 }, { R-R/2, R/6 } },  // ----->
    { { R, 0 }, { R-R/2, -R/6 } },
    { { -R+R/8, 0 }, { -R-R/8, R/6 } }, // >----->
    { { -R+R/8, 0 }, { -R-R/8, -R/6 } },
    { { -R+3*R/8, 0 }, { -R+R/8, R/6 } }, // >>----->
    { { -R+3*R/8, 0 }, { -R+R/8, -R/6 } },
    { { -R/2, 0 }, { -R/2, -R/6 } }, // >>-d--->
    { { -R/2, -R/6 }, { -R/2+R/6, -R/6 } },
    { { -R/2+R/6, -R/6 }, { -R/2+R/6, R/4 } },
    { { -R/6, 0 }, { -R/6, -R/6 } }, // >>-dd-->
    { { -R/6, -R/6 }, { 0, -R/6 } },
    { { 0, -R/6 }, { 0, R/4 } },
    { { R/6, R/4 }, { R/6, -R/7 } }, // >>-ddt->
    { { R/6, -R/7 }, { R/6+R/32, -R/7-R/32 } },
    { { R/6+R/32, -R/7-R/32 }, { R/6+R/10, -R/7 } }
};
#undef R
#define NUMCHEATPLYRLINES (sizeof(cheat_player_arrow)/sizeof(mline_t))

#define R (FRACUNIT)
mline_t triangle_guy[] = {
    { { -.867*R, -.5*R }, { .867*R, -.5*R } },
    { { .867*R, -.5*R } , { 0, R } },
    { { 0, R }, { -.867*R, -.5*R } }
};
#undef R
#define NUMTRIANGLEGUYLINES (sizeof(triangle_guy)/sizeof(mline_t))

#define R (FRACUNIT)
mline_t thintriangle_guy[] = {
    { { -.5*R, -.7*R }, { R, 0 } },
    { { R, 0 }, { -.5*R, .7*R } },
    { { -.5*R, .7*R }, { -.5*R, -.7*R } }
};
#undef R
#define NUMTHINTRIANGLEGUYLINES (sizeof(thintriangle_guy)/sizeof(mline_t))




static int      cheating = 0;
static int      grid = 0;

static int      leveljuststarted = 1;   // kluge until AM_LevelInit() is called

boolean         automapactive[MAXPLAYERS] = { false, false };
static int      finit_width;
static int      finit_height;

// location of window on screen
static int      f_x;
static int      f_y;

// size of window on screen
static int      f_w;
static int      f_h;

static int      lightlev[MAXPLAYERS];               // used for funky strobing effect
static byte*    fb[MAXPLAYERS];                     // pseudo-frame buffer
static int      amclock[MAXPLAYERS];

static mpoint_t m_paninc[MAXPLAYERS]; // how far the window pans each tic (map coords)
static fixed_t  mtof_zoommul[MAXPLAYERS]; // how far the window zooms in each tic (map coords)
static fixed_t  ftom_zoommul[MAXPLAYERS]; // how far the window zooms in each tic (fb coords)

static fixed_t  m_x[MAXPLAYERS], m_y[MAXPLAYERS];   // LL x,y where the window is on the map (map coords)
static fixed_t  m_x2[MAXPLAYERS], m_y2[MAXPLAYERS]; // UR x,y where the window is on the map (map coords)

//
// width/height of window on map (map coords)
//
static fixed_t  m_w[MAXPLAYERS];
static fixed_t  m_h[MAXPLAYERS];

// based on level size
static fixed_t  min_x;
static fixed_t  min_y; 
static fixed_t  max_x;
static fixed_t  max_y;

static fixed_t  max_w; // max_x-min_x,
static fixed_t  max_h; // max_y-min_y

// based on player size
static fixed_t  min_w;
static fixed_t  min_h;


static fixed_t  min_scale_mtof; // used to tell when to stop zooming out
static fixed_t  max_scale_mtof; // used to tell when to stop zooming in

// old stuff for recovery later
static fixed_t old_m_w[MAXPLAYERS], old_m_h[MAXPLAYERS];
static fixed_t old_m_x[MAXPLAYERS], old_m_y[MAXPLAYERS];

// old location used by the Follower routine
static mpoint_t f_oldloc[MAXPLAYERS];

// used by MTOF to scale from map-to-frame-buffer coords
fixed_t scale_mtof[MAXPLAYERS] = { INITSCALEMTOF, INITSCALEMTOF};
// used by FTOM to scale from frame-buffer-to-map coords (=1/scale_mtof)
static fixed_t scale_ftom[MAXPLAYERS];

static player_t *plr[MAXPLAYERS]; // the player represented by an arrow

static patch_t *marknums[MAXPLAYERS][10]; // numbers used for marking by the automap
static mpoint_t markpoints[MAXPLAYERS][AM_NUMMARKPOINTS]; // where the points are
int markpointnum[MAXPLAYERS] = { 0, 0 }; // next point to be assigned

int followplayer[MAXPLAYERS] = { 1, 1 }; // specifies whether to follow the player around

static unsigned char cheat_amap_seq[] = { 0xb2, 0x26, 0x26, 0x2e, 0xff };
static cheatseq_t cheat_amap = { cheat_amap_seq, 0 };

boolean stopped[MAXPLAYERS] = { true, true };

extern boolean viewactive;
//extern byte screens[][SCREENWIDTH*SCREENHEIGHT];

void resinit_am_map_c(void)
  {
  finit_width = SCREENWIDTH;
  finit_height = SCREENHEIGHT - 32;
  }

// Calculates the slope and slope according to the x-axis of a line
// segment in map coordinates (with the upright y-axis n' all) so
// that it can be used with the brain-dead drawing stuff.

void
AM_getIslope
( mline_t*      ml,
  islope_t*     is )
{
    int dx, dy;

    dy = ml->a.y - ml->b.y;
    dx = ml->b.x - ml->a.x;
    if (!dy) is->islp = (dx<0?-MAXINT:MAXINT);
    else is->islp = FixedDiv(dx, dy);
    if (!dx) is->slp = (dy<0?-MAXINT:MAXINT);
    else is->slp = FixedDiv(dy, dx);

}

//
//
//
void AM_activateNewScale(void)
{
    m_x[g_cAMCurrentPlayer] += m_w[g_cAMCurrentPlayer]/2;
    m_y[g_cAMCurrentPlayer] += m_h[g_cAMCurrentPlayer]/2;
    m_w[g_cAMCurrentPlayer] = FTOM(f_w);
    m_h[g_cAMCurrentPlayer] = FTOM(f_h);
    m_x[g_cAMCurrentPlayer] -= m_w[g_cAMCurrentPlayer]/2;
    m_y[g_cAMCurrentPlayer] -= m_h[g_cAMCurrentPlayer]/2;
    m_x2[g_cAMCurrentPlayer] = m_x[g_cAMCurrentPlayer] + m_w[g_cAMCurrentPlayer];
    m_y2[g_cAMCurrentPlayer] = m_y[g_cAMCurrentPlayer] + m_h[g_cAMCurrentPlayer];
}

//
//
//
void AM_saveScaleAndLoc(void)
{
    old_m_x[g_cAMCurrentPlayer] = m_x[g_cAMCurrentPlayer];
    old_m_y[g_cAMCurrentPlayer] = m_y[g_cAMCurrentPlayer];
    old_m_w[g_cAMCurrentPlayer] = m_w[g_cAMCurrentPlayer];
    old_m_h[g_cAMCurrentPlayer] = m_h[g_cAMCurrentPlayer];
}

//
//
//
void AM_restoreScaleAndLoc(void)
{

    m_w[g_cAMCurrentPlayer] = old_m_w[g_cAMCurrentPlayer];
    m_h[g_cAMCurrentPlayer] = old_m_h[g_cAMCurrentPlayer];
    if (!followplayer[g_cAMCurrentPlayer])
    {
        m_x[g_cAMCurrentPlayer] = old_m_x[g_cAMCurrentPlayer];
        m_y[g_cAMCurrentPlayer] = old_m_y[g_cAMCurrentPlayer];
    } else {
        m_x[g_cAMCurrentPlayer] = plr[g_cAMCurrentPlayer]->mo->x - m_w[g_cAMCurrentPlayer]/2;
        m_y[g_cAMCurrentPlayer] = plr[g_cAMCurrentPlayer]->mo->y - m_h[g_cAMCurrentPlayer]/2;
    }
    m_x2[g_cAMCurrentPlayer] = m_x[g_cAMCurrentPlayer] + m_w[g_cAMCurrentPlayer];
    m_y2[g_cAMCurrentPlayer] = m_y[g_cAMCurrentPlayer] + m_h[g_cAMCurrentPlayer];

    // Change the scaling multipliers
    scale_mtof[g_cAMCurrentPlayer] = FixedDiv(f_w<<FRACBITS, m_w[g_cAMCurrentPlayer]);
    scale_ftom[g_cAMCurrentPlayer] = FixedDiv(FRACUNIT, scale_mtof[g_cAMCurrentPlayer]);
}

//
// adds a marker at the current location
//
void AM_addMark(void)
{
    markpoints[g_cAMCurrentPlayer][markpointnum[g_cAMCurrentPlayer]].x = m_x[g_cAMCurrentPlayer] + m_w[g_cAMCurrentPlayer]/2;
    markpoints[g_cAMCurrentPlayer][markpointnum[g_cAMCurrentPlayer]].y = m_y[g_cAMCurrentPlayer] + m_h[g_cAMCurrentPlayer]/2;
    markpointnum[g_cAMCurrentPlayer] = (markpointnum[g_cAMCurrentPlayer] + 1) % AM_NUMMARKPOINTS;

}

//
// Determines bounding box of all vertices,
// sets global variables controlling zoom range.
//
void AM_findMinMaxBoundaries(void)
{
    int i;
    fixed_t a;
    fixed_t b;

    min_x = min_y =  MAXINT;
    max_x = max_y = -MAXINT;
  
    for (i=0;i<numvertexes;i++)
    {
        if (vertexes[i].x < min_x)
            min_x = vertexes[i].x;
        else if (vertexes[i].x > max_x)
            max_x = vertexes[i].x;
    
        if (vertexes[i].y < min_y)
            min_y = vertexes[i].y;
        else if (vertexes[i].y > max_y)
            max_y = vertexes[i].y;
    }
  
    max_w = max_x - min_x;
    max_h = max_y - min_y;

    min_w = 2*PLAYERRADIUS; // const? never changed?
    min_h = 2*PLAYERRADIUS;

    a = FixedDiv(f_w<<FRACBITS, max_w);
    b = FixedDiv(f_h<<FRACBITS, max_h);
  
    min_scale_mtof = a < b ? a : b;
    max_scale_mtof = FixedDiv(f_h<<FRACBITS, 2*PLAYERRADIUS);

}


//
//
//
void AM_changeWindowLoc(void)
{
    if (m_paninc[g_cAMCurrentPlayer].x || m_paninc[g_cAMCurrentPlayer].y)
    {
        followplayer[g_cAMCurrentPlayer] = 0;
        f_oldloc[g_cAMCurrentPlayer].x = MAXINT;
    }

    m_x[g_cAMCurrentPlayer] += m_paninc[g_cAMCurrentPlayer].x;
    m_y[g_cAMCurrentPlayer] += m_paninc[g_cAMCurrentPlayer].y;

    if (m_x[g_cAMCurrentPlayer] + m_w[g_cAMCurrentPlayer]/2 > max_x)
        m_x[g_cAMCurrentPlayer] = max_x - m_w[g_cAMCurrentPlayer]/2;
    else if (m_x[g_cAMCurrentPlayer] + m_w[g_cAMCurrentPlayer]/2 < min_x)
        m_x[g_cAMCurrentPlayer] = min_x - m_w[g_cAMCurrentPlayer]/2;
  
    if (m_y[g_cAMCurrentPlayer] + m_h[g_cAMCurrentPlayer]/2 > max_y)
        m_y[g_cAMCurrentPlayer] = max_y - m_h[g_cAMCurrentPlayer]/2;
    else if (m_y[g_cAMCurrentPlayer] + m_h[g_cAMCurrentPlayer]/2 < min_y)
        m_y[g_cAMCurrentPlayer] = min_y - m_h[g_cAMCurrentPlayer]/2;

    m_x2[g_cAMCurrentPlayer] = m_x[g_cAMCurrentPlayer] + m_w[g_cAMCurrentPlayer];
    m_y2[g_cAMCurrentPlayer] = m_y[g_cAMCurrentPlayer] + m_h[g_cAMCurrentPlayer];
}


//
//
//
void AM_initVariables(void)
{
    int pnum;
    static event_t st_notify = { ev_keyup, AM_MSGENTERED };

    automapactive[g_cAMCurrentPlayer] = true;
    //fb[g_cAMCurrentPlayer] = screens[0];
        fb[g_cAMCurrentPlayer] = screensMP[5*g_cAMCurrentPlayer];

    f_oldloc[g_cAMCurrentPlayer].x = MAXINT;
    amclock[g_cAMCurrentPlayer] = 0;
    lightlev[g_cAMCurrentPlayer] = 0;

    m_paninc[g_cAMCurrentPlayer].x = m_paninc[g_cAMCurrentPlayer].y = 0;
    ftom_zoommul[g_cAMCurrentPlayer] = FRACUNIT;
    mtof_zoommul[g_cAMCurrentPlayer] = FRACUNIT;

    m_w[g_cAMCurrentPlayer] = FTOM(f_w);
    m_h[g_cAMCurrentPlayer] = FTOM(f_h);

    // find player to center on initially
    //if (!playeringame[pnum = consoleplayer])          // MR260698
        if (!playeringame[pnum = g_cAMCurrentPlayer])
        for (pnum=0;pnum<MAXPLAYERS;pnum++)
            if (playeringame[pnum])
                break;
  
    plr[g_cAMCurrentPlayer] = &players[pnum];
    m_x[g_cAMCurrentPlayer] = plr[g_cAMCurrentPlayer]->mo->x - m_w[g_cAMCurrentPlayer]/2;
    m_y[g_cAMCurrentPlayer] = plr[g_cAMCurrentPlayer]->mo->y - m_h[g_cAMCurrentPlayer]/2;
    AM_changeWindowLoc();

    // for saving & restoring
    old_m_x[g_cAMCurrentPlayer] = m_x[g_cAMCurrentPlayer];
    old_m_y[g_cAMCurrentPlayer] = m_y[g_cAMCurrentPlayer];
    old_m_w[g_cAMCurrentPlayer] = m_w[g_cAMCurrentPlayer];
    old_m_h[g_cAMCurrentPlayer] = m_h[g_cAMCurrentPlayer];

    // inform the status bar of the change
    ST_Responder(&st_notify);

}

//
// 
//
void AM_loadPics(void)
{
    int i;
    char namebuf[9];
  
    for (i=0;i<10;i++)
    {
        sprintf(namebuf, "AMMNUM%d", i);
        marknums[g_cAMCurrentPlayer][i] = W_CacheLumpName(namebuf, PU_STATIC);
    }

}

void AM_unloadPics(void)
{
    int i;
  
    for (i=0;i<10;i++)
        Z_ChangeTag(marknums[g_cAMCurrentPlayer][i], PU_CACHE);

}

void AM_clearMarks(void)
{
    int i;

    for (i=0;i<AM_NUMMARKPOINTS;i++)
        markpoints[g_cAMCurrentPlayer][i].x = -1; // means empty
    markpointnum[g_cAMCurrentPlayer] = 0;
}

//
// should be called at the start of every level
// right now, i figure it out myself
//
void AM_LevelInit(void)
{
    leveljuststarted = 0;

    f_x = f_y = 0;
    f_w = finit_width;
    f_h = finit_height;

    AM_clearMarks();

    AM_findMinMaxBoundaries();
    scale_mtof[g_cAMCurrentPlayer] = FixedDiv(min_scale_mtof, (int) (0.7*FRACUNIT));
    if (scale_mtof[g_cAMCurrentPlayer] > max_scale_mtof)
        scale_mtof[g_cAMCurrentPlayer] = min_scale_mtof;
    scale_ftom[g_cAMCurrentPlayer] = FixedDiv(FRACUNIT, scale_mtof[g_cAMCurrentPlayer]);
}




//
//
//
void AM_Stop (void)
{
    static event_t st_notify = { 0, ev_keyup, AM_MSGEXITED };

    AM_unloadPics();
    automapactive[g_cAMCurrentPlayer] = false;
    ST_Responder(&st_notify);
    stopped[g_cAMCurrentPlayer] = true;
}

//
//
//
// MR070798
int lastlevel[MAXPLAYERS] = { -1, -1 }, lastepisode[MAXPLAYERS] = { -1, -1 };
void AM_Start (void)
{
    // MR070798
        //static int lastlevel[MAXPLAYERS] = { -1, -1 }, lastepisode[MAXPLAYERS] = { -1, -1 };

    if (!stopped[g_cAMCurrentPlayer]) AM_Stop();
    stopped[g_cAMCurrentPlayer] = false;
    if (lastlevel[g_cAMCurrentPlayer] != gamemap || lastepisode[g_cAMCurrentPlayer] != gameepisode)
    {
        AM_LevelInit();
        lastlevel[g_cAMCurrentPlayer] = gamemap;
        lastepisode[g_cAMCurrentPlayer] = gameepisode;
    }
    AM_initVariables();
    AM_loadPics();
}

//
// set the window scale to the maximum size
//
void AM_minOutWindowScale(void)
{
    scale_mtof[g_cAMCurrentPlayer] = min_scale_mtof;
    scale_ftom[g_cAMCurrentPlayer] = FixedDiv(FRACUNIT, scale_mtof[g_cAMCurrentPlayer]);
    AM_activateNewScale();
}

//
// set the window scale to the minimum size
//
void AM_maxOutWindowScale(void)
{
    scale_mtof[g_cAMCurrentPlayer] = max_scale_mtof;
    scale_ftom[g_cAMCurrentPlayer] = FixedDiv(FRACUNIT, scale_mtof[g_cAMCurrentPlayer]);
    AM_activateNewScale();
}


//
// Handle events (user inputs) in automap mode
//
boolean
AM_Responder
( event_t*      ev )
{

    int rc;
    static int cheatstate=0;
    static int bigstate=0;
    static char buffer[20];

        // MRSuit
        g_cAMCurrentPlayer=g_cCurrentPlayerForCmd;

// MR110798
    if (!g_cAMCurrentPlayer&&(ev->type == ev_keydown && ev->data1 == AM_GRABMOUSEKEY))
        fn_vChangeGrabMouse();

    if (!g_cAMCurrentPlayer&&(ev->type == ev_keydown && ev->data1 == AM_NEXTLVL))
        G_ExitLevel();

    rc = false;

    if (!automapactive[g_cAMCurrentPlayer])
    {
        if (ev->type == ev_keydown && ev->data1 == AM_STARTKEY)
        {
            AM_Start ();
            viewactive = false;
            rc = true;
        }
    }

    else if (ev->type == ev_keydown)
    {

        rc = true;
// MR300698
/*      switch(ev->data1)
        {
          case AM_PANRIGHTKEY: // pan right
            if (!followplayer[g_cAMCurrentPlayer]) m_paninc[g_cAMCurrentPlayer].x = FTOM(F_PANINC);
            else rc = false;
            break;
          case AM_PANLEFTKEY: // pan left
            if (!followplayer[g_cAMCurrentPlayer]) m_paninc[g_cAMCurrentPlayer].x = -FTOM(F_PANINC);
            else rc = false;
            break;
          case AM_PANUPKEY: // pan up
            if (!followplayer[g_cAMCurrentPlayer]) m_paninc[g_cAMCurrentPlayer].y = FTOM(F_PANINC);
            else rc = false;
            break;
          case AM_PANDOWNKEY: // pan down
            if (!followplayer[g_cAMCurrentPlayer]) m_paninc[g_cAMCurrentPlayer].y = -FTOM(F_PANINC);
            else rc = false;
            break;
          case AM_ZOOMOUTKEY: // zoom out
            mtof_zoommul[g_cAMCurrentPlayer] = M_ZOOMOUT;
            ftom_zoommul[g_cAMCurrentPlayer] = M_ZOOMIN;
            break;
          case AM_ZOOMINKEY: // zoom in
            mtof_zoommul[g_cAMCurrentPlayer] = M_ZOOMIN;
            ftom_zoommul[g_cAMCurrentPlayer] = M_ZOOMOUT;
            break;
          case AM_ENDKEY:
            bigstate = 0;
            viewactive = true;
            AM_Stop ();
            break;
          case AM_GOBIGKEY:
            bigstate = !bigstate;
            if (bigstate)
            {
                AM_saveScaleAndLoc();
                AM_minOutWindowScale();
            }
            else AM_restoreScaleAndLoc();
            break;
          case AM_FOLLOWKEY:
            followplayer[g_cAMCurrentPlayer] = !followplayer[g_cAMCurrentPlayer];
            f_oldloc[g_cAMCurrentPlayer].x = MAXINT;
            plr[g_cAMCurrentPlayer]->message = followplayer[g_cAMCurrentPlayer] ? AMSTR_FOLLOWON : AMSTR_FOLLOWOFF;
            break;
          case AM_GRIDKEY:
            grid = !grid;
            plr[g_cAMCurrentPlayer]->message = grid ? AMSTR_GRIDON : AMSTR_GRIDOFF;
            break;
          case AM_MARKKEY:
            sprintf(buffer, "%s %d", AMSTR_MARKEDSPOT, markpointnum);
            plr[g_cAMCurrentPlayer]->message = buffer;
            AM_addMark();
            break;
          case AM_CLEARMARKKEY:
            AM_clearMarks();
            plr[g_cAMCurrentPlayer]->message = AMSTR_MARKSCLEARED;
            break;
          default:
            cheatstate=0;
            rc = false;
        }*/
        if (ev->data1==AM_PANRIGHTKEY)
        {    if (!followplayer[g_cAMCurrentPlayer]) m_paninc[g_cAMCurrentPlayer].x = FTOM(F_PANINC);
            else rc = false;
        }
        else
        if (ev->data1==AM_PANLEFTKEY)
        {    if (!followplayer[g_cAMCurrentPlayer]) m_paninc[g_cAMCurrentPlayer].x = -FTOM(F_PANINC);
            else rc = false;
        }
        else
        if (ev->data1==AM_PANUPKEY)
        {    if (!followplayer[g_cAMCurrentPlayer]) m_paninc[g_cAMCurrentPlayer].y = FTOM(F_PANINC);
            else rc = false;
        }
        else
        if (ev->data1==AM_PANDOWNKEY)
        {    if (!followplayer[g_cAMCurrentPlayer]) m_paninc[g_cAMCurrentPlayer].y = -FTOM(F_PANINC);
            else rc = false;
        }
        else
        if (ev->data1==AM_ENDKEY)
        {    bigstate = 0;
            viewactive = true;
            AM_Stop ();
        }
        else
        switch(ev->data1)
        {
          case AM_ZOOMOUTKEY: // zoom out
            mtof_zoommul[g_cAMCurrentPlayer] = M_ZOOMOUT;
            ftom_zoommul[g_cAMCurrentPlayer] = M_ZOOMIN;
            break;
          case AM_ZOOMINKEY: // zoom in
            mtof_zoommul[g_cAMCurrentPlayer] = M_ZOOMIN;
            ftom_zoommul[g_cAMCurrentPlayer] = M_ZOOMOUT;
            break;
          case AM_GOBIGKEY:
            bigstate = !bigstate;
            if (bigstate)
            {
                AM_saveScaleAndLoc();
                AM_minOutWindowScale();
            }
            else AM_restoreScaleAndLoc();
            break;
          case AM_FOLLOWKEY:
            followplayer[g_cAMCurrentPlayer] = !followplayer[g_cAMCurrentPlayer];
            f_oldloc[g_cAMCurrentPlayer].x = MAXINT;
            plr[g_cAMCurrentPlayer]->message = followplayer[g_cAMCurrentPlayer] ? AMSTR_FOLLOWON : AMSTR_FOLLOWOFF;
            break;
          case AM_GRIDKEY:
            grid = !grid;
            plr[g_cAMCurrentPlayer]->message = grid ? AMSTR_GRIDON : AMSTR_GRIDOFF;
            break;
          case AM_MARKKEY:
            sprintf(buffer, "%s %d", AMSTR_MARKEDSPOT, markpointnum);
            plr[g_cAMCurrentPlayer]->message = buffer;
            AM_addMark();
            break;
          case AM_CLEARMARKKEY:
            AM_clearMarks();
            plr[g_cAMCurrentPlayer]->message = AMSTR_MARKSCLEARED;
            break;
          default:
            cheatstate=0;
            rc = false;
        }
        // End MR300698
        if (!deathmatch && cht_CheckCheat(&cheat_amap, (char)ev->data1))
        {
            rc = false;
            cheating = (cheating+1) % 3;
        }
    }

    else if (ev->type == ev_keyup)
    {
        rc = false;
// MR300698
/*      switch (ev->data1)
        {
          case AM_PANRIGHTKEY:
            if (!followplayer[g_cAMCurrentPlayer]) m_paninc[g_cAMCurrentPlayer].x = 0;
            break;
          case AM_PANLEFTKEY:
            if (!followplayer[g_cAMCurrentPlayer]) m_paninc[g_cAMCurrentPlayer].x = 0;
            break;
          case AM_PANUPKEY:
            if (!followplayer[g_cAMCurrentPlayer]) m_paninc[g_cAMCurrentPlayer].y = 0;
            break;
          case AM_PANDOWNKEY:
            if (!followplayer[g_cAMCurrentPlayer]) m_paninc[g_cAMCurrentPlayer].y = 0;
            break;
          case AM_ZOOMOUTKEY:
          case AM_ZOOMINKEY:
            mtof_zoommul[g_cAMCurrentPlayer] = FRACUNIT;
            ftom_zoommul[g_cAMCurrentPlayer] = FRACUNIT;
            break;
        }*/

        if (ev->data1==AM_PANRIGHTKEY)
        {    if (!followplayer[g_cAMCurrentPlayer]) m_paninc[g_cAMCurrentPlayer].x = 0;

        }
        else
        if (ev->data1==AM_PANLEFTKEY)
        {    if (!followplayer[g_cAMCurrentPlayer]) m_paninc[g_cAMCurrentPlayer].x = 0;
        }
        else
        if (ev->data1==AM_PANUPKEY)
        {    if (!followplayer[g_cAMCurrentPlayer]) m_paninc[g_cAMCurrentPlayer].y = 0;
        }
        else
        if (ev->data1==AM_PANDOWNKEY)
        {    if (!followplayer[g_cAMCurrentPlayer]) m_paninc[g_cAMCurrentPlayer].y = 0;
        }
        else
        switch (ev->data1)
        {
          case AM_ZOOMOUTKEY:
          case AM_ZOOMINKEY:
            mtof_zoommul[g_cAMCurrentPlayer] = FRACUNIT;
            ftom_zoommul[g_cAMCurrentPlayer] = FRACUNIT;
            break;
        }
// End MR300698
    }

    return rc;

}


//
// Zooming
//
void AM_changeWindowScale(void)
{

    // Change the scaling multipliers
    scale_mtof[g_cAMCurrentPlayer] = FixedMul(scale_mtof[g_cAMCurrentPlayer], mtof_zoommul[g_cAMCurrentPlayer]);
    scale_ftom[g_cAMCurrentPlayer] = FixedDiv(FRACUNIT, scale_mtof[g_cAMCurrentPlayer]);

    if (scale_mtof[g_cAMCurrentPlayer] < min_scale_mtof)
        AM_minOutWindowScale();
    else if (scale_mtof[g_cAMCurrentPlayer] > max_scale_mtof)
        AM_maxOutWindowScale();
    else
        AM_activateNewScale();
}


//
//
//
void AM_doFollowPlayer(void)
{

    if (f_oldloc[g_cAMCurrentPlayer].x != plr[g_cAMCurrentPlayer]->mo->x || f_oldloc[g_cAMCurrentPlayer].y != plr[g_cAMCurrentPlayer]->mo->y)
    {
        m_x[g_cAMCurrentPlayer] = FTOM(MTOF(plr[g_cAMCurrentPlayer]->mo->x)) - m_w[g_cAMCurrentPlayer]/2;
        m_y[g_cAMCurrentPlayer] = FTOM(MTOF(plr[g_cAMCurrentPlayer]->mo->y)) - m_h[g_cAMCurrentPlayer]/2;
        m_x2[g_cAMCurrentPlayer] = m_x[g_cAMCurrentPlayer] + m_w[g_cAMCurrentPlayer];
        m_y2[g_cAMCurrentPlayer] = m_y[g_cAMCurrentPlayer] + m_h[g_cAMCurrentPlayer];
        f_oldloc[g_cAMCurrentPlayer].x = plr[g_cAMCurrentPlayer]->mo->x;
        f_oldloc[g_cAMCurrentPlayer].y = plr[g_cAMCurrentPlayer]->mo->y;

        //  m_x = FTOM(MTOF(plr->mo->x - m_w/2));
        //  m_y = FTOM(MTOF(plr->mo->y - m_h/2));
        //  m_x = plr->mo->x - m_w/2;
        //  m_y = plr->mo->y - m_h/2;

    }

}

//
//
//
// MR070798
int nexttic[MAXPLAYERS] = { 0, 0 };
int litelevelscnt[MAXPLAYERS] = { 0, 0 };

void AM_updateLightLev(void)
{
    // MR070798
        //static nexttic[MAXPLAYERS] = { 0, 0 };
    static int litelevels[] = { 0, 4, 7, 10, 12, 14, 15, 15 };
    // MR070798
        //static int litelevelscnt[MAXPLAYERS] = { 0, 0 };
   
    // Change light level
    if (amclock[g_cAMCurrentPlayer]>nexttic[g_cAMCurrentPlayer])
    {
        lightlev[g_cAMCurrentPlayer] = litelevels[litelevelscnt[g_cAMCurrentPlayer]++];
        if (litelevelscnt[g_cAMCurrentPlayer] == sizeof(litelevels)/sizeof(int)) litelevelscnt[g_cAMCurrentPlayer] = 0;
        nexttic[g_cAMCurrentPlayer] = amclock[g_cAMCurrentPlayer] + 6 - (amclock[g_cAMCurrentPlayer] % 6);
    }

}


//
// Updates on Game Tick
//
void AM_Ticker (void)
{

        // MRSuit
        g_cAMCurrentPlayer=g_cCurrentPlayerForDsp;

    if (!automapactive[g_cAMCurrentPlayer])
        return;

    amclock[g_cAMCurrentPlayer]++;

    if (followplayer[g_cAMCurrentPlayer])
        AM_doFollowPlayer();

    // Change the zoom if necessary
    if (ftom_zoommul[g_cAMCurrentPlayer] != FRACUNIT)
        AM_changeWindowScale();

    // Change x,y location
    if (m_paninc[g_cAMCurrentPlayer].x || m_paninc[g_cAMCurrentPlayer].y)
        AM_changeWindowLoc();

    // Update light level
    // AM_updateLightLev();

}


//
// Clear automap frame buffer.
//
void AM_clearFB(int color)
{
// MR110798
#ifndef WATWIN31
    memset(fb[g_cAMCurrentPlayer], color, f_w*f_h*BPP);
#else
    memset(fb[g_cAMCurrentPlayer]+SBARHEIGHT*SCREENWIDTH, color, f_w*f_h*BPP);
#endif
}


//
// Automap clipping of lines.
//
// Based on Cohen-Sutherland clipping algorithm but with a slightly
// faster reject and precalculated slopes.  If the speed is needed,
// use a hash algorithm to handle  the common cases.
//
boolean
AM_clipMline
( mline_t*      ml,
  fline_t*      fl )
{
    enum
    {
        LEFT    =1,
        RIGHT   =2,
        BOTTOM  =4,
        TOP     =8
    };
    
    register    outcode1 = 0;
    register    outcode2 = 0;
    register    outside;
    
    fpoint_t    tmp;
    int         dx;
    int         dy;

    
#define DOOUTCODE(oc, mx, my) \
    (oc) = 0; \
    if ((my) < 0) (oc) |= TOP; \
    else if ((my) >= f_h) (oc) |= BOTTOM; \
    if ((mx) < 0) (oc) |= LEFT; \
    else if ((mx) >= f_w) (oc) |= RIGHT;

    
    // do trivial rejects and outcodes
    if (ml->a.y > m_y2[g_cAMCurrentPlayer])
        outcode1 = TOP;
    else if (ml->a.y < m_y[g_cAMCurrentPlayer])
        outcode1 = BOTTOM;

    if (ml->b.y > m_y2[g_cAMCurrentPlayer])
        outcode2 = TOP;
    else if (ml->b.y < m_y[g_cAMCurrentPlayer])
        outcode2 = BOTTOM;
    
    if (outcode1 & outcode2)
        return false; // trivially outside

    if (ml->a.x < m_x[g_cAMCurrentPlayer])
        outcode1 |= LEFT;
    else if (ml->a.x > m_x2[g_cAMCurrentPlayer])
        outcode1 |= RIGHT;
    
    if (ml->b.x < m_x[g_cAMCurrentPlayer])
        outcode2 |= LEFT;
    else if (ml->b.x > m_x2[g_cAMCurrentPlayer])
        outcode2 |= RIGHT;
    
    if (outcode1 & outcode2)
        return false; // trivially outside

    // transform to frame-buffer coordinates.
    fl->a.x = CXMTOF(ml->a.x);
    fl->a.y = CYMTOF(ml->a.y);
    fl->b.x = CXMTOF(ml->b.x);
    fl->b.y = CYMTOF(ml->b.y);

    DOOUTCODE(outcode1, fl->a.x, fl->a.y);
    DOOUTCODE(outcode2, fl->b.x, fl->b.y);

    if (outcode1 & outcode2)
        return false;

    while (outcode1 | outcode2)
    {
        // may be partially inside box
        // find an outside point
        if (outcode1)
            outside = outcode1;
        else
            outside = outcode2;
        
        // clip to each side
        if (outside & TOP)
        {
            dy = fl->a.y - fl->b.y;
            dx = fl->b.x - fl->a.x;
            tmp.x = fl->a.x + (dx*(fl->a.y))/dy;
            tmp.y = 0;
        }
        else if (outside & BOTTOM)
        {
            dy = fl->a.y - fl->b.y;
            dx = fl->b.x - fl->a.x;
            tmp.x = fl->a.x + (dx*(fl->a.y-f_h))/dy;
            tmp.y = f_h-1;
        }
        else if (outside & RIGHT)
        {
            dy = fl->b.y - fl->a.y;
            dx = fl->b.x - fl->a.x;
            tmp.y = fl->a.y + (dy*(f_w-1 - fl->a.x))/dx;
            tmp.x = f_w-1;
        }
        else if (outside & LEFT)
        {
            dy = fl->b.y - fl->a.y;
            dx = fl->b.x - fl->a.x;
            tmp.y = fl->a.y + (dy*(-fl->a.x))/dx;
            tmp.x = 0;
        }

        if (outside == outcode1)
        {
            fl->a = tmp;
            DOOUTCODE(outcode1, fl->a.x, fl->a.y);
        }
        else
        {
            fl->b = tmp;
            DOOUTCODE(outcode2, fl->b.x, fl->b.y);
        }
        
        if (outcode1 & outcode2)
            return false; // trivially outside
    }

    return true;
}
#undef DOOUTCODE


//
// Classic Bresenham w/ whatever optimizations needed for speed
//
// two functions - one for 8bpp, one for 16bpp

void
AM_drawFline8
( fline_t*      fl,
  int           color )
{
    register int x;
    register int y;
    register int dx;
    register int dy;
    register int sx;
    register int sy;
    register int ax;
    register int ay;
    register int d;
    
    static fuck = 0;

    // For debugging only
    if (      fl->a.x < 0 || fl->a.x >= f_w
           || fl->a.y < 0 || fl->a.y >= f_h
           || fl->b.x < 0 || fl->b.x >= f_w
           || fl->b.y < 0 || fl->b.y >= f_h)
    {
        fprintf(stderr, "fuck %d \r", fuck++);
        return;
    }

    dx = fl->b.x - fl->a.x;
    ax = 2 * (dx<0 ? -dx : dx);
    sx = dx<0 ? -1 : 1;

    dy = fl->b.y - fl->a.y;
    ay = 2 * (dy<0 ? -dy : dy);
    sy = dy<0 ? -1 : 1;

    x = fl->a.x;
    y = fl->a.y;

    if (ax > ay)
    {
        d = ay - ax/2;
        while (1)
        {
// MR110798
#ifndef WATWIN31
       fb[g_cAMCurrentPlayer][(y)*f_w+(x)]=(color);
#else
       fb[g_cAMCurrentPlayer][REAL_Y(y)*f_w+(x)]=(color);
#endif
            if (x == fl->b.x) return;
            if (d>=0)
            {
                y += sy;
                d -= ax;
            }
            x += sx;
            d += ay;
        }
    }
    else
    {
        d = ax - ay/2;
        while (1)
        {
// MR110798
#ifndef WATWIN31
       fb[g_cAMCurrentPlayer][(y)*f_w+(x)]=(color);
#else
       fb[g_cAMCurrentPlayer][REAL_Y(y)*f_w+(x)]=(color);
#endif
            if (y == fl->b.y) return;
            if (d >= 0)
            {
                x += sx;
                d -= ay;
            }
            y += sy;
            d += ax;
        }
    }
}

void
AM_drawFline16
( fline_t*      fl,
  int           color )
{
    register int x;
    register int y;
    register int dx;
    register int dy;
    register int sx;
    register int sy;
    register int ax;
    register int ay;
    register int d;
    
    static fuck = 0;

    short *tempbuffer;


    tempbuffer=(short *)fb;
    // For debugging only
    if (      fl->a.x < 0 || fl->a.x >= f_w
           || fl->a.y < 0 || fl->a.y >= f_h
           || fl->b.x < 0 || fl->b.x >= f_w
           || fl->b.y < 0 || fl->b.y >= f_h)
    {
        fprintf(stderr, "fuck %d \r", fuck++);
        return;
    }

    dx = fl->b.x - fl->a.x;
    ax = 2 * (dx<0 ? -dx : dx);
    sx = dx<0 ? -1 : 1;

    dy = fl->b.y - fl->a.y;
    ay = 2 * (dy<0 ? -dy : dy);
    sy = dy<0 ? -1 : 1;

    x = fl->a.x;
    y = fl->a.y;

    if (ax > ay)
    {
        d = ay - ax/2;
        while (1)
        {
// MR110798
#ifndef WATWIN31
       tempbuffer[(y)*f_w+(x)]=palette_color[color];
#else
       tempbuffer[REAL_Y(y)*f_w+(x)]=palette_color[color];
#endif
            if (x == fl->b.x) return;
            if (d>=0)
            {
                y += sy;
                d -= ax;
            }
            x += sx;
            d += ay;
        }
    }
    else
    {
        d = ax - ay/2;
        while (1)
        {
// MR110798
#ifndef WATWIN31
       tempbuffer[(y)*f_w+(x)]=palette_color[color];
#else
       tempbuffer[REAL_Y(y)*f_w+(x)]=palette_color[color];
#endif
            if (y == fl->b.y) return;
            if (d >= 0)
            {
                x += sx;
                d -= ay;
            }
            y += sy;
            d += ax;
        }
    }
}



void
AM_drawFline
( fline_t*      fl,
  int           color )
{
if (BPP==1)
  AM_drawFline8(fl,color);
else
  AM_drawFline16(fl,color);
}


//
// Clip lines, draw visible part sof lines.
//
void
AM_drawMline
( mline_t*      ml,
  int           color )
{
    static fline_t fl;

    if (AM_clipMline(ml, &fl))
        AM_drawFline(&fl, color); // draws it on frame buffer using fb coords
}



//
// Draws flat (floor/ceiling tile) aligned grid lines.
//
void AM_drawGrid(int color)
{
    fixed_t x, y;
    fixed_t start, end;
    mline_t ml;

    // Figure out start of vertical gridlines
    start = m_x[g_cAMCurrentPlayer];
    if ((start-bmaporgx)%(MAPBLOCKUNITS<<FRACBITS))
        start += (MAPBLOCKUNITS<<FRACBITS)
            - ((start-bmaporgx)%(MAPBLOCKUNITS<<FRACBITS));
    end = m_x[g_cAMCurrentPlayer] + m_w[g_cAMCurrentPlayer];

    // draw vertical gridlines
    ml.a.y = m_y[g_cAMCurrentPlayer];
    ml.b.y = m_y[g_cAMCurrentPlayer]+m_h[g_cAMCurrentPlayer];
    for (x=start; x<end; x+=(MAPBLOCKUNITS<<FRACBITS))
    {
        ml.a.x = x;
        ml.b.x = x;
        AM_drawMline(&ml, color);
    }

    // Figure out start of horizontal gridlines
    start = m_y[g_cAMCurrentPlayer];
    if ((start-bmaporgy)%(MAPBLOCKUNITS<<FRACBITS))
        start += (MAPBLOCKUNITS<<FRACBITS)
            - ((start-bmaporgy)%(MAPBLOCKUNITS<<FRACBITS));
    end = m_y[g_cAMCurrentPlayer] + m_h[g_cAMCurrentPlayer];

    // draw horizontal gridlines
    ml.a.x = m_x[g_cAMCurrentPlayer];
    ml.b.x = m_x[g_cAMCurrentPlayer] + m_w[g_cAMCurrentPlayer];
    for (y=start; y<end; y+=(MAPBLOCKUNITS<<FRACBITS))
    {
        ml.a.y = y;
        ml.b.y = y;
        AM_drawMline(&ml, color);
    }

}

// MR290698
short VisibleAM[16] = {
        0x0001,
        0x0002,
        0x0004,
        0x0008,
        0x0010,
        0x0020,
        0x0040,
        0x0080,
        0x0100,
        0x0200,
        0x0400,
        0x0800,
        0x1000,
        0x2000,
        0x4000,
        0x8000
};

//
// Determines visible lines, draws them.
// This is LineDef based, not LineSeg based.
//
void AM_drawWalls(void)
{
    int i;
    static mline_t l;

    for (i=0;i<numlines;i++)
    {
        l.a.x = lines[i].v1->x;
        l.a.y = lines[i].v1->y;
        l.b.x = lines[i].v2->x;
        l.b.y = lines[i].v2->y;
        // MR290698 (AM)
        //if (cheating || (lines[i].flags & ML_MAPPED))
        if (cheating || (lines[i].flagsAM & VisibleAM[g_cAMCurrentPlayer]))
        {
            if ((lines[i].flags & LINE_NEVERSEE) && !cheating)
                continue;
            if (!lines[i].backsector)
            {
                AM_drawMline(&l, WALLCOLORS+lightlev[g_cAMCurrentPlayer]);
            }
            else
            {
                if (lines[i].special == 39)
                { // teleporters
                    AM_drawMline(&l, WALLCOLORS+WALLRANGE/2);
                }
                else if (lines[i].flags & ML_SECRET) // secret door
                {
                    if (cheating) AM_drawMline(&l, SECRETWALLCOLORS + lightlev[g_cAMCurrentPlayer]);
                    else AM_drawMline(&l, WALLCOLORS+lightlev[g_cAMCurrentPlayer]);
                }
                else if (lines[i].backsector->floorheight
                           != lines[i].frontsector->floorheight) {
                    AM_drawMline(&l, FDWALLCOLORS + lightlev[g_cAMCurrentPlayer]); // floor level change
                }
                else if (lines[i].backsector->ceilingheight
                           != lines[i].frontsector->ceilingheight) {
                    AM_drawMline(&l, CDWALLCOLORS+lightlev[g_cAMCurrentPlayer]); // ceiling level change
                }
                else if (cheating) {
                    AM_drawMline(&l, TSWALLCOLORS+lightlev[g_cAMCurrentPlayer]);
                }
            }
        }
        else if (plr[g_cAMCurrentPlayer]->powers[pw_allmap])
        {
            if (!(lines[i].flags & LINE_NEVERSEE)) AM_drawMline(&l, GRAYS+3);
        }
    }
}


//
// Rotation in 2D.
// Used to rotate player arrow line character.
//
void
AM_rotate
( fixed_t*      x,
  fixed_t*      y,
  angle_t       a )
{
    fixed_t tmpx;

    tmpx =
        FixedMul(*x,finecosine[a>>ANGLETOFINESHIFT])
        - FixedMul(*y,finesine[a>>ANGLETOFINESHIFT]);
    
    *y   =
        FixedMul(*x,finesine[a>>ANGLETOFINESHIFT])
        + FixedMul(*y,finecosine[a>>ANGLETOFINESHIFT]);

    *x = tmpx;
}

void
AM_drawLineCharacter
( mline_t*      lineguy,
  int           lineguylines,
  fixed_t       scale,
  angle_t       angle,
  int           color,
  fixed_t       x,
  fixed_t       y )
{
    int         i;
    mline_t     l;

    for (i=0;i<lineguylines;i++)
    {
        l.a.x = lineguy[i].a.x;
        l.a.y = lineguy[i].a.y;

        if (scale)
        {
            l.a.x = FixedMul(scale, l.a.x);
            l.a.y = FixedMul(scale, l.a.y);
        }

        if (angle)
            AM_rotate(&l.a.x, &l.a.y, angle);

        l.a.x += x;
        l.a.y += y;

        l.b.x = lineguy[i].b.x;
        l.b.y = lineguy[i].b.y;

        if (scale)
        {
            l.b.x = FixedMul(scale, l.b.x);
            l.b.y = FixedMul(scale, l.b.y);
        }

        if (angle)
            AM_rotate(&l.b.x, &l.b.y, angle);
        
        l.b.x += x;
        l.b.y += y;

        AM_drawMline(&l, color);
    }
}

void AM_drawPlayers(void)
{
    int         i;
    player_t*   p;
    static int  their_colors[] = { GREENS, GRAYS, BROWNS, REDS };
    int         their_color = -1;
    int         color;

    if (!netgame)
    {
        if (cheating)
            AM_drawLineCharacter
                (cheat_player_arrow, NUMCHEATPLYRLINES, 0,
                 plr[g_cAMCurrentPlayer]->mo->angle, WHITE, plr[g_cAMCurrentPlayer]->mo->x, plr[g_cAMCurrentPlayer]->mo->y);
        else
            AM_drawLineCharacter
                (player_arrow, NUMPLYRLINES, 0, plr[g_cAMCurrentPlayer]->mo->angle,
                 WHITE, plr[g_cAMCurrentPlayer]->mo->x, plr[g_cAMCurrentPlayer]->mo->y);
        return;
    }

    for (i=0;i<MAXPLAYERS;i++)
    {
        their_color++;
        p = &players[i];

        if ( (deathmatch && !singledemo) && p != plr[g_cAMCurrentPlayer])
            continue;

        if (!playeringame[i])
            continue;

        if (p->powers[pw_invisibility])
            color = 246; // *close* to black
        else
            color = their_colors[their_color];
        
        AM_drawLineCharacter
            (player_arrow, NUMPLYRLINES, 0, p->mo->angle,
             color, p->mo->x, p->mo->y);
    }

}

void
AM_drawThings
( int   colors,
  int   colorrange)
{
    int         i;
    mobj_t*     t;

    for (i=0;i<numsectors;i++)
    {
        t = sectors[i].thinglist;
        while (t)
        {
            AM_drawLineCharacter
                (thintriangle_guy, NUMTHINTRIANGLEGUYLINES,
                 16<<FRACBITS, t->angle, colors+lightlev[g_cAMCurrentPlayer], t->x, t->y);
            t = t->snext;
        }
    }
}

void AM_drawMarks(void)
{
    int i, fx, fy, w, h;

    for (i=0;i<AM_NUMMARKPOINTS;i++)
    {
        if (markpoints[g_cAMCurrentPlayer][i].x != -1)
        {
            //      w = SHORT(marknums[i]->width);
            //      h = SHORT(marknums[i]->height);
            w = 5; // because something's wrong with the wad, i guess
            h = 6; // because something's wrong with the wad, i guess
            fx = CXMTOF(markpoints[g_cAMCurrentPlayer][i].x);
            fy = CYMTOF(markpoints[g_cAMCurrentPlayer][i].y);
            if (fx >= f_x && fx <= f_w - w && fy >= f_y && fy <= f_h - h)
                V_DrawPatch(fx, fy, FB, marknums[g_cAMCurrentPlayer][i]);
        }
    }

}

void AM_drawCrosshair(int color)
  {
  if (BPP==1)
    fb[g_cAMCurrentPlayer][(f_w*(f_h+1))/2] = color; // single point for now
  else
    {
    short *tempbuffer;

    tempbuffer=(short *)fb[g_cAMCurrentPlayer];
    fb[g_cAMCurrentPlayer][(f_w*(f_h+1))/2] = palette_color[color]; // single point for now
    }
}

void AM_Drawer (void)
{
    
        g_cAMCurrentPlayer=g_cCurrentPlayerForDsp;
        
        if (!automapactive[g_cAMCurrentPlayer]) return;

    AM_clearFB(BACKGROUND);
    if (grid)
        AM_drawGrid(GRIDCOLORS);
    AM_drawWalls();
    AM_drawPlayers();
    if (cheating==2)
      AM_drawThings(THINGCOLORS, THINGRANGE);
    AM_drawCrosshair(XHAIRCOLORS);

    AM_drawMarks();

    V_MarkRect(f_x, f_y, f_w, f_h);

}
