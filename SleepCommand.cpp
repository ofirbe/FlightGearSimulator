//
// Created by michael on 21/12/2019.
//

#include "SleepCommand.h"
#include "VarCommand.h"

/**
 * execute - the method executes the sleep command - makes the current thread sleep for the required time, and returns
 * the number of steps we need to jump in the lexer vector, in order to get the next command.
 * @param: vector<string> lexerVector - the vector that the lexer created from fly.txt.
 * @param: int currentIndex - the current index of the vector.
 * @return int:  the number of steps we need to jump in the array.
 */
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