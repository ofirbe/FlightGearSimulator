#include "Lexer.h"
#include "Parser.h"
#include <thread>
#include "InterMath.h"

int main() {
  Lexer l;
  vector<string> vct = l.lexerFunc();

  Parser parser;
  parser.parse(vct);

//  varMap["h0"] = new Var("h0", 6);
//  varMap["heading"] = new Var("heading", 4);
//
//  VarCommand *v = new VarCommand();
//  string exp = "(h0 - heading)/80";
//  Expression *newExp = v->createExp(exp);
//
//  cout << newExp->calculate() << endl;


//  InterMath *inter = new InterMath();
//  string str1 = "(h0-heading)/80";
//  string str2 = "h0=-9.412254";
//  string str3 = "heading=-9.422254";
//  inter->setVariables(str2);
//  inter->setVariables(str3);
//  cout << inter->interpret(str1)->calculate() << endl;

//  varMap["throttle"] = new Var("throttle", 0.2);
//  varMap;
//
//  string leftExp = vct[134 + 1];
//  string oper = vct[134 + 2];
//  string rightExp = vct[134 + 3];
//
//  VarCommand *v = new VarCommand();
//  Expression *newLeftExp = v->createExp(leftExp);
//  Expression *newRightExp = v->createExp(rightExp);
//
//  BooleanExpression *boolExp = new BooleanExpression(newLeftExp, newRightExp, oper);
//
//  cout.precision(17);
//  cout << newLeftExp->calculate() << endl;
//  cout.precision(17);
//  cout << newRightExp->calculate() << endl;
//
//  cout << boolExp->calculate() << endl;


//  for (int i = 0; i < vct.size(); i++) {
//    cout << "index=";
//    cout << i;
//    cout << " ";
//    cout << vct[i] << endl;
//  }

//  cout << vct[196] << endl;
//  cout << vct.size() << endl;

  return 0;
}