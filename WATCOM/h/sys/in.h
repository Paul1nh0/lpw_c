/*
 * $Header:   H:\devkit.dos\vcs\include\netinet\in.h_v   1.5   04 Aug 1994 14:51:46   paul  $
 */

/* Constants and structures for the Internet system.
 *
 * Copyright (C) 1987-1994 by FTP Software, Inc.
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
 * Edit History
 * 25-Apr-88	jbvb	Add IPPORT_RESERVED, rename filler to match 4BSD.
 * 29-Jun-89	dab	Fixed typo where htons() was declared twice and
 *			ntohs() was omitted.
 * 07-Nov-91	paul	added parameters to function prototypes
 */

#ifndef _NETINET_IN_H
#define _NETINET_IN_H

#ifdef MSW3
#include <winsock.h>
#else

/* Protocols
*/
#define	IPPROTO_ICMP	1	/* IP control message protocol */
#define	IPPROTO_TCP	6	/* Transmission control protocol */
#define	IPPROTO_UDP	17	/* User datagram protocol */

#define	IPPROTO_RAW	255	/* Raw IP packets */
#define	IPPROTO_MAX	256

#define	IPPORT_RESERVED	1024	/* BSD believes (port < 1024) == secure */

/* Internet Address structure
*/
struct in_addr {
    union {
	struct { unsigned char	 s_b1, s_b2, s_b3, s_b4; }	S_un_b;
	struct { unsigned short s_w1, s_w2; }			S_un_w;
	unsigned long S_addr;
    } S_un;
#define s_addr	S_un.S_addr
#define	s_net	S_un.S_un_b.s_b1
#define	s_host	S_un.S_un_b.s_b2
#define	s_lh	S_un.S_un_b.s_b3
#define	s_impno	S_un.S_un_b.s_b4
#define	s_imp	S_un.S_un_w.s_w2
};

#define	INADDR_ANY		0x00000000L
#define	INADDR_BROADCAST	0xFFFFFFFFL

struct sockaddr_in {
    short		sin_family;
    unsigned short		sin_port;
    struct in_addr	sin_addr;
    char		sin_zero[8];
};

#ifndef	_NTOHL
#define	_NTOHL
unsigned long	htonl(unsigned long), ntohl(unsigned long);
unsigned short	htons(unsigned short), ntohs(unsigned short);
#endif


#endif	/* MSW3 */

#endif	/* _NETINET_IN_H */

/*
 * $Log:   H:\devkit.dos\vcs\include\netinet\in.h_v  $
 * 
 *    Rev 1.5   04 Aug 1994 14:51:46   paul
 * If windows, include winsock.h instead.
 * 
 *    Rev 1.4   28 Jul 1993 15:31:32   arnoff
 * Merge Lilac Branch into trunk.
 * 
 *    Rev 1.3.1.0   08 Apr 1993 17:14:00   arnoff
 * Protected against multiple includes.
 * 
 *    Rev 1.3   24 Feb 1992 17:49:54   arnoff
 * correct in.h path
 * 
 *    Rev 1.2   03 Feb 1992 23:27:52   arnoff
 * pre beta-2 testing freeze
 * 
 *    Rev 1.1   30 Jan 1992 19:50:00   arnoff
 *  
 */
