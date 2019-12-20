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

class Command {

 public:
  //return how many jumps at the array we need.
  virtual int execute(vector<string> lexerVector, int currentIndex) {};
};

#endif //EX3__COMMAND_H_
