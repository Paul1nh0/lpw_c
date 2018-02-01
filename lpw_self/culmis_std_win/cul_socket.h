#ifndef __CULSOCKET_H__
#define __CULSOCKET_H__

extern S32 cul_socket_init(S8* ip,S32 port);
extern S32 cul_socket_close(S32 socket_id);
extern S32 cul_socket_send(S32 socket_id,S8* buf,S32 len);
extern S32 cul_socket_recv(S32 socket_id,S8* buf,S32 len,S32 time_out);

#endif
