//
// Created by michael on 16/12/2019.
//

#ifndef EX3__PARSER_H_
#define EX3__PARSER_H_

#include "Lexer.h"
#include "Command.h"
#include "ExpressionHandling.h"
#include "ConnectControlClient.h"
#include "OpenDataServer.h"
#include <map>

class Parser {
 private:
  map<string, Command*> _commandsMap;

 public:
  Parser() {
    _commandsMap["connectControlClient"] = new ConnectControlClient();
    _commandsMap["openDataServer"] = new OpenDataServer();

  };

  void parse(vector<string> vct) {
    int index = 0;
    while (index < vct.size()) {
      if (_commandsMap.find(vct[index]) != _commandsMap.end()) {
        Command *command = _commandsMap.find(vct[index])->second;
        index += command->execute(vct, index);
      } else {
        cout << "return null when try to check if command from the array is at the map\n" << endl;
        index++;
      }
    }
  }
};

#endif //EX3__PARSER_H_
