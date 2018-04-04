/*
 * $Header:   H:\devkit.dos\vcs\include\sys\socket.h_v   1.13   04 Aug 1994 14:52:26   paul  $
 */

/* Socket definitions, address families, options
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
 * 20-Oct-87	jbvb	Add definition for SOMAXCONN, per HP bug report.
 * 21-Jan-88	jbvb	Add definition for SO_DONTLINGER (4.2 compatible)
 *			 in place of SO_USELOOPBACK.
 * 25-Apr-88	jbvb	Add the rest of the Protocol Family definitions.
 * 27 OCT 89	stev	4.3ize.  add struct linger.
 * 26-Feb-92	paul	changed SOL_SOCKET from 0xffff (unsigned) to
 *			 -1 (signed).  Is this right???
 * 07-Apr-93	rcq	added ifdef to protect from multiple includes
 */

#ifndef _SYS_SOCKET_H
#define _SYS_SOCKET_H

#ifdef MSW3
#include <winsock.h>
#else

/* Socket Types
*/
#define	SOCK_STREAM	1		/* TCP (stream)			*/
#define	SOCK_DGRAM	2		/* UDP (datagram		*/
#define	SOCK_RAW	3		/* direct protocol interface 	*/
#define	SOCK_RDM	4		/* reliably-delivered message 	*/
#define	SOCK_SEQPACKET	5		/* sequenced packet stream 	*/

/* Socket Levels
*/
#define	SOL_SOCKET	-1

/* Socket Options
*/
#define	SO_DEBUG	0x01	/* record debugging info 		*/
#define	SO_ACCEPTCONN	0x02	/* socket is listen()ing 		*/
#define	SO_REUSEADDR	0x04	/* allow local address to be reused 	*/
#define	SO_KEEPALIVE	0x08	/* keep connections alive 		*/
#define	SO_DONTROUTE	0x10	/* send from this interface, dont route	*/
#define	SO_BROADCAST	0x20	/* use hardware broadcast		*/
#define	SO_DONTLINGER	0x40	/* 4.2 compatible 			*/
#define	SO_LINGER	0x80	/* linger on close if data present 	*/
#define SO_OOBINLINE	0x100	/* leave received OOB data in line 	*/


#define	SO_SNDBUF	0x1001	/* send buffer size			*/
#define	SO_RCVBUF	0x1002	/* recieve buffer size			*/
#define	SO_SNDLOWAT	0x1003	/* send low water mark			*/
#define	SO_RCVLOWAT	0x1004	/* recieve low water mark		*/
#define	SO_SNDTIMEO	0x1005	/* send timeout				*/
#define	SO_RCVTIMEO	0x1006	/* recieve timeout			*/
#define SO_ERROR	0x1007	/* get and clear error status		*/
#define SO_TYPE		0x1008	/* get socket type (ie: SOCK_STREAM)	*/

#define	MSG_OOB		0x01
#define	MSG_PEEK	0x02
#define	MSG_DONTROUTE	0x04

/*Structure used for manipulating linger option.
 */
struct	linger {
	int	l_onoff;		/* option on/off */
	int	l_linger;		/* linger time */
};


/* Address Families
*/
#define	AF_UNSPEC	0		/* unspecified (roll your own)	*/
#define	AF_UNIX		1		/* local to host(pipes, portals)*/
#define	AF_INET		2		/* internetwork: UDP, TCP, etc. */
#define	AF_IMPLINK	3		/* arpanet imp addresses 	*/
#define	AF_PUP		4		/* pup protocols: e.g. BSP 	*/
#define	AF_CHAOS	5		/* mit CHAOSnet protocols 	*/
#define	AF_NS		6		/* XEROX NS protocols 		*/
#define	AF_NBS		7		/* national br. of stds.	*/
#define	AF_ECMA		8		/* european computer makers	*/
#define	AF_DATAKIT	9		/* datakit protocols 		*/
#define	AF_CCITT	10		/* CCITT protocols, X.25 etc 	*/
#define	AF_SNA		11		/* IBM SNA			*/
#define AF_DECnet	12		/* DECnet 			*/
#define AF_DLI		13		/* Direct data link interface 	*/
#define AF_LAT		14		/* LAT 				*/
#define	AF_HYLINK	15		/* NSC Hyperchannel 		*/
#define AF_APPLETALK	16		/* Apple talk 			*/
#define AF_BSC		17		/* BISYNC 2780/3780 		*/
#define AF_DSS		18		/* Distributed system services 	*/

#define	AF_MAX		19

/* Protocol Families
*/
#define	PF_UNSPEC	AF_UNSPEC
#define	PF_UNIX		AF_UNIX
#define	PF_INET		AF_INET
#define	PF_IMPLINK	AF_IMPLINK	/* Internet Protocols */
#define	PF_PUP		AF_PUP
#define	PF_CHAOS	AF_CHAOS
#define	PF_NS		AF_NS
#define	PF_NBS		AF_NBS
#define	PF_ECMA		AF_ECMA
#define	PF_DATAKIT	AF_DATAKIT
#define	PF_CCITT	AF_CCITT
#define	PF_SNA		AF_SNA
#define PF_DECnet	AF_DECnet
#define PF_DLI		AF_DLI
#define PF_LAT		AF_LAT
#define	PF_HYLINK	AF_HYLINK
#define PF_APPLETALK	AF_APPLETALK
#define PF_BSC		AF_BSC
#define PF_DSS		AF_DSS

#define	PF_MAX		AF_MAX

/* Maximum queue length specifiable by listen().
*/
#define	SOMAXCONN	5

struct sockaddr {
    unsigned short	sa_family;	/* address family */
    char	sa_data[14];	/* up to 14 bytes of address */
};

struct sockproto {
    unsigned short	sp_family;	/* address family */
    unsigned short	sp_protocol;	/* protocol */
};


#endif /* MSW3 */

#endif /* _SYS_SOCKET_H */

/*
 * $Log:   H:\devkit.dos\vcs\include\sys\socket.h_v  $
 * 
 *    Rev 1.13   04 Aug 1994 14:52:26   paul
 * If windows, include winsock.h instead.
 * 
 *    Rev 1.12   28 Jul 1993 15:20:42   arnoff
 * Merge Lilac Branch into trunk.
 * 
 *    Rev 1.11.1.0   19 May 1993 08:49:26   natalia
 * 
 *    Rev 1.11   12 Apr 1992 21:17:06   arnoff
 * Changed SOL_SOCKET from 0xffff (unsigned) to -1 (signed).  Is this right???
 * 
 *    Rev 1.10   03 Feb 1992 23:28:06   arnoff
 * pre beta-2 testing freeze
 * 
 *    Rev 1.9   30 Jan 1992 19:50:22   arnoff
 *  
 */
