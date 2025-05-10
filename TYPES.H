/****************************************************
 * COPYRIGHT (C)  KISEL STUDIOS. All rights reserved.
 *
 * FILE:          TYPES.H. 
 * PURPOSE:       Header File with typedefs for Project.
 * PROGRAMMER:    Ivan Pashkov, 10-5, IP5.
 * LAST UPDATE:   18.01.2024
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

#ifndef __PAINT_TYPES_H_
#define __PAINT_TYPES_H_

#include <commondf.h>


#ifdef VOID
#undef VOID
#endif /* VOID */
/* Void type big verison */
typedef void           VOID;


#ifndef UL
/* Unsigned int type short version */
typedef unsigned int   UL;
#endif /* !UL */


#ifndef UC
/* Unsigned char type short version */
typedef unsigned char  UC;
#endif /* !UC */


#ifndef DBL
/* Double type short version */
typedef double         DBL;
#endif /* !DBL */


#ifndef FLT
/* Float type short version */
typedef float          FLT;
#endif /* !DBL */


#ifndef TIME
/* time_t type big version */
typedef long           TIME;
#endif /* !TIME */



#endif /* !__PAINT_TYPES_H_ */



/* END OF 'TYPES.H' FILE */
