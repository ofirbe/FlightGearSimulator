#include "OpenDataServer.h"
#include "Lexer.h"
#include "ConnectControlClient.h"
#include <thread>
#include "Parser.h"
typedef vector<string> vector1;

int main() {
  Lexer l;
  vector<string> vct = l.lexerFunc();
  int v = 2;
  Parser parser;
  parser.parse(vct);

//  Command *c = new OpenDataServer();
//  c->execute(vct,0);

  //OpenDataServer o;
  //thread open(&OpenDataServer::execute, o, vct);

//  ConnectControlClient c;
//  c.execute(vct, 1);
  //open.join();
  return 0;
}