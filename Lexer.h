//
// Created by michael on 13/12/2019.
//

#ifndef EX3__LEXER_H_
#define EX3__LEXER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "ExpressionHandling.h"
using namespace std;

class Lexer {

 public:
  /**
 * lexerFunc - the method lexerFunc is charge to create the vector that contain all the words and signs that exists at the fly.txt
 *the method open the file and read it line by line, separate every line by spaces and expressions and put it at the vectors ceil's.
 * @return  vector<string> :lexerVector - the vector that we created from fly.txt.
 */
  vector<string> lexerFunc() {
    int firstCloser = 0;
    int countCLoser = 0, countOpen = 0;
    vector<string> inputVector;

    fstream f;
    f.open("fly.txt");

    if (!f.is_open()) {
      throw "could not open the file";
    }

    string line;
    while (getline(f, line)) {

      // ignoring the tabs
      line.erase(remove(line.begin(), line.end(), '\t'), line.end());

      if (!line.empty()) {
        string currentWord = "";
        for (int i = 0; i < line.length(); i++) {
          //Handle parenthesis
          if (line[i] == '(') {
            if (currentWord != "") {
              inputVector.push_back(currentWord);
              i++;
              currentWord = "";
            }
            countOpen++;
            firstCloser = 1;
            while (countOpen != countCLoser) {
              if (line[i] == '(') {
                if (firstCloser == 1) {
                  firstCloser = 0;
                } else {
                  countOpen++;
                }
                currentWord += line[i];
                i++;
              } else if (line[i] == ')') {
                countCLoser++;
                i++;
              } else if (line[i] == ',') {
                if (currentWord != "") {
                  inputVector.push_back(currentWord);
                  i++;
                  currentWord = "";
                } else {
                  i++;
                }
              } else if (line[i] == '"') {
                currentWord += line[i];
                i++;
                while (line[i] != '"') {
                  currentWord += line[i];
                  i++;
                }
                currentWord += line[i];
                inputVector.push_back(currentWord);
                i++;
                currentWord = "";
              } else {
                currentWord += line[i];
                i++;
              }

            }
            if (currentWord != "") {
              inputVector.push_back(currentWord);
              i++;
              currentWord = "";
            }
          }
          if (line[i] == '/' && line[i + 1] == '/') {
            break;
          }

          if (line[i] != ',' && line[i] != '(' && line[i] != ' ' && line[i] != ')') {
            if (line[i] == '/') {
              if (line[i + 1] == '/') {
                break;
              }
            }

            //check if find an Mathematic Expression
            if (line[i] == '=' || (line[i] == '>' && line[i - 1] != '-') || (line[i] == '<' && line[i + 1] != '-')
                || line[i] == '!') {
              //push the Math Operator
              //if there is no space between the operator to the last word.
              if (currentWord != "") {
                inputVector.push_back(currentWord);
                currentWord = "";
              }
              currentWord += line[i];
              if ((line[i] == '>' && line[i + 1] == '=') || (line[i] == '<' && line[i + 1] == '=')
                  || (line[i] == '!' && line[i + 1] == '=') || (line[i] == '=' && line[i + 1] == '=')) {
                currentWord += line[i + 1];
                i++;
              }
              inputVector.push_back(currentWord);
              i++;
              currentWord = ""; //reset word

              //after operand we want the rest of the line to be one ceil at the lexer array (except {/})
              while (i < line.length()) {
                if (line[i] != ' ') {
                  if (line[i] == '{' || line[i] == '}') {
                    if (currentWord != "") {
                      inputVector.push_back(currentWord);
                      currentWord = "";
                      currentWord += line[i];
                      inputVector.push_back(currentWord);
                      currentWord = "";
                    }
                  } else {
                    currentWord += line[i];
                  }
                }
                i++;
              }
              if (currentWord != "") {
                inputVector.push_back(currentWord);
              }
              break;

            } else {
              currentWord += line[i];
              //if the last char is part of legal word!
              if ((i + 1) == line.length()) {
                // add to the list
                inputVector.push_back(currentWord);
              }
            }
          } else {

            if (currentWord != "") {
              // add to the list
              inputVector.push_back(currentWord);

            }
            //reset the current word
            currentWord = "";
          }
        }
      }
    }

    f.close();

    return inputVector;
  }

};

#endif //EX3__LEXER_H_