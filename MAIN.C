/****************************************************
 * COPYRIGHT (C)  KISEL STUDIOS. All rights reserved.
 *
 * FILE:          MAIN.C.
 * PURPOSE:       Main File of Project.
 * PROGRAMMER:    Ivan Pashkov, 10-5, IP5.
 * LAST UPDATE:   17.01.2024
 * 
 * PROJECT:       Paint Win32 Application
 * 
 * NOTIFICATION:  No part of this file can be
 *                changed without agrements
 *                I.Pashkov and Kisel Studios.
 ****************************************************/

#include <glut.h>  

#include "paint.h"

/* Main window handle global variable */
HWND hWnd;

/* OpenGL Display callback function
 * Special function for initializing the GLUT callback
 */
static VOID InitDisplay( VOID ) 
{
  static INT a = 1;

  if (a)
    a--, Display();

  //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  // <EMPTY>
  // 
  // This function is a stub for GLUT
  // Real function that draws something:
  // CONTROLLERS.C -> VOID Display( VOID )
  //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
} /* End of 'InitDisplay' function */

/* Main of Project function */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT CmdShow )
{
  INT argc = 0;
  CHAR *argv[] = {CmdLine};

  /* Check memory leaks in Debug mode */
  SetDbgMemHooks();

  /* Load Font */
  LoadFont();

  /* Initialization */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

  /* Create Window */
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(W, H + 32);
  glutCreateWindow("PAINT");
  hWnd = FindWindowA(NULL, "PAINT");

  /* Base draw */
#ifdef __DEBUG_PAINT_
  //MessageBox(hWnd, L"This is Paint on OpenGL!", L"PAINT", MB_ICONINFORMATION | MB_OK);
#ifdef _DEBUG  
  OutputDebugString(L"\nThis is Paint on OpenGL\n\nCopyright (C) Kisel Studios 2021-2024. All rights reserved\n\n");
#endif /* _DEBUG */
#endif /* __DEBUG_PAINT_ */
  glClearColor(0, 0, 0, 1);
  BaseDraw();

  /* Keyboard & Mouse & Display Callback functions init */
  glutMotionFunc(Mouse);
  glutDisplayFunc(InitDisplay);
  glutKeyboardFunc(Keyboard);
  glutSpecialFunc(Special);
  glutPassiveMotionFunc(SMouse);
  glutMouseFunc(PMouse);
  glutReshapeFunc(Reshape);

  /* First drawing pixels on display */
  Display();

  /* Cycle */
  glutMainLoop();
} /* End of 'WinMain' function */

/* END OF 'MAIN.C' FILE */
