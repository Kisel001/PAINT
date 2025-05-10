/****************************************************
 * COPYRIGHT (C)  KISEL STUDIOS. All rights reserved.
 *
 * FILE:          PAINT.H. 
 * PURPOSE:       Basic Header File of Project.
 * PROGRAMMER:    Ivan Pashkov, 10-5, IP5.
 * LAST UPDATE:   21.01.2024
 *
 * PROJECT:       Paint Win32 Application
 *
 * NOTIFICATION:  No part of this file can be
 *                changed without agrements
 *                I.Pashkov and Kisel Studios.
 ****************************************************/



#if (defined _MSC_VER) && (_MSC_VER >= 400) 
#pragma once
#endif /* _MSC_VER */

#ifndef __PAINT_H_
#define __PAINT_H_



//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// Set status of Paint Project debug mode
// 0 = DISABLE
// 1 = ENABLE
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#define __PAINT_COMMON_PROJECT_DBG_ACTIVATE_STATUS_ 0

#if __PAINT_COMMON_PROJECT_DBG_ACTIVATE_STATUS_ == 1
#include <stdio.h>
#define __DEBUG_PAINT_
#endif /* !__DEBUG_PAINT_ */

/* Disable useless warnings */
#if (defined _MSC_VER) && (_MSC_VER >= 400) 
#pragma warning(disable:6031 4554 4996 4067 4024 28251 4028)
#endif /* _MSC_VER */

/* Debug memory allocation support */
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// If compile configuration is DEBUG
// And activated Debug Paint Mode
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#if (defined _DEBUG) && (defined __DEBUG_PAINT_)
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
     _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
       _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else /* _DEBUG && __DEBUG_PAINT_ */
#  define SetDbgMemHooks() ((void)0)
#endif /* _DEBUG && __DEBUG_PAINT_ */

#include <stdlib.h>

#include "types.h"



/***
 * DEFINE
 ***/



/* Window Weight Size */
#define W  1500

/* Window Height Size */
#define H  700



/***
 * Define fast micro-functions
 ***/



#ifndef min3
/* Minimal count from 3 counts function */
#define min3(a, b, c)        (min(min((a), (b)), (c)))
#endif /* !min3 */

#ifndef max3
/* Maximal count from 3 counts function */
#define max3(a, b, c)        (max(max((a), (b)), (c)))
#endif /* !max3 */

#ifndef IP5_ABS
/* Fast module of count function */
#define IP5_ABS(x)           ((x) >= 0 ? (x) : -(x))
#endif /* !IP5_ABS */

#ifndef IP5_RGB
/* Fast Get DWORD Color from RGB function */
#define IP5_RGB(r, g, b)     ((DWORD)(((BYTE)(r) << 16) | ((BYTE)(g) << 8) | ((BYTE)(b))))
#endif /* !IP5_RGB */

#ifndef IP5_GetRed
/* Get red code from DWORD Color function */
#define IP5_GetRed(color)    (((color) >> 16) & 0xFF)
#endif /* !IP5_GetRed */

#ifndef IP5_GetGreen
/* Get green code from DWORD Color function */
#define IP5_GetGreen(color)  (((color) >> 8) & 0xFF)
#endif /* !IP5_GetGreen */

#ifndef IP5_GetBlue
/* Get blue code from DWORD Color function */
#define IP5_GetBlue(color)   ((color) & 0xFF)
#endif /* !IP5_GetBlue */



/*** 
 * GLOBAL MASSIVES & VARRIABLES 
 ***/



extern DWORD Color;           /* Variable with Color */
extern ULONG COMMON_RAD;      /* Variable with Common Radius of Circle */
extern INT Painting_Mode;     /* Variable with Mode of Painting */
extern INT IsActiveTextMode;  /* Variable with Text Mode Status */
extern INT TRIANGLE_STATE;    /* Variable with State of Triangle Drawing */
extern HWND hWnd;             /* Window Variable */



/***
 * FUNCTIONS PROTOTYPES 
 ***/



