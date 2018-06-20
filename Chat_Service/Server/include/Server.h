#ifndef _SERVER_H
#define _SERVER_H

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <iostream>
#include <vector>

using namespace std;

#define TRUE 1
#define FALSE 0
#define PORT 1234

class Server
{
public:
  int server_fd;
  int new_socket;
  int valread;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  char buffer[1024];
  string t;
  char *message = "Hello from server \n";
  fd_set readfds;
  int client_socket[30];
  int master_socket;
  int opt = TRUE;
  int max_sd;
  int max_clients = 30;
  int sd;
  int activity;

  vector <struct sockaddr_in> client_addr;

/* function */
  Server();
  ~Server();
  void Create_Master_Socket();
  void Set_Master_Socket_Multiple();
  void Type_Socket();
  void Bind_Socket();
  void Specify_Pending();
  void Accept_Incoming();
  int Start_Run();
};

#endif
