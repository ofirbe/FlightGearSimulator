#include "OpenDataServer.h"
#include "Lexer.h"
#include "ConnectControlClient.h"
#include <thread>
#include "Parser.h"

int main() {
  Lexer l;
  vector<string> vct = l.lexerFunc();

//  OpenDataServer o;
//  o.execute(vct, 1);

  Parser parser;
  parser.parse(vct);

  for (auto x:varMap) {
    cout << "name = " + x.first + "  value = ";
    cout << x.second->calculate() << endl;
  }

//  ConnectControlClient c;
//  c.execute(vct, 1);
  return 0;
}