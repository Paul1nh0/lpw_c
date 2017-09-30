/*
 *  netinet/in.h      IP related definitions
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
#ifndef _NETINET_IN_H_INCLUDED
#define _NETINET_IN_H_INCLUDED

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file;
#endif

#ifndef _COMDEF_H_INCLUDED
 #include <_comdef.h>
#endif

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack( __push, 4 )

/* Internet address. */
struct in_addr {
    uint32_t       s_addr;     /* address in network byte order */
};

struct sockaddr_in {
    sa_family_t    sin_family; /* address family: AF_INET */
    uint16_t       sin_port;   /* port in network byte order */
    struct in_addr sin_addr;   /* internet address */
    char           __pad[ 16 - sizeof( sa_family_t ) - sizeof( uint16_t ) - sizeof( struct in_addr ) ];
};

#define IPPROTO_IP              0
#define IPPROTO_ICMP            1
#define IPPROTO_IGMP            2
#define IPPROTO_IPIP            4
#define IPPROTO_IPV4            IPPROTO_IPIP
#define IPPROTO_TCP             6
#define IPPROTO_EGP             8
#define IPPROTO_PUP             12
#define IPPROTO_UDP             17
#define IPPROTO_IDP             22
#define IPPROTO_DCCP            33
#define IPPROTO_IPV6            41
#define IPPROTO_ROUTING         43
#define IPPROTO_FRAGMENT        44
#define IPPROTO_RSVP            46
#define IPPROTO_GRE             47
#define IPPROTO_ESP             50
#define IPPROTO_AH              51
#define IPPROTO_ICMPV6          58                
#define IPPROTO_PIM             103
#define IPPROTO_COMP            108
#define IPPROTO_SCTP            132
#define IPPROTO_RAW             255

#define INADDR_ANY              0x00000000UL
#define INADDR_BROADCAST        0xffffffffUL    /* 255.255.255.255 */
#define INADDR_NONE             0xffffffffUL
#define INADDR_LOOPBACK         0x7f000001UL    /* 127.0.0.1 */

#define INADDR_UNSPEC_GROUP     0xe0000000UL    /* 224.0.0.0 */
#define INADDR_ALLHOSTS_GROUP   0xe0000001UL    /* 224.0.0.1 */
#define INADDR_ALLRTRS_GROUP    0xe0000002UL    /* 224.0.0.2 */
#define INADDR_MAX_LOCAL_GROUP  0xe00000ffUL    /* 224.0.0.255 */

#define IN_CLASSA(a)            ((((uint32_t)(a)) & 0x80000000UL) == 0)
#define IN_CLASSA_NET           0xff000000UL
#define IN_CLASSA_NSHIFT        24
#define IN_CLASSA_HOST          (0xffffffffUL & ~IN_CLASSA_NET)
#define IN_CLASSA_MAX           128

#define IN_CLASSB(a)            ((((uint32_t)(a)) & 0xc0000000UL) == 0x80000000UL)
#define IN_CLASSB_NET           0xffff0000UL
#define IN_CLASSB_NSHIFT        16
#define IN_CLASSB_HOST          (0xffffffffUL & ~IN_CLASSB_NET)
#define IN_CLASSB_MAX           65536

#define IN_CLASSC(a)            ((((uint32_t)(a)) & 0xe0000000UL) == 0xc0000000UL)
#define IN_CLASSC_NET           0xffffff00UL
#define IN_CLASSC_NSHIFT        8
#define IN_CLASSC_HOST          (0xffffffffUL & ~IN_CLASSC_NET)

#define IN_CLASSD(a)            ((((uint32_t)(a)) & 0xf0000000UL) == 0xe0000000UL)
#define IN_MULTICAST(a)         IN_CLASSD(a)

#define IN_EXPERIMENTAL(a)      ((((uint32_t)(a)) & 0xe0000000UL) == 0xe0000000UL)
#define IN_BADCLASS(a)          ((((uint32_t)(a)) & 0xf0000000UL) == 0xf0000000UL)

#define IP_LOOPBACKNET          127

_WCRTLINK unsigned long int htonl(unsigned long int hostlong);
_WCRTLINK unsigned short int htons(unsigned short int hostshort);
_WCRTLINK unsigned long int ntohl(unsigned long int netlong);
_WCRTLINK unsigned short int ntohs(unsigned short int netshort);

#pragma pack( __pop )

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !_NETINET_IN_H_INCLUDED */
