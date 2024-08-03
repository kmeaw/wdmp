# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

!IF "$(CFG)" == ""
CFG=NtDoom - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to NtDoom - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "NtDoom - Win32 Release" && "$(CFG)" != "NtDoom - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "wdmp.mak" CFG="NtDoom - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NtDoom - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "NtDoom - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "NtDoom - Win32 Debug"
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NtDoom - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\wdmp.exe"

CLEAN : 
	-@erase ".\Release\wdmp.exe"
	-@erase ".\Release\G_game.obj"
	-@erase ".\Release\W32NetEm.obj"
	-@erase ".\Release\R_draw2.obj"
	-@erase ".\Release\St_stuff.obj"
	-@erase ".\Release\M_argv.obj"
	-@erase ".\Release\P_maputl.obj"
	-@erase ".\Release\P_tick.obj"
	-@erase ".\Release\Doomdef.obj"
	-@erase ".\Release\Info.obj"
	-@erase ".\Release\P_mobj.obj"
	-@erase ".\Release\M_cheat.obj"
	-@erase ".\Release\Hu_lib.obj"
	-@erase ".\Release\F_wipe.obj"
	-@erase ".\Release\R_draw1.obj"
	-@erase ".\Release\P_doors.obj"
	-@erase ".\Release\P_saveg.obj"
	-@erase ".\Release\P_telept.obj"
	-@erase ".\Release\D_main.obj"
	-@erase ".\Release\P_switch.obj"
	-@erase ".\Release\Bench.obj"
	-@erase ".\Release\P_sight.obj"
	-@erase ".\Release\P_inter.obj"
	-@erase ".\Release\Am_map.obj"
	-@erase ".\Release\Win32vid.obj"
	-@erase ".\Release\D_items.obj"
	-@erase ".\Release\Qmus2mid.obj"
	-@erase ".\Release\I_system.obj"
	-@erase ".\Release\Z_zone.obj"
	-@erase ".\Release\D_net.obj"
	-@erase ".\Release\M_misc.obj"
	-@erase ".\Release\R_sky.obj"
	-@erase ".\Release\R_main.obj"
	-@erase ".\Release\I_main.obj"
	-@erase ".\Release\W_wad.obj"
	-@erase ".\Release\P_lights.obj"
	-@erase ".\Release\P_ceilng.obj"
	-@erase ".\Release\Sounds.obj"
	-@erase ".\Release\P_user.obj"
	-@erase ".\Release\I_net.obj"
	-@erase ".\Release\P_enemy.obj"
	-@erase ".\Release\M_bbox.obj"
	-@erase ".\Release\P_setup.obj"
	-@erase ".\Release\Doomstat.obj"
	-@erase ".\Release\P_floor.obj"
	-@erase ".\Release\Wi_stuff.obj"
	-@erase ".\Release\Funcpntr.obj"
	-@erase ".\Release\P_pspr.obj"
	-@erase ".\Release\R_things.obj"
	-@erase ".\Release\R_segs.obj"
	-@erase ".\Release\Midassou.obj"
	-@erase ".\Release\R_plane.obj"
	-@erase ".\Release\Dstrings.obj"
	-@erase ".\Release\R_data.obj"
	-@erase ".\Release\P_plats.obj"
	-@erase ".\Release\V_video2.obj"
	-@erase ".\Release\Multires.obj"
	-@erase ".\Release\M_random.obj"
	-@erase ".\Release\M_swap.obj"
	-@erase ".\Release\P_map.obj"
	-@erase ".\Release\M_menu.obj"
	-@erase ".\Release\Hu_stuff.obj"
	-@erase ".\Release\Tables.obj"
	-@erase ".\Release\V_video1.obj"
	-@erase ".\Release\P_spec.obj"
	-@erase ".\Release\S_sound.obj"
	-@erase ".\Release\M_fixed.obj"
	-@erase ".\Release\F_finale.obj"
	-@erase ".\Release\St_lib.obj"
	-@erase ".\Release\R_bsp.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I ".\midas" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I ".\midas" /D "WIN32" /D "NDEBUG" /D\
 "_CONSOLE" /Fp"$(INTDIR)/wdmp.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/wdmp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib wsock32.lib midas\midas.lib /nologo /subsystem:console /machine:I386 /nodefaultlib:"libc" /defaultlib:"libcmt"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib wsock32.lib\
 midas\midas.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)/wdmp.pdb" /machine:I386 /nodefaultlib:"libc"\
 /out:"$(OUTDIR)/wdmp.exe" /defaultlib:"libcmt" 
LINK32_OBJS= \
	"$(INTDIR)/G_game.obj" \
	"$(INTDIR)/W32NetEm.obj" \
	"$(INTDIR)/R_draw2.obj" \
	"$(INTDIR)/St_stuff.obj" \
	"$(INTDIR)/M_argv.obj" \
	"$(INTDIR)/P_maputl.obj" \
	"$(INTDIR)/P_tick.obj" \
	"$(INTDIR)/Doomdef.obj" \
	"$(INTDIR)/Info.obj" \
	"$(INTDIR)/P_mobj.obj" \
	"$(INTDIR)/M_cheat.obj" \
	"$(INTDIR)/Hu_lib.obj" \
	"$(INTDIR)/F_wipe.obj" \
	"$(INTDIR)/R_draw1.obj" \
	"$(INTDIR)/P_doors.obj" \
	"$(INTDIR)/P_saveg.obj" \
	"$(INTDIR)/P_telept.obj" \
	"$(INTDIR)/D_main.obj" \
	"$(INTDIR)/P_switch.obj" \
	"$(INTDIR)/Bench.obj" \
	"$(INTDIR)/P_sight.obj" \
	"$(INTDIR)/P_inter.obj" \
	"$(INTDIR)/Am_map.obj" \
	"$(INTDIR)/Win32vid.obj" \
	"$(INTDIR)/D_items.obj" \
	"$(INTDIR)/Qmus2mid.obj" \
	"$(INTDIR)/I_system.obj" \
	"$(INTDIR)/Z_zone.obj" \
	"$(INTDIR)/D_net.obj" \
	"$(INTDIR)/M_misc.obj" \
	"$(INTDIR)/R_sky.obj" \
	"$(INTDIR)/R_main.obj" \
	"$(INTDIR)/I_main.obj" \
	"$(INTDIR)/W_wad.obj" \
	"$(INTDIR)/P_lights.obj" \
	"$(INTDIR)/P_ceilng.obj" \
	"$(INTDIR)/Sounds.obj" \
	"$(INTDIR)/P_user.obj" \
	"$(INTDIR)/I_net.obj" \
	"$(INTDIR)/P_enemy.obj" \
	"$(INTDIR)/M_bbox.obj" \
	"$(INTDIR)/P_setup.obj" \
	"$(INTDIR)/Doomstat.obj" \
	"$(INTDIR)/P_floor.obj" \
	"$(INTDIR)/Wi_stuff.obj" \
	"$(INTDIR)/Funcpntr.obj" \
	"$(INTDIR)/P_pspr.obj" \
	"$(INTDIR)/R_things.obj" \
	"$(INTDIR)/R_segs.obj" \
	"$(INTDIR)/Midassou.obj" \
	"$(INTDIR)/R_plane.obj" \
	"$(INTDIR)/Dstrings.obj" \
	"$(INTDIR)/R_data.obj" \
	"$(INTDIR)/P_plats.obj" \
	"$(INTDIR)/V_video2.obj" \
	"$(INTDIR)/Multires.obj" \
	"$(INTDIR)/M_random.obj" \
	"$(INTDIR)/M_swap.obj" \
	"$(INTDIR)/P_map.obj" \
	"$(INTDIR)/M_menu.obj" \
	"$(INTDIR)/Hu_stuff.obj" \
	"$(INTDIR)/Tables.obj" \
	"$(INTDIR)/V_video1.obj" \
	"$(INTDIR)/P_spec.obj" \
	"$(INTDIR)/S_sound.obj" \
	"$(INTDIR)/M_fixed.obj" \
	"$(INTDIR)/F_finale.obj" \
	"$(INTDIR)/St_lib.obj" \
	"$(INTDIR)/R_bsp.obj"

