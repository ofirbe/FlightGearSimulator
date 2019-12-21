//
// Created by michael on 20/12/2019.
//

#ifndef EX3__WHILECOMMAND_H_
#define EX3__WHILECOMMAND_H_
#include "Command.h"

class WhileCommand : public Command {
 public:
  int execute(vector<string> lexerVector, int index);
};


#endif //EX3__WHILECOMMAND_H_