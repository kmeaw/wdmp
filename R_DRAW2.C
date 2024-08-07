// Emacs style mode select   -*- C++ -*-
//-----------------------------------------------------------------------------
//
// $Id: r_draw2.c,v 1.2 1998/01/05 13:41:07 pekangas Exp $
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
// $Log: r_draw2.c,v $
// Revision 1.2  1998/01/05 13:41:07  pekangas
// No more duplicate symbols
//
// Revision 1.1  1998/01/04 19:28:26  pekangas
// Initial revision
//
//
// DESCRIPTION:
//	The actual span/column drawing functions.
//	Here find the main potential for optimization,
//	 e.g. inline assembly, different algorithms.
//
//-----------------------------------------------------------------------------


const char
r_draw2_rcsid[] = "$Id: r_draw2.c,v 1.2 1998/01/05 13:41:07 pekangas Exp $";

#include <stdio.h>

#include "doomdef.h"

#include "i_system.h"
#include "z_zone.h"
#include "w_wad.h"

#include "r_local.h"

// Needs access to LFB (guess what).
#include "multires.h"

// State.
#include "doomstat.h"

/* [Petteri] no-allegro-hack: */
#ifndef palette_color
extern int palette_color[256];
#endif

// ?
#define MAXWIDTH			1120
#define MAXHEIGHT			832

// status bar height at bottom of screen
#define SBARHEIGHT		32

//
// All drawing to the view buffer is accomplished in this file.
// The other refresh files only know about ccordinates,
//  not the architecture of the frame buffer.
// Conveniently, the frame buffer is a linear one,
//  and we need only the base address,
//  and the total size == width*height*depth/8.,
//


/* [Petteri] These come from r_draw1.c: */
extern byte*		viewimage; 
extern int		viewwidth;
extern int		scaledviewwidth;
extern int		viewheight;
extern int		viewwindowx;
extern int		viewwindowy; 
// MRMP
extern byte*		ylookupMP[MAXPLAYERS][MAXHEIGHT]; 
extern byte*		*ylookup; 
//extern byte*		ylookup[MAXHEIGHT]; 
extern int		columnofs[MAXWIDTH]; 

 
// just for profiling
extern int			dccount;

//
// Spectre/Invisibility.
//
#define FUZZTABLE		50 
#define FUZZOFF	1
extern int fuzzoffset[FUZZTABLE];
extern int	fuzzpos;

void resinit_r_draw_c16(void)
  {
  int i;

  for (i=0;i<FUZZTABLE;i++)
    fuzzoffset[i]*=SCREENWIDTH;
  fuzzpos=0;
  }

//
// A column is a vertical slice/span from a wall texture that,
//  given the DOOM style restrictions on the view orientation,
//  will always have constant z depth.
// Thus a special case loop for very fast rendering can
//  be used. It has also been used with Wolfenstein 3D.
// 
void R_DrawColumn16 (void)
{ 
    int			count; 
    short*		dest;
    fixed_t		frac;
    fixed_t		fracstep;
    short*     tempcolormap;
 
    count = dc_yh - dc_yl; 

    // Zero length, column does not exceed a pixel.
    if (count < 0) 
	return; 
				 
#ifdef RANGECHECK 
    if ((unsigned)dc_x >= SCREENWIDTH
	|| dc_yl < 0
	|| dc_yh >= SCREENHEIGHT) 
	I_Error ("R_DrawColumn: %i to %i at %i", dc_yl, dc_yh, dc_x); 
#endif 

    // Framebuffer destination address.
    // Use ylookup LUT to avoid multiply with ScreenWidth.
    // Use columnofs LUT for subwindows? 
    dest = (short *)(ylookup[dc_yl] + columnofs[dc_x]);

    // Determine scaling,
    //  which is the only mapping to be done.
    fracstep = dc_iscale; 
    frac = dc_texturemid + (dc_yl-centery)*fracstep; 

    // Inner loop that does the actual texture mapping,
    //  e.g. a DDA-lile scaling.
    // This is as fast as it gets.

    tempcolormap=(short *)(dc_colormap);
    do 
    {
	// Re-map color indices from wall texture column
	//  using a lighting/special effects LUT.
	*dest = tempcolormap[dc_source[(frac>>FRACBITS)&127]];
	
	dest += SCREENWIDTH;
	frac += fracstep;
	
    } while (count--); 
} 