"$(OUTDIR)\wdmp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "NtDoom__"
# PROP BASE Intermediate_Dir "NtDoom__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\wdmp.exe" "$(OUTDIR)\wdmp.bsc"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\wdmp.bsc"
	-@erase ".\Debug\Hu_stuff.sbr"
	-@erase ".\Debug\G_game.sbr"
	-@erase ".\Debug\Sounds.sbr"
	-@erase ".\Debug\Bench.sbr"
	-@erase ".\Debug\V_video1.sbr"
	-@erase ".\Debug\P_user.sbr"
	-@erase ".\Debug\M_bbox.sbr"
	-@erase ".\Debug\S_sound.sbr"
	-@erase ".\Debug\M_fixed.sbr"
	-@erase ".\Debug\W32NetEm.sbr"
	-@erase ".\Debug\D_net.sbr"
	-@erase ".\Debug\R_sky.sbr"
	-@erase ".\Debug\P_pspr.sbr"
	-@erase ".\Debug\W_wad.sbr"
	-@erase ".\Debug\St_stuff.sbr"
	-@erase ".\Debug\R_draw2.sbr"
	-@erase ".\Debug\R_segs.sbr"
	-@erase ".\Debug\P_maputl.sbr"
	-@erase ".\Debug\F_wipe.sbr"
	-@erase ".\Debug\R_data.sbr"
	-@erase ".\Debug\I_net.sbr"
	-@erase ".\Debug\Funcpntr.sbr"
	-@erase ".\Debug\M_swap.sbr"
	-@erase ".\Debug\Doomdef.sbr"
	-@erase ".\Debug\M_menu.sbr"
	-@erase ".\Debug\Dstrings.sbr"
	-@erase ".\Debug\P_telept.sbr"
	-@erase ".\Debug\Z_zone.sbr"
	-@erase ".\Debug\M_misc.sbr"
	-@erase ".\Debug\M_cheat.sbr"
	-@erase ".\Debug\P_switch.sbr"
	-@erase ".\Debug\R_draw1.sbr"
	-@erase ".\Debug\P_doors.sbr"
	-@erase ".\Debug\P_saveg.sbr"
	-@erase ".\Debug\Info.sbr"
	-@erase ".\Debug\Win32vid.sbr"
	-@erase ".\Debug\P_sight.sbr"
	-@erase ".\Debug\Qmus2mid.sbr"
	-@erase ".\Debug\I_system.sbr"
	-@erase ".\Debug\P_inter.sbr"
	-@erase ".\Debug\P_spec.sbr"
	-@erase ".\Debug\P_map.sbr"
	-@erase ".\Debug\St_lib.sbr"
	-@erase ".\Debug\P_lights.sbr"
	-@erase ".\Debug\D_items.sbr"
	-@erase ".\Debug\P_ceilng.sbr"
	-@erase ".\Debug\F_finale.sbr"
	-@erase ".\Debug\M_argv.sbr"
	-@erase ".\Debug\P_tick.sbr"
	-@erase ".\Debug\Doomstat.sbr"
	-@erase ".\Debug\P_enemy.sbr"
	-@erase ".\Debug\Wi_stuff.sbr"
	-@erase ".\Debug\P_setup.sbr"
	-@erase ".\Debug\R_bsp.sbr"
	-@erase ".\Debug\P_mobj.sbr"
	-@erase ".\Debug\R_things.sbr"
	-@erase ".\Debug\P_floor.sbr"
	-@erase ".\Debug\Midassou.sbr"
	-@erase ".\Debug\Hu_lib.sbr"
	-@erase ".\Debug\V_video2.sbr"
	-@erase ".\Debug\D_main.sbr"
	-@erase ".\Debug\Multires.sbr"
	-@erase ".\Debug\M_random.sbr"
	-@erase ".\Debug\R_plane.sbr"
	-@erase ".\Debug\P_plats.sbr"
	-@erase ".\Debug\Am_map.sbr"
	-@erase ".\Debug\Tables.sbr"
	-@erase ".\Debug\R_main.sbr"
	-@erase ".\Debug\I_main.sbr"
	-@erase ".\Debug\wdmp.exe"
	-@erase ".\Debug\P_mobj.obj"
	-@erase ".\Debug\R_things.obj"
	-@erase ".\Debug\P_floor.obj"
	-@erase ".\Debug\Midassou.obj"
	-@erase ".\Debug\Hu_lib.obj"
	-@erase ".\Debug\V_video2.obj"
	-@erase ".\Debug\D_main.obj"
	-@erase ".\Debug\Multires.obj"
	-@erase ".\Debug\M_random.obj"
	-@erase ".\Debug\R_plane.obj"
	-@erase ".\Debug\P_plats.obj"
	-@erase ".\Debug\Am_map.obj"
	-@erase ".\Debug\Tables.obj"
	-@erase ".\Debug\R_main.obj"
	-@erase ".\Debug\I_main.obj"
	-@erase ".\Debug\Hu_stuff.obj"
	-@erase ".\Debug\G_game.obj"
	-@erase ".\Debug\Sounds.obj"
	-@erase ".\Debug\Bench.obj"
	-@erase ".\Debug\V_video1.obj"
	-@erase ".\Debug\P_user.obj"
	-@erase ".\Debug\M_bbox.obj"
	-@erase ".\Debug\S_sound.obj"
	-@erase ".\Debug\M_fixed.obj"
	-@erase ".\Debug\W32NetEm.obj"
	-@erase ".\Debug\D_net.obj"
	-@erase ".\Debug\R_sky.obj"
	-@erase ".\Debug\P_pspr.obj"
	-@erase ".\Debug\W_wad.obj"
	-@erase ".\Debug\St_stuff.obj"
	-@erase ".\Debug\R_draw2.obj"
	-@erase ".\Debug\R_segs.obj"
	-@erase ".\Debug\P_maputl.obj"
	-@erase ".\Debug\F_wipe.obj"
	-@erase ".\Debug\R_data.obj"
	-@erase ".\Debug\I_net.obj"
	-@erase ".\Debug\Funcpntr.obj"
	-@erase ".\Debug\M_swap.obj"
	-@erase ".\Debug\Doomdef.obj"
	-@erase ".\Debug\M_menu.obj"
	-@erase ".\Debug\Dstrings.obj"
	-@erase ".\Debug\P_telept.obj"
	-@erase ".\Debug\Z_zone.obj"
	-@erase ".\Debug\M_misc.obj"
	-@erase ".\Debug\M_cheat.obj"
	-@erase ".\Debug\P_switch.obj"
	-@erase ".\Debug\R_draw1.obj"
	-@erase ".\Debug\P_doors.obj"
	-@erase ".\Debug\P_saveg.obj"
	-@erase ".\Debug\Info.obj"
	-@erase ".\Debug\Win32vid.obj"
	-@erase ".\Debug\P_sight.obj"
	-@erase ".\Debug\Qmus2mid.obj"
	-@erase ".\Debug\I_system.obj"
	-@erase ".\Debug\P_inter.obj"
	-@erase ".\Debug\P_spec.obj"
	-@erase ".\Debug\P_map.obj"
	-@erase ".\Debug\St_lib.obj"
	-@erase ".\Debug\P_lights.obj"
	-@erase ".\Debug\D_items.obj"
	-@erase ".\Debug\P_ceilng.obj"
	-@erase ".\Debug\F_finale.obj"
	-@erase ".\Debug\M_argv.obj"
	-@erase ".\Debug\P_tick.obj"
	-@erase ".\Debug\Doomstat.obj"
	-@erase ".\Debug\P_enemy.obj"
	-@erase ".\Debug\Wi_stuff.obj"
	-@erase ".\Debug\P_setup.obj"
	-@erase ".\Debug\R_bsp.obj"
	-@erase ".\Debug\wdmp.ilk"
	-@erase ".\Debug\wdmp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I ".\midas" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /FR /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I ".\midas" /D "WIN32" /D "_DEBUG"\
 /D "_CONSOLE" /FR"$(INTDIR)/" /Fp"$(INTDIR)/wdmp.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/wdmp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/Hu_stuff.sbr" \
	"$(INTDIR)/G_game.sbr" \
	"$(INTDIR)/Sounds.sbr" \
	"$(INTDIR)/Bench.sbr" \
	"$(INTDIR)/V_video1.sbr" \
	"$(INTDIR)/P_user.sbr" \
	"$(INTDIR)/M_bbox.sbr" \
	"$(INTDIR)/S_sound.sbr" \
	"$(INTDIR)/M_fixed.sbr" \
	"$(INTDIR)/W32NetEm.sbr" \
	"$(INTDIR)/D_net.sbr" \
	"$(INTDIR)/R_sky.sbr" \
	"$(INTDIR)/P_pspr.sbr" \
	"$(INTDIR)/W_wad.sbr" \
	"$(INTDIR)/St_stuff.sbr" \
	"$(INTDIR)/R_draw2.sbr" \
	"$(INTDIR)/R_segs.sbr" \
	"$(INTDIR)/P_maputl.sbr" \
	"$(INTDIR)/F_wipe.sbr" \
	"$(INTDIR)/R_data.sbr" \
	"$(INTDIR)/I_net.sbr" \
	"$(INTDIR)/Funcpntr.sbr" \
	"$(INTDIR)/M_swap.sbr" \
	"$(INTDIR)/Doomdef.sbr" \
	"$(INTDIR)/M_menu.sbr" \
	"$(INTDIR)/Dstrings.sbr" \
	"$(INTDIR)/P_telept.sbr" \
	"$(INTDIR)/Z_zone.sbr" \
	"$(INTDIR)/M_misc.sbr" \
	"$(INTDIR)/M_cheat.sbr" \
	"$(INTDIR)/P_switch.sbr" \
	"$(INTDIR)/R_draw1.sbr" \
	"$(INTDIR)/P_doors.sbr" \
	"$(INTDIR)/P_saveg.sbr" \
	"$(INTDIR)/Info.sbr" \
	"$(INTDIR)/Win32vid.sbr" \
	"$(INTDIR)/P_sight.sbr" \
	"$(INTDIR)/Qmus2mid.sbr" \
	"$(INTDIR)/I_system.sbr" \
	"$(INTDIR)/P_inter.sbr" \
	"$(INTDIR)/P_spec.sbr" \
	"$(INTDIR)/P_map.sbr" \
	"$(INTDIR)/St_lib.sbr" \
	"$(INTDIR)/P_lights.sbr" \
	"$(INTDIR)/D_items.sbr" \
	"$(INTDIR)/P_ceilng.sbr" \
	"$(INTDIR)/F_finale.sbr" \
	"$(INTDIR)/M_argv.sbr" \
	"$(INTDIR)/P_tick.sbr" \
	"$(INTDIR)/Doomstat.sbr" \
	"$(INTDIR)/P_enemy.sbr" \
	"$(INTDIR)/Wi_stuff.sbr" \
	"$(INTDIR)/P_setup.sbr" \
	"$(INTDIR)/R_bsp.sbr" \
	"$(INTDIR)/P_mobj.sbr" \
	"$(INTDIR)/R_things.sbr" \
	"$(INTDIR)/P_floor.sbr" \
	"$(INTDIR)/Midassou.sbr" \
	"$(INTDIR)/Hu_lib.sbr" \
	"$(INTDIR)/V_video2.sbr" \
	"$(INTDIR)/D_main.sbr" \
	"$(INTDIR)/Multires.sbr" \
	"$(INTDIR)/M_random.sbr" \
	"$(INTDIR)/R_plane.sbr" \
	"$(INTDIR)/P_plats.sbr" \
	"$(INTDIR)/Am_map.sbr" \
	"$(INTDIR)/Tables.sbr" \
	"$(INTDIR)/R_main.sbr" \
	"$(INTDIR)/I_main.sbr"

