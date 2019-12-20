//
// Created by michael on 20/12/2019.
//

#ifndef EX3__WHILECOMMAND_H_
#define EX3__WHILECOMMAND_H_
#include "Command.h"
#endif //EX3__WHILECOMMAND_H_
class WhileCommand : public Command {
  int execute(vector<string> lexerVector, int index) {
    cout<<"Im While"<<endl;
    return 1;
  }
};