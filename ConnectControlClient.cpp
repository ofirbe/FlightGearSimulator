//
// Created by ofir on 22/12/2019.
//

#include "ConnectControlClient.h"
#include "Parser.h"

/**
 * CTOR
 */
ConnectControlClient::ConnectControlClient() {
  //create socket
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    //error
    std::cerr << "Could not create a socket" << std::endl;
    //return -1;
    exit(1);
  }
  this->client_socket = client_socket;
}

/**
 * DTOR
 */
ConnectControlClient::~ConnectControlClient() {
  close(this->client_socket); //closing the socket
}

/**
 * runExucteMethosAsThread - the method runs the connection (to client) thread by the ip and port it gets.
 * @param: string ipAdress - the ip address.
 * @param: string portNum - the port number.
 */
int ConnectControlClient::runExucteMethosAsThread(string ipAdress, string portNum) {

  // calculating the port number
  VarCommand *v = new VarCommand();
  Expression *portExp = v->createExp(portNum);
  int portNumInInt = portExp->calculate();

  string tmp = ipAdress;
  tmp.erase(remove(tmp.begin(), tmp.end(), '"'), tmp.end());
  char localHostAddress[tmp.length() + 1];
  strcpy(localHostAddress, tmp.c_str());

  //We need to create a sockaddr obj to hold address of server
  sockaddr_in address; //in means IP4
  address.sin_family = AF_INET;//IP4
  address.sin_addr.s_addr = inet_addr(localHostAddress);  //the localhost address
  address.sin_port = htons(portNumInInt);
  //we need to convert our number (both port & localhost)
  // to a number that the network understands.

  // Requesting a connection with the server on local host with the port from above

  int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
  if (is_connect == -1) {
    std::cerr << "Could not connect to host server" << std::endl;
    //return -2;
    exit(1);
  } else {
    std::cout << "Client is now connected to server" << std::endl;
  }

  //if here we made a connection so run over the queue and send commands to server
  while (true) {
    while (!connectControlQueue.empty()) {
      string command = "set " + connectControlQueue.front() + "\r\n";
      connectControlQueue.pop();
      char sendCommend[command.size() + 1];
      strcpy(sendCommend, command.c_str());
      int is_sent = send(client_socket, sendCommend, strlen(sendCommend), 0);
      if (is_sent == -1) {
        std::cout << command << std::endl;
        std::cout << "Error sending message" << std::endl;
      }
    }
  }
}
/**
 * execute - the method executes the ConnectControlClient command - connecting to the client and sending it
 * commands. The method returns the number of steps we need to jump in the lexer
 * vector, in order to get the next command.
 * @param: vector<string> lexerVector - the vector that the lexer created from fly.txt.
 * @param: int currentIndex - the current index of the vector.
 * @return int:  the number of steps we need to jump in the array.
 */
int ConnectControlClient::execute(vector<string> lexerVector, int index) {
  thread ConnectControlClientThread
      (&ConnectControlClient::runExucteMethosAsThread, this, lexerVector[index + 1], lexerVector[index + 2]);
  ConnectControlClientThread.detach();

  // returning the number of cells to jump in the array
  return 3;
}