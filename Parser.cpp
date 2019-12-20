//
// Created by michael on 16/12/2019.
//

#include "Parser.h"

Parser::Parser() {
  _commandsMap["connectControlClient"] = new ConnectControlClient();
  _commandsMap["openDataServer"] = new OpenDataServer();
  _commandsMap["Sleep"] = new SleepCommand();
  _commandsMap["Print"] = new PrintCommand();
  _commandsMap["while"] = new WhileCommand();
  _commandsMap["if"] = new IfCommand();
  _commandsMap["var"] = new VarCommand();
}

void Parser::parse(vector<string> vct) {
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