void R_DrawColumnLow16 (void)
{ 
    int			count; 
    short*		dest;
    short*		dest2;
    fixed_t		frac;
    fixed_t		fracstep;
    short*     tempcolormap;
 
    count = dc_yh - dc_yl; 

    // Zero length.
    if (count < 0) 
	return; 
				 
#ifdef RANGECHECK 
    if ((unsigned)dc_x >= SCREENWIDTH
	|| dc_yl < 0
	|| dc_yh >= SCREENHEIGHT)
    {
	
	I_Error ("R_DrawColumn: %i to %i at %i", dc_yl, dc_yh, dc_x);
    }
    //	dccount++; 
#endif 
    // Blocky mode, need to multiply by 2.
    dc_x <<= 1;
    
    dest = (short *)(ylookup[dc_yl] + columnofs[dc_x]);
    dest2 = (short *)(ylookup[dc_yl] + columnofs[dc_x+1]);
    
    fracstep = dc_iscale; 
    frac = dc_texturemid + (dc_yl-centery)*fracstep;

    tempcolormap=(short *)dc_colormap;
    do 
    {
	// Hack. Does not work corretly.
	*dest2 = *dest = tempcolormap[dc_source[(frac>>FRACBITS)&127]];
	dest += SCREENWIDTH;
	dest2 += SCREENWIDTH;
	frac += fracstep; 

    } while (count--);
}


//
// Spectre/Invisibility.
//



//
// Framebuffer postprocessing.
// Creates a fuzzy image by copying pixels
//  from adjacent ones to left and right.
// Used with an all black colormap, this
//  could create the SHADOW effect,
//  i.e. spectres and invisible players.
//
void R_DrawFuzzColumn16 (void)
{ 
    int			count; 
    short*		dest;
    fixed_t		frac;
    fixed_t		fracstep;
    unsigned short temppixel;

    // Adjust borders. Low... 
    if (!dc_yl) 
	dc_yl = 1;

    // .. and high.
    if (dc_yh == viewheight-1) 
	dc_yh = viewheight - 2; 
		 
    count = dc_yh - dc_yl; 

    // Zero length.
    if (count < 0) 
	return; 

    
#ifdef RANGECHECK 
    if ((unsigned)dc_x >= SCREENWIDTH
	|| dc_yl < 0 || dc_yh >= SCREENHEIGHT)
    {
	I_Error ("R_DrawFuzzColumn: %i to %i at %i",
		 dc_yl, dc_yh, dc_x);
    }
#endif

    // Does not work with blocky mode.
    dest = (short *)(ylookup[dc_yl] + columnofs[dc_x]);

    // Looks familiar.
    fracstep = dc_iscale; 
    frac = dc_texturemid + (dc_yl-centery)*fracstep; 

    // Looks like an attempt at dithering,
    //  using the colormap #6 (of 0-31, a bit
    //  brighter than average).
    do 
    {
	// Lookup framebuffer, and retrieve
	//  a pixel that is either one column
	//  left or right of the current one.
	// Add index from colormap to index.
   temppixel=dest[fuzzoffset[fuzzpos]];
	*dest = ((temppixel>>1)&hicolortransmask1)+((temppixel>>2)&hicolortransmask2);

	// Clamp table lookup index.
	if (++fuzzpos == FUZZTABLE) 
	    fuzzpos = 0;
	
	dest += SCREENWIDTH;

	frac += fracstep; 
    } while (count--); 
} 
 
  
 

//
// R_DrawTranslatedColumn
// Used to draw player sprites
//  with the green colorramp mapped to others.
// Could be used with different translation
//  tables, e.g. the lighter colored version
//  of the BaronOfHell, the HellKnight, uses
//  identical sprites, kinda brightened up.
//

