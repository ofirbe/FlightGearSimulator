//
// Created by michael on 16/12/2019.
//

#include "Parser.h"

// definition of the global variable
map<string, Var *> varMap;
map<string, Command *> commandsMap;

Parser::Parser() {
  commandsMap["connectControlClient"] = new ConnectControlClient();
  commandsMap["openDataServer"] = new OpenDataServer();
  commandsMap["Sleep"] = new SleepCommand();
  commandsMap["Print"] = new PrintCommand();
  commandsMap["while"] = new WhileCommand();
  commandsMap["if"] = new IfCommand();
  commandsMap["var"] = new VarCommand();
}

void Parser::parse(vector<string> vct) {
  int index = 0;
  while (index < vct.size()) {
    // it is a command from the map
    if (commandsMap.find(vct[index]) != commandsMap.end()) {
      Command *command = commandsMap.find(vct[index])->second;
      index += command->execute(vct, index);
    } else {
      // the rest of the cases: x = 4
      Command *command = commandsMap.find("var")->second;
      index += command->execute(vct, index);
    }
  }
}