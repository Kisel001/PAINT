/****************************************************
 * COPYRIGHT (C)  KISEL STUDIOS. All rights reserved.
 *
 * FILE:          INTERFACE.C.
 * PURPOSE:       File with Interface Functions.
 * PROGRAMMER:    Ivan Pashkov, 10-5, IP5.
 * LAST UPDATE:   18.01.2024
 *
 * PROJECT:       Paint Win32 Application
 *
 * NOTIFICATION:  No part of this file can be
 *                changed without agrements
 *                I.Pashkov and Kisel Studios.
 ****************************************************/

#include "paint.h"
#include "common_colors.h"
#include "cord.h"

/* Draw Color Code function */
VOID PrintColorCode(VOID)
{
    BYTE
        r1, r2, r3,
        g1, g2, g3,
        b1, b2, b3,
        c1 = IP5_GetRed(Color),
        c2 = IP5_GetGreen(Color),
        c3 = IP5_GetBlue(Color);
    CHAR Buf[100];

    Rect(W - 170, H + 3, 105, 20, GFX_BLACK);

    r3 = c1 % 10;
    r2 = (c1 /= 10) % 10;
    r1 = (c1 / 10) % 10;

    g3 = c2 % 10;
    g2 = (c2 /= 10) % 10;
    g1 = (c2 / 10) % 10;


    b3 = c3 % 10;
    b2 = (c3 /= 10) % 10;
    b1 = (c3 / 10) % 10;

    wsprintfA(Buf, "%d%d%d, %d%d%d, %d%d%d", r1, r2, r3, g1, g2, g3, b1, b2, b3);

    DrawLetters(W - 170, H + 4, Buf, GFX_WHITE, 1);
} /* End of 'PrintColorCode' function */

/* Draw Mouse Coordinates function */
VOID PrintCoordinates(INT x, INT y)
{
    UL x1, x2, x3, x4, y1, y2, y3;

    Rect(1, H + 3, 90, 16, GFX_BLACK);

    if (x >= W || y >= H || x <= 0 || y <= 0)
        DrawLetters(2, H + 4, " ???? X ???", GFX_WHITE, 1);

    else
    {
        CHAR Buf[100];

        x4 = x % 10;
        x3 = (x / 10) % 10;
        x2 = (x / 100) % 10;
        x1 = (x >= 1000 ? 1 : 0);

        y3 = y % 10;
        y2 = (y / 10) % 10;
        y1 = y / 100;

        wsprintfA(Buf, "%d%d%d%d X %d%d%d", x1, x2, x3, x4, y1, y2, y3);

        DrawLetters(10, H + 4, Buf, GFX_WHITE, 1);
    }
} /* End of 'PrintCoordinates' function */

/* Draw Save Button static function */
static VOID DrawSaveButton(VOID)
{
    Rect(CORD_BUTTON_SAVE_X, CORD_BUTTON_SAVE_Y + H, CORD_BUTTON_SL_DX, CORD_BUTTON_SL_DY, GFX_LIME);
    DrawLetters(CORD_BUTTON_SAVE_X + 2, CORD_BUTTON_SAVE_Y + H + 2, " SAVE", GFX_BLACK, 1);
} /* End of 'DrawSaveButton' function */

/* Draw Load Button static function */
static VOID DrawLoadButton(VOID)
{
    Rect(CORD_BUTTON_LOAD_X, CORD_BUTTON_LOAD_Y + H, CORD_BUTTON_SL_DX, CORD_BUTTON_SL_DY, GFX_RED);
    DrawLetters(CORD_BUTTON_LOAD_X + 2, CORD_BUTTON_LOAD_Y + H + 2, " LOAD", GFX_BLACK, 1);
} /* End of 'DrawLoadButton' function */

/* Draw Color Indicator Frame static function */
static VOID DrawColorIndicatorFrame(VOID)
{
    Rect(CORD_COLOR_INDICATOR_X, CORD_COLOR_INDICATOR_Y, 25, 1, GFX_WHITE);
    Rect(CORD_COLOR_INDICATOR_X, CORD_COLOR_INDICATOR_Y, 1, 25, GFX_WHITE);
    Rect(CORD_COLOR_INDICATOR_X, CORD_COLOR_INDICATOR_Y + 25, 25, 1, GFX_WHITE);
    Rect(CORD_COLOR_INDICATOR_X + 25, CORD_COLOR_INDICATOR_Y, 1, 25, GFX_WHITE);
} /* End of 'DrawColorIndicatorFrame' function */

