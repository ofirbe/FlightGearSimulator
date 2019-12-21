//
// Created by michael on 20/12/2019.
//

#ifndef EX3__IFCOMMAND_H_
#define EX3__IFCOMMAND_H_
#include "Command.h"

class IfCommand : public Command {
 public:
  int execute(vector<string> lexerVector, int index);
};

#endif //EX3__IFCOMMAND_H_