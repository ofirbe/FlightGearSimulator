//
// Created by michael on 20/12/2019.
//

#ifndef EX3__PRINTCOMMAND_H_
#define EX3__PRINTCOMMAND_H_
#include "Command.h"
#include "Parser.h"

class PrintCommand : public Command {
 public:
  int execute(vector<string> lexerVector, int index);
};

#endif //EX3__PRINTCOMMAND_H_