/* Draw Color Indicator Color in Frame function */
VOID DrawColorIndicatorColor(VOID)
{
    Rect(CORD_COLOR_INDICATOR_X + 2, CORD_COLOR_INDICATOR_Y + 2, 22, 22, Color);
} /* End of 'DrawColorIndicator' function */

/* Draw Clear Window Button static function */
static VOID DrawClearWindowButton(VOID)
{
    Rect(CORD_BUTTON_CLEAR_X, CORD_BUTTON_CLEAR_Y + H, CORD_BUTTON_CLEAR_DX, CORD_BUTTON_CLEAR_DY, GFX_LIGHT_BLUE);
    DrawLetters(CORD_BUTTON_CLEAR_X + 2, CORD_BUTTON_SAVE_Y + H + 2, " CLEAR", GFX_BLACK, 1);
} /* End of 'DrawClearWindowButton' function */

/* Draw Triangle Draw Button static function */
static VOID DrawTriangleDrawButton(VOID)
{
    Rect(CORD_BUTTON_TRIANGLE_X, CORD_BUTTON_TRIANGLE_Y + H, CORD_BUTTON_TRIANGLE_DX, CORD_BUTTON_TRIANGLE_DY, GFX_YELLOW);
    DrawLetters(CORD_BUTTON_TRIANGLE_X + 2, CORD_BUTTON_TRIANGLE_Y + H + 2, " TRIANGLE", GFX_BLACK, 1);
} /* End of 'DrawTriangleDrawButton' function */

/* Memory set by DWORD value static function */
static VOID memsetint( DWORD *dst, DWORD value, size_t count )
{
    while (count--)
        *dst++ = value;
} /* End of 'memsetint' function */

/* Clear Window function */
VOID ClearWindowFunc(VOID)
{
    memsetint(GetFrame(), 0xFFFFFF, W * H);
    //Rect(0, 0, W, H, GFX_WHITE);
} /* End of 'ClearWindowFunc' function */

/* Check mode after special mode function */
VOID CheckModeAfterSpecialMode( VOID )
{
    Rect(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, 110, 20, GFX_BLACK);
    
    if (TRIANGLE_STATE != 0) // Triangle Draw Mode
    {
        CHAR Buf[100];

        wsprintfA(Buf, " TRIANGLE :: %d", TRIANGLE_STATE);
        DrawLetters(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, Buf, GFX_WHITE, 1);
    }
    else if (Painting_Mode == 1) // Default Circle Mode
        DrawLetters(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, " PENCIL", GFX_WHITE, 1);
    else if (Painting_Mode == 2) // Transpanence Circle Mode
        DrawLetters(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, " TRANSPANENCE", GFX_WHITE, 1);
    else if (Painting_Mode == 3) // Mixing Circle Mode
        DrawLetters(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, " MIXING", GFX_WHITE, 1);
} /* End of 'CheckModeAfterSpecialMode' function */

/* Base Draw in Main function */
VOID BaseDraw(VOID)
{
#ifdef __DEBUG_PAINT_
    INT i;
#endif /* __DEBUG_PAINT_ */

    /* Fill the screen with white */
    memsetint(GetFrame(), 0xFFFFFF, W * H);

    /* Draw the bottom panel */
    Rect(0, H + 1, W, 2, GFX_WHITE);

    /* Draw Buttons */
    DrawSaveButton();
    DrawLoadButton();
    DrawClearWindowButton();
    DrawTriangleDrawButton();

    /* Draw Color indicator */
    DrawColorIndicatorFrame();
    DrawColorIndicatorColor();

    /* Draw coordinates mouse indicator */
    PrintCoordinates(-1, -1);

#ifdef __DEBUG_PAINT_
    for (i = 0; i < 256; i++)
      DrawLetter(100 + (i % 16) * 16, 100 + (i / 16) * 16, (CHAR)i, GFX_BLACK, 1);
#endif /* __DEBUG_PAINT_ */

    /* Draw Coordinates & Base Mode */
    DrawLetters(W - 170, H + 4, "000, 000, 000", GFX_WHITE, 1);
    DrawLetters(CORD_MODE_INDICATOR_1_X, H + CORD_MODE_INDICATOR_1_Y, " MODE:", GFX_WHITE, 1);
    DrawLetters(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, " PENCIL", GFX_WHITE, 1);
    Display();
} /* End of 'BaseDraw' function */

/* END OF 'INTERFACE.C' FILE */
