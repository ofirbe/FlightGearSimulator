//
// Created by michael on 20/12/2019.
//

#include "VarCommand.h"
#include "InterMath.h"

Expression *VarCommand::createExp(string expIsString) {

  InterMath *inter = new InterMath();
  for (int i = 0; i < expIsString.length(); i++) {

    string partOfExp = "";
    string numAsString = "";

    // if it is a alphabetic char
    while (isalpha(expIsString[i])) {
      partOfExp += expIsString[i];
      i++;
    }

    // we finished part of the expression string - alphabetic string expression
    if (varMap.find(partOfExp) != varMap.end()) {
      // we found the expression at the map
      string variableSetting = "";
      variableSetting += partOfExp;
      variableSetting += "=";
      double calc = varMap.find(partOfExp)->second->calculate();
      string calcInStr = to_string(calc);
      variableSetting += calcInStr;
      inter->setVariables(variableSetting);
    }
  }

  Expression *newExp = inter->interpret(expIsString);
  return newExp;
}

int VarCommand::execute(vector<string> lexerVector, int index) {
  int isNewVar = 0;
  Var *newVar;

  if (lexerVector[index] == "var") {
    // it is a new var definition
    isNewVar = 1;
  }

  if (isNewVar == 1) {
    // it is a new var
    string name = lexerVector[index + 1];
    int oper;
    string sim = "";

    if (lexerVector[index + 2] == "->")
      oper = OUT;
    else if (lexerVector[index + 2] == "<-")
      oper = IN;
    else
      oper = REGULAR;

    if (oper != REGULAR) {
      sim = lexerVector[index + 4];
      newVar = new Var(name, sim, oper);

      // adding the new variable into the map
      varMap[name] = newVar;

      // return how much to jump
      return 5;
    } else {
      // what is the name of the var (from the map) we want to move into our new local var?
      string newValueOfVar = lexerVector[index + 3];

      // creating the new exp of the variable by the string we get
      Expression *newExp = createExp(newValueOfVar);

      newVar = new Var(name, newExp->calculate(), REGULAR);

      // adding the new variable into the map
      varMap[name] = newVar;

      // return how much to jump
      return 4;
    }
  } else {
    // it is an existing var and we want to update it
    string name = lexerVector[index];
    string newValue = lexerVector[index + 2];

    // creating the new exp of the variable by the string we get
    Expression *newExp = createExp(newValue);

    newVar = new Var(name, newExp->calculate(), REGULAR);

    if (varMap.find(name) != varMap.end()) {
      //deleting the current var
      varMap.erase(varMap.find(name));
    }

    // adding the new variable into the map
    varMap[name] = newVar;

    // return how much to jump
    return 3;
  }
}