//#define BENCH
#ifdef BENCH

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

HDC hDCMain;
DWORD lBeginTime;
DWORD lEllapsedTime;

void fn_vStartBench()
{
    lBeginTime=timeGetTime();
}

void fn_vEndBench()
{ char szText[255];

    lEllapsedTime=timeGetTime()-lBeginTime;
    sprintf(szText,"%06ld",lEllapsedTime);
    
    TextOut(hDCMain,5,5,szText,strlen(szText));
}

#endif  // BENCH
