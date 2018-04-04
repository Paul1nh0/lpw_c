/*
 * $Header:   H:\devkit.dos\vcs\include\sys\time.h_v   1.12   17 Nov 1994 15:00:58   paul  $
 */

/* Time structures used by gettimeofday
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
 * 28-Feb-92	paul	added gettimeofday prototype
 */

#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_

#define u_long unsigned long

struct timeval {
	u_long	tv_sec;
	u_long	tv_usec;
};

struct timezone {
	int	tz_minuteswest;
	int	tz_dsttime;
};

int gettimeofday(struct timeval *, struct timezone *);

#endif /* _SYS_TIME_H_ */

/*
 * $Log:   H:\devkit.dos\vcs\include\sys\time.h_v  $
 * 
 *    Rev 1.12   17 Nov 1994 15:00:58   paul
 * Moved gettimeofday() prototype inside multiple-inclusion protection.
 * 
 *    Rev 1.11   13 Apr 1992 12:10:26   arnoff
 * Added full copyright text
 * Added gettimeofday prototype
 * 
 *    Rev 1.10   03 Feb 1992 23:28:08   arnoff
 * pre beta-2 testing freeze
 * 
 *    Rev 1.9   30 Jan 1992 19:50:24   arnoff
 *  
 */
