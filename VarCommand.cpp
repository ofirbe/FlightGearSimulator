//
// Created by michael on 20/12/2019.
//

#include "VarCommand.h"

int VarCommand::execute(vector<string> lexerVector, int index) {
  string name = lexerVector[index + 1];
  int oper;
  if (lexerVector[index + 2] == "->")
    oper = OUT;
  else if (lexerVector[index + 2] == "<-")
    oper = IN;
  else
    oper = REGULAR;
  string sim = lexerVector[index + 4];

  Var *newVar = new Var(name, sim, oper);

  // adding the new variable into the map
  _varMap[name] = newVar;

  // return how much to jump
  return 5;
}