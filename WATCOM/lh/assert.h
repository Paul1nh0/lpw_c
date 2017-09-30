/*
 *  FILE: assert.h/cassert
 *
 * =========================================================================
 *
 *                          Open Watcom Project
 *
 *    Copyright (c) 2002-2010 Open Watcom Contributors. All Rights Reserved.
 *    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
 *
 *    This file is automatically generated. Do not edit directly.
 *
 * =========================================================================
 */

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file;
#endif

#ifndef _COMDEF_H_INCLUDED
 #include <_comdef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#undef assert

#ifdef NDEBUG
 #define assert(ignore)    ((void)0)
#else
 _WCRTLINK extern void _assert( char *, char *, int );
 _WCRTLINK extern void _wassert( char *, char *, int );
 _WCRTLINK extern void __assert( int, char *, char *, int );
 _WCRTLINK extern void __wassert( int, char *, char *, int );
 _WCRTLINK extern void _assert99( char *, char *, char *, int );
 _WCRTLINK extern void _wassert99( char *, char *, char *, int );
 _WCRTLINK extern void __assert99( int, char *, char *, char *, int );
 _WCRTLINK extern void __wassert99( int, char *, char *, char *, int );

#if defined(_LINUX_SOURCE) || !defined(NO_EXT_KEYS) /* extensions enabled */
 #ifdef __C89
  #ifdef _UNICODE
   #define assert(expr)  ((expr)?(void)0:_wassert(#expr,__FILE__,__LINE__))
  #else
   #define assert(expr)  ((expr)?(void)0:_assert(#expr,__FILE__,__LINE__))
  #endif
 #else
  #ifdef _UNICODE
   #define assert(expr)  ((expr)?(void)0:_wassert99(#expr,__func__,__FILE__,__LINE__))
  #else
   #define assert(expr)  ((expr)?(void)0:_assert99(#expr,__func__,__FILE__,__LINE__))
  #endif
 #endif
#else  /* extensions disabled */
 #ifdef __C89
  #ifdef _UNICODE
   #define assert(expr)  __wassert(expr,#expr,__FILE__,__LINE__)
  #else
   #define assert(expr)  __assert(expr,#expr,__FILE__,__LINE__)
  #endif
 #else
  #ifdef _UNICODE
   #define assert(expr)  __wassert99(expr,#expr,__func__,__FILE__,__LINE__)
  #else
   #define assert(expr)  __assert99(expr,#expr,__func__,__FILE__,__LINE__)
  #endif
 #endif
#endif /* extensions disabled */

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
