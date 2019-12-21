cmake_minimum_required(VERSION 3.15)
project(Ex3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(Ex3 main.cpp Lexer.cpp Lexer.h ExpressionHandling.h Command.cpp Command.h Parser.cpp Parser.h OpenDataServer.cpp OpenDataServer.h InterMath.h ConnectControlClient.h Var.h SleepCommand.h VarCommand.h VarCommand.cpp PrintCommand.h WhileCommand.h IfCommand.h WhileCommand.cpp IfCommand.cpp)