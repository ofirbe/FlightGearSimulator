#include "OpenDataServer.h"
#include "Lexer.h"
#include "ConnectControlClient.h"
#include <thread>
#include "Parser.h"

int main() {
  Lexer l;
  vector<string> vct = l.lexerFunc();

  Parser parser;
  parser.parse(vct);

  //ConnectControlClient c;
  //c.execute(vct, 1);
  return 0;
}