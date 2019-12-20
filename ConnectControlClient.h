//
// Created by ofir on 18/12/2019.
//


#ifndef EX3__CONNECTCONTROLCLIENT_H_
#define EX3__CONNECTCONTROLCLIENT_H_
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

// the define Port and address will get the information from the lexer.
#define PORT 5402
#define localHostAddress "127.0.0.1"

class ConnectControlClient : public Command {
 public:
  int check = 3;
  int execute(vector<string> lexerVector, int currentIndex){
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
      //error
      std::cerr << "Could not create a socket" << std::endl;
      return -1;
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr(localHostAddress);  //the localhost address
    address.sin_port = htons(PORT);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with the port from above

    int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    if (is_connect == -1) {
      std::cerr << "Could not connect to host server" << std::endl;
      return -2;
    } else {
      std::cout << "Client is now connected to server" << std::endl;
    }

    //if here we made a connection
    char hello[] = "set controls/flight/rudder -1\r\n";
    //char hello[] = "set controls/flight/rudder -1\r\n";
    int is_sent = send(client_socket, hello, strlen(hello), 0);
    if (is_sent == -1) {
      std::cout << "Error sending message" << std::endl;
    } else {
      std::cout << "Hello message sent to server" << std::endl;
    }

    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);
    std::cout << buffer << std::endl;

    close(client_socket);
    return 3;
  }
};

#endif //EX3__CONNECTCONTROLCLIENT_H_