//
// Created by michael on 21/12/2019.
//

#include "PrintCommand.h"
#include "ExpressionHandling.h"

int PrintCommand::execute(vector<string> lexerVector, int index) {

  string strToPrint = lexerVector[index + 1];
  if (strToPrint.front() == '"' && strToPrint.back() == '"') {
    // it is a string (not a var)
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