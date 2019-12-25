#include "Lexer.h"
#include "Parser.h"
#include <thread>

int main() {
  Lexer l;
  vector<string> vct = l.lexerFunc();



  Parser parser;
  parser.parse(vct);

  return 0;
}