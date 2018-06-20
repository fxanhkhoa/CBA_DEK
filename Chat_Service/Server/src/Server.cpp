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

int Server::Start_Run() {
  int i;
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
    // wait for an activity on one of the sockets , timeout is NULL ,
    // so wait indefinitely
    activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

    if ((activity < 0) && (errno != EINTR)) {
      cout << "select error" << endl;
    }

    // If something happened on the master socket ,
    // then its an incoming connection
    if (FD_ISSET(master_socket, &readfds)) {
      if ((new_socket = accept(master_socket, (struct sockaddr *)&address,
                               (socklen_t *)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
      }
      // inform user of socket number - used in send and receive commands
      printf("New connection , socket fd is %d , ip is : %s , port : %d\n ",
             new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

      //Push to vector
      client_addr.push_back(address);
      cout << inet_ntoa(client_addr[0].sin_addr) <<endl;

      // send new connection greeting message
      if (send(new_socket, message, strlen(message), 0) != strlen(message)) {
        perror("send");
      }

      puts("Welcome message sent successfully");

      // add new socket to array of sockets
      for (i = 0; i < max_clients; i++) {
        // if position is empty
        if (client_socket[i] == 0) {
          client_socket[i] = new_socket;
          printf("Adding to list of sockets as %d\n", i);

          break;
        }
      }
    }
    // else its some IO operation on some other socket
    for (i = 0; i < max_clients; i++) {
      sd = client_socket[i];

      if (FD_ISSET(sd, &readfds)) {
        // Check if it was for closing , and also read the
        // incoming message
        valread = recv(sd, buffer, 1024 - 1, 0);
        cout <<endl;
        if (valread == 0) {
          // Somebody disconnected , get his details and print
          getpeername(sd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
          printf("Host disconnected , ip %s , port %d \n",
                 inet_ntoa(address.sin_addr), ntohs(address.sin_port));

          // Close the socket and mark as 0 in list for reuse
          close(sd);
          client_socket[i] = 0;
        }

        // Echo back the message that came in
        if (valread > 0){
          // set the string terminating NULL byte on the end
          // of the data read
          for (int j = 2; j < valread; j++)
            cout << buffer[j];
          buffer[valread] = '\0';
          send(sd, buffer, valread, 0);
          send(sd, inet_ntoa(address.sin_addr), 12, 0);
          send(sd, "\n", 1, 0);
        }
      }
    }
  }
  return 0;
}
