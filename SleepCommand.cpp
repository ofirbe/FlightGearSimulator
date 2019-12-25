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
  //sleep for millisecond (/1000)
  int timeToSleep = exp->calculate();
  std::this_thread::sleep_for(std::chrono::milliseconds(timeToSleep));

  return 2;
}