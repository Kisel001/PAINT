/****************************************************
 * COPYRIGHT (C)  KISEL STUDIOS. All rights reserved.
 *
 * FILE:          PCX.C.
 * PURPOSE:       File with Func for Load PCX image.
 * PROGRAMMER:    Ivan Pashkov, 10-5, IP5.
 * LAST UPDATE:   18.01.2024
 *
 * PROJECT:       Paint Win32 Application
 *
 * NOTIFICATION:  No part of this file can be
 *                changed without agrements
 *                I.Pashkov and Kisel Studios.
 ****************************************************/

#include <stdio.h>

#include "paint.h"

#ifdef _MSC_VER
#pragma pack(push)
#pragma pack(4)
#endif // _MSC_VER
#include <pcxhead.h>
#ifdef _MSC_VER
#pragma pack(pop)
#endif // _MSC_VER

#ifdef soutput
#undef soutput
#endif /* soutput() */
/* Get R, G, B code by NOP & BPP function */
#define soutput() \
for (i = 0; i < SW; i++)                                                                                  \
{                                                                                                         \
  if (NOP == 1 && BPP == 24)                                                                              \
    R = Planes[0][i * 3], G = Planes[0][i * 3 + 1], B = Planes[0][i * 3 + 2];                             \
  else if (NOP == 3 && BPP == 8)                                                                          \
    R = Planes[0][i], G = Planes[1][i], B = Planes[2][i];                                                 \
  else if (NOP == 1 && BPP == 8)                                                                          \
  {                                                                                                       \
    v = Planes[0][i];                                                                                     \
    R = Palette[v % 255][0], G = Palette[v % 255][1], B = Palette[v % 255][2];                            \
  }                                                                                                       \
  else if (NOP == 1 && BPP == 4)                                                                          \
  {                                                                                                       \
    v = (Planes[0][i >> 1] >> ((1 - (i & 1)) << 2)) & 0x0F;                                               \
    R = Head.Pal[3 * v + 0], G = Head.Pal[3 * v + 1], B = Head.Pal[3 * v + 2];                            \
  }                                                                                                       \
  else if (NOP == 1 && BPP == 1)                                                                          \
  {                                                                                                       \
    v = (Planes[0][i >> 3] >> (7 - (i & 7))) & 1;                                                         \
    R = Head.Pal[3 * v + 0], G = Head.Pal[3 * v + 1], B = Head.Pal[3 * v + 2];                            \
  }                                                                                                       \
  else if (NOP == 4 && BPP == 1)                                                                          \
  {                                                                                                       \
    v = (Planes[0][i >> 3] >> (7 - (i & 7))) & 1;                                                         \
    v |= ((Planes[1][i >> 3] >> (7 - (i & 7))) & 1) << 1;                                                 \
    v |= ((Planes[2][i >> 3] >> (7 - (i & 7))) & 1) << 2;                                                 \
    v |= ((Planes[3][i >> 3] >> (7 - (i & 7))) & 1) << 3;                                                 \
    R = Head.Pal[3 * v + 0], G = Head.Pal[3 * v + 1], B = Head.Pal[3 * v + 2];                            \
  }                                                                                                       \
  else if (NOP = 1 && BPP == 2)                                                                           \
  {                                                                                                       \
    v = (Planes[0][i >> 1] >> ((1 - (i & 1)) << 2)) & 0x03;                                               \
    R = Head.Pal[3 * v + 0], G = Head.Pal[3 * v + 1], B = Head.Pal[3 * v + 2];                            \
  }                                                                                                       \
  else                                                                                                    \
  {                                                                                                       \
    MessageBox(hWnd, L"Internal picture parameters are set incorrectly!", L"IMAGE ERROR", MB_ICONERROR);  \
    free(bulk);                                                                                           \
    fclose(F);                                                                                            \
    return FALSE;                                                                                         \
    /*R = 0, G = 255, B = 0; */                                                                           \
  }                                                                                                       \
  PutPixel(i + X0 - SW / 2, y + Y0 - SH / 2, IP5_RGB(R, G, B), 0);                                        \
}  /* End of 'soutout' function */

