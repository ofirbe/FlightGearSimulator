//
// Created by michael on 16/12/2019.
//

#include "OpenDataServer.h"

  int OpenDataServer::runExucteMethosAsThread(string portNum) {
    int portNumInInt = stoi(portNum);
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
      //error
      std::cerr << "Could not create a socket" << std::endl;
      return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(portNumInInt);

    //we need to convert our number to a number that the network understands

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
      std::cerr << "Could not bind the socket to an IP" << std::endl;
      return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) {
      //can also set to SOMAXCON (max connections)
      std::cerr << "Error during listening command" << std::endl;
      return -3;
    } else {
      std::cout << "Server is now listening ..." << std::endl;
    }


      // accepting a client
      int client_socket = accept(socketfd, (struct sockaddr *) &address,
                                 (socklen_t *) &address);

      std::cout << client_socket << std::endl;

      if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
        return -4;
      }

    close(socketfd); //closing the listening socket

    while (true) {
      //reading from client
      char buffer[1024] = {0};
      int valread = read(client_socket, buffer, 1024);
      int indexAtMap =1;
      char* splitInfo = strtok(buffer,",");

      //get data from the client and put it at the right place at the flightDataMap
      while (splitInfo != NULL)
      {
        double currentInfo = atof(splitInfo);
        flightDataMap[indexToCommandKey(indexAtMap)]=currentInfo;
        splitInfo = strtok (NULL, ",");
        indexAtMap++;
      }
    }
  }

  int OpenDataServer::execute(vector<string> lexerVector, int index) {
    thread openDataServerThread(&OpenDataServer::runExucteMethosAsThread, this, lexerVector[index + 1]);
    openDataServerThread.detach();

    // returning the number of cells to jump in the array
    return 2;
  }

  //get index (the number of the data from the xml file) and return the corresponding Key(string) at the flightDataMap
  string OpenDataServer::indexToCommandKey(int index){
    switch (index) {
      case 1:return ("/instrumentation/airspeed-indicator/indicated-speed-kt");
      case 2:return ("/sim/time/warp");
      case 3:return ("/controls/switches/magnetos");
      case 4:return ("//instrumentation/heading-indicator/offset-deg");
      case 5:return ("/instrumentation/altimeter/indicated-altitude-ft");
      case 6:return ("/instrumentation/altimeter/pressure-alt-ft");
      case 7:return ("/instrumentation/attitude-indicator/indicated-pitch-deg");
      case 8:return ("/instrumentation/attitude-indicator/indicated-roll-deg");
      case 9:return ("/instrumentation/attitude-indicator/internal-pitch-deg");
      case 10:return ("/instrumentation/attitude-indicator/internal-roll-deg");
      case 11:return ("/instrumentation/encoder/indicated-altitude-ft");
      case 12:return ("/instrumentation/encoder/pressure-alt-ft");
      case 13:return ("/instrumentation/gps/indicated-altitude-ft");
      case 14:return ("/instrumentation/gps/indicated-ground-speed-kt");
      case 15:return ("/instrumentation/gps/indicated-vertical-speed");
      case 16:return ("/instrumentation/heading-indicator/indicated-heading-deg");
      case 17:return ("/instrumentation/magnetic-compass/indicated-heading-deg");
      case 18:return ("/instrumentation/slip-skid-ball/indicated-slip-skid");
      case 19:return ("/instrumentation/turn-indicator/indicated-turn-rate");
      case 20:return ("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
      case 21:return ("/controls/flight/aileron");
      case 22:return ("/controls/flight/elevator");
      case 23:return ("/controls/flight/rudder");
      case 24:return ("/controls/flight/flaps");
      case 25:return ("/controls/engines/engine/throttle");
      case 26:return ("/controls/engines/current-engine/throttle");
      case 27:return ("/controls/switches/master-avionics");
      case 28:return ("/controls/switches/starter");
      case 29:return ("/engines/active-engine/auto-start");
      case 30:return ("/controls/flight/speedbrake");
      case 31:return ("/sim/model/c172p/brake-parking");
      case 32:return ("/controls/engines/engine/primer");
      case 33:return ("/controls/engines/current-engine/mixture");
      case 34:return ("/controls/switches/master-bat");
      case 35:return ("/controls/switches/master-alt");
      case 36:return ("/engines/engine/rpm");
      default: cout<<"no More Commands Was Found At The xml File"<<endl;
    }
}
