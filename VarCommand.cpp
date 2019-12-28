//
// Created by michael on 20/12/2019.
//

#include "VarCommand.h"
#include "InterMath.h"

Expression *VarCommand::createExp(string expIsString) {

// deleting spaces from the string
  expIsString.erase(remove(expIsString.begin(), expIsString.end(), ' '), expIsString.end());

  InterMath *inter = new InterMath();
  for (int i = 0; i < expIsString.length(); i++) {

    string partOfExp = "";
    string numAsString = "";

    // if it is a alphabetic char
    while (isalpha(expIsString[i]) || isdigit(expIsString[i]) || expIsString[i] == '_') {
      partOfExp += expIsString[i];
      i++;
    }

    // we finished part of the expression string - alphabetic string expression
    if (varMap.find(partOfExp) != varMap.end()) {
      // we found the expression at the map
      string variableSetting = "";
      variableSetting += partOfExp;
      variableSetting += "=";
      double calc = 0;

      if (varMap.find(partOfExp) != varMap.end()) {
        string simCheck = varMap.find(partOfExp)->second->getSim();
        if (flightDataMap.find(simCheck) != flightDataMap.end()) {
          calc = flightDataMap.find(simCheck)->second;
        } else {
          cout << "Error finding the value in the flight sim map :: VAR:  ";
          cout << flightDataMap.find(simCheck)->first << endl;
          cout << partOfExp << endl;

          calc = varMap.find(partOfExp)->second->calculate();
        }
      }
//      else {
//        calc = varMap.find(partOfExp)->second->calculate();
//      }

      string calcInStr = to_string(calc);
      variableSetting += calcInStr;
      inter->setVariables(variableSetting);

//      cout << "setVariables = ";
//      cout << variableSetting << endl;
    }
  }

  Expression *newExp = inter->interpret(expIsString);
//  if (newExp != nullptr) {
//    cout << "calculate = ";
//    cout << newExp->calculate() << endl;
//  }

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

    if (lexerVector[index + 2] == "->") //put var at varMap
      oper = OUT;
    else if (lexerVector[index + 2] == "<-") //update var command(sim) from the xml map
      oper = IN;
    else
      oper = REGULAR;

    if (oper != REGULAR) {
      sim = lexerVector[index + 4];
      // deleting the "" from the sim command
      sim.erase(std::remove(sim.begin(), sim.end(), '"'), sim.end());
      newVar = new Var(name, sim, oper);

      // adding the new variable into the map
      varMap[name] = newVar;

      //if oper is <- so find the value at the map that we created from the client data and set it to the var.
      if (oper == IN) {
        if (flightDataMap.find(sim) != flightDataMap.end()) {
          newVar->setValue(flightDataMap.find(sim)->second);
          newVar->setSim(sim);
        }
      }
      // return how much to jump
      return 5;
    } else { //
      // what is the name of the var (from the map) we want to move into our new local var?
      string newValueOfVar = lexerVector[index + 3];

      string newSim;
      if (varMap.find(newValueOfVar) != varMap.end()) {
        newSim = varMap.find(newValueOfVar)->second->getSim();
      }

      // creating the new exp of the variable by the string we get
      Expression *newExp = createExp(newValueOfVar);

      newVar = new Var(name, newExp->calculate(), REGULAR);

      newVar->setSim(newSim);

      // adding the new variable into the map
      varMap[name] = newVar;

      // return how much to jump
      return 4;
    }
  } else {
    // it is an existing var and we want to update it and use it
    string name = lexerVector[index];
    string newValue = lexerVector[index + 2];

    // creating the new exp of the variable by the string we get
    Expression *newExp = createExp(newValue);

    if (varMap.find(name) != varMap.end()) {
      varMap.find(name)->second->setValue(newExp->calculate());
      if (varMap.find(name)->second->getVarKind() == OUT) { //OUT= push to the queue command+value
        string strSim = varMap.find(name)->second->getSim();
        strSim.erase(std::remove(strSim.begin(), strSim.end(), '"'), strSim.end());
        connectControlQueue.push(
            strSim + " " + to_string(varMap.find(name)->second->getValue()));
      }
    } else {
      newVar = new Var(name, newExp->calculate(), REGULAR);
      // adding the new variable into the map
      varMap[name] = newVar;
      cout << "ERROR: Var from txt with operand '=' never found at the map so i create him now" << endl;
    }

    // return how much to jump
    return 3;
  }
}