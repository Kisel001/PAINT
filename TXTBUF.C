/****************************************************
 * COPYRIGHT (C)  KISEL STUDIOS. All rights reserved.
 *
 * FILE:          TXTBUF.C.
 * PURPOSE:       File with handling user text buffers.
 * PROGRAMMER:    Ivan Pashkov, 10-5, IP5.
 * LAST UPDATE:   21.01.2024
 *
 * PROJECT:       Paint Win32 Application
 *
 * NOTIFICATION:  No part of this file can be
 *                changed without agrements
 *                I.Pashkov and Kisel Studios.
 ****************************************************/

#include <string.h>

#include "paint.h"


/* Special buffers arrays for text mode */
static DWORD CopyBufferArray[W * (H + 32)];  /* Copy buffer array */
static DWORD FrameBuf[W * H];                /* Buffer with color text info */
static INT FrameStat[W * H];                 /* Buffer with status of text mode */

/* Put Pixel in txt buffer function */
VOID PutPixelTxt(INT X, INT Y, DWORD color, INT state)
{
    INT offset;
    if (X < 0 || Y < 0 || X >= W || Y >= H)
        return;

    offset = W * Y + X;

    FrameBuf[offset] = color;
    FrameStat[offset] = state;
} /* End of 'PutPixelTxt' function */

/* Copy user color Frame and text color Frame to DrawPixel function */
VOID * CopyBuffer( VOID )
{
    DWORD 
        *dstCopy = CopyBufferArray,
        *dstBuf = FrameBuf;
    INT *dstStat = FrameStat;
    UINT count = W * H;

    memcpy(CopyBufferArray, GetFrame(), W * (H + 32) * sizeof(DWORD));

    while (count--)
    {
        if (*dstStat++)
            *dstCopy = *dstBuf;
        dstCopy++;
        dstBuf++;
    }

    return (VOID *)CopyBufferArray;
} /* End of 'CopyBuffer' function */

/* Fill text state buffer by state function */
VOID FillTextRect(INT X, INT Y, INT DX, INT DY, INT state)
{
    INT i, j;

    for (j = Y; j < DY + Y; j++)
        for (i = X; i < DX + X; i++)
            FrameStat[W * j + i] = state;
} /* End of 'FillTextRect' function */

/* Release buffer to frame function */
static VOID ReleseBuffer( VOID )
{
    DWORD
        *dstBuf = FrameBuf,
        *dstFrame = GetFrame();
    INT *dstStat = FrameStat;
    UINT count = W * H;

    while (count--)
    {
        if (*dstStat)
            *dstFrame = *dstBuf;             
        ++dstFrame;
        ++dstBuf;
        ++dstStat;
    }

    /* Clear buffers */
    memset(FrameBuf, 0, W * H * sizeof(DWORD));
    memset(FrameStat, 0, W * H * sizeof(DWORD));
} /* End of 'ReleaseBuffer' function */

/* End of text mode function */
VOID CloseTxtMode(VOID)
{
    IsActiveTextMode = 0;
    ReleseBuffer();
    CheckModeAfterSpecialMode();
} /* Ebd of 'CloseTxtMode' function */

/* END OF 'TXTBUF.C' FILE */
