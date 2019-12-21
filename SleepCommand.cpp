//
// Created by michael on 21/12/2019.
//

#include "SleepCommand.h"
#include "VarCommand.h"

int SleepCommand::execute(vector<string> lexerVector, int index) {

  string sleepTime = lexerVector[index + 1];

  VarCommand *v = new VarCommand();
  // creating the expression by using the function
  Expression *exp = v->createExp(sleepTime);

  sleep(exp->calculate());

  return 2;
}