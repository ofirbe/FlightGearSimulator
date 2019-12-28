//
// Created by michael on 21/12/2019.
//

#include "WhileCommand.h"
#include "VarCommand.h"

int WhileCommand::countBetweenBrakets(vector<string> lexerVector, int index) {
  int count = 0;

  while (index < lexerVector.size() && lexerVector[index] != "}") {
    count++;
    index++;
  }

  return (count + 1);
}

int WhileCommand::execute(vector<string> lexerVector, int index) {

  int backUpIndex = index;
  int returnIndex = 0;

  string leftExp = lexerVector[index + 1];
  string oper = lexerVector[index + 2];
  string rightExp = lexerVector[index + 3];

  VarCommand *v = new VarCommand();
  Expression *newLeftExp = v->createExp(leftExp);
  Expression *newRightExp = v->createExp(rightExp);

  // creating the boolean expression
  BooleanExpression *boolExp = new BooleanExpression(newLeftExp, newRightExp, oper);

  // running the loop
  while (boolExp->calculate()) {
    index += 5;
    returnIndex = 0;
    // executing the commands in the while loop
    while (index < lexerVector.size() && lexerVector[index] != "}") {

      if (commandsMap.find(lexerVector[index]) != commandsMap.end()) {
        Command *command = commandsMap.find(lexerVector[index])->second;
        returnIndex += command->execute(lexerVector, index);
        index += command->execute(lexerVector, index);
      } else {
        // the rest of the cases: x = 4
        Command *command = commandsMap.find("var")->second;
        returnIndex += command->execute(lexerVector, index);
        index += command->execute(lexerVector, index);
      }
//      cout << "while index: ";
//      cout << index << endl;
//
//      cout << "Return index: ";
//      cout << returnIndex << endl;
    }

    newLeftExp = v->createExp(leftExp);
    newRightExp = v->createExp(rightExp);

    // creating the boolean expression
    boolExp = new BooleanExpression(newLeftExp, newRightExp, oper);

    index = backUpIndex;
  }

  if (returnIndex != 0)
    return (returnIndex + 6);
  else
    return countBetweenBrakets(lexerVector, index);
}