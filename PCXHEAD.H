/***************************************************************
 * Copyright (C) 1997
 *    Computer Graphics Support Group of 30 Phys-Math Gymnasium
 ***************************************************************/

/* FILE NAME   : PCXHEAD.H
 * PURPOSE     : PCX (ZSoft) image file format handle types.
 * PROGRAMMER  : Karulin Jaroslaw.
 * LAST UPDATE : 25.06.1997
 * NOTE        : Module prefix 'PCX'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Gymnasium
 */

#ifndef _PCXHEAD_H_
#define _PCXHEAD_H_

#include <commondf.h>

/* PCX file info header (128 bytes) */
typedef struct tagpcxFILEHEAD
{
  BYTE Manuf;        /* PCX file signature always 0x0A */
  BYTE Version;      /* Version:
                      *   0 - 2.50
                      *   2 - 2.80
                      *   3 - 2.80 (no palette)
                      *   4 - Win
                      *   5 - 3.00 */
  BYTE Encode;       /* If 1 -> use RLE , if 0 -> without compress */
  BYTE BitsPerPixel; /* Bits per pixel */
  WORD X1;           /* Image left coordinates */
  WORD Y1;           /* Image top coordinates */
  WORD X2;           /* Image right coordinates */
  WORD Y2;           /* Image bottom coordinates */
  WORD HRes;         /* Horizontal image resolution (dpi) */
  WORD VRes;         /* Vertical image resolution (dpi) */
  BYTE Pal[48];      /* Palette: 3x16 (RGB: 0..255)*/
  BYTE VideoMode;    /* Screen mode number (not used) */
  BYTE PlanesAmount; /* Number of planes (for old ver.(2.5)=0) */
  WORD BytesPerLine; /* Bytes per line */
  WORD PaletteInfo;  /* Palette info : if 1 -> Color , if 2 -> GrayScale */
  WORD ScrHRes;      /* Screen horizontal resolution */
  WORD ScrVRes;      /* Screen vertical resolution */
  BYTE Reserved[54]; /* Not used */
} pcxFILEHEAD;

/***
 * Useful macros
 ***/

/* Determine image width */
#define PCX_GetWidth(PcxHead) ((PcxHead)->X2 - (PcxHead)->X1 + 1)

/* Determine image height */
#define PCX_GetHeight(PcxHead) ((PcxHead)->Y2 - (PcxHead)->Y1 + 1)

#endif /* _PCXHEAD_H_ */

/* END OF 'PCXHEAD.H' FILE */
