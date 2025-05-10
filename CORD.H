/****************************************************
 * COPYRIGHT (C)  KISEL STUDIOS. All rights reserved.
 *
 * FILE:          CORD.H.
 * PURPOSE:       Define of Interface coordinates.
 * PROGRAMMER:    Ivan Pashkov, 10-5, IP5.
 * LAST UPDATE:   17.01.2024
 *
 * PROJECT:       Paint Win32 Application
 *
 * NOTIFICATION:  No part of this file can be
 *                changed without agrements
 *                I.Pashkov and Kisel Studios.
 ****************************************************/



#if (defined _MSC_VER) && (_MSC_VER >= 400) 
#pragma once
#endif /* _WIN32 */

#ifndef __CORD_PAINT_H_
#define __CORD_PAINT_H_



/***
 * DEFINE COORDINATES OF UI
 ***/


/* CORD BUTTON SAVE (X, Y) */

#define CORD_BUTTON_SAVE_X       110
#define CORD_BUTTON_SAVE_Y       4


/* CORD BUTTON LOAD (X, Y) */

#define CORD_BUTTON_LOAD_X       170
#define CORD_BUTTON_LOAD_Y       4


/* CORD BUTTON SAVE & LOAD (DX, DY) */

#define CORD_BUTTON_SL_DX        50
#define CORD_BUTTON_SL_DY        20


/* CORD BUTTON CLEAR (X, Y) */

#define CORD_BUTTON_CLEAR_X      230
#define CORD_BUTTON_CLEAR_Y      4


/* CORD BUTTON CLEAR (DX, DY) */

#define CORD_BUTTON_CLEAR_DX     58
#define CORD_BUTTON_CLEAR_DY     20


/* CORD BUTTON DRAW TRIANGLE (X, Y) */

#define CORD_BUTTON_TRIANGLE_X   1050
#define CORD_BUTTON_TRIANGLE_Y   4


/* CORD BUTTON DRAW TRIANGLE (DX, DY) */

#define CORD_BUTTON_TRIANGLE_DX  82
#define CORD_BUTTON_TRIANGLE_DY  20


/* CORD MODE INDICATOR (X, Y) */

#define CORD_MODE_INDICATOR_1_X  1150
#define CORD_MODE_INDICATOR_1_Y  4


/* CORD MODE INDICATOR (DX, DY) */

#define CORD_MODE_INDICATOR_2_X  1200
#define CORD_MODE_INDICATOR_2_Y  4


/* CORD COLOR INDICATOR (X, Y) */

#define CORD_COLOR_INDICATOR_X   1450
#define CORD_COLOR_INDICATOR_Y   704


/* CORD COLOR INDICATOR (DX, DY) */

#define CORD_COLOR_INDICATOR_DX  25
#define CORD_COLOR_INDICATOR_DY  25



#endif /* !__CORD_PAINT_H_ */



/* END OF 'CORD.H' FILE */
