// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id: hu_lib.c,v 1.3 1998/01/04 19:28:58 pekangas Exp $
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
// $Log: hu_lib.c,v $
// Revision 1.3  1998/01/04 19:28:58  pekangas
// Added hicolor and multiresulution support from Chi Hoang's DOS port
//
// Revision 1.2  1997/12/29 19:50:52  pekangas
// Ported to WinNT/95 environment using Watcom C 10.6.
// Everything expect joystick support is implemented, but networking is
// untested. Crashes way too often with problems in FixedDiv().
// Compiles with no warnings at warning level 3, uses MIDAS 1.1.1.
//
// Revision 1.1.1.1  1997/12/28 12:59:02  pekangas
// Initial DOOM source release from id Software
//
//
// DESCRIPTION:  heads-up text and input code
//
//-----------------------------------------------------------------------------

const char
hu_lib_rcsid[] = "$Id: hu_lib.c,v 1.3 1998/01/04 19:28:58 pekangas Exp $";

#include <ctype.h>

#include "doomdef.h"

#include "multires.h"
#include "m_swap.h"

#include "hu_lib.h"
#include "r_local.h"
#include "doomstat.h"

// boolean : whether the screen is always erased
#define noterased viewwindowx

// MR110798
#ifdef WATWIN31
#define REAL_Y(x) (SCREENHEIGHT-1-x)
#endif

extern boolean  automapactive[MAXPLAYERS];  // in AM_map.c

void HUlib_init(void)
{
}

void HUlib_clearTextLine(hu_textline_t* t)
{
    t->len = 0;
    t->l[0] = 0;
    t->needsupdate = true;
}

void
HUlib_initTextLine
( hu_textline_t*        t,
  int                   x,
  int                   y,
  patch_t**             f,
  int                   sc )
{
    t->x = x;
    t->y = y;
    t->f = f;
    t->sc = sc;
    HUlib_clearTextLine(t);
}

boolean
HUlib_addCharToTextLine
( hu_textline_t*        t,
  char                  ch )
{

    if (t->len == HU_MAXLINELENGTH)
        return false;
    else
    {
        t->l[t->len++] = ch;
        t->l[t->len] = 0;
        t->needsupdate = 4;
        return true;
    }

}

boolean HUlib_delCharFromTextLine(hu_textline_t* t)
{

    if (!t->len) return false;
    else
    {
        t->l[--t->len] = 0;
        t->needsupdate = 4;
        return true;
    }

}

void
HUlib_drawTextLine
( hu_textline_t*        l,
  boolean               drawcursor )
{

    int                 i;
    int                 w;
    int                 x;
    unsigned char       c;

    // draw the new stuff
    x = l->x;
    for (i=0;i<l->len;i++)
    {
        c = toupper(l->l[i]);
        if (c != ' '
            && c >= l->sc
            && c <= '_')
        {
            w = SHORT(l->f[c - l->sc]->width);
            if (x+w > SCREENWIDTH)
                break;
            V_DrawPatchDirect(x, l->y, FG, l->f[c - l->sc]);
            x += w;
        }
        else
        {
            x += 4;
            if (x >= SCREENWIDTH)
                break;
        }
    }

    // draw the cursor if requested
    if (drawcursor
        && x + SHORT(l->f['_' - l->sc]->width) <= SCREENWIDTH)
    {
        V_DrawPatchDirect(x, l->y, FG, l->f['_' - l->sc]);
    }
}


// sorta called by HU_Erase and just better darn get things straight
// MR070798
boolean lastautomapactive[MAXPLAYERS] = { true, true };
void HUlib_eraseTextLine(hu_textline_t* l)
{
    int                 lh;
    int                 y;
    int                 yoffset;
    //static boolean    lastautomapactive[MAXPLAYERS] = { true, true };     // MRSuit

    // Only erases when NOT in automap and the screen is reduced,
    // and the text must either need updating or refreshing
    // (because of a recent change back from the automap)

    if (!automapactive[g_cCurrentPlayerForDsp] &&
        viewwindowx && l->needsupdate)
    {
        lh = SHORT(l->f[0]->height) + 1;
        // MR110798
#ifndef WATWIN31
        for (y=l->y,yoffset=y*SCREENWIDTH ; y<l->y+lh ; y++,yoffset+=SCREENWIDTH)
#else
        for (y=l->y,yoffset=REAL_Y(y)*SCREENWIDTH ; y<l->y+lh ; y++,yoffset-=SCREENWIDTH)
#endif
        {
            if (y < viewwindowy || y >= viewwindowy + viewheight)
                R_VideoErase(yoffset, SCREENWIDTH); // erase entire line
            else
            {
                R_VideoErase(yoffset, viewwindowx); // erase left border
                R_VideoErase(yoffset + viewwindowx + viewwidth, viewwindowx);
                // erase right border
            }
        }
    }

    lastautomapactive[g_cCurrentPlayerForDsp] = automapactive[g_cCurrentPlayerForDsp];
    if (l->needsupdate) l->needsupdate--;

}

