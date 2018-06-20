#include "Server.h"

Server::Server() {
  for (int i = 0; i < 30; i++) {
    client_socket[i] = 0;
  }
}

Server::~Server() {}

void Server::Create_Master_Socket() {
  if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }
}

void Server::Set_Master_Socket_Multiple() {
  if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                 sizeof(opt)) < 0) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
}

void Server::Type_Socket() {
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);
}

/* bind socket to localhost + port */
void Server::Bind_Socket() {
  if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
  cout << "Listener on Port " << PORT;
}

void Server::Specify_Pending() {
  if (listen(master_socket, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
}

void Server::Accept_Incoming() {
  addrlen = sizeof(address);
  puts("waiting for connections ...");
}

void Server::Start_Run() {
  while (TRUE) {
    // Clear the socket set
    FD_ZERO(&readfds);

    // add master socket to set
    FD_SET(master_socket, &readfds);
    max_sd = master_socket;

    // add child sockets to set
    for (i = 0; i < max_clients; i++) {
      // socket descriptor
      sd = client_socket[i];

      // if valid socket descriptor then add to read list
      if (sd > 0)
        FD_SET(sd, &readfds);

      // highest file descriptor number, need it for the select function
      if (sd > max_sd)
        max_sd = sd;
    }
    //wait for an activity on one of the sockets , timeout is NULL ,
    //so wait indefinitely
    activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

    if ((activity < 0) && (errno!=EINTR))
    {
      cout<<"select error" << endl;
    }

    //If something happened on the master socket ,
    //then its an incoming connection 
  }
}