void R_DrawTranslatedColumn16 (void)
{ 
    int			count; 
    short*		dest;
    fixed_t		frac;
    fixed_t		fracstep;	 
    short*     tempcolormap;

    count = dc_yh - dc_yl; 
    if (count < 0) 
	return; 
				 
#ifdef RANGECHECK 
    if ((unsigned)dc_x >= SCREENWIDTH
	|| dc_yl < 0
	|| dc_yh >= SCREENHEIGHT)
    {
	I_Error ( "R_DrawColumn: %i to %i at %i",
		  dc_yl, dc_yh, dc_x);
    }
    
#endif 


    // FIXME. As above.
    dest = (short *)(ylookup[dc_yl] + columnofs[dc_x]);

    // Looks familiar.
    fracstep = dc_iscale; 
    frac = dc_texturemid + (dc_yl-centery)*fracstep; 

    // Here we do an additional index re-mapping.
    tempcolormap=(short *)dc_colormap;
    do 
    {
	// Translation tables are used
	//  to map certain colorramps to other ones,
	//  used with PLAY sprites.
	// Thus the "green" ramp of the player 0 sprite
	//  is mapped to gray, red, black/indigo. 
	*dest = tempcolormap[dc_translation[dc_source[frac>>FRACBITS]]];
	dest += SCREENWIDTH;
	
	frac += fracstep; 
    } while (count--); 
} 




//
// R_InitTranslationTables
// Creates the translation tables to map
//  the green color ramp to gray, brown, red.
// Assumes a given structure of the PLAYPAL.
// Could be read from a lump instead.
//
void R_InitTranslationTables16 (void)
{
    int		i;
	
    translationtables = Z_Malloc (256*3*2+255, PU_STATIC, 0);
    translationtables = (byte *)(( (int)translationtables + 255 )& ~255);
    
    // translate just the 16 green colors
    for (i=0 ; i<256 ; i++)
    {
	if (i >= 0x70 && i<= 0x7f)
	{
	    // map green ramp to gray, brown, red
	    translationtables[i] = 0x60 + (i&0xf);
	    translationtables [i+256] = 0x40 + (i&0xf);
	    translationtables [i+512] = 0x20 + (i&0xf);
	}
	else
	{
	    // Keep all other colors as is.
	    translationtables[i] = translationtables[i+256] 
		= translationtables[i+512] = i;
	}
    }
}


//
// R_DrawSpan 
// With DOOM style restrictions on view orientation,
//  the floors and ceilings consist of horizontal slices
//  or spans with constant z depth.
// However, rotation around the world z axis is possible,
//  thus this mapping, while simpler and faster than
//  perspective correct texture mapping, has to traverse
//  the texture at an angle in all but a few cases.
// In consequence, flats are not stored by column (like walls),
//  and the inner loop has to step in texture space u and v.
//


//
// Draws the actual span.
void R_DrawSpan16 (void)
{ 
    fixed_t		xfrac;
    fixed_t		yfrac; 
    short*		dest;
    int			count;
    int			spot;
    short*     tempcolormap;
	 
#ifdef RANGECHECK 
    if (ds_x2 < ds_x1
	|| ds_x1<0
	|| ds_x2>=SCREENWIDTH  
	|| (unsigned)ds_y>SCREENHEIGHT)
    {
	I_Error( "R_DrawSpan: %i to %i at %i",
		 ds_x1,ds_x2,ds_y);
    }
//	dscount++; 
#endif 

    
    xfrac = ds_xfrac; 
    yfrac = ds_yfrac; 
	 
    dest = (short *)(ylookup[ds_y] + columnofs[ds_x1]);

    // We do not check for zero spans here?
    count = ds_x2 - ds_x1; 

    tempcolormap=(short *)ds_colormap;
    do 
    {
	// Current texture index in u,v.
	spot = ((yfrac>>(16-6))&(63*64)) + ((xfrac>>16)&63);

	// Lookup pixel from flat texture tile,
	//  re-index using light/colormap.
	*dest++ = tempcolormap[ds_source[spot]];

	// Next step in u,v.
	xfrac += ds_xstep; 
	yfrac += ds_ystep;
	
    } while (count--); 
} 


