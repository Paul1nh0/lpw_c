/*
 * $Header:   H:\devkit.dos\vcs\include\netdb.h_v   1.12   20 Oct 1993 12:01:18   paul  $
 */

/* Structures returned by database lookup routines for network library.
 *
 *	/usr/include/netdb.h
 *
 * Copyright (C) 1986-1993 by FTP Software, Inc.
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
 * edit history:
 *     14SEP89	stev	added 4.3ism to struct hostent
 *     12NOV89	stev	added h_error values (thanx, berkeley)
 *     21MAR90	stev	daveb doesnt like the smartass h_errno
 * 			 comments, so i am fixing them.
 * 25-Feb-92	paul	added full copyright text
 *			if'd out unimplemented fctns getnetbyname, getnetent
 *			added void argument to some prototypes
 *			added prototypes for set*ent, end*ent
 * 28AUG91	gakio	added optional DLLFAR attributes for MSW3
 * 28-Sep-92	rcq	setprotent() & setservent() return int not void now
 */


#ifndef _NETDB_H
#define _NETDB_H INCLUDED


/* In the MS Windows WinApp environment, various pointers are DLLFAR and
   the location of the structures allocated by these calls is within the
   DLL itself.  Also, simplified access is provided via 'host_nm_query'
   and 'host_ad_query'.

   NOTE: When used in the MS Windows environment, this header MUST be
   included AFTER "pctcp/winapp.h". */

#ifndef MSW3
#define DLLFAR
#endif /* MSW3 */

struct hostent {
    char DLLFAR	*h_name;	/* primary name of host 		*/
    char DLLFAR	* DLLFAR *h_aliases;	/* other names of host 		*/
    int		h_addrtype;	/* address type (always AF_INET) 	*/
    int		h_length;	/* length of address (always 4) 	*/
    char DLLFAR	* DLLFAR *h_addr_list;	/* address 			*/
};
#define h_addr	h_addr_list[0]	/* backward compatibility		*/

#ifdef	__UNDEF__
struct netent {
    char	*n_name;	/* primary name of network 		*/
    char	**n_aliases;	/* other names of network 		*/
    long	n_net;		/* network number 			*/
    int		n_addrtype;	/* address type (always AF_INET) 	*/
};
#endif

struct servent {
    char DLLFAR *s_name;	/* primary name of service 		*/
    char DLLFAR * DLLFAR *s_aliases;	/* other names of service	*/
    int		s_port;		/* port number to use 			*/
    char DLLFAR *s_proto;	/* protocol service is offered on 	*/
};

struct protoent {
    char DLLFAR *p_name;	/* primary name of protocol 		*/
    char DLLFAR * DLLFAR *p_aliases;	/* other names of protocol 	*/
    int		p_proto;	/* protocol number 			*/
};

struct hostent	DLLFAR * DLLFAR gethostbyname(char DLLFAR *);
struct hostent  DLLFAR * DLLFAR gethostbyaddr(char DLLFAR *, int, int);
struct hostent	DLLFAR * DLLFAR gethostent(void);
void sethostent(int);
void endhostent(void);

struct servent	DLLFAR * DLLFAR getservbyname(char DLLFAR *, char DLLFAR *);
struct servent  DLLFAR * DLLFAR getservbyport(int, char DLLFAR *);
struct servent	DLLFAR * DLLFAR getservent(void);
int setservent(int);
void endservent(void);

struct protoent	DLLFAR * DLLFAR getprotobyname(char DLLFAR *);
struct protoent DLLFAR * DLLFAR getprotobynumber(int);
struct protoent	DLLFAR * DLLFAR getprotoent(void);
int setprotoent(int);
void endprotoent(void);

#ifdef	__UNDEF__
struct netent	DLLFAR * DLLFAR getnetbyname(char DLLFAR *);
struct netent   DLLFAR * DLLFAR getnetbyaddr(char DLLFAR *, int, int);
struct netent	DLLFAR * DLLFAR getnetent(void);
void setnetent(int);
void endnetent(void);
#endif

/* 
return values from gethostby*() in h_errno. comments stolen from the bugs
mail daveb sent in at the end of feburary. thanx, dave. (stev, 21MAR90)
*/


#define HOST_NOT_FOUND	1	/* Sorry, no such host is known		*/

#define TRY_AGAIN	2	/* This is usually a temporary error	*/
				/* and means that the local server did	*/
				/* not receive a response from an	*/
				/* authoritative server.  A retry at	*/
				/* some later time may succeed.		*/

#define NO_RECOVERY	3	/* This is a non-recoverable error.	*/

#define NO_ADDRESS	4	/* The requested name is valid but does	*/
				/* not have an IP address; this is not a*/
				/* temporary error.  This means another */
				/* type of request to the name server	*/
				/* may result in an answer.		*/

extern int h_errno;

#endif /* _NETDB_H */

/*
 * $Log:   H:\devkit.dos\vcs\include\netdb.h_v  $
 * 
 *    Rev 1.12   20 Oct 1993 12:01:18   paul
 * Made h_errno extern, to avoid multiple declarations
 *   (it's actually declared in the domain lib)
 * 
 *    Rev 1.11   13 Oct 1993 17:42:08   arnoff
 * added h_errno per customer request.
 * 
 *    Rev 1.10   05 Oct 1992 11:50:56   rcq
 * setprotoent() & setservent() prototypes changed from void to int
 * 
 *    Rev 1.9   12 Apr 1992 21:16:04   arnoff
 * Added full copyright text.
 * If'd out unimplemented functions getnetbyname, getnetent.
 * Added void argument to get*ent prototypes.
 * Added prototypes for set*ent, end*ent.
 * 
 *    Rev 1.8   30 Jan 1992 08:26:50   arnoff
 *  
 */
