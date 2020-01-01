#include "Lexer.h"
#include "Parser.h"
#include <thread>

int main() {
  Lexer l;
  vector<string> vct = l.lexerFunc();

  Parser parser;
  parser.parse(vct);


//  for (int i = 0; i < vct.size(); i++) {
//    cout << "index=";
//    cout << i;
//    cout << " ";
//    cout << vct[i] << endl;
//  }


  return 0;
}