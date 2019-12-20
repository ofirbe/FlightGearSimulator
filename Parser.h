//
// Created by michael on 16/12/2019.
//

#ifndef EX3__PARSER_H_
#define EX3__PARSER_H_
#include <map>
#include "Lexer.h"
#include "Command.h"
#include "ExpressionHandling.h"
#include "ConnectControlClient.h"
#include "OpenDataServer.h"
#include "SleepCommand.h"
#include "WhileCommand.h"
#include "IfCommand.h"
#include "PrintCommand.h"
#include "VarCommand.h"

// global map of variables
map<string, Var *> _varMap;

class Parser {
 private:
  map<string, Command *> _commandsMap;

 public:
  Parser();
  void parse(vector<string> vct);
};

#endif //EX3__PARSER_H_