WDMP V0.9 (Windows Doom Multi-Player) [30/07/98]
-------------------------------------

My goal was to be able to play Doom on a single PC.
WDMP is based on the NT-Doom sources by Petteri Kangaslampi.
WDMP compiles with Watcom V11.0, Microsoft Visual C V4.0 & V5.0 compilers. (It compiles
also with Borland C 3.1, but the exe doesn't work).

The minimal requirements for WDMP are a 486DX2/66 with 8Mb of RAM with Win3.1/Win32s.
A Pentium with 16Mb of RAM & Win95/NT is recommended.

WDMP32s.EXE is for Win32s.
WDMP.EXE is for WinNT/95.

See NTREAD.TXT file for original NT-DOOM options.

What's new in V0.9:
-------------------
- 3 and 4 players support
- Autosizing of the windows: command line -autosize
- To choose the IWAD directory: command line: -iwad <WadDirName>
- Bug fixed in text messages

Features:
---------
- From 2 to 4 players can play on a single PC.
	Comand line: -players <NumberOfPlayers>

- Joystick support
	New command line option: - joysty <sensitivity%> where sensitivity is a number 
	between 1 & 100.

- GrabMouse can activate/deactivate by the '²' key (the key below Esc). Useful when you
  want to move one window.

- Sounds:
	You can hear sound from only one player. To cycle between the players press 
	the 'F5' key. (low details not available anymore).
	The sounds work only under WinNT/95. Win32s crashes when using the MIDAS library.	

- New command line option: -1pal
	Use it to deactivate the palettes changes (when you pick up things, etc.), if you
	experience some slackening in 8 bits display.

- New cheats:
	-allweapons <player> command line option: <player> is a number between 0 & 3. He
	will have all the weapons... (useful if you play against someone who never 
	deathmatch before ;-)
	- Press the 'Small Enter' key to go to the next level.

- Each player has a doomrc?.cfg for his keys configuration. (? is a number between 1-4).
	To configure these keys, a little SETUP program is included. Just press the key and read
	the value (it's not very user friendly, but it was very simple and fast to write it).
	See the KEYS.TXT files to see the defaults keys.

Some recomandations to play on a low end machine:
-------------------------------------------------
- If you play under Win32s:
	In the "386 enhanced" panel, check "Exclusive foreground task" & 32 bits Disk Access.
- Use a 640x480x256c desktop & use the -1pal option.
- Use the -nomusic option.

Sources considerations:
-----------------------

- Under Win32s you should use Watcom V11.0 to compile. You should also define WATWIN31 in platform.h
  (as a dib's origin is the lower-left corner and not the upper-left corner, some changes
   have been made in the rendering process to accelerate the display on low end machines).
- If you want to deactivate the -allweapons option just comment the CHEATERMP define in platform.h.
- In r_draw1.c define X86_ASM to enable some assembler optimizations.

Any comments, bug reports, etc. are welcome.

E-mail address: kokak@free.fr
Doom Page: http://www.doomworld.com/doomgl
Personal homepage: http://kokak.free.fr

	Michaël Ryssen.