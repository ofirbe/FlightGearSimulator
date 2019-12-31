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
#include <thread>
#include <bits/stdc++.h>
#include "Command.h"
using namespace std;

class ConnectControlClient : public Command {
 public:
  void runExucteMethosAsThread(string ipAdress, string portNum);
  int execute(vector<string> lexerVector, int index);
};

#endif //EX3__CONNECTCONTROLCLIENT_H_