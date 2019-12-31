//
// Created by michael on 21/12/2019.
//

#include "IfCommand.h"
#include "VarCommand.h"

/**
 * countBetweenBrakets - the method counts the number of cells we need to jump at the vector in case
 * that the ifCommand will not by executed (the condition is false).
 * @param: vector<string> lexerVector - the vector that the lexer created from fly.txt.
 * @param: int currentIndex - the current index of the vector.
 * @return int:  the number of steps we need to jump in the array.
 */
int IfCommand::countBetweenBrakets(vector<string> lexerVector, int index) {
  int count = 0;

  while (index < lexerVector.size() && lexerVector[index] != "}") {
    count++;
    index++;
  }

  return (count + 1);
}

/**
 * execute - the method executes the if command - executes the commands between '{' and '}' if the condition she gets
 * is true. Otherwise the command would not be executed. Moreover, it returns the number of steps we
 * need to jump in the lexer vector, in order to get the next command.
 * @param: vector<string> lexerVector - the vector that the lexer created from fly.txt.
 * @param: int currentIndex - the current index of the vector.
 * @return int:  the number of steps we need to jump in the array.
 */
int IfCommand::execute(vector<string> lexerVector, int index) {

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
  if (boolExp->calculate()) {

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
      cout << "while index: ";
      cout << index << endl;

      cout << "Return index: ";
      cout << returnIndex << endl;
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