//
// Again..
//
void R_DrawSpanLow16 (void)
{ 
    fixed_t		xfrac;
    fixed_t		yfrac; 
    short*		dest;
    int			count;
    int			spot;
    short*     tempcolormap;
	 
#ifdef RANGECHECK 
    if (ds_x2 < ds_x1
	|| ds_x1<0
	|| ds_x2>=SCREENWIDTH  
	|| (unsigned)ds_y>SCREENHEIGHT)
    {
	I_Error( "R_DrawSpan: %i to %i at %i",
		 ds_x1,ds_x2,ds_y);
    }
//	dscount++; 
#endif 
	 
    xfrac = ds_xfrac;
    yfrac = ds_yfrac; 

    // Blocky mode, need to multiply by 2.
    ds_x1 <<= 1;
    ds_x2 <<= 1;
    
    dest = (short *)(ylookup[ds_y] + columnofs[ds_x1]);
  
    
    count = ds_x2 - ds_x1; 
    tempcolormap=(short *)(ds_colormap);
    do 
    { 
	spot = ((yfrac>>(16-6))&(63*64)) + ((xfrac>>16)&63);
	// Lowres/blocky mode does it twice,
	//  while scale is adjusted appropriately.
	*dest++ = tempcolormap[ds_source[spot]];
	*dest++ = tempcolormap[ds_source[spot]];
	
	xfrac += ds_xstep; 
	yfrac += ds_ystep; 

    } while (count--); 
}

//
// R_InitBuffer 
// Creats lookup tables that avoid
//  multiplies and other hazzles
//  for getting the framebuffer address
//  of a pixel to draw.
//
void
R_InitBuffer16
( int		width,
  int		height ) 
{ 
    int		i; 

    // Handle resize,
    //  e.g. smaller view windows
    //  with border and/or status bar.
    viewwindowx = (SCREENWIDTH-width) >> 1; 

    // Column offset. For windows.
    for (i=0 ; i<width ; i++) 
	columnofs[i] = (viewwindowx*2) + i*2;

    // Samw with base row offset.
    if (width == SCREENWIDTH) 
	viewwindowy = 0; 
    else 
	viewwindowy = (SCREENHEIGHT-SBARHEIGHT-height) >> 1; 

    // Preclaculate all row offsets.
    for (i=0 ; i<height ; i++) 
	ylookup[i] = screens[0] + (i+viewwindowy)*SCREENWIDTH*2;
} 
 
 


//
// R_FillBackScreen
// Fills the back screen with a pattern
//  for variable screen sizes
// Also draws a beveled edge.
//
void R_FillBackScreen16 (void)
{ 
    byte*	src;
    byte*   tempsrc;
    short*	dest;
    int		x;
    int		y; 
    patch_t*	patch;

    // DOOM border patch.
    char	name1[] = "FLOOR7_2";

    // DOOM II border patch.
    char	name2[] = "GRNROCK";	

    char*	name;

    if ((scaledviewwidth == SCREENWIDTH)&&(viewheight==SCREENHEIGHT))
	return;
	
    if ( gamemode == commercial)
	name = name2;
    else
	name = name1;
    
    src = W_CacheLumpName (name, PU_CACHE); 
    dest = (short *)(screens[1]);
	 
    for (y=0 ; y<SCREENHEIGHT/*-SBARHEIGHT*/ ; y++)
    { 
    tempsrc=src+((y&63)<<6);
    for (x=0;x<SCREENWIDTH;x++)
      {
      *dest=palette_color[tempsrc[x&63]];
      dest++;
      }
    }
	if (SCREENWIDTH==scaledviewwidth)
     return;

   if ((viewwindowy-8)>=0)
     {
     patch = W_CacheLumpName ("brdr_t",PU_CACHE);
     for (x=0 ; x<scaledviewwidth ; x+=8)
       V_DrawPatch (viewwindowx+x,viewwindowy-8,1,patch);
     }
   if ((viewwindowy+viewheight+8)<(SCREENHEIGHT-SBARHEIGHT))
     {
     patch = W_CacheLumpName ("brdr_b",PU_CACHE);
     for (x=0 ; x<scaledviewwidth ; x+=8)
       V_DrawPatch (viewwindowx+x,viewwindowy+viewheight,1,patch);
     }
   if ((viewwindowx-8)>=0)
     {
     patch = W_CacheLumpName ("brdr_l",PU_CACHE);
     for (y=0 ; y<viewheight ; y+=8)
       V_DrawPatch (viewwindowx-8,viewwindowy+y,1,patch);
     }
   if ((viewwindowx+scaledviewwidth+8)<SCREENWIDTH)
     {
     patch = W_CacheLumpName ("brdr_r",PU_CACHE);
     for (y=0 ; y<viewheight ; y+=8)
       V_DrawPatch (viewwindowx+scaledviewwidth,viewwindowy+y,1,patch);
     }

    // Draw beveled edge. 
    if (((viewwindowx-8)>=0)&&((viewwindowy-8)>=0))
      V_DrawPatch (viewwindowx-8,
		 viewwindowy-8,
		 1,
		 W_CacheLumpName ("brdr_tl",PU_CACHE));
    
    if (((viewwindowx+scaledviewwidth+8)<SCREENWIDTH)&&((viewwindowy-8)>=0))
      V_DrawPatch (viewwindowx+scaledviewwidth,
		 viewwindowy-8,
		 1,
		 W_CacheLumpName ("brdr_tr",PU_CACHE));
    
    if (((viewwindowx-8)>=0)&&((viewwindowy+viewheight+8)<(SCREENHEIGHT-SBARHEIGHT)))
      V_DrawPatch (viewwindowx-8,
		 viewwindowy+viewheight,
		 1,
		 W_CacheLumpName ("brdr_bl",PU_CACHE));
    
    if (((viewwindowx+scaledviewwidth+8)<SCREENWIDTH)&&((viewwindowy+viewheight+8)<(SCREENHEIGHT-SBARHEIGHT)))
      V_DrawPatch (viewwindowx+scaledviewwidth,
		 viewwindowy+viewheight,
		 1,
		 W_CacheLumpName ("brdr_br",PU_CACHE));
} 
 

