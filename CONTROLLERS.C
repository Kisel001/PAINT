/****************************************************
 * COPYRIGHT (C)  KISEL STUDIOS. All rights reserved.
 *
 * FILE:          CONTROLLERS.C. 
 * PURPOSE:       File with OpenGL Controllers Callback Functions.
 * PROGRAMMER:    Ivan Pashkov, 10-5, IP5.
 * LAST UPDATE:   21.01.2024
 *
 * PROJECT:       Paint Win32 Application
 *
 * NOTIFICATION:  No part of this file can be
 *                changed without agrements
 *                I.Pashkov and Kisel Studios.
 ****************************************************/

#include <glut.h>

#include "paint.h"
#include "common_colors.h"
#include "cord.h"

/* Static variables for correct work System of Drawing */
static BOOL oldState;
static BOOL oldState1 = 0;

/* Static variables for Text Mode */
static INT STRING_X = 0;       /* X coordinate in text mode */
static INT STRING_Y = 0;       /* Y coordinate in text mode */
static UINT COUNT_LETTERS = 0; /* Variable with Count of Letters in Text Mode */

/* Display drawing function */
VOID Display( VOID )
{
    /* Cleaning the rear Debug screen */
    glClear(GL_COLOR_BUFFER_BIT);
    
    /* Painting Pixels */
    glRasterPos2d(-1, 1);
    glPixelZoom(1, -1);
    glDrawPixels(W, H + 32, GL_BGRA_EXT, GL_UNSIGNED_BYTE,
        //-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        // Text mode is activated ?
        // If yes -> Copy txt mode
        // Else use base Frame buffer
        //-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        IsActiveTextMode == 1 ? CopyBuffer() : GetFrame());

    /* Cycle Completion */
    glFinish();

    /* Redisplay window */
    glutSwapBuffers();
    glutPostRedisplay();
} /* End of 'Display' function */

/* OpenGL Keyboard callback function */
VOID Keyboard( UC Key, INT X, INT Y )
{
    UC z = 0;

    /* If Text Mode Activing */
    if (IsActiveTextMode == 1)
    {
        /* EXIT FROM STRING MODE */
        if (Key == 27 || // Escape
            Key == 13)   // Enter
            CloseTxtMode();
        /* The user pressed a valid character key */
        else if (Key >= ' ' && Key <= '~')
        {
            DrawLetter(STRING_X, STRING_Y, Key, Color, 0);
            STRING_X += 8;
            COUNT_LETTERS++;
        }
        /* If Key == BACKSPACE -> Del Symbol */
        else if (Key == 8 && COUNT_LETTERS > 0) // 8 == BackSpace
        {
            STRING_X -= 8;
            FillTextRect(STRING_X, STRING_Y, 8, 16, 0);
            COUNT_LETTERS--;
        }
        /* The text reached the edge of the screen */
        if (STRING_X >= W - 8)
            CloseTxtMode();
        if (STRING_X < 1)
            CloseTxtMode();
    }
    else // Text mode not actived
    {
        /* EXIT FROM PROGRAMM */
        if (Key == 27) // Escape
            if (MessageBox(hWnd, L"Did you want leave from program?", L"PAINT", MB_ICONQUESTION | MB_YESNO) == IDYES)
                exit(0);

        /* PAINTING MODE */
        if (Key == 'c' || Key == 'C') // Default Circle Mode
        {
            Painting_Mode = 1;
            Rect(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, 110, 20, GFX_BLACK);
            DrawLetters(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, " PENCIL", GFX_WHITE, 1);
        }
        else if (Key == 't' || Key == 'T') // Transpanence Circle Mode
        {
            Rect(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, 110, 20, GFX_BLACK);
            DrawLetters(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, " TRANSPANENCE", GFX_WHITE, 1);
            Painting_Mode = 2;
        }
        else if (Key == 'm' || Key == 'M') // Mixing Circle Mode
        {
            Rect(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, 110, 20, GFX_BLACK);
            DrawLetters(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, " MIXING", GFX_WHITE, 1);
            Painting_Mode = 3;
        }
        /* PIPETTE */
        if (Key == 'p' || Key == 'P')
            PipetteFunc(X, Y), z++;

        /* LOAD PCX IMAGE */
        if (Key == 'i' || Key == 'I')
            LoadPCXImage(X, Y);

        /* COLOR */
        if (Key == 'r' || Key == 'R') // Red
            ChangeColorFunc(255, 0, 0), z++;
        else if (Key == 'y' || Key == 'Y') // Yellow
            ChangeColorFunc(255, 255, 0), z++;
        else if (Key == 'w' || Key == 'W') // White
            ChangeColorFunc(255, 255, 255), z++;
        else if (Key == 'b' || Key == 'B') // Blue
            ChangeColorFunc(0, 0, 255), z++;
        else if (Key == 'o' || Key == 'O') // Orange
            ChangeColorFunc(255, 128, 0), z++;
        else if (Key == 'g' || Key == 'G') // Green
            ChangeColorFunc(0, 255, 0), z++;
        else if (Key == 'd' || Key == 'D') // Dark
            ChangeColorFunc(0, 0, 0), z++;
        else if (Key == 'l' || Key == 'L') // Light Blue
            ChangeColorFunc(0, 191, 255), z++;
        else if (Key == 'v' || Key == 'V') // Violet
            ChangeColorFunc(180, 0, 255), z++;
        else if (Key == '0') // Custom Color
            NewCustomColorFunc(), z++;

        /* If Color Changed */
        if (z != 0)
            PrintColorCode(), DrawColorIndicatorColor();

        /* RADIUS */
        if (Key == '1')
            COMMON_RAD = 2;
        else if (Key == '2')
            COMMON_RAD = 3;
        else if (Key == '3')
            COMMON_RAD = 5;
        else if (Key == '4')
            COMMON_RAD = 10;
        else if (Key == '5')
            COMMON_RAD = 15;
        else if (Key == '6')
            COMMON_RAD = 20;
        else if (Key == '7')
            COMMON_RAD = 25;
        else if (Key == '8')
            COMMON_RAD = 30;
        else if (Key == '9')
            COMMON_RAD = 40;

        /* FILLING MODE */
        if (Key == 'F' || Key == 'f')
            if (X < 1 || Y < 1 || X > W - 1 || Y > H - 1)
                ;
            else
                NewFillingFunc(X, Y, Color, GetColor(X, Y));

        if (Key == 'A' || Key == 'a')
          MessageBox(hWnd, L"Copyright (C) Ivan Pashkov, PML #30, 11-5. All rights reserved.", L"PAINT", MB_ICONINFORMATION);
    }

    Display();
} /* End of 'Keyboard' function */

/* OpenGL special keys of Keyboard callback function */
VOID Special(INT Key, INT X, INT Y)
{
    /* <EMPTY> */
} /* End of 'Special' function */

/* OpenGL Mouse Motion callback function */
VOID Mouse(INT x, INT y)
{
    static INT oldX, oldY;

    // If actived Draw Triagle Mode -> Return;
    if (TRIANGLE_STATE > 0)
        return;

    if (oldState != oldState1 && oldState1 == 0)
    {
        oldX = x;
        oldY = y;
    }

    oldState1 = oldState;

    if (IsActiveTextMode != 0)
        CloseTxtMode();
    
    if (x < W && y < H + 2)
      PutLine(x, y, oldX, oldY, Color, Painting_Mode);
    PrintCoordinates(x, y);

    oldX = x;
    oldY = y;

    Display();
} /* End of 'Mouse' function */

/* OpenGL Mouse Passive Motion callback function */
VOID SMouse(INT X, INT Y)
{
    oldState1 = oldState;
    PrintCoordinates(X, Y);

    Display();
} /* End of 'SMouse' function */

/* OpenGL Mouse Button Press callback function */
VOID PMouse(INT B, INT STATE, INT X, INT Y)
{   
    //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    // Special Bool Tag.
    // If the click was to initialize the point of the triangle,
    // then there is no need to update the state for drawing.
    //
    // FALSE - no activy
    // TRUE - activy
    //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    BOOL StateTagTriangle = FALSE;

    if (TRIANGLE_STATE > 0 && !STATE && X < W && Y < H)
        AddTriangleCoordinated(X, Y), StateTagTriangle = TRUE;

    else if (X >= W || Y >= H - 12)
       ;

    else if (!STATE && !IsActiveTextMode)
    {
        IsActiveTextMode = 1; 
        STRING_X = X; 
        STRING_Y = Y;

        COUNT_LETTERS = 0;
        Rect(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, 110, 20, GFX_BLACK);
        DrawLetters(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, " TEXT", GFX_WHITE, 1);
    }

    /* IF PRESSED SAVE BUTTON -> SAVE FILE */
    if (!STATE && X >= CORD_BUTTON_SAVE_X &&
        Y >= CORD_BUTTON_SAVE_Y + H &&
        X <= CORD_BUTTON_SAVE_X + CORD_BUTTON_SL_DX &&
        Y <= CORD_BUTTON_SAVE_Y + H + CORD_BUTTON_SL_DY)
        SaveFileFunc();

    /* IF PRESSED LOAD BUTTON -> OPEN FILE */
    else if (!STATE && X >= CORD_BUTTON_LOAD_X &&
        Y >= CORD_BUTTON_LOAD_Y + H &&
        X <= CORD_BUTTON_LOAD_X + CORD_BUTTON_SL_DX &&
        Y <= CORD_BUTTON_LOAD_Y + H + CORD_BUTTON_SL_DY)
        OpenFileFunc();

    /* IF PRESSED CLEAR BUTTON -> CLEAR WINDOW */
    else if (!STATE && X >= CORD_BUTTON_CLEAR_X &&
        Y >= CORD_BUTTON_CLEAR_Y + H &&
        X <= CORD_BUTTON_CLEAR_X + CORD_BUTTON_CLEAR_DX &&
        Y <= CORD_BUTTON_CLEAR_Y + H + CORD_BUTTON_CLEAR_DY)
        ClearWindowFunc();

    /* IF PRESSED TRIANGLE BUTTON -> GO TO DRAW TRIANGLE MODE */
    else if (!STATE && X >= CORD_BUTTON_TRIANGLE_X &&
        Y >= CORD_BUTTON_TRIANGLE_Y + H &&
        X <= CORD_BUTTON_TRIANGLE_X + CORD_BUTTON_TRIANGLE_DX &&
        Y <= CORD_BUTTON_TRIANGLE_Y + H + CORD_BUTTON_CLEAR_DY)
    {
        Rect(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, 110, 20, GFX_BLACK);
        DrawLetters(CORD_MODE_INDICATOR_2_X, H + CORD_MODE_INDICATOR_2_Y, " TRIANGLE :: 1", GFX_WHITE, 1);
        TRIANGLE_STATE = 1;
    }

    /* IF PRESSED COLOR INDICATOR -> CUSTOM CHANGE COLOR */
    else if (!STATE && X >= CORD_COLOR_INDICATOR_X &&
        Y >= CORD_COLOR_INDICATOR_Y &&
        X <= CORD_COLOR_INDICATOR_X + CORD_COLOR_INDICATOR_DX &&
        Y <= CORD_COLOR_INDICATOR_Y + CORD_COLOR_INDICATOR_DY)
    {
        NewCustomColorFunc();
        PrintColorCode();
        DrawColorIndicatorColor();
    }
    
    else if (StateTagTriangle == FALSE)
        oldState = !STATE; // 1 - OnButton, 0 - DisButton

    Display();
} /* End of 'PMouse' function */

/* OpenGL Reshape window callback function */
VOID Reshape( INT widht, INT height )
{
  glViewport(0, 0, widht, height);
  
  Display();
} /* End of 'Reshape' function */

/* END OF 'CONTROLLES.C' FILE */
