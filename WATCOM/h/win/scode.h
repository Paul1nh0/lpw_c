/*
 *  scode.h     Component Object Model (COM) error codes
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

#ifndef __SCODE_H__
#define __SCODE_H__

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file;
#endif

/* Primitive data types */
typedef long        SCODE;
typedef SCODE       *PSCODE;
typedef void FAR    *HRESULT;

/* Success value */
#define NOERROR 0

/* Severity codes */
#define SEVERITY_SUCCESS    0
#define SEVERITY_ERROR      1

/* Macros for working with COM error codes */
#define SUCCEEDED( x )      ((SCODE)(x) >= 0)
#define FAILED( x )         ((SCODE)(x) < 0)
#define SCODE_CODE( x )     ((x) & 0x0000FFFF)
#define SCODE_FACILITY( x ) (((x) >> 16) & 0x00001FFF)
#define SCODE_SEVERITY( x ) (((x) >> 31) & 0x00000001)
#define MAKE_SCODE( p1, p2, p3 ) \
    ((SCODE)(((unsigned long)(p1) << 31) | ((unsigned long)(p2) << 16) | \
    ((unsigned long)(p3))))

/* Facility codes */
#define FACILITY_NULL       0x0000
#define FACILITY_RPC        0x0001
#define FACILITY_DISPATCH   0x0002
#define FACILITY_STORAGE    0x0003
#define FACILITY_ITF        0x0004

/* COM error codes */
#define S_OK            0L
#define S_FALSE         MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_NULL, 1 )
#define E_UNEXPECTED    MAKE_SCODE( SEVERITY_ERROR, FACILITY_NULL, 0xFFFF )
#define E_NOTIMPL       MAKE_SCODE( SEVERITY_ERROR, FACILITY_NULL, 1 )
#define E_OUTOFMEMORY   MAKE_SCODE( SEVERITY_ERROR, FACILITY_NULL, 2 )
#define E_INVALIDARG    MAKE_SCODE( SEVERITY_ERROR, FACILITY_NULL, 3 )
#define E_NOINTERFACE   MAKE_SCODE( SEVERITY_ERROR, FACILITY_NULL, 4 )
#define E_POINTER       MAKE_SCODE( SEVERITY_ERROR, FACILITY_NULL, 5 )
#define E_HANDLE        MAKE_SCODE( SEVERITY_ERROR, FACILITY_NULL, 6 )
#define E_ABORT         MAKE_SCODE( SEVERITY_ERROR, FACILITY_NULL, 7 )
#define E_FAIL          MAKE_SCODE( SEVERITY_ERROR, FACILITY_NULL, 8 )
#define E_ACCESSDENIED  MAKE_SCODE( SEVERITY_ERROR, FACILITY_NULL, 9 )

/* OLE error codes */
#define OLE_E_FIRST MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x0000 )
#define OLE_E_LAST  MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x00FF )
#define OLE_S_FIRST MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x0000 )
#define OLE_S_LAST  MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x00FF )

/* Drag/drop error codes */
#define DRAGDROP_E_FIRST    MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x0100 )
#define DRAGDROP_E_LAST     MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x010F )
#define DRAGDROP_S_FIRST    MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x0100 )
#define DRAGDROP_S_LAST     MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x010F )

/* Class factory error codes */
#define CLASSFACTORY_E_FIRST    MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x0110 )
#define CLASSFACTORY_E_LAST     MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x011F )
#define CLASSFACTORY_S_FIRST    MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x0110 )
#define CLASSFACTORY_S_LAST     MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x011F )

/* Marshalling error codes */
#define MARSHAL_E_FIRST MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x0120 )
#define MARSHAL_E_LAST  MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x012F )
#define MARSHAL_S_FIRST MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x0120 )
#define MARSHAL_S_LAST  MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x012F )

/* Data error codes */
#define DATA_E_FIRST    MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x0130 )
#define DATA_E_LAST     MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x013F )
#define DATA_S_FIRST    MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x0130 )
#define DATA_S_LAST     MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x013F )

/* View error codes */
#define VIEW_E_FIRST    MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x0140 )
#define VIEW_E_LAST     MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x014F )
#define VIEW_S_FIRST    MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x0140 )
#define VIEW_S_LAST     MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x014F )

/* Registration database error codes */
#define REGDB_E_FIRST   MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x0150 )
#define REGDB_E_LAST    MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x015F )
#define REGDB_S_FIRST   MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x0150 )
#define REGDB_S_LAST    MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x015F )

/* Cache error codes */
#define CACHE_E_FIRST   MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x0170 )
#define CACHE_E_LAST    MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x017F )
#define CACHE_S_FIRST   MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x0170 )
#define CACHE_S_LAST    MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x017F )

/* OLE object error codes */
#define OLEOBJ_E_FIRST  MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x0180 )
#define OLEOBJ_E_LAST   MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x018F )
#define OLEOBJ_S_FIRST  MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x0180 )
#define OLEOBJ_S_LAST   MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x018F )

/* Client site error codes */
#define CLIENTSITE_E_FIRST  MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x0190 )
#define CLIENTSITE_E_LAST   MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x019F )
#define CLIENTSITE_S_FIRST  MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x0190 )
#define CLIENTSITE_S_LAST   MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x019F )

/* In-place error codes */
#define INPLACE_E_FIRST MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x01A0 )
#define INPLACE_E_LAST  MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x01AF )
#define INPLACE_S_FIRST MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x01A0 )
#define INPLACE_S_LAST  MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x01AF )

/* Enumeration error codes */
#define ENUM_E_FIRST    MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x01B0 )
#define ENUM_E_LAST     MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x01BF )
#define ENUM_S_FIRST    MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x01B0 )
#define ENUM_S_LAST     MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x01BF )

/* OLE 1.0 conversion error codes */
#define CONVERT10_E_FIRST   MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x01C0 )
#define CONVERT10_E_LAST    MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x01CF )
#define CONVERT10_S_FIRST   MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x01C0 )
#define CONVERT10_S_LAST    MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x01CF )

/* Clipboard error codes */
#define CLIPBRD_E_FIRST MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x01D0 )
#define CLIPBRD_E_LAST  MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x01DF )
#define CLIPBRD_S_FIRST MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x01D0 )
#define CLIPBRD_S_LAST  MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x01DF )

/* Moniker error codes */
#define MK_E_FIRST  MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x01E0 )
#define MK_E_LAST   MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x01EF )
#define MK_S_FIRST  MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x01E0 )
#define MK_S_LAST   MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x01EF )

/* COM error codes */
#define CO_E_FIRST  MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x01F0 )
#define CO_E_LAST   MAKE_SCODE( SEVERITY_ERROR, FACILITY_ITF, 0x01FF )
#define CO_S_FIRST  MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x01F0 )
#define CO_S_LAST   MAKE_SCODE( SEVERITY_SUCCESS, FACILITY_ITF, 0x01FF )

/* Functions in COMPOBJ.DLL */
STDAPI  PropagateResult( HRESULT, SCODE );

/* Functions implemented as macros */
#define GetScode( x )           ((SCODE)(x) & 0x800FFFFF)
#define ResultFromScode( x )    ((HRESULT)((SCODE)(x) & 0x800FFFFF))

#endif /* __SCODE_H__ */
