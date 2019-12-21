//
// Created by michael on 20/12/2019.
//

#ifndef EX3__VARCOMMAND_H_
#define EX3__VARCOMMAND_H_

#include "Command.h"
#include "Var.h"
#include "Parser.h"

class VarCommand : public Command {
 public:
  int execute(vector<string> lexerVector, int index);
  Expression *createExp(string expIsString);
};

#endif //EX3__VARCOMMAND_H_