"$(OUTDIR)\wdmp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib wsock32.lib midas\midas.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libcd" /nodefaultlib:"libc" /defaultlib:libcmt
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib wsock32.lib\
 midas\midas.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)/wdmp.pdb" /debug /machine:I386 /nodefaultlib:"libcd"\
 /nodefaultlib:"libc" /out:"$(OUTDIR)/wdmp.exe" /defaultlib:libcmt 
LINK32_OBJS= \
	"$(INTDIR)/P_mobj.obj" \
	"$(INTDIR)/R_things.obj" \
	"$(INTDIR)/P_floor.obj" \
	"$(INTDIR)/Midassou.obj" \
	"$(INTDIR)/Hu_lib.obj" \
	"$(INTDIR)/V_video2.obj" \
	"$(INTDIR)/D_main.obj" \
	"$(INTDIR)/Multires.obj" \
	"$(INTDIR)/M_random.obj" \
	"$(INTDIR)/R_plane.obj" \
	"$(INTDIR)/P_plats.obj" \
	"$(INTDIR)/Am_map.obj" \
	"$(INTDIR)/Tables.obj" \
	"$(INTDIR)/R_main.obj" \
	"$(INTDIR)/I_main.obj" \
	"$(INTDIR)/Hu_stuff.obj" \
	"$(INTDIR)/G_game.obj" \
	"$(INTDIR)/Sounds.obj" \
	"$(INTDIR)/Bench.obj" \
	"$(INTDIR)/V_video1.obj" \
	"$(INTDIR)/P_user.obj" \
	"$(INTDIR)/M_bbox.obj" \
	"$(INTDIR)/S_sound.obj" \
	"$(INTDIR)/M_fixed.obj" \
	"$(INTDIR)/W32NetEm.obj" \
	"$(INTDIR)/D_net.obj" \
	"$(INTDIR)/R_sky.obj" \
	"$(INTDIR)/P_pspr.obj" \
	"$(INTDIR)/W_wad.obj" \
	"$(INTDIR)/St_stuff.obj" \
	"$(INTDIR)/R_draw2.obj" \
	"$(INTDIR)/R_segs.obj" \
	"$(INTDIR)/P_maputl.obj" \
	"$(INTDIR)/F_wipe.obj" \
	"$(INTDIR)/R_data.obj" \
	"$(INTDIR)/I_net.obj" \
	"$(INTDIR)/Funcpntr.obj" \
	"$(INTDIR)/M_swap.obj" \
	"$(INTDIR)/Doomdef.obj" \
	"$(INTDIR)/M_menu.obj" \
	"$(INTDIR)/Dstrings.obj" \
	"$(INTDIR)/P_telept.obj" \
	"$(INTDIR)/Z_zone.obj" \
	"$(INTDIR)/M_misc.obj" \
	"$(INTDIR)/M_cheat.obj" \
	"$(INTDIR)/P_switch.obj" \
	"$(INTDIR)/R_draw1.obj" \
	"$(INTDIR)/P_doors.obj" \
	"$(INTDIR)/P_saveg.obj" \
	"$(INTDIR)/Info.obj" \
	"$(INTDIR)/Win32vid.obj" \
	"$(INTDIR)/P_sight.obj" \
	"$(INTDIR)/Qmus2mid.obj" \
	"$(INTDIR)/I_system.obj" \
	"$(INTDIR)/P_inter.obj" \
	"$(INTDIR)/P_spec.obj" \
	"$(INTDIR)/P_map.obj" \
	"$(INTDIR)/St_lib.obj" \
	"$(INTDIR)/P_lights.obj" \
	"$(INTDIR)/D_items.obj" \
	"$(INTDIR)/P_ceilng.obj" \
	"$(INTDIR)/F_finale.obj" \
	"$(INTDIR)/M_argv.obj" \
	"$(INTDIR)/P_tick.obj" \
	"$(INTDIR)/Doomstat.obj" \
	"$(INTDIR)/P_enemy.obj" \
	"$(INTDIR)/Wi_stuff.obj" \
	"$(INTDIR)/P_setup.obj" \
	"$(INTDIR)/R_bsp.obj"

