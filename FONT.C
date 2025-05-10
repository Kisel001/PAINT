/****************************************************
 * COPYRIGHT (C)  KISEL STUDIOS. All rights reserved.
 *
 * FILE:          FONT.C.
 * PURPOSE:       File with processing of Font.
 * PROGRAMMER:    Ivan Pashkov, 10-5, IP5.
 * LAST UPDATE:   13.01.2024
 *
 * PROJECT:       Paint Win32 Application
 *
 * NOTIFICATION:  No part of this file can be
 *                changed without agrements
 *                I.Pashkov and Kisel Studios.
 ****************************************************/

#include <stdio.h>
#include <stdarg.h>

#include "paint.h"

/* Special staic Massive for saving Font */
static UC Font[4096];

/* Load Font from file function */
VOID LoadFont( VOID )
{
    static const CHAR *Filename = "_VGA!FONT-8x16.FNT";
    FILE *F;

    fopen_s(&F, Filename, "rb");

    if (F == NULL)
    {
        MessageBox(GetActiveWindow(), L"Font file are not finded!\n\nFont are not loaded!", L"FILE ERROR", MB_ICONERROR);
        return;
    }

    fread(Font, 16, 256, F);
    fclose(F);
} /* End of 'LoadFont' function */

/* Draw One Letter function */
VOID DrawLetter( UL X, UL Y, CHAR symbol, DWORD Color, UC MODE )
{
    INT i, j;

    for (i = 0; i < 16; i++)
        for (j = 0; j < 8; j++)
            if (Font[16 * (BYTE)symbol + i] & (0x80 >> j))
                if (MODE == 1)
                    PutPixel(X + j, Y + i, Color, 1);
                else
                    PutPixelTxt(X + j, Y + i, Color, 1);
} /* End of 'DrawLetter' function */

/* Draw Some Letters function */
VOID DrawLetters( UL X, UL Y, const CHAR *str, DWORD Color, UC MODE, ... )
{
    INT save_x = X;
    static CHAR Buf[10000];
    va_list L;

    if (str == NULL)
        return;
    
    va_start(L, MODE);
    vsprintf(Buf, str, L);
    str = Buf;

    while (*str != 0)
    {
        if (*str == '\n') // If symbol == line feed
            X = save_x, Y += 16;
        else
            DrawLetter(X, Y, *str, Color, MODE);
        X += 8;
    
        str++;
    
        if (!MODE && Y >= H - 10)
            return;
    }
} /* End of 'DrawLetters' function */

/* END OF 'FONT.C' FILE */
