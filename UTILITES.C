/****************************************************
 * COPYRIGHT (C)  KISEL STUDIOS. All rights reserved.
 * 
 * FILE:          UTILITES.C. 
 * PURPOSE:       File with functions-utilites for drawing.
 * PROGRAMMER:    Ivan Pashkov, 10-5, IP5.
 * LAST UPDATE:   23.01.2024
 *  
 * PROJECT:       Paint Win32 Application
 * 
 * NOTIFICATION:  No part of this file can be
 *                changed without agrements
 *                I.Pashkov and Kisel Studios.
 ****************************************************/

#include <string.h>
#include <glut.h>

#include "paint.h"
#include "common_colors.h"
#include "cord.h"

/* Array with Pixels */
static DWORD Frame[W * (H + 32)];

#ifdef TR_CORD
#undef TR_CORD
#endif /* TR_CORD */
#ifdef tagTR_CORD
#undef tagTR_CORD
#endif /* tagTR_CORD */
/* Special local type for Triangle Coordinates */
typedef struct tagTR_CORD
{
  INT
    X[3], Y[3]; /* Coordinates of triangle points */
} TR_CORD;

/* Clarity for transpanecnce mode */
#define CLARITY  0.07

/* Get Frame function */
VOID * GetFrame( VOID ) 
{
  return (VOID *)Frame;
} /* End of 'GetFrame' function */

/* Draw one pixel function */
VOID PutPixel( INT X, INT Y, DWORD color, UC MODE )
{
    if ((X < 0 || Y < 0 || X >= W || Y >= H) && !MODE)
        return;

    Frame[W * Y + X] = color;
} /* End of 'PutPixel' function */

/* Draw Circle Static function */
static VOID Circle( INT X, INT Y, INT RAD, DWORD Color )
{
    INT i, j, iconst = X - RAD - 1;
    INT sqRad = RAD * RAD, jmax = Y + RAD + 1, imax = X + RAD + 1;

    for (j = Y - RAD - 1; j < jmax; j++)
        for (i = iconst; i < imax; i++)
            if (((i - X) * (i - X) + (j - Y) * (j - Y)) <= sqRad)
                PutPixel(i, j, Color, 0);
} /* End of 'Circle' function */

/* X, Y -> get POINT{X, Y} static inline function */
static inline POINT GetPoint( INT X, INT Y )
{
    POINT p = {X, Y};
    return p;
} /* End of 'GetPoint' function */

/* New Filling function */
VOID NewFillingFunc( UL X, UL Y, DWORD Color, DWORD Color1 )
{
    POINT *Pixels;
    UL N = 0;

    if (Color == Color1)
      return;

    if ((Pixels = (POINT*)malloc(W * H * sizeof(POINT))) == NULL) // Memory for Pixels, limited by screen size, checking successful of allocation
    {
        MessageBox(hWnd, L"Failed to allocate memory for the program!", L"MEMORY ERROR", MB_ICONERROR);
        return;
    }

    /* Clear memory for safety */
    memset(Pixels, 0, W * H * sizeof(POINT));

    /* Add base Pixel Coordinates in stack */
    Pixels[N++] = GetPoint(X, Y);

    while (N != 0)
    {
        /* Getting pixel coordinates from stack */
        INT X0 = Pixels[--N].x,
            Y0 = Pixels[N].y;

        PutPixel(X0, Y0, Color, 0); // Draw the current pixel from the stack

        //Display();

        /* Check for Fill 4 Pixels around */
        if (Y0 > 0 && GetColor(X0, Y0 - 1) == Color1)
          Pixels[N++] = GetPoint(X0, Y0 - 1);

        if (Y0 < H - 1 && GetColor(X0, Y0 + 1) == Color1)
          Pixels[N++] = GetPoint(X0, Y0 + 1);

        if (X0 > 0 && GetColor(X0 - 1, Y0) == Color1)
          Pixels[N++] = GetPoint(X0 - 1, Y0);

        if (X0 < W - 1 && GetColor(X0 + 1, Y0) == Color1)
          Pixels[N++] = GetPoint(X0 + 1, Y0);
    }

    /* Free memory for *Pixels */
    free(Pixels);
} /* End of 'NewFillingFunc' function */

/* Draw Transparence Pixel static function */
static VOID TransparenceFunc( UL X, UL Y, DWORD Color, FLOAT clarity )
{
    INT Offset;
    UC R0, G0, B0, R, G, B;

    if (X < 0 || Y < 0 || X >= W || Y >= H)
        return;

    Offset = W * Y + X;

    R0 = (Frame[Offset] >> 16) & 255;
    G0 = (Frame[Offset] >> 8) & 255;
    B0 = Frame[Offset] & 255;

    R = IP5_GetRed(Color);
    G = IP5_GetGreen(Color);
    B = IP5_GetBlue(Color);

    R0 = R0 * (1 - clarity) + clarity * R;
    G0 = G0 * (1 - clarity) + clarity * G;
    B0 = B0 * (1 - clarity) + clarity * B;

    Frame[W * Y + X] = IP5_RGB(R0, G0, B0);
} /* End of 'TransparenceFunc' function */

