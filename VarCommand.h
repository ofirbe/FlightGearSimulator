//
// Created by michael on 20/12/2019.
//

#ifndef EX3__VARCOMMAND_H_
#define EX3__VARCOMMAND_H_

#include "Command.h"
#include "Var.h"
#include "Parser.h"

class VarCommand : public Command {
  int execute(vector<string> lexerVector, int index);
};

#endif //EX3__VARCOMMAND_H_