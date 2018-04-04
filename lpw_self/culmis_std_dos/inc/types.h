/*
 * $Header:   H:\devkit.dos\vcs\include\sys\types.h_v   1.18   20 May 1994 11:58:52   paul  $
 */

/*
 * INCLUDE/SYS/TYPES.H - Definitions of basic system data types.
 *
 * Copyright (C) 1986-1994 by FTP Software, Inc.  All rights reserved.
 * 
 * This software is furnished under a license and may be used and copied
 * only in accordance with the terms of such license and with the
 * inclusion of the above copyright notice. This software or any other
 * copies thereof may not be provided or otherwise made available to any
 * other person. No title to and ownership of the software is hereby
 * transferred.
 * 
 * The information in this software is subject to change without notice
 * and should not be construed as a commitment by FTP Software, Inc.
 *
 * EDIT HISTORY:
 * 9/2/87	romkey		Changed ino_t from u_long to unsigned short
 *				for MSC compatability.
 * 05-Jun-88	jbvb	Remove size_t definition (for MSC 5.1).
 * 27OCT89	stev	add 4.3 stuff for select()
 * 24JAN90	stev	add #define _SYS_TYPES_ to avoid multiple includes
 * 05-Apr-91    Ben     Put '_' in front of time_t_defined to match msc
 * 13-Jun-91	wcl	changed '1' to '1L' in FD_SET, FD_ISSET, FD_CLR
 * 27-Feb-92	Ben	Added #ifdefs for ino_t, dev_t, & off_t
 * 24-Aug-92	paul	added MSC7-compatible typedefs _ino_t, _dev_t, _off_t
 * 04-Oct-92	rcq	added ifdefs to handle different time_t definitions
 *			between MSC6, MSC7 and other compilers
 */

#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H
#define INVALID_SOCKET  -1

/* First pull in the typedefs from the vendors' versions of <sys/types.h> */

/* Also defined in <time.h> */
#if	!defined(_TIME_T_DEFINED) && !defined (_TIME_T) && \
	!defined(_TIME_T_DEFINED_)
#if	(defined(_MSC_VER) && (_MSC_VER >= 700)) || (defined(__WATCOMC__))
typedef unsigned long time_t;	/* sigh... */
#else
typedef long time_t;		/* MSC 6, Borland */
#endif	/* _MSC_VER */
#define _TIME_T_DEFINED		/* Microsoft */
#define _TIME_T			/* Borland */
#define _TIME_T_DEFINED_	/* Watcom */
#endif

#ifndef _INO_T_DEFINED
#if	(defined (__WATCOMC__) && (__WATCOMC__ >= 950))
typedef	unsigned int	 ino_t;
#else
typedef	unsigned short	 ino_t;		/* i-node number (not used on DOS) */
typedef unsigned short	_ino_t;		/* MSC7+ version */
#endif
#define _INO_T_DEFINED
#endif

#ifndef _DEV_T_DEFINED
#if	(defined (__WATCOMC__) && (__WATCOMC__ >= 950))
typedef	int		 dev_t;
#else
typedef	short		 dev_t;		/* device code */
typedef short		_dev_t;		/* MSC7+ version */
#endif
#define _DEV_T_DEFINED
#endif

#ifndef _OFF_T_DEFINED
typedef	long		 off_t;		/* file offset value */
typedef long		_off_t;		/* MSC7+ version */
#define _OFF_T_DEFINED
#endif

/* Finally, add our stuff for sockets support */
/*
typedef	unsigned char	u_char;
typedef	unsigned short	u_short;
typedef	unsigned int	u_int;
typedef	unsigned long	u_long;
*/
typedef	long		daddr_t;
typedef	char *		caddr_t;

#ifndef _WINSOCKAPI_	/* winsock defines its own versions of this stuff */

/* stuff added for DOS sockets select()
*/

#define NBBY	8	/* number of bits in a byte			*/

#ifdef   FD_SETSIZE
#undef   FD_SETSIZE	/* We insist on using our value of FD_SETSIZE   */
#endif

#define  FD_SETSIZE	32	/* maximum number of DOS file descrs	*/

#define MAXSELFD	FD_SETSIZE /* max # of descrs select() groks	*/

typedef long	fd_mask;	/* longest easily used number type	*/

#define NFDBITS	(sizeof(fd_mask)* NBBY)	/* Number of File Descr BITS	*/

#define NFDSHIFT	0	/* how far to shift over sizeof(fd_mask)*/

#ifndef  howmany	/* used to find howmany longs needed for allowed*/
#define  howmany(x,y)	(((x) + ((y) - 1)) / (y)) /* number of FDs	*/
#endif /*howmany*/

typedef struct fd_set  {
    fd_mask	fds_bits[howmany(FD_SETSIZE, NFDBITS)];
} fd_set;

#define	FD_SET(n, p)	((p)->fds_bits[(n)/NFDBITS] |= (1L << ((n) % NFDBITS)))
#define	FD_CLR(n, p)	((p)->fds_bits[(n)/NFDBITS] &= ~(1L << ((n)% NFDBITS)))
#define	FD_ISSET(n, p)	((p)->fds_bits[(n)/NFDBITS] & (1L << ((n) % NFDBITS)))

#endif /* _WINSOCKAPI_ */

#endif /* _SYS_TYPES_H */

/*
 * $Log:   H:\devkit.dos\vcs\include\sys\types.h_v  $
 * 
 *    Rev 1.18   20 May 1994 11:58:52   paul
 * Added Watcom 9.5 typedefs for ino_t and dev_t.
 * 
 *    Rev 1.17   01 May 1994 14:25:34   paul
 * Increased max number of sockets from 20 to 32.
 * 
 *    Rev 1.16   07 Mar 1994 16:37:44   paul
 * Winsock has its own (conflicting) FD_SET definitions, so only define
 *     our version for DOS sockets.
 * 
 *    Rev 1.14   27 Jan 1994 12:30:52   carvalho
 * Result of v3.0 branch and v2.3 trunk merge.
 * 
 *    Rev 1.13.1.0   29 Dec 1993 17:08:18   paul
 *   Rearranged, added Watcom support to the increasingly baroque time_t
 * 
 *    Rev 1.13   05 Oct 1992 11:12:52   rcq
 * types.new
 * 
 *    Rev 1.12   24 Aug 1992 15:25:48   paul
 * added MSC7-compatible typedefs _ino_t, _dev_t, _off_t
 * 
 *    Rev 1.11   27 Feb 1992 17:37:44   arnoff
 * Ben	Added #ifdefs for ino_t, dev_t, & off_t
 * 
 */