/* Draw Clarity Circle static function */
static VOID ClarityCircle( UL X, UL Y, UL RAD, DWORD Color, FLOAT C )
{
    UL i, j, sqRad = RAD * RAD, jmax = Y + RAD + 1, imax = X + RAD + 1, iconst = X - RAD - 1;

    if (X < 0 || Y < 0 || X >= W || Y >= H)
        return;

    for (j = Y - RAD - 1; j < jmax; j++)
        for (i = iconst; i < imax; i++)
            if ((i - X) * (i - X) + (j - Y) * (j - Y) <= sqRad)
                TransparenceFunc(i, j, Color, C);
} /* End of 'ClarityCircle' function */

/* Change Color by Pipette function */
VOID PipetteFunc( UL X, UL Y )
{
    if (X < 0 || Y < 0 || X >= W || Y >= H)
        return;

    Color = GetColor(X, Y);
} /* End of 'PipetteFunc' function */

/* RGB Code Color -> Color function */
VOID ChangeColorFunc(UC R, UC G, UC B)
{
    Color = IP5_RGB(R, G, B);

#ifdef __DEBUG_PAINT_
    printf("\n%d% d %d :: %x", R, G, B, Color);
#endif /* __DEBUG_PAINT_ */
} /* End of 'ChangleColorFunc' function */

/* New Custom Color Select function */
VOID NewCustomColorFunc( VOID )
{
    static CHOOSECOLOR cc = { 0 };
    static DWORD CustomColors[16];

    Rect(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, 115, 20, GFX_BLACK);
    DrawLetters(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, " CHANGE COLOR", GFX_WHITE, 1);
    glDrawPixels(W, H + 32, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Frame);
    
    glFinish();
    glutSwapBuffers();
    glutPostRedisplay();

    cc.lStructSize = sizeof(CHOOSECOLOR);
    cc.rgbResult = RGB((Color << 16) & 255, (Color << 8) & 255, Color & 255);
    cc.hwndOwner = hWnd;
    cc.lpCustColors = CustomColors;
    cc.Flags = CC_ANYCOLOR | CC_FULLOPEN | CC_PREVENTFULLOPEN | CC_RGBINIT;

    if (ChooseColor(&cc))
    {
        BYTE
            r = GetRValue(cc.rgbResult),
            g = GetGValue(cc.rgbResult),
            b = GetBValue(cc.rgbResult);

        ChangeColorFunc(r, g, b);
    }

    CheckModeAfterSpecialMode();
} /* End of 'NewCustomColorFunc' function */

/* Draw Rect function */
VOID Rect( UL X1, UL Y1, UL X2, UL Y2, DWORD Color )
{
    UL i, j;

    for (j = 0; j < Y2; j++)
        for (i = 0; i < X2; i++)
            PutPixel(X1 + i, Y1 + j, Color, 1);
} /* End of 'Rect' function */

/* Draw Mixing Color static function */
static VOID MixingCircle( UL X, UL Y, UL RAD )
{
    UL 
        i, j,
        sqRad = RAD * RAD,
        jmax = Y + RAD + 1, imax = X + RAD + 1, iconst = X - RAD - 1,
        RedSumm = 0, GreenSumm = 0, BlueSumm = 0,
        Color_AV = 0,
        Pixel_Count = 0;

    if (X < 0 || Y < 0 || X >= W || Y >= H)
        return;

    for (j = Y - RAD - 1; j < jmax; j++)
        for (i = iconst; i < imax; i++)
            if ((i - X) * (i - X) + (j - Y) * (j - Y) <= sqRad)
            {
                BlueSumm += IP5_GetBlue(GetColor(i, j));
                GreenSumm += IP5_GetGreen(GetColor(i, j));
                RedSumm += IP5_GetRed(GetColor(i, j));
                Pixel_Count++;
            }

    /* If Pixels Count <= 0 -> NO PIXELS */
    if (!Pixel_Count)
        return;

    Color_AV = IP5_RGB(RedSumm / Pixel_Count, GreenSumm / Pixel_Count, BlueSumm / Pixel_Count);
    
    for (j = Y - RAD - 1; j < jmax; j++)
        for (i = iconst; i < imax; i++)
            if ((i - X) * (i - X) + (j - Y) * (j - Y) <= sqRad)
                PutPixel(i, j, Color_AV, 0);
} /* End of 'MixingColor' function */

