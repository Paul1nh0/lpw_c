#include "cul_macro.h"
#include "cul_std_string.h"
#include "cul_log.h"
#include "sys/time.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "cul_common.h"
#include "cul_socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

S32 cul_socket_init(S8* ip,S32 port)
{
    	struct sockaddr_in server;
	struct linger zeroLinger;
    S32 socket_id = 0;
#ifdef CUL_WINDOWS
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2 );
	int ret = WSAStartup(wVersionRequested, &wsaData);
	if (ret != 0)
	{
		return 0;
	}
#else
	struct timeval timeout;
	struct hostent *he;
#endif
	cul_log_string(LOG_SOCKET,"socket_init ip:%s,port:%d",ip,port);

	if ((socket_id = socket(AF_INET ,SOCK_STREAM,0))==-1)
	{
		cul_log_string(LOG_SOCKET,"socket create failed");
		return(0 );
	}
#ifdef CUL_WINDOWS

#else
	if ((he=gethostbyname(ip))==NULL)
	{
		cul_log_string(LOG_SOCKET,"socket get ip failed");
		return( 0 );	
	}
	cul_log_string(LOG_SOCKET,"this is for debug test");
	//log_str_out(LOG_SOCKET,"he");
#endif
	memset(&server,0x00,sizeof(server));
	server.sin_family = AF_INET ;
	server.sin_port = htons(port);
#ifdef CUL_WINDOWS
	server.sin_addr.s_addr = inet_addr(ip);
#else
	server.sin_addr = *((struct in_addr *)he->h_addr);
#endif
	zeroLinger.l_onoff = 1;
	zeroLinger.l_linger = 0;
	if(setsockopt(socket_id,SOL_SOCKET,SO_LINGER ,(const char *)&zeroLinger,sizeof(zeroLinger)))
	{
		cul_log_string(LOG_SOCKET,"set zeroLinger failed");
		return( 0 );
	}
    
	if (connect(socket_id,(struct sockaddr *) &server,sizeof(struct sockaddr ))==-1)
	{
	/*	socket_close(socket_data->socket_id); */
		cul_log_string(LOG_SOCKET,"socket connect failed");
		return( 0 );
	}
	return socket_id;
}

S32 cul_socket_close(S32 socket_id)
{
#ifdef CUL_WINDOWS
	closesocket(socket_id);
#else
	close(socket_id);
#endif
    return 0;
}


S32 cul_socket_send(S32 socket_id,S8* buf,S32 len)
{
#ifdef CUL_WINDOWS
	if(0 >= send(socket_id,buf,len,0))
#else
	if(0 >= send(socket_id,buf,len,0))
#endif
	{
		cul_log_string(LOG_SOCKET,"send failed");
		return -1;
	}
	return 0;    
}

S32 cul_socket_recv(S32 socket_id,S8* buf,S32 len,S32 time_out)
{
    	int nRet;
	U32 DataLen = 0;

	int 		   nResult,iMax;
	fd_set		   fdr ;

	struct timeval timeout;
#if 1
	FD_ZERO(&fdr);
	FD_SET(socket_id, &fdr);

	timeout.tv_sec = 0;/*socket_data->time_out;*/
	timeout.tv_usec = time_out*1000*1000;

	iMax = socket_id + 1;
	
	nResult = select(iMax , &fdr , NULL , NULL , &timeout);
	if(nResult < 0)
	{
		return -1;
	}
	else if( nResult == 0)
	{
		return -1 ;
	}
#endif
	memset(buf, 0, len);
	nRet = recv(socket_id, (char *)buf,len,0);
	if (nRet <= 0)
	{
		cul_log_string(LOG_SOCKET,"recv timeout %d time %d",len,time_out);
		return -1;
	}

	DataLen = (U8)buf[0] * 256 + (U8)buf[1];
	if (DataLen <0 || DataLen > 4096)
	{
		cul_log_string(LOG_SOCKET,"recv parse failed len:%d",DataLen);
		return -1;
	}
	return 0;
}