//
// Copy a screen buffer.
//
void
R_VideoErase16
( unsigned	ofs,
  int		count ) 
{ 
  // LFB copy.
  // This might not be a good idea if memcpy
  //  is not optiomal, e.g. byte by byte on
  //  a 32bit CPU, as GNU GCC/Linux libc did
  //  at one point.
    memcpy (screens[0]+ofs*2, screens[1]+ofs*2, count*2);
} 


//
// R_DrawViewBorder
// Draws the border around the view
//  for different size windows?
//
 
void R_DrawViewBorder16 (void)
{ 
    int		top;
    int		side,side2;
    int		ofs;
    int		i; 

    //if screenwidth>320, draw stuff around status bar, even if scaledviewwidth==SCREENWIDTH
    if ((SCREENWIDTH>320)&&(SCREENHEIGHT!=viewheight))
      {
      ofs=(SCREENHEIGHT-SBARHEIGHT)*SCREENWIDTH;
      side=(SCREENWIDTH-320)/2; side2=side*2;
      R_VideoErase16(ofs,side);

      ofs+=(SCREENWIDTH-side);
      for (i=1;i<SBARHEIGHT;i++)
        {
        R_VideoErase16(ofs,side2);
        ofs+=SCREENWIDTH;
        }
      R_VideoErase16(ofs,side);
      }

    if (scaledviewwidth == SCREENWIDTH) 
	return; 
  
    top = ((SCREENHEIGHT-SBARHEIGHT)-viewheight)/2; 
    side = (SCREENWIDTH-scaledviewwidth)/2; 
 
    // copy top and one line of left side 
    R_VideoErase16 (0, top*SCREENWIDTH+side);
 
    // copy one line of right side and bottom 
    ofs = (viewheight+top)*SCREENWIDTH-side; 
    R_VideoErase16 (ofs, top*SCREENWIDTH+side);
 
    // copy sides using wraparound 
    ofs = top*SCREENWIDTH + SCREENWIDTH-side; 
    side <<= 1;
    
    for (i=1 ; i<viewheight ; i++) 
    { 
	R_VideoErase16 (ofs, side);
	ofs += SCREENWIDTH; 
    }

    // ? 
    V_MarkRect (0,0,SCREENWIDTH, SCREENHEIGHT-SBARHEIGHT); 
} 
 
 
