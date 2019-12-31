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

// declaration of global map of variables
extern map<string, Var *> varMap; //all the var that the parser found under the Command "var" (from fly.txt)
extern map<string, Command *> commandsMap; //all the commands like OpenDataServer,ConnectClient etc...
extern map<string, double> flightDataMap; //all the info that exist at the xml file and we get from OpenDataServer.
extern queue <string> connectControlQueue; //the connectControlClient will always listen to the queue

class Parser {
 public:
  Parser();
  void parse(vector<string> vct);
  void initializeFlightDataMap();
};

#endif //EX3__PARSER_H_