//
// Created by michael on 20/12/2019.
//

#ifndef EX3__VAR_H_
#define EX3__VAR_H_

#endif //EX3__VAR_H_
#include <string>
#include "ExpressionHandling.h"
using namespace std;

// ENUM that represents the type of the var: -> or = or <-
enum kindOfVar { IN = 1, OUT = 2, REGULAR = 3 };

class Var : public Expression {
 private:
  string name;
  double value;
  int varKind;
  string simCommand;

 public:
  Var(string n, double val, int newVarKind) {
    name = n;
    value = val;
    varKind = newVarKind;

    // if we did not fill that field, the default value is "" (empty)
    simCommand = "";
  }
  Var(string n, double val, int newVarKind, string newSimCommand) {
    name = n;
    value = val;
    varKind = newVarKind;
    simCommand = newSimCommand;
  }

  double calculate() {
    return value;
  }

  Var &operator++() {
    value = value + 1;
    return *this;
  }
  Var &operator--() {
    value = value - 1;
    return *this;
  }
  Var &operator+=(double num) {
    value = value + num;
    return *this;
  }
  Var &operator-=(double num) {
    value = value - num;
    return *this;
  }
  Var &operator++(int) {
    value = value + 1;
    return *this;

  }
  Var &operator--(int) {
    value = value - 1;
    return *this;
  }
};