/*===========
 * FOR PAINT
 *===========*/


/* Draw one pixel function */
VOID PutPixel(INT X, INT Y, DWORD Color, UC MODE);

/* Draw Rect function */
VOID Rect(UL X1, UL Y1, UL X2, UL Y2, DWORD Color);

/* New Filling function */
VOID NewFillingFunc(UL X, UL Y, DWORD Color, DWORD Color1);

/* Correct Draw Line function */
VOID PutLine(INT X1, INT Y1, INT X2, INT Y2, DWORD Color, INT Mode);


/*==========
 * UTILITES
 *==========*/


/* Get Frame function */
VOID * GetFrame(VOID);

/* Get color from array with pixels function */
__inline DWORD GetColor(INT X, INT Y)
{
  DWORD color = ((DWORD *)GetFrame())[W * Y + X];

  return color;
} /* End of 'GetColor' function */

/* Change Color by Pipette function */
VOID PipetteFunc(UL X, UL Y);

/* RGB Code Color -> Color function */
VOID ChangeColorFunc(UC R, UC G, UC B);

/* New Custom Color Select function */
VOID NewCustomColorFunc(VOID);

/* Add Triangle Coordinates in Struct function */
VOID AddTriangleCoordinated(INT X, INT Y);


/*=================
 * DRAW UI ELEMETS 
 *=================*/


/* Draw Color Code function */
VOID PrintColorCode(VOID);

/* Draw Mouse Coordinates function */
VOID PrintCoordinates(INT x, INT y);

/* Draw Color Indicator Color in Frame function */
VOID DrawColorIndicatorColor(VOID);

/* Clear Window function */
VOID ClearWindowFunc(VOID);

/* Base Draw in Main function */
VOID BaseDraw(VOID);	

/* Check mode after special mode function */
VOID CheckModeAfterSpecialMode(VOID);


/*=============
 * CONTROLLERS 
 *=============*/


/* OpenGL Keyboard callback function */
VOID Keyboard(UC Key, INT X, INT Y);

/* OpenGL special keys of Keyboard callback function */
VOID Special(INT Key, INT X, INT Y);

/* OpenGL Mouse Motion callback function */
VOID Mouse(INT x, INT y);

/* OpenGL Mouse Passive Motion callback function */
VOID SMouse(INT X, INT Y);

/* OpenGL Mouse Button Press callback function */
VOID PMouse(INT B, INT S, INT X, INT Y);

/* OpenGL Reshape window callback function */
VOID Reshape(INT widht, INT height);

/* Display drawing function */
VOID Display(VOID);


/*======
 * FONT
 *======*/


/* Load Font from file function */
VOID LoadFont(VOID);

/* Draw One Letter function */
VOID DrawLetters( UL X, UL Y, const CHAR *str, DWORD Color, UC MODE, ... );

/* Draw Some Letters function */
VOID DrawLetter(UL X, UL Y, CHAR symbol, DWORD Color, UC MODE);


/*=========================
 * SAVING & LOADING IMAGES
 *=========================*/


/* Open (Import) File with WinAPI Explorer function */
VOID OpenFileFunc(VOID); // Import v 2.0

/* Save (Export) File with WinAPI Explorer function */
VOID SaveFileFunc(VOID); // Export v 2.0


/*===========
 * PCX IMAGE
 *===========*/


/* Load PCX Image function */
VOID LoadPCXImage(INT X0, INT Y0);


/*================
 * TEXT BUFFERING
 *================*/


/* Put Pixel in txt buffer function */
VOID PutPixelTxt(INT X, INT Y, DWORD Color, INT state);

/* Copy user color Frame and text color Frame to DrawPixel function */
VOID* CopyBuffer(VOID);

/* Fill text state buffer by state function */
VOID FillTextRect(INT X, INT Y, INT DX, INT DY, INT state);

/* End of text mode function */
VOID CloseTxtMode(VOID);


#endif /* !__PAINT_H_ */



/* END OF 'PAINT.H' FILE */
