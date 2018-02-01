/************************************************************************* 
  > File Name: Server.c 
  > Author: SongLee 
 ************************************************************************/
#include<netinet/in.h> // sockaddr_in 
#include<sys/types.h>  // socket 
#include<sys/socket.h> // socket 
#include<stdio.h>    // printf 
#include<stdlib.h>   // exit 
#include<string.h>   // bzero 
  
#define SERVER_PORT 8000 
#define LENGTH_OF_LISTEN_QUEUE 20 
#define BUFFER_SIZE 1024 
#define FILE_NAME_MAX_SIZE 512 
  
int main(void) 
{ 
  // ��������ʼ��һ���������˵�socket��ַ�ṹ 
  struct sockaddr_in server_addr; 
  bzero(&server_addr, sizeof(server_addr)); 
  server_addr.sin_family = AF_INET; 
  server_addr.sin_addr.s_addr = htons(INADDR_ANY); 
  server_addr.sin_port = htons(SERVER_PORT); 
  
  // ����socket�����ɹ�������socket������ 
  int server_socket_fd = socket(PF_INET, SOCK_STREAM, 0); 
  if(server_socket_fd < 0) 
  { 
    perror("Create Socket Failed:"); 
    exit(1); 
  } 
  int opt = 1; 
  setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); 
  
  // ��socket��socket��ַ�ṹ 
  if(-1 == (bind(server_socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)))) 
  { 
    perror("Server Bind Failed:"); 
    exit(1); 
  } 
    
  // socket���� 
  if(-1 == (listen(server_socket_fd, LENGTH_OF_LISTEN_QUEUE))) 
  { 
    perror("Server Listen Failed:"); 
    exit(1); 
  } 
  
  while(1) 
  { 
    // ����ͻ��˵�socket��ַ�ṹ 
    struct sockaddr_in client_addr; 
    socklen_t client_addr_length = sizeof(client_addr); 
  
    // �����������󣬷���һ���µ�socket(������)�������socket����ͬ���ӵĿͻ���ͨ�� 
    // accept����������ӵ��Ŀͻ�����Ϣд��client_addr�� 
    int new_server_socket_fd = accept(server_socket_fd, (struct sockaddr*)&client_addr, &client_addr_length); 
    if(new_server_socket_fd < 0) 
    { 
      perror("Server Accept Failed:"); 
      break; 
    } 
  
    // recv�����������ݵ�������buffer�� 
    char buffer[BUFFER_SIZE]; 
    bzero(buffer, BUFFER_SIZE); 
    if(recv(new_server_socket_fd, buffer, BUFFER_SIZE, 0) < 0) 
    { 
      perror("Server Recieve Data Failed:"); 
      break; 
    } 
  
    // Ȼ���buffer(������)������file_name�� 
    char file_name[FILE_NAME_MAX_SIZE+1]; 
    bzero(file_name, FILE_NAME_MAX_SIZE+1); 
    strncpy(file_name, buffer, strlen(buffer)>FILE_NAME_MAX_SIZE?FILE_NAME_MAX_SIZE:strlen(buffer)); 
    printf("%s\n", file_name); 
  
    // ���ļ�����ȡ�ļ����� 
    FILE *fp = fopen(file_name, "r"); 
    if(NULL == fp) 
    { 
      printf("File:%s Not Found\n", file_name); 
    } 
    else
    { 
      bzero(buffer, BUFFER_SIZE); 
      int length = 0; 
      // ÿ��ȡһ�����ݣ��㽫�䷢�͸��ͻ��ˣ�ѭ��ֱ���ļ�����Ϊֹ 
      while((length = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0) 
      { 
        if(send(new_server_socket_fd, buffer, length, 0) < 0) 
        { 
          printf("Send File:%s Failed./n", file_name); 
          break; 
        } 
        bzero(buffer, BUFFER_SIZE); 
      } 
  
      // �ر��ļ� 
      fclose(fp); 
      printf("File:%s Transfer Successful!\n", file_name); 
    } 
    // �ر���ͻ��˵����� 
    close(new_server_socket_fd); 
  } 
  // �رռ����õ�socket 
  close(server_socket_fd); 
  return 0; 
} 
