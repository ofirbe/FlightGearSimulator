//
// Created by michael on 16/12/2019.
//

#ifndef EX3__COMMAND_H_
#define EX3__COMMAND_H_

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
using namespace std;

/**
 * execute - the method executes the current command, and returns the number of steps we need to jump in the lexer
 * vector, in order to get the next command.
 * @param: vector<string> lexerVector - the vector that the lexer created from fly.txt.
 * @param: int currentIndex - the current index of the vector.
 * @return int:  the number of steps we need to jump in the array.
 */

class Command {

 public:
  virtual int execute(vector<string> lexerVector, int currentIndex) {};
};

#endif //EX3__COMMAND_H_
