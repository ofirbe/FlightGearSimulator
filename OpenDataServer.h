//
// Created by michael on 16/12/2019.
//

#ifndef EX3__OPENDATASERVER_H_
#define EX3__OPENDATASERVER_H_

#include "Command.h"
#include <thread>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <map>
#include "Parser.h"
class OpenDataServer : public Command {
 private:
  int socketId;
 public:
  OpenDataServer();
  ~OpenDataServer();
  void runExucteMethosAsThread(string portNum);
  int execute(vector<string> lexerVector, int index);
  string indexToCommandKey(int index);
};

#endif //EX3__OPENDATASERVER_H_