"$(OUTDIR)\wdmp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "NtDoom - Win32 Release"
# Name "NtDoom - Win32 Debug"

!IF  "$(CFG)" == "NtDoom - Win32 Release"

!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Am_map.c
DEP_CPP_AM_MA=\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\doomdef.h"\
	".\St_stuff.h"\
	".\P_local.h"\
	".\..\wdmp\w_wad.h"\
	".\M_cheat.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\r_state.h"\
	".\Dstrings.h"\
	".\Am_map.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_event.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	".\D_french.h"\
	".\D_englsh.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\Am_map.obj" : $(SOURCE) $(DEP_CPP_AM_MA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\Am_map.obj" : $(SOURCE) $(DEP_CPP_AM_MA) "$(INTDIR)"

"$(INTDIR)\Am_map.sbr" : $(SOURCE) $(DEP_CPP_AM_MA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D_items.c
DEP_CPP_D_ITE=\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\doomdef.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\D_items.obj" : $(SOURCE) $(DEP_CPP_D_ITE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\D_items.obj" : $(SOURCE) $(DEP_CPP_D_ITE) "$(INTDIR)"

"$(INTDIR)\D_items.sbr" : $(SOURCE) $(DEP_CPP_D_ITE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D_main.c
DEP_CPP_D_MAI=\
	".\..\wdmp\platform.h"\
	".\Unistd.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\doomstat.h"\
	".\Dstrings.h"\
	".\..\wdmp\sounds.h"\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\w_wad.h"\
	".\S_sound.h"\
	".\..\wdmp\multires.h"\
	".\F_finale.h"\
	".\F_wipe.h"\
	".\..\wdmp\m_argv.h"\
	".\..\wdmp\m_misc.h"\
	".\M_menu.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\i_sound.h"\
	".\..\wdmp\i_video.h"\
	".\G_game.h"\
	".\Hu_stuff.h"\
	".\Wi_stuff.h"\
	".\St_stuff.h"\
	".\Am_map.h"\
	".\P_setup.h"\
	".\R_local.h"\
	".\..\wdmp\d_main.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_think.h"\
	".\D_french.h"\
	".\D_englsh.h"\
	".\..\wdmp\r_data.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\d_event.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	
NODEP_CPP_D_MAI=\
	".\dir.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\D_main.obj" : $(SOURCE) $(DEP_CPP_D_MAI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\D_main.obj" : $(SOURCE) $(DEP_CPP_D_MAI) "$(INTDIR)"

"$(INTDIR)\D_main.sbr" : $(SOURCE) $(DEP_CPP_D_MAI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\D_net.c

!IF  "$(CFG)" == "NtDoom - Win32 Release"

DEP_CPP_D_NET=\
	".\M_menu.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\i_video.h"\
	".\I_net.h"\
	".\G_game.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\d_think.h"\
	
NODEP_CPP_D_NET=\
	".\fn_vSelectPlayer"\
	

"$(INTDIR)\D_net.obj" : $(SOURCE) $(DEP_CPP_D_NET) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"

DEP_CPP_D_NET=\
	".\M_menu.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\i_video.h"\
	".\I_net.h"\
	".\G_game.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\d_think.h"\
	

"$(INTDIR)\D_net.obj" : $(SOURCE) $(DEP_CPP_D_NET) "$(INTDIR)"

"$(INTDIR)\D_net.sbr" : $(SOURCE) $(DEP_CPP_D_NET) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Doomdef.c
DEP_CPP_DOOMD=\
	".\..\wdmp\doomdef.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\Doomdef.obj" : $(SOURCE) $(DEP_CPP_DOOMD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\Doomdef.obj" : $(SOURCE) $(DEP_CPP_DOOMD) "$(INTDIR)"

"$(INTDIR)\Doomdef.sbr" : $(SOURCE) $(DEP_CPP_DOOMD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Doomstat.c
DEP_CPP_DOOMS=\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\d_think.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\Doomstat.obj" : $(SOURCE) $(DEP_CPP_DOOMS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\Doomstat.obj" : $(SOURCE) $(DEP_CPP_DOOMS) "$(INTDIR)"

"$(INTDIR)\Doomstat.sbr" : $(SOURCE) $(DEP_CPP_DOOMS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dstrings.c
DEP_CPP_DSTRI=\
	".\Dstrings.h"\
	".\D_french.h"\
	".\D_englsh.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\Dstrings.obj" : $(SOURCE) $(DEP_CPP_DSTRI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\Dstrings.obj" : $(SOURCE) $(DEP_CPP_DSTRI) "$(INTDIR)"

"$(INTDIR)\Dstrings.sbr" : $(SOURCE) $(DEP_CPP_DSTRI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\F_finale.c
DEP_CPP_F_FIN=\
	".\..\wdmp\i_system.h"\
	".\M_swap.h"\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\w_wad.h"\
	".\S_sound.h"\
	".\Dstrings.h"\
	".\..\wdmp\sounds.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\r_state.h"\
	".\Hu_stuff.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\r_data.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\D_french.h"\
	".\D_englsh.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\F_finale.obj" : $(SOURCE) $(DEP_CPP_F_FIN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\F_finale.obj" : $(SOURCE) $(DEP_CPP_F_FIN) "$(INTDIR)"

"$(INTDIR)\F_finale.sbr" : $(SOURCE) $(DEP_CPP_F_FIN) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\F_wipe.c
DEP_CPP_F_WIP=\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\i_video.h"\
	".\..\wdmp\multires.h"\
	".\M_random.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\doomstat.h"\
	".\F_wipe.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\r_data.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\F_wipe.obj" : $(SOURCE) $(DEP_CPP_F_WIP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\F_wipe.obj" : $(SOURCE) $(DEP_CPP_F_WIP) "$(INTDIR)"

"$(INTDIR)\F_wipe.sbr" : $(SOURCE) $(DEP_CPP_F_WIP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Funcpntr.c
DEP_CPP_FUNCP=\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\r_data.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_ticcmd.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\Funcpntr.obj" : $(SOURCE) $(DEP_CPP_FUNCP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\Funcpntr.obj" : $(SOURCE) $(DEP_CPP_FUNCP) "$(INTDIR)"

"$(INTDIR)\Funcpntr.sbr" : $(SOURCE) $(DEP_CPP_FUNCP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\G_game.c
DEP_CPP_G_GAM=\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\z_zone.h"\
	".\F_finale.h"\
	".\..\wdmp\m_argv.h"\
	".\..\wdmp\m_misc.h"\
	".\M_menu.h"\
	".\M_random.h"\
	".\..\wdmp\i_system.h"\
	".\P_setup.h"\
	".\P_saveg.h"\
	".\P_tick.h"\
	".\..\wdmp\d_main.h"\
	".\Wi_stuff.h"\
	".\Hu_stuff.h"\
	".\St_stuff.h"\
	".\Am_map.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\w_wad.h"\
	".\P_local.h"\
	".\S_sound.h"\
	".\Dstrings.h"\
	".\..\wdmp\sounds.h"\
	".\..\wdmp\r_data.h"\
	".\R_sky.h"\
	".\G_game.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\d_event.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\D_french.h"\
	".\D_englsh.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\G_game.obj" : $(SOURCE) $(DEP_CPP_G_GAM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\G_game.obj" : $(SOURCE) $(DEP_CPP_G_GAM) "$(INTDIR)"

"$(INTDIR)\G_game.sbr" : $(SOURCE) $(DEP_CPP_G_GAM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Hu_lib.c
DEP_CPP_HU_LI=\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\multires.h"\
	".\M_swap.h"\
	".\Hu_lib.h"\
	".\R_local.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\r_data.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\Hu_lib.obj" : $(SOURCE) $(DEP_CPP_HU_LI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\Hu_lib.obj" : $(SOURCE) $(DEP_CPP_HU_LI) "$(INTDIR)"

"$(INTDIR)\Hu_lib.sbr" : $(SOURCE) $(DEP_CPP_HU_LI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Hu_stuff.c
DEP_CPP_HU_ST=\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\z_zone.h"\
	".\M_swap.h"\
	".\Hu_stuff.h"\
	".\Hu_lib.h"\
	".\..\wdmp\w_wad.h"\
	".\S_sound.h"\
	".\..\wdmp\doomstat.h"\
	".\Dstrings.h"\
	".\..\wdmp\sounds.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\D_french.h"\
	".\D_englsh.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\Hu_stuff.obj" : $(SOURCE) $(DEP_CPP_HU_ST) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\Hu_stuff.obj" : $(SOURCE) $(DEP_CPP_HU_ST) "$(INTDIR)"

"$(INTDIR)\Hu_stuff.sbr" : $(SOURCE) $(DEP_CPP_HU_ST) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\I_main.c
DEP_CPP_I_MAI=\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\m_argv.h"\
	".\..\wdmp\d_main.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\I_main.obj" : $(SOURCE) $(DEP_CPP_I_MAI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\I_main.obj" : $(SOURCE) $(DEP_CPP_I_MAI) "$(INTDIR)"

"$(INTDIR)\I_main.sbr" : $(SOURCE) $(DEP_CPP_I_MAI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\I_net.c
DEP_CPP_I_NET=\
	".\..\wdmp\platform.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\m_argv.h"\
	".\..\wdmp\doomstat.h"\
	".\I_net.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\win32.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\I_net.obj" : $(SOURCE) $(DEP_CPP_I_NET) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\I_net.obj" : $(SOURCE) $(DEP_CPP_I_NET) "$(INTDIR)"

"$(INTDIR)\I_net.sbr" : $(SOURCE) $(DEP_CPP_I_NET) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\I_system.c
DEP_CPP_I_SYS=\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\m_misc.h"\
	".\..\wdmp\i_video.h"\
	".\..\wdmp\i_sound.h"\
	".\..\wdmp\d_net.h"\
	".\G_game.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\sounds.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\d_event.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\I_system.obj" : $(SOURCE) $(DEP_CPP_I_SYS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\I_system.obj" : $(SOURCE) $(DEP_CPP_I_SYS) "$(INTDIR)"

"$(INTDIR)\I_system.sbr" : $(SOURCE) $(DEP_CPP_I_SYS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Info.c
DEP_CPP_INFO_=\
	".\..\wdmp\sounds.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\doomdef.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\Info.obj" : $(SOURCE) $(DEP_CPP_INFO_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\Info.obj" : $(SOURCE) $(DEP_CPP_INFO_) "$(INTDIR)"

"$(INTDIR)\Info.sbr" : $(SOURCE) $(DEP_CPP_INFO_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M_argv.c

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\M_argv.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\M_argv.obj" : $(SOURCE) "$(INTDIR)"

"$(INTDIR)\M_argv.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M_bbox.c
DEP_CPP_M_BBO=\
	".\m_bbox.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\m_fixed.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\M_bbox.obj" : $(SOURCE) $(DEP_CPP_M_BBO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\M_bbox.obj" : $(SOURCE) $(DEP_CPP_M_BBO) "$(INTDIR)"

"$(INTDIR)\M_bbox.sbr" : $(SOURCE) $(DEP_CPP_M_BBO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M_cheat.c
DEP_CPP_M_CHE=\
	".\M_cheat.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\M_cheat.obj" : $(SOURCE) $(DEP_CPP_M_CHE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\M_cheat.obj" : $(SOURCE) $(DEP_CPP_M_CHE) "$(INTDIR)"

"$(INTDIR)\M_cheat.sbr" : $(SOURCE) $(DEP_CPP_M_CHE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M_fixed.c
DEP_CPP_M_FIX=\
	".\..\wdmp\platform.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\M_fixed.obj" : $(SOURCE) $(DEP_CPP_M_FIX) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\M_fixed.obj" : $(SOURCE) $(DEP_CPP_M_FIX) "$(INTDIR)"

"$(INTDIR)\M_fixed.sbr" : $(SOURCE) $(DEP_CPP_M_FIX) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M_menu.c
DEP_CPP_M_MEN=\
	".\Unistd.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	".\..\wdmp\doomdef.h"\
	".\Dstrings.h"\
	".\..\wdmp\d_main.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\i_video.h"\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\w_wad.h"\
	".\R_local.h"\
	".\Hu_stuff.h"\
	".\G_game.h"\
	".\..\wdmp\m_argv.h"\
	".\M_swap.h"\
	".\S_sound.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\sounds.h"\
	".\M_menu.h"\
	".\D_french.h"\
	".\D_englsh.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\r_data.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\M_menu.obj" : $(SOURCE) $(DEP_CPP_M_MEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\M_menu.obj" : $(SOURCE) $(DEP_CPP_M_MEN) "$(INTDIR)"

"$(INTDIR)\M_menu.sbr" : $(SOURCE) $(DEP_CPP_M_MEN) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M_misc.c
DEP_CPP_M_MIS=\
	{$(INCLUDE)}"\sys\Stat.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\Unistd.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\z_zone.h"\
	".\M_swap.h"\
	".\..\wdmp\m_argv.h"\
	".\..\wdmp\w_wad.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\i_video.h"\
	".\..\wdmp\multires.h"\
	".\Hu_stuff.h"\
	".\..\wdmp\doomstat.h"\
	".\Dstrings.h"\
	".\..\wdmp\m_misc.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\r_data.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_net.h"\
	".\D_french.h"\
	".\D_englsh.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\M_misc.obj" : $(SOURCE) $(DEP_CPP_M_MIS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\M_misc.obj" : $(SOURCE) $(DEP_CPP_M_MIS) "$(INTDIR)"

"$(INTDIR)\M_misc.sbr" : $(SOURCE) $(DEP_CPP_M_MIS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M_random.c

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\M_random.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\M_random.obj" : $(SOURCE) "$(INTDIR)"

"$(INTDIR)\M_random.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\M_swap.c
DEP_CPP_M_SWA=\
	".\M_swap.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\M_swap.obj" : $(SOURCE) $(DEP_CPP_M_SWA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\M_swap.obj" : $(SOURCE) $(DEP_CPP_M_SWA) "$(INTDIR)"

"$(INTDIR)\M_swap.sbr" : $(SOURCE) $(DEP_CPP_M_SWA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Multires.c
DEP_CPP_MULTI=\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\m_argv.h"\
	".\..\wdmp\d_event.h"\
	".\R_plane.h"\
	".\..\wdmp\r_state.h"\
	".\R_things.h"\
	".\Am_map.h"\
	".\..\wdmp\multires.h"\
	".\V_video1.h"\
	".\V_video2.h"\
	".\R_draw1.h"\
	".\R_draw2.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\r_data.h"\
	".\..\wdmp\r_defs.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\Multires.obj" : $(SOURCE) $(DEP_CPP_MULTI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\Multires.obj" : $(SOURCE) $(DEP_CPP_MULTI) "$(INTDIR)"

"$(INTDIR)\Multires.sbr" : $(SOURCE) $(DEP_CPP_MULTI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_ceilng.c
DEP_CPP_P_CEI=\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\doomdef.h"\
	".\P_local.h"\
	".\S_sound.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\sounds.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_ceilng.obj" : $(SOURCE) $(DEP_CPP_P_CEI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_ceilng.obj" : $(SOURCE) $(DEP_CPP_P_CEI) "$(INTDIR)"

"$(INTDIR)\P_ceilng.sbr" : $(SOURCE) $(DEP_CPP_P_CEI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_doors.c
DEP_CPP_P_DOO=\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\doomdef.h"\
	".\P_local.h"\
	".\S_sound.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\r_state.h"\
	".\Dstrings.h"\
	".\..\wdmp\sounds.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	".\D_french.h"\
	".\D_englsh.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_doors.obj" : $(SOURCE) $(DEP_CPP_P_DOO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_doors.obj" : $(SOURCE) $(DEP_CPP_P_DOO) "$(INTDIR)"

"$(INTDIR)\P_doors.sbr" : $(SOURCE) $(DEP_CPP_P_DOO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_enemy.c
DEP_CPP_P_ENE=\
	".\M_random.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\doomdef.h"\
	".\P_local.h"\
	".\S_sound.h"\
	".\G_game.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\sounds.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_enemy.obj" : $(SOURCE) $(DEP_CPP_P_ENE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_enemy.obj" : $(SOURCE) $(DEP_CPP_P_ENE) "$(INTDIR)"

"$(INTDIR)\P_enemy.sbr" : $(SOURCE) $(DEP_CPP_P_ENE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_floor.c
DEP_CPP_P_FLO=\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\doomdef.h"\
	".\P_local.h"\
	".\S_sound.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\sounds.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_floor.obj" : $(SOURCE) $(DEP_CPP_P_FLO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_floor.obj" : $(SOURCE) $(DEP_CPP_P_FLO) "$(INTDIR)"

"$(INTDIR)\P_floor.sbr" : $(SOURCE) $(DEP_CPP_P_FLO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_inter.c
DEP_CPP_P_INT=\
	".\..\wdmp\doomdef.h"\
	".\Dstrings.h"\
	".\..\wdmp\sounds.h"\
	".\..\wdmp\doomstat.h"\
	".\M_random.h"\
	".\..\wdmp\i_system.h"\
	".\Am_map.h"\
	".\P_local.h"\
	".\S_sound.h"\
	".\P_inter.h"\
	".\D_french.h"\
	".\D_englsh.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\d_event.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_inter.obj" : $(SOURCE) $(DEP_CPP_P_INT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_inter.obj" : $(SOURCE) $(DEP_CPP_P_INT) "$(INTDIR)"

"$(INTDIR)\P_inter.sbr" : $(SOURCE) $(DEP_CPP_P_INT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_lights.c
DEP_CPP_P_LIG=\
	".\..\wdmp\z_zone.h"\
	".\M_random.h"\
	".\..\wdmp\doomdef.h"\
	".\P_local.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\doomtype.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\win32.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_lights.obj" : $(SOURCE) $(DEP_CPP_P_LIG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_lights.obj" : $(SOURCE) $(DEP_CPP_P_LIG) "$(INTDIR)"

"$(INTDIR)\P_lights.sbr" : $(SOURCE) $(DEP_CPP_P_LIG) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_map.c
DEP_CPP_P_MAP=\
	".\m_bbox.h"\
	".\M_random.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\doomdef.h"\
	".\P_local.h"\
	".\S_sound.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\sounds.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_map.obj" : $(SOURCE) $(DEP_CPP_P_MAP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_map.obj" : $(SOURCE) $(DEP_CPP_P_MAP) "$(INTDIR)"

"$(INTDIR)\P_map.sbr" : $(SOURCE) $(DEP_CPP_P_MAP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_maputl.c
DEP_CPP_P_MAPU=\
	".\m_bbox.h"\
	".\..\wdmp\doomdef.h"\
	".\P_local.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\m_fixed.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\win32.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_maputl.obj" : $(SOURCE) $(DEP_CPP_P_MAPU) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_maputl.obj" : $(SOURCE) $(DEP_CPP_P_MAPU) "$(INTDIR)"

"$(INTDIR)\P_maputl.sbr" : $(SOURCE) $(DEP_CPP_P_MAPU) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_mobj.c
DEP_CPP_P_MOB=\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\z_zone.h"\
	".\M_random.h"\
	".\..\wdmp\doomdef.h"\
	".\P_local.h"\
	".\..\wdmp\sounds.h"\
	".\St_stuff.h"\
	".\Hu_stuff.h"\
	".\S_sound.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_mobj.obj" : $(SOURCE) $(DEP_CPP_P_MOB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_mobj.obj" : $(SOURCE) $(DEP_CPP_P_MOB) "$(INTDIR)"

"$(INTDIR)\P_mobj.sbr" : $(SOURCE) $(DEP_CPP_P_MOB) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_plats.c
DEP_CPP_P_PLA=\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\z_zone.h"\
	".\M_random.h"\
	".\..\wdmp\doomdef.h"\
	".\P_local.h"\
	".\S_sound.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\sounds.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_plats.obj" : $(SOURCE) $(DEP_CPP_P_PLA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_plats.obj" : $(SOURCE) $(DEP_CPP_P_PLA) "$(INTDIR)"

"$(INTDIR)\P_plats.sbr" : $(SOURCE) $(DEP_CPP_P_PLA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_pspr.c
DEP_CPP_P_PSP=\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\d_event.h"\
	".\M_random.h"\
	".\P_local.h"\
	".\S_sound.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\sounds.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\doomtype.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_pspr.obj" : $(SOURCE) $(DEP_CPP_P_PSP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_pspr.obj" : $(SOURCE) $(DEP_CPP_P_PSP) "$(INTDIR)"

"$(INTDIR)\P_pspr.sbr" : $(SOURCE) $(DEP_CPP_P_PSP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_saveg.c
DEP_CPP_P_SAV=\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\z_zone.h"\
	".\P_local.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_saveg.obj" : $(SOURCE) $(DEP_CPP_P_SAV) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_saveg.obj" : $(SOURCE) $(DEP_CPP_P_SAV) "$(INTDIR)"

"$(INTDIR)\P_saveg.sbr" : $(SOURCE) $(DEP_CPP_P_SAV) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_setup.c
DEP_CPP_P_SET=\
	".\..\wdmp\z_zone.h"\
	".\M_swap.h"\
	".\m_bbox.h"\
	".\G_game.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\w_wad.h"\
	".\..\wdmp\doomdef.h"\
	".\P_local.h"\
	".\S_sound.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_setup.obj" : $(SOURCE) $(DEP_CPP_P_SET) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_setup.obj" : $(SOURCE) $(DEP_CPP_P_SET) "$(INTDIR)"

"$(INTDIR)\P_setup.sbr" : $(SOURCE) $(DEP_CPP_P_SET) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_sight.c
DEP_CPP_P_SIG=\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\i_system.h"\
	".\P_local.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\win32.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_sight.obj" : $(SOURCE) $(DEP_CPP_P_SIG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_sight.obj" : $(SOURCE) $(DEP_CPP_P_SIG) "$(INTDIR)"

"$(INTDIR)\P_sight.sbr" : $(SOURCE) $(DEP_CPP_P_SIG) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_spec.c
DEP_CPP_P_SPE=\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\m_argv.h"\
	".\M_random.h"\
	".\..\wdmp\w_wad.h"\
	".\R_local.h"\
	".\P_local.h"\
	".\G_game.h"\
	".\S_sound.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\sounds.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\r_defs.h"\
	".\P_spec.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_spec.obj" : $(SOURCE) $(DEP_CPP_P_SPE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_spec.obj" : $(SOURCE) $(DEP_CPP_P_SPE) "$(INTDIR)"

"$(INTDIR)\P_spec.sbr" : $(SOURCE) $(DEP_CPP_P_SPE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_switch.c
DEP_CPP_P_SWI=\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\doomdef.h"\
	".\P_local.h"\
	".\G_game.h"\
	".\S_sound.h"\
	".\..\wdmp\sounds.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_switch.obj" : $(SOURCE) $(DEP_CPP_P_SWI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_switch.obj" : $(SOURCE) $(DEP_CPP_P_SWI) "$(INTDIR)"

"$(INTDIR)\P_switch.sbr" : $(SOURCE) $(DEP_CPP_P_SWI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_telept.c
DEP_CPP_P_TEL=\
	".\..\wdmp\doomdef.h"\
	".\S_sound.h"\
	".\P_local.h"\
	".\..\wdmp\sounds.h"\
	".\..\wdmp\r_state.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\win32.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_telept.obj" : $(SOURCE) $(DEP_CPP_P_TEL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_telept.obj" : $(SOURCE) $(DEP_CPP_P_TEL) "$(INTDIR)"

"$(INTDIR)\P_telept.sbr" : $(SOURCE) $(DEP_CPP_P_TEL) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_tick.c
DEP_CPP_P_TIC=\
	".\..\wdmp\z_zone.h"\
	".\P_local.h"\
	".\..\wdmp\doomstat.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_tick.obj" : $(SOURCE) $(DEP_CPP_P_TIC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_tick.obj" : $(SOURCE) $(DEP_CPP_P_TIC) "$(INTDIR)"

"$(INTDIR)\P_tick.sbr" : $(SOURCE) $(DEP_CPP_P_TIC) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\P_user.c
DEP_CPP_P_USE=\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\d_event.h"\
	".\P_local.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\doomtype.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\P_user.obj" : $(SOURCE) $(DEP_CPP_P_USE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\P_user.obj" : $(SOURCE) $(DEP_CPP_P_USE) "$(INTDIR)"

"$(INTDIR)\P_user.sbr" : $(SOURCE) $(DEP_CPP_P_USE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Qmus2mid.c
DEP_CPP_QMUS2=\
	{$(INCLUDE)}"\sys\Types.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	".\qmus2mid.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\Qmus2mid.obj" : $(SOURCE) $(DEP_CPP_QMUS2) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\Qmus2mid.obj" : $(SOURCE) $(DEP_CPP_QMUS2) "$(INTDIR)"

"$(INTDIR)\Qmus2mid.sbr" : $(SOURCE) $(DEP_CPP_QMUS2) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\R_bsp.c
DEP_CPP_R_BSP=\
	".\..\wdmp\doomdef.h"\
	".\m_bbox.h"\
	".\..\wdmp\i_system.h"\
	".\R_main.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\r_data.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\win32.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\R_bsp.obj" : $(SOURCE) $(DEP_CPP_R_BSP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\R_bsp.obj" : $(SOURCE) $(DEP_CPP_R_BSP) "$(INTDIR)"

"$(INTDIR)\R_bsp.sbr" : $(SOURCE) $(DEP_CPP_R_BSP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\R_data.c
DEP_CPP_R_DAT=\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\z_zone.h"\
	".\M_swap.h"\
	".\..\wdmp\w_wad.h"\
	".\..\wdmp\doomdef.h"\
	".\R_local.h"\
	".\P_local.h"\
	".\..\wdmp\doomstat.h"\
	".\R_sky.h"\
	".\..\wdmp\r_data.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\tables.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\win32.h"\
	".\P_spec.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\R_data.obj" : $(SOURCE) $(DEP_CPP_R_DAT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\R_data.obj" : $(SOURCE) $(DEP_CPP_R_DAT) "$(INTDIR)"

"$(INTDIR)\R_data.sbr" : $(SOURCE) $(DEP_CPP_R_DAT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\R_draw1.c
DEP_CPP_R_DRA=\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\w_wad.h"\
	".\R_local.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\R_draw1.obj" : $(SOURCE) $(DEP_CPP_R_DRA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\R_draw1.obj" : $(SOURCE) $(DEP_CPP_R_DRA) "$(INTDIR)"

"$(INTDIR)\R_draw1.sbr" : $(SOURCE) $(DEP_CPP_R_DRA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\R_draw2.c
DEP_CPP_R_DRAW=\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\w_wad.h"\
	".\R_local.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\R_draw2.obj" : $(SOURCE) $(DEP_CPP_R_DRAW) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\R_draw2.obj" : $(SOURCE) $(DEP_CPP_R_DRAW) "$(INTDIR)"

"$(INTDIR)\R_draw2.sbr" : $(SOURCE) $(DEP_CPP_R_DRAW) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\R_main.c
DEP_CPP_R_MAI=\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\d_net.h"\
	".\m_bbox.h"\
	".\R_local.h"\
	".\R_sky.h"\
	".\St_stuff.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\d_event.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\R_main.obj" : $(SOURCE) $(DEP_CPP_R_MAI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\R_main.obj" : $(SOURCE) $(DEP_CPP_R_MAI) "$(INTDIR)"

"$(INTDIR)\R_main.sbr" : $(SOURCE) $(DEP_CPP_R_MAI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\R_plane.c
DEP_CPP_R_PLA=\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\w_wad.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\doomstat.h"\
	".\R_local.h"\
	".\R_sky.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\R_plane.obj" : $(SOURCE) $(DEP_CPP_R_PLA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\R_plane.obj" : $(SOURCE) $(DEP_CPP_R_PLA) "$(INTDIR)"

"$(INTDIR)\R_plane.sbr" : $(SOURCE) $(DEP_CPP_R_PLA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\R_segs.c
DEP_CPP_R_SEG=\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\doomstat.h"\
	".\R_local.h"\
	".\R_sky.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\R_segs.obj" : $(SOURCE) $(DEP_CPP_R_SEG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\R_segs.obj" : $(SOURCE) $(DEP_CPP_R_SEG) "$(INTDIR)"

"$(INTDIR)\R_segs.sbr" : $(SOURCE) $(DEP_CPP_R_SEG) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\R_sky.c
DEP_CPP_R_SKY=\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_data.h"\
	".\R_sky.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_ticcmd.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\R_sky.obj" : $(SOURCE) $(DEP_CPP_R_SKY) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\R_sky.obj" : $(SOURCE) $(DEP_CPP_R_SKY) "$(INTDIR)"

"$(INTDIR)\R_sky.sbr" : $(SOURCE) $(DEP_CPP_R_SKY) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\R_things.c
DEP_CPP_R_THI=\
	".\..\wdmp\doomdef.h"\
	".\M_swap.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\w_wad.h"\
	".\R_local.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\R_things.obj" : $(SOURCE) $(DEP_CPP_R_THI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\R_things.obj" : $(SOURCE) $(DEP_CPP_R_THI) "$(INTDIR)"

"$(INTDIR)\R_things.sbr" : $(SOURCE) $(DEP_CPP_R_THI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\S_sound.c
DEP_CPP_S_SOU=\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\i_sound.h"\
	".\..\wdmp\sounds.h"\
	".\S_sound.h"\
	".\..\wdmp\z_zone.h"\
	".\M_random.h"\
	".\..\wdmp\w_wad.h"\
	".\..\wdmp\doomdef.h"\
	".\P_local.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\R_local.h"\
	".\P_spec.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\S_sound.obj" : $(SOURCE) $(DEP_CPP_S_SOU) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\S_sound.obj" : $(SOURCE) $(DEP_CPP_S_SOU) "$(INTDIR)"

"$(INTDIR)\S_sound.sbr" : $(SOURCE) $(DEP_CPP_S_SOU) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Sounds.c
DEP_CPP_SOUND=\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\sounds.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\Sounds.obj" : $(SOURCE) $(DEP_CPP_SOUND) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\Sounds.obj" : $(SOURCE) $(DEP_CPP_SOUND) "$(INTDIR)"

"$(INTDIR)\Sounds.sbr" : $(SOURCE) $(DEP_CPP_SOUND) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\St_lib.c
DEP_CPP_ST_LI=\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\multires.h"\
	".\M_swap.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\w_wad.h"\
	".\St_stuff.h"\
	".\St_lib.h"\
	".\R_local.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\r_data.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\d_net.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\St_lib.obj" : $(SOURCE) $(DEP_CPP_ST_LI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\St_lib.obj" : $(SOURCE) $(DEP_CPP_ST_LI) "$(INTDIR)"

"$(INTDIR)\St_lib.sbr" : $(SOURCE) $(DEP_CPP_ST_LI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\St_stuff.c
DEP_CPP_ST_ST=\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\i_video.h"\
	".\..\wdmp\z_zone.h"\
	".\M_random.h"\
	".\..\wdmp\w_wad.h"\
	".\..\wdmp\doomdef.h"\
	".\G_game.h"\
	".\St_stuff.h"\
	".\St_lib.h"\
	".\R_local.h"\
	".\P_local.h"\
	".\P_inter.h"\
	".\Am_map.h"\
	".\M_cheat.h"\
	".\S_sound.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\doomstat.h"\
	".\Dstrings.h"\
	".\..\wdmp\sounds.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\P_spec.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\d_net.h"\
	".\D_french.h"\
	".\D_englsh.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\St_stuff.obj" : $(SOURCE) $(DEP_CPP_ST_ST) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\St_stuff.obj" : $(SOURCE) $(DEP_CPP_ST_ST) "$(INTDIR)"

"$(INTDIR)\St_stuff.sbr" : $(SOURCE) $(DEP_CPP_ST_ST) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Tables.c
DEP_CPP_TABLE=\
	".\..\wdmp\tables.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\Tables.obj" : $(SOURCE) $(DEP_CPP_TABLE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\Tables.obj" : $(SOURCE) $(DEP_CPP_TABLE) "$(INTDIR)"

"$(INTDIR)\Tables.sbr" : $(SOURCE) $(DEP_CPP_TABLE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\V_video1.c
DEP_CPP_V_VID=\
	".\..\wdmp\i_system.h"\
	".\R_local.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\doomstat.h"\
	".\m_bbox.h"\
	".\M_swap.h"\
	".\V_video1.h"\
	".\..\wdmp\w_wad.h"\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\win32.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\V_video1.obj" : $(SOURCE) $(DEP_CPP_V_VID) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\V_video1.obj" : $(SOURCE) $(DEP_CPP_V_VID) "$(INTDIR)"

"$(INTDIR)\V_video1.sbr" : $(SOURCE) $(DEP_CPP_V_VID) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\V_video2.c
DEP_CPP_V_VIDE=\
	".\..\wdmp\i_system.h"\
	".\R_local.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\doomstat.h"\
	".\m_bbox.h"\
	".\M_swap.h"\
	".\V_video2.h"\
	".\..\wdmp\w_wad.h"\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\win32.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\V_video2.obj" : $(SOURCE) $(DEP_CPP_V_VIDE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\V_video2.obj" : $(SOURCE) $(DEP_CPP_V_VIDE) "$(INTDIR)"

"$(INTDIR)\V_video2.sbr" : $(SOURCE) $(DEP_CPP_V_VIDE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\W_wad.c
DEP_CPP_W_WAD=\
	".\..\wdmp\platform.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\Unistd.h"\
	{$(INCLUDE)}"\sys\Stat.h"\
	".\..\wdmp\doomtype.h"\
	".\M_swap.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\w_wad.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\W_wad.obj" : $(SOURCE) $(DEP_CPP_W_WAD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\W_wad.obj" : $(SOURCE) $(DEP_CPP_W_WAD) "$(INTDIR)"

"$(INTDIR)\W_wad.sbr" : $(SOURCE) $(DEP_CPP_W_WAD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\W32NetEm.c
DEP_CPP_W32NE=\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\m_argv.h"\
	".\..\wdmp\d_main.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\win32.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\r_data.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\W32NetEm.obj" : $(SOURCE) $(DEP_CPP_W32NE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\W32NetEm.obj" : $(SOURCE) $(DEP_CPP_W32NE) "$(INTDIR)"

"$(INTDIR)\W32NetEm.sbr" : $(SOURCE) $(DEP_CPP_W32NE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Wi_stuff.c
DEP_CPP_WI_ST=\
	".\..\wdmp\z_zone.h"\
	".\M_random.h"\
	".\M_swap.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\w_wad.h"\
	".\G_game.h"\
	".\R_local.h"\
	".\S_sound.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\sounds.h"\
	".\..\wdmp\multires.h"\
	".\Wi_stuff.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\r_data.h"\
	".\R_main.h"\
	".\R_bsp.h"\
	".\R_segs.h"\
	".\R_plane.h"\
	".\R_things.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\win32.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\Wi_stuff.obj" : $(SOURCE) $(DEP_CPP_WI_ST) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\Wi_stuff.obj" : $(SOURCE) $(DEP_CPP_WI_ST) "$(INTDIR)"

"$(INTDIR)\Wi_stuff.sbr" : $(SOURCE) $(DEP_CPP_WI_ST) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Z_zone.c
DEP_CPP_Z_ZON=\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\Z_zone.obj" : $(SOURCE) $(DEP_CPP_Z_ZON) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\Z_zone.obj" : $(SOURCE) $(DEP_CPP_Z_ZON) "$(INTDIR)"

"$(INTDIR)\Z_zone.sbr" : $(SOURCE) $(DEP_CPP_Z_ZON) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Bench.c

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\Bench.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\Bench.obj" : $(SOURCE) "$(INTDIR)"

"$(INTDIR)\Bench.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Midassou.c
DEP_CPP_MIDAS=\
	".\..\wdmp\midas.h"\
	".\..\wdmp\midasdll.h"\
	".\..\wdmp\z_zone.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\i_sound.h"\
	".\..\wdmp\m_argv.h"\
	".\..\wdmp\m_misc.h"\
	".\..\wdmp\w_wad.h"\
	".\..\wdmp\i_video.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\win32.h"\
	{$(INCLUDE)}"\sys\Types.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\sounds.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\d_think.h"\
	
NODEP_CPP_MIDAS=\
	".\lang.h"\
	".\mtypes.h"\
	".\errors.h"\
	".\mglobals.h"\
	".\mmem.h"\
	".\file.h"\
	".\sdevice.h"\
	".\gmplayer.h"\
	".\timer.h"\
	".\dma.h"\
	".\mutils.h"\
	".\..\wdmp\ems.h"\
	".\mpoll.h"\
	".\madpcm.h"\
	".\waveread.h"\
	".\midasfx.h"\
	".\midasstr.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\Midassou.obj" : $(SOURCE) $(DEP_CPP_MIDAS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\Midassou.obj" : $(SOURCE) $(DEP_CPP_MIDAS) "$(INTDIR)"

"$(INTDIR)\Midassou.sbr" : $(SOURCE) $(DEP_CPP_MIDAS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Win32vid.c
DEP_CPP_WIN32=\
	".\..\wdmp\win32.h"\
	".\..\wdmp\doomstat.h"\
	".\..\wdmp\i_system.h"\
	".\..\wdmp\multires.h"\
	".\..\wdmp\m_argv.h"\
	".\..\wdmp\d_main.h"\
	".\..\wdmp\doomdef.h"\
	".\..\wdmp\doomtype.h"\
	".\..\wdmp\doomdata.h"\
	".\..\wdmp\d_net.h"\
	".\..\wdmp\d_player.h"\
	".\..\wdmp\d_items.h"\
	".\..\wdmp\p_pspr.h"\
	".\..\wdmp\p_mobj.h"\
	".\..\wdmp\d_ticcmd.h"\
	".\..\wdmp\m_fixed.h"\
	".\..\wdmp\tables.h"\
	".\..\wdmp\info.h"\
	".\..\wdmp\platform.h"\
	".\..\wdmp\d_think.h"\
	".\..\wdmp\d_event.h"\
	".\..\wdmp\r_data.h"\
	".\..\wdmp\r_defs.h"\
	".\..\wdmp\r_state.h"\
	

!IF  "$(CFG)" == "NtDoom - Win32 Release"


"$(INTDIR)\Win32vid.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NtDoom - Win32 Debug"


"$(INTDIR)\Win32vid.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"

"$(INTDIR)\Win32vid.sbr" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