/* Draw PCX image static function */
static BOOL DrawPCX( const WCHAR *Filename, INT X0, INT Y0 )
{
  FILE *F;
  pcxFILEHEAD Head;
  INT SW, SH, p, x = 0, y = 0, rep, NOP, i, v, BPP, R, G, B, BPL;
  BYTE bt, C;
  BYTE *bulk, **Planes;
  static BYTE Palette[256][3];
    
  if ((F = _wfopen(Filename, L"rb")) == NULL)
  {
    MessageBox(hWnd, L"Image file are not loaded!", L"IMAGE ERROR", MB_ICONERROR);
    return FALSE;
  }

  fread(&Head, sizeof(pcxFILEHEAD), 1, F);

  /* Incorrect picture parameters */
  if (Head.Manuf != 0x0A || Head.Encode != 1)
  {
    fclose(F);
    MessageBox(hWnd, L"Internal picture parameters are set incorrectly!", L"IMAGE ERROR", MB_ICONERROR);
    return FALSE;
  }

  SW = Head.X2 - Head.X1 + 1;
  SH = Head.Y2 - Head.Y1 + 1;
  NOP = Head.PlanesAmount;
  BPP = Head.BitsPerPixel;
  BPL = Head.BytesPerLine;

  bulk = malloc(sizeof(BYTE) * Head.PlanesAmount +
                Head.BytesPerLine * Head.PlanesAmount * 2);

  if (bulk == NULL)
  {
      fclose(F);
      MessageBox(hWnd, L"Failed to allocate memory for the program!", L"MEMORY ERROR", MB_ICONERROR);
      return FALSE;
  }

  /* Assigning pointers to the memory buffer */
  Planes = (BYTE**)bulk;
  for (p = 0; p < Head.PlanesAmount; p++)
      Planes[p] = (BYTE*)(bulk + sizeof(BYTE*) * Head.PlanesAmount +
          Head.BytesPerLine * p);
    
  //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  // The palette is at the end of the file. 
  // It's a must read
  //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  if (BPP * NOP == 8)
  {
      fseek(F, -769, SEEK_END);
      fread(&C, 1, 1, F);
      fread(Palette, 3, 256, F);
      fseek(F, sizeof(pcxFILEHEAD), SEEK_SET);
  }

  p = 0;

  while (y < SH)
  {
      bt = fgetc(F);
      if ((bt & 0xC0) == 0xC0)
      {
          rep = bt & 63;
          bt = fgetc(F);
      }
      else
          rep = 1;
      while (rep-- > 0)
      {
          Planes[p][x++] = bt;
          if (x >= BPL)
          {
              x = 0;
              p++;

              if (p >= NOP) // Reading the horizontal line is finished -> draw it
              {
                  soutput();
                  y++;
                  p = 0;
              }
              if (y >= SH) // The picture is fully read
                  break;
          }
      }
  }

  free(bulk);
  fclose(F);

  return TRUE;
} /* End of 'DrawPCX' function */

/* Load PCX Image function */
VOID LoadPCXImage(INT X0, INT Y0)
{
  OPENFILENAME ofn = { 0 };
  WCHAR FileName[300];

  memset(FileName, 0, 300 * sizeof(WCHAR));

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
  ofn.hwndOwner = hWnd;
  ofn.lpstrDefExt = L"*.pcx";
  ofn.lpstrFile = FileName;
  ofn.nMaxFile = sizeof(FileName);
  ofn.lpstrTitle = L"Load Image";
  ofn.lpstrFilter = L"PCX images (*.pcx)\0*.pcx\0All files (*.*)\0*.*\0";
  ofn.nFilterIndex = 1;

  if (GetOpenFileName(&ofn))
      DrawPCX(ofn.lpstrFile, X0, Y0);
} /* End of 'LoadPCXImage' function */

/* END OF 'PCX.C' FILE */