void
HUlib_initSText
( hu_stext_t*   s,
  int           x,
  int           y,
  int           h,
  patch_t**     font,
  int           startchar,
  boolean*      on )
{

    int i;

    s->h = h;
    s->on = on;
    s->laston = true;
    s->cl = 0;
    for (i=0;i<h;i++)
        HUlib_initTextLine(&s->l[i],
                           x, y - i*(SHORT(font[0]->height)+1),
                           font, startchar);

}

void HUlib_addLineToSText(hu_stext_t* s)
{

    int i;

    // add a clear line
    if (++s->cl == s->h)
        s->cl = 0;
    HUlib_clearTextLine(&s->l[s->cl]);

    // everything needs updating
    for (i=0 ; i<s->h ; i++)
        s->l[i].needsupdate = 4;

}

void
HUlib_addMessageToSText
( hu_stext_t*   s,
  char*         prefix,
  char*         msg )
{
    HUlib_addLineToSText(s);
    if (prefix)
        while (*prefix)
            HUlib_addCharToTextLine(&s->l[s->cl], *(prefix++));

    while (*msg)
        HUlib_addCharToTextLine(&s->l[s->cl], *(msg++));
}

void HUlib_drawSText(hu_stext_t* s)
{
    int i, idx;
    hu_textline_t *l;

    if (!*s->on)
        return; // if not on, don't draw

    // draw everything
    for (i=0 ; i<s->h ; i++)
    {
        idx = s->cl - i;
        if (idx < 0)
            idx += s->h; // handle queue of lines
        
        l = &s->l[idx];

        // need a decision made here on whether to skip the draw
        HUlib_drawTextLine(l, false); // no cursor, please
    }

}

void HUlib_eraseSText(hu_stext_t* s)
{

    int i;

    for (i=0 ; i<s->h ; i++)
    {
        if (s->laston && !*s->on)
            s->l[i].needsupdate = 4;
        HUlib_eraseTextLine(&s->l[i]);
    }
    s->laston = *s->on;

}

void
HUlib_initIText
( hu_itext_t*   it,
  int           x,
  int           y,
  patch_t**     font,
  int           startchar,
  boolean*      on )
{
    it->lm = 0; // default left margin is start of text
    it->on = on;
    it->laston = true;
    HUlib_initTextLine(&it->l, x, y, font, startchar);
}


// The following deletion routines adhere to the left margin restriction
void HUlib_delCharFromIText(hu_itext_t* it)
{
    if (it->l.len != it->lm)
        HUlib_delCharFromTextLine(&it->l);
}

void HUlib_eraseLineFromIText(hu_itext_t* it)
{
    while (it->lm != it->l.len)
        HUlib_delCharFromTextLine(&it->l);
}

// Resets left margin as well
void HUlib_resetIText(hu_itext_t* it)
{
    it->lm = 0;
    HUlib_clearTextLine(&it->l);
}

void
HUlib_addPrefixToIText
( hu_itext_t*   it,
  char*         str )
{
    while (*str)
        HUlib_addCharToTextLine(&it->l, *(str++));
    it->lm = it->l.len;
}

// wrapper function for handling general keyed input.
// returns true if it ate the key
boolean
HUlib_keyInIText
( hu_itext_t*   it,
  unsigned char ch )
{

    if (ch >= ' ' && ch <= '_') 
        HUlib_addCharToTextLine(&it->l, (char) ch);
    else 
        if (ch == KEY_BACKSPACE) 
            HUlib_delCharFromIText(it);
        else 
            if (ch != KEY_ENTER) 
                return false; // did not eat key

    return true; // ate the key

}

void HUlib_drawIText(hu_itext_t* it)
{

    hu_textline_t *l = &it->l;

    if (!*it->on)
        return;
    HUlib_drawTextLine(l, true); // draw the line w/ cursor

}

void HUlib_eraseIText(hu_itext_t* it)
{
    if (it->laston && !*it->on)
        it->l.needsupdate = 4;
    HUlib_eraseTextLine(&it->l);
    it->laston = *it->on;
}

