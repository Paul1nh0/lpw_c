/*
 *  pmwp.h      OS/2 Presentation Manager Workplace include file
 *              for 32-bit development.
 *
 * =========================================================================
 *
 *                          Open Watcom Project
 *
 * Copyright (c) 2004-2010 The Open Watcom Contributors. All Rights Reserved.
 *
 *    This file is automatically generated. Do not edit directly.
 *
 * =========================================================================
 */

#ifndef PMWP_INCLUDED
#define PMWP_INCLUDED

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file;
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define INCL_WPERRORS
#include <pmerr.h>

#ifdef INCL_WINWORKPLACE
    #define INCL_WPCLASS
#endif

typedef LHANDLE HOBJECT;

#if defined(INCL_WPCLASS) || !defined(INCL_NOCOMMON)

#ifndef LOCATION_DESKTOP
    #define LOCATION_DESKTOP ((PSZ)0xFFFF0001)
#endif

#define CCHMAXCLASS 3

#define QC_First 0
#define QC_FIRST 0
#define QC_Next  1
#define QC_NEXT  1
#define QC_Last  2
#define QC_LAST  2

#define CO_FAILIFEXISTS     0
#define CO_REPLACEIFEXISTS  1
#define CO_UPDATEIFEXISTS   2

typedef struct _OBJECTIMAGE {
    HPOINTER hptrObject;
} OBJECTIMAGE, *POBJECTIMAGE;

typedef struct _OBJCLASS {
    struct _OBJCLASS *pNext;
    PSZ pszClassName;
    PSZ pszModName;
} OBJCLASS, *POBJCLASS;

HOBJECT APIENTRY WinCopyObject(HOBJECT,HOBJECT,ULONG);
HOBJECT APIENTRY WinCreateObject(PCSZ,PCSZ,PCSZ,PCSZ,ULONG);
HOBJECT APIENTRY WinCreateShadow(HOBJECT,HOBJECT,ULONG);
BOOL    APIENTRY WinDeregisterObjectClass(PCSZ);
BOOL    APIENTRY WinDestroyObject(HOBJECT);
BOOL    APIENTRY WinEnumObjectClasses(POBJCLASS,PULONG);
BOOL    APIENTRY WinIsSOMDDReady(VOID);
BOOL    APIENTRY WinIsWPDServerReady(VOID);
HOBJECT APIENTRY WinMoveObject(HOBJECT,HOBJECT,ULONG);
BOOL    APIENTRY WinOpenObject(HOBJECT,ULONG,BOOL);
BOOL    APIENTRY WinQueryActiveDesktopPathname(PCSZ,ULONG);
HOBJECT APIENTRY WinQueryObject(PCSZ);
BOOL    APIENTRY WinQueryObjectPath(HOBJECT,PCSZ,ULONG);
BOOL    APIENTRY WinRegisterObjectClass(PCSZ,PCSZ);
BOOL    APIENTRY WinReplaceObjectClass(PCSZ,PCSZ,BOOL);
APIRET  APIENTRY WinRestartSOMDD(BOOL);
APIRET  APIENTRY WinRestartWPDServer(BOOL);
BOOL    APIENTRY WinSaveObject(HOBJECT,BOOL);
BOOL    APIENTRY WinSetObjectData(HOBJECT,PCSZ);

#endif

#if !defined(INCL_NOCOMMON)

#define  SETTINGS_PAGE_NUMBERS 1

typedef struct _PAGEINFO {
    ULONG   cb;
    HWND    hwndPage;
    PFNWP   pfnwp;
    ULONG   resid;
    PVOID   pCreateParams;
    USHORT  dlgid;
    USHORT  usPageStyleFlags;
    USHORT  usPageInsertFlags;
    USHORT  usSettingsFlags;
    PSZ     pszName;
    USHORT  idDefaultHelpPanel;
    USHORT  usReserved2;
    PSZ     pszHelpLibraryName;
    PUSHORT pHelpSubtable;
    HMODULE hmodHelpSubtable;
    ULONG   ulPageInsertId;
} PAGEINFO, *PPAGEINFO;

typedef struct _ICONPOS {
    POINTL ptlIcon;
    CHAR   szIdentity[1];
} ICONPOS, *PICONPOS;

BOOL     APIENTRY WinFreeFileIcon(HPOINTER);
HPOINTER APIENTRY WinLoadFileIcon(PCSZ,BOOL);
HPOINTER APIENTRY WinLoadFileIconN(PCSZ,BOOL,ULONG);
BOOL     APIENTRY WinRestoreWindowPos(PCSZ,PCSZ,HWND);
BOOL     APIENTRY WinShutdownSystem(HAB,HMQ);
BOOL     APIENTRY WinStoreWindowPos(PCSZ,PCSZ,HWND);

#ifdef INCL_WINPOINTERS

BOOL     APIENTRY WinSetFileIcon(PCSZ,PICONINFO);
BOOL     APIENTRY WinSetFileIconN(PCSZ,PICONINFO,ULONG);

#endif

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
