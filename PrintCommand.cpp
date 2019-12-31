//
// Created by michael on 21/12/2019.
//

#include "PrintCommand.h"
#include "ExpressionHandling.h"

/**
 * execute - the method executes the print command - prints the required value, and returns the number of steps we
 * need to jump in the lexer vector, in order to get the next command.
 * @param: vector<string> lexerVector - the vector that the lexer created from fly.txt.
 * @param: int currentIndex - the current index of the vector.
 * @return int:  the number of steps we need to jump in the array.
 */
int PrintCommand::execute(vector<string> lexerVector, int index) {

  string strToPrint = lexerVector[index + 1];
  if (strToPrint.front() == '"' && strToPrint.back() == '"') {
    // it is a string (not a var)
    strToPrint.erase(std::remove(strToPrint.begin(), strToPrint.end(), '"'), strToPrint.end());
    cout << strToPrint << endl;
  } else {
    // it is a var
    VarCommand *v = new VarCommand();
    // creating the expression by using the function
    Expression *exp = v->createExp(strToPrint);
    cout << exp->calculate() << endl;
  }

  // how many cells to jump
  return 2;
}