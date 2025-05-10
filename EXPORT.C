/****************************************************
 * COPYRIGHT (C)  KISEL STUDIOS. All rights reserved.
 *
 * FILE:          EXPORT.C.
 * PURPOSE:       File with processing Export & Import Images.
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
#include <string.h>

#include "paint.h"

/* Export Frame to File static function */
static VOID Export(const WCHAR* filename)
{
    FILE *F;
    INT count = W * H;
    DWORD *dst = GetFrame();

    F = _wfopen(filename, L"wb");

    if (F == NULL)
    {
        MessageBox(GetActiveWindow(), L"Export File are not opened!", L"FILE ERROR", MB_ICONERROR);
        return;
    }

    /* For every elements x (DWORD: __xxxxxx) of Frame[] put bytes in file */
    while (count--)
    {
        fputc(IP5_GetBlue(*dst), F);
        fputc(IP5_GetGreen(*dst), F);
        fputc(IP5_GetRed(*dst), F);
        dst++;
    }

    fclose(F);
} /* End of 'Export' function */

/* Import Frame from File static function */
static VOID Import(const WCHAR* filename)
{
    FILE* F;
    INT count = W * H;
    DWORD *dst = GetFrame();

    //memset(Frame, W * H * 4, 0x0);

    F = _wfopen(filename, L"rb");

    if (F == NULL)
    {
        MessageBox(GetActiveWindow(), L"Import File are not opened!", L"FILE ERROR", MB_ICONERROR);
        return;
    }

    /* For every elements x (DWORD: __xxxxxx) of Frame[] read bytes from file */
    while (count--)
        fread(dst++, 3, 1, F);
        //*dst++ = ((DWORD)fgetc(F) & 255) | (((DWORD)fgetc(F) & 255) << 8) | (((DWORD)fgetc(F) & 255) << 16);

    fclose(F);
} /* End of 'Import' function */

/* Open (Import) File with WinAPI Explorer function */
VOID OpenFileFunc(VOID)
{
    OPENFILENAME ofn = { 0 };
    WCHAR FileName[300];

    memset(FileName, 0, 300 * sizeof(WCHAR));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
    ofn.hwndOwner = hWnd;
    ofn.lpstrDefExt = L"*.tpf";
    ofn.lpstrFile = FileName;
    ofn.nMaxFile = sizeof(FileName);
    ofn.lpstrTitle = L"Load Image";
    ofn.lpstrFilter = L"TPF images (*.tpf)\0*.tpf\0All files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;

    if (GetOpenFileName(&ofn))
        Import(ofn.lpstrFile);
} /* End of 'OpenFileFunc' function */

/* Save (Export) File with WinAPI Explorer function */
VOID SaveFileFunc(VOID)
{
    OPENFILENAME ofn = { 0 };
    WCHAR FileName[300];

    memset(FileName, 0, 300 * sizeof(WCHAR));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
    ofn.hwndOwner = hWnd;
    ofn.lpstrDefExt = L"*.tpf";
    ofn.lpstrFile = FileName;
    ofn.nMaxFile = sizeof(FileName);
    ofn.lpstrTitle = L"Save Image";
    ofn.lpstrFilter = L"TPF images (*.tpf)\0*.tpf\0All files (*.*)\0*.*\0";

    ofn.nFilterIndex = 1;

    if (GetSaveFileName(&ofn))
        Export(ofn.lpstrFile);
} /* End of 'SaveFileFunc' function */

/* END OF 'EXPORT.C' FILE */
