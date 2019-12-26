#include "Lexer.h"
#include "Parser.h"
#include <thread>
#include "InterMath.h"

int main() {
  Lexer l;
  vector<string> vct = l.lexerFunc();

//  InterMath *inter = new InterMath();
//  string str1 = "(h0-heading)/80";
//  string str2 = "h0=-9.412254";
//  string str3 = "heading=-9.422254";
//  inter->setVariables(str2);
//  inter->setVariables(str3);
//  cout << inter->interpret(str1)->calculate() << endl;

  Parser parser;
  parser.parse(vct);

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