/* Correct Draw Line function */
VOID PutLine(INT X1, INT Y1, INT X2, INT Y2, DWORD Color, INT Mode)
{
    INT dx, dy, F, IncrE, IncrNE, tmp, x, y, sx, count;

    if (Y1 > Y2)
        COM_SWAP(X1, X2, tmp), COM_SWAP(Y1, Y2, tmp);

    dy = Y2 - Y1;
    dx = X2 - X1;
    
    if (dx < 0)
        sx = -1, dx = -dx;
    else
        sx = 1;

    x = X1;
    y = Y1;
    
    switch (Mode)
    {
    case 1: // DEFAULT MODE
        Circle(x, y, COMMON_RAD, Color);
        break;
    case 2: // TRANSPANENCE MODE
        ClarityCircle(x, y, COMMON_RAD, Color, CLARITY);
        break;
    case 3: // MIXING MODE
        MixingCircle(x, y, COMMON_RAD);
        break;
    default:
        Circle(x, y, COMMON_RAD, Color);
        break;
    }

    if (dx >= dy)
    {
        F = 2 * dy - dx;
        IncrE = 2 * dy;
        IncrNE = 2 * dy - 2 * dx;
        count = dx;

        while (count--)
        {
            if (F > 0)
                y++, F += IncrNE;
            else
                F += IncrE;
            x += sx;

            switch (Mode)
            {
            case 1: // DEFAULT MODE
                Circle(x, y, COMMON_RAD, Color);
                break;
            case 2: // TRANSPANENCE MODE
                ClarityCircle(x, y, COMMON_RAD, Color, CLARITY);
                break;
            case 3: // MIXING MODE
                MixingCircle(x, y, COMMON_RAD);
                break;
            default:
                Circle(x, y, COMMON_RAD, Color);
                break;
            }
        }
    }
    else
    {
        F = 2 * dx - dy;
        IncrE = 2 * dx;
        IncrNE = 2 * dx - 2 * dy;
        count = dy;

        while (count--)
        {
            if (F > 0)
                x += sx, F += IncrNE;
            else
                F += IncrE;
            y++;

            switch (Mode)
            {
            case 1: // DEFAULT MODE
                Circle(x, y, COMMON_RAD, Color);
                break;
            case 2: // TRANSPANENCE MODE
                ClarityCircle(x, y, COMMON_RAD, Color, CLARITY);
                break;
            case 3: // MIXING MODE
                MixingCircle(x, y, COMMON_RAD);
                break;
            default:
                Circle(x, y, COMMON_RAD, Color);
                break;
            }
        }
    }
} /* End of 'PutLine' function */

#ifdef SquareTriangle
#undef SquareTriangle
#endif /* SquareTriangle */

/* Get Square of triangle function */
#define SquareTriangle(X1, Y1, X2, Y2, X3, Y3) \
((IP5_ABS(((X1) - (X2)) * ((Y1) - (Y3)) -  ((X1) - (X3)) * ((Y1) - (Y2)))) / 2.0)

/* Draw Triangle Static function */
static VOID DrawTriangle(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3)
{
    DBL S = SquareTriangle(x1, y1, x2, y2, x3, y3), w, v, u;
    INT minX, minY, maxX, maxY, i, j;

    maxX = max3(x1, x2, x3);
    maxY = max3(y1, y2, y3);

    minX = min3(x1, x2, x3);
    minY = min3(y1, y2, y3);

    for (i = minY; i <= maxY; i++)
        for (j = minX; j <= maxX; j++)
        {
            DBL tmp = 
              (w = SquareTriangle(x1, y1, x2, y2, j, i) / S) + 
              (v = SquareTriangle(x1, y1, j, i, x3, y3) / S) + 
              (u = SquareTriangle(j, i, x2, y2, x3, y3) / S);

            if (tmp <= 1.001)
                PutPixel(j, i, Color  /*RGB((INT)(u * 255), (INT)(v * 255), (INT)(w * 255)) */, 0);
        }
} /* End of 'DrawTrinagle' function */

/* Add Triangle Coordinates in Struct function */
VOID AddTriangleCoordinated(INT X, INT Y)
{
    /* Local struct with Corrdinates of Triangle */
    static TR_CORD BASIC_TR_CORD = { 0 };
        
    Rect(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, 116, 20, GFX_BLACK);

    if (TRIANGLE_STATE >= 1 && TRIANGLE_STATE <= 3)
    {
        BASIC_TR_CORD.X[TRIANGLE_STATE - 1] = X;
        BASIC_TR_CORD.Y[TRIANGLE_STATE++ - 1] = Y;

        if (TRIANGLE_STATE != 4)
        {
            CHAR Buf[100];

            wsprintfA(Buf, " TRIANGLE :: %d", TRIANGLE_STATE);
            DrawLetters(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, Buf, GFX_WHITE, 1);
        }
        else
        {
            DrawTriangle(BASIC_TR_CORD.X[0], BASIC_TR_CORD.Y[0], BASIC_TR_CORD.X[1], BASIC_TR_CORD.Y[1], BASIC_TR_CORD.X[2], BASIC_TR_CORD.Y[2]);
            TRIANGLE_STATE = 0;
            CheckModeAfterSpecialMode();
        }
    }
    else
    {
        MessageBox(GetActiveWindow(), L"Triangle Drawing Error!\n\nLoss of triangle point stack status.", L"TRIANGLE DRAWING ERROR", MB_ICONERROR);
        TRIANGLE_STATE = 0;

        CheckModeAfterSpecialMode();
    }
} /* End of 'AddTriangleCoordinates' function */

/* END OF 'UTILITES.C' FILE */
