//
// Created by michael on 18/12/2019.
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
  int flagNeg = 0; //0-pos 1-neg
 protected:
  map<const string, Var *> localVarMap;
  //Expression& interpret(string str);
 public:
  InterMath() {};
  /**
 * infixToPostfix - the method converts string to queue by the shunting-yard algorithm.
 * @param: string s - the string we want to convert.
 * @return queue<string> - queue of infix expression.
 */
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
          if (!st.empty() && st.top() != "(") {
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

  /**
    * interpret - the method interpret the string it gets by using the infixToPostfix method and return expreesion
    * accordingly.
    * @param: string str - the string we want to convert.
    * @return Expression* - the expression.
    */
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
          if (localVarMap.find(qu.front()) == varMap.end()) {
            throw ("illegal variable assignment!");
          }
          st.push(reinterpret_cast<Expression *const>(this->localVarMap[qu.front()]));
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
    this->localVarMap.clear();
    return exp;
  }

  /**
  * checkIfNum - the method checks if the string it gets is a valid number.
  * @param: string str - the string we want to check.
  * @return int - 1 if the string is a number and 0 otherwise.
  */
  int checkIfNum(string str) {
    if (str[0] == '-') {
      flagNeg = 1;
      str.erase(str.begin());
    }

    int check = 1;
    int sLen = str.length();
    for (int i = 0; i < sLen; i++) {
      if (!(isdigit(str[i]) || str[i] == '.')) {
        check = 0;
      }
    }

    if (sLen == 0)
      return 0;
    else
      return check;
  }

    /**
  * prec -the methods returns precedence of operators.
  * @param: string c - the string we want to check.
  * @return int - 1 2 and (-1) by the precedence of operators.
  */
  int prec(string c) {
    if (c == "*" || c == "/")
      return 2;
    else if (c == "+" || c == "-")
      return 1;
    else
      return -1;
  }

    /**
  * setVariables - the method get string by the defition of "x=2;y=3..." and set the variables map of the interpreter
  * so the name and the value of the variable are according to the string.
  * @param: string var - the string we want to check.
  */
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
          string str = token;
          if (flagNeg == 1) {
            str.erase(str.begin());
          }
          value = stod(str);

          if (flagNeg == 1)
            value = value * (-1);

        } else {
          name = token;
        }
        Var *variable = new Var(name, value, REGULAR);
        token = strtok(NULL, "=");
        this->localVarMap[name] = variable;
      }
      temp.pop();
    }
  };
  virtual ~InterMath() {};
};
#endif //EX3__INTERMATH_H_
