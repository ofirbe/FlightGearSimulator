//
// Created by ofir on 18/12/2019.
//

#ifndef EX3__INTERMATH_H_
#define EX3__INTERMATH_H_
#include <cstring>
#include <sstream>
#include <regex>
#include <stack>
#include <queue>
#include <iostream>
#include "ExpressionHandling.h"
#include "Var.h"
#include <map>

class InterMath {
 protected:
  map<const string, Var *> varMap;
  //Expression& interpret(string str);
 public:
  queue<string> infixToPostfix(string s) {
    stack<string> st;
    queue<string> qu;
    string c;
    regex varReg("^[A-Za-z]|[0-9]|[_]$");;
    int flag = 0;
    int length = s.length();
    for (int i = 0; i < length; i++) {
      flag = 0;
      c = s[i];
      string num = "";

      //check number with more then one digit.
      if (isdigit(s[i])) {
        while (prec(c) == -1 && (c != ")") && (c != "(") && i < length) {
          num += c;
          i++;
          c = s[i];
        }
        qu.push(num);
        flag = 1;
      }

      // check first minus unary expression
      bool flagUnary = false;
      if (((i == 0) && (c == "-")) || ((c == "-") && (s[i - 1] == '('))) {
        st.push("@");
        flagUnary = true;
        flag = 1;
      }
      if (((i == 0) && (c == "+")) || ((c == "+") && (s[i - 1] == '('))) {
        st.push("$");
        flagUnary = true;
        flag = 1;
      }

      if (prec(c) != (-1) && flagUnary == false) {
        while ((!st.empty()) && ((prec(st.top()) > prec(c)) || ((prec(st.top()) == prec(c))))
            && (st.top() != "(")) {
          qu.push(st.top());
          st.pop();
        }
        st.push(c);
        flag = 1;
      }
      if (c == "(") {
        st.push(c);
        flag = 1;
      }
      if (c == ")") {
        while (st.top() != "(") {
          qu.push(st.top());
          st.pop();
        }
        if (st.top() == "(") {
          st.pop();
          if (st.top() != "(") {
            qu.push(st.top());
            st.pop();
          }
        }
        flag = 1;
      }
      if (flag == 0) {//check flag if something happend this round
        //variable
        string regCheck = "";

        while (regex_match(c, varReg)) {
          regCheck += c;
          i++;
          c = s[i];
        }
        i--;
        c = s[i];
        qu.push(regCheck);
        flag = 1;
      }
    }
    while (!st.empty()) {
      qu.push(st.top());
      st.pop();
    }
    return qu;
  }
  InterMath();
  Expression *interpret(string str) {
    queue<string> qu = infixToPostfix(str);
    stack<Expression *> st; //stack for expressions.
    while (!qu.empty()) {
      //If Binary Expression
      if ((qu.front() != "@") && (qu.front() != "$")) {
        if (checkIfNum(qu.front())) {
          Value *val = new Value(stod(qu.front()));
          st.push(val);
          qu.pop();
        } else if (prec(qu.front()) != -1) {
          string op = qu.front();
          if (st.empty()) {
            throw ("illegal math expression");
          }
          Expression *right = st.top();
          st.pop();
          if (st.empty()) {
            throw ("illegal math expression");
          }
          Expression *left = st.top();
          st.pop();
          if (op == "+") {
            Plus *ex = new Plus(left, right);
            st.push(ex);
          } else if (op == "-") {
            Minus *ex = new Minus(left, right);
            st.push(ex);
          } else if (op == "*") {
            Mul *ex = new Mul(left, right);
            st.push(ex);
          } else if (op == "/") {
            Div *ex = new Div(left, right);
            st.push(ex);
          }
          qu.pop();
        } else {
          //variable
          if (varMap.find(qu.front()) == varMap.end()) {
            throw ("illegal variable assignment!");
          }

          st.push(reinterpret_cast<Expression *const>(this->varMap[qu.front()]));////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          /*
           * I changed that line because it wrote that there is a problem with the casting.
           *
           */

          qu.pop();
        }
      }
        //else- the Expression is Unary.
      else {
        string unOp = qu.front();
        Expression *uEx = st.top();
        st.pop();
        //@=minus unary
        if (unOp == "@") {
          UMinus *ex = new UMinus(uEx);
          st.push(ex);
          //$=plus unary
        } else if (unOp == "$") {
          UPlus *ex = new UPlus(uEx);
          st.push(ex);
        }
        qu.pop();
      }
    }
    Expression *exp = st.top();
    st.pop();
    //clear map
    this->varMap.clear();
    return exp;
  }
  int checkIfNum(string str) {
    //1=number;0=notNumber
    int check = 1;
    int sLen = str.length();
    for (int i = 0; i < sLen; i++) {
      if (!(isdigit(str[i]) || str[i] == '.')) {
        check = 0;
      }
    }
    return check;
  }
//Function to return precedence of operators
  int prec(string c) {
    if (c == "*" || c == "/")
      return 2;
    else if (c == "+" || c == "-")
      return 1;
    else
      return -1;
  }
  void setVariables(string var) {
    stack<string> temp;
    char *newStr = const_cast<char *>(var.c_str());
    char *token = strtok(newStr, ";");
    while (token != NULL) {
      temp.push(token);
      token = strtok(NULL, ";");
    }
    while (!temp.empty()) {
      double value = 0;
      string name = "";
      newStr = const_cast<char *>(temp.top().c_str());
      token = strtok(newStr, "=");
      while (token != NULL) {
        if (checkIfNum(token)) {
          value = stod(token);
        } else {
          name = token;
        }
        Var *variable = new Var(name, value, REGULAR);
        token = strtok(NULL, "=");
        this->varMap[name] = variable;
      }
      temp.pop();

    }
  };
  virtual ~InterMath() {};
};
#endif //EX3__INTERMATH_H_
