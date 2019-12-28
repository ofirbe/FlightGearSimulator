//
// Created by michael on 16/12/2019.
//

#ifndef EX3__EXPRESSIONHANDLING_H_
#define EX3__EXPRESSIONHANDLING_H_
#include <string>
using namespace std;

class ExpressionHandling {
};

class Expression {
 public:
  virtual double calculate() = 0;
  virtual ~Expression() {}
};

class BinaryOperator : public Expression {
 public:
  BinaryOperator(Expression *expLeft, Expression *expRight) {
    expL = expLeft;
    expR = expRight;
  }
  virtual ~BinaryOperator() {
    delete (expL);
    delete (expR);
  }
 protected:
  Expression *expR;
  Expression *expL;
};

class UnaryOperator : public Expression {
 public:
  UnaryOperator(Expression *expression) {
    exp = expression;
  }
  virtual ~UnaryOperator() {
    delete (exp);
  }
 protected:
  Expression *exp;
};

class Mul : public BinaryOperator {
 public:
  double calculate() {
    return (expL->calculate() * expR->calculate());
  }
  Mul(Expression *expLeft, Expression *expRight) : BinaryOperator(expLeft, expRight) {};
};

class Div : public BinaryOperator {
 public:
  double calculate() {
    if (expR->calculate() == 0) {
      throw ("division by zero");
    }
    return (expL->calculate() / expR->calculate());
  }
  Div(Expression *expLeft, Expression *expRight) : BinaryOperator(expLeft, expRight) {};
};

class Plus : public BinaryOperator {
 public:
  double calculate() {
    return (expL->calculate() + expR->calculate());
  }
  Plus(Expression *expLeft, Expression *expRight) : BinaryOperator(expLeft, expRight) {}
};

class Minus : public BinaryOperator {
 public:
  double calculate() {
    return (expL->calculate() - expR->calculate());
  }
  Minus(Expression *expLeft, Expression *expRight) : BinaryOperator(expLeft, expRight) {}
};

class UPlus : public UnaryOperator {
 public:
  double calculate() {
    return (exp->calculate());
  }
  UPlus(Expression *expression) : UnaryOperator(expression) {}
};

class UMinus : public UnaryOperator {
 public:
  double calculate() {
    return (-(exp->calculate()));
  }
  UMinus(Expression *expression) : UnaryOperator(expression) {}
};

class Value : public Expression {
 private:
  const double num;
 public:
  Value(double n) : num(n) {}
  double calculate() {
    return num;
  }
};

class BooleanExpression : public BinaryOperator {
 private:
  string oper;
 public:

  BooleanExpression(Expression *expLeft, Expression *expRight, string newOper) : BinaryOperator(expLeft, expRight) {
    oper = newOper;
  }

  double calculate() {

    double leftValue = expL->calculate();
    double rightValue = expR->calculate();

    double x1 = leftValue * 1000000;
    double x2 = rightValue * 1000000;

    double y1 = (int) x1;
    double y2 = (int) x2;

    if (oper == "<") {
      return leftValue < rightValue;
    }
    if (oper == ">") {
      return leftValue > rightValue;
    }
    if (oper == "<=") {
      return leftValue <= rightValue;
    }
    if (oper == ">=") {
      return leftValue >= rightValue;
    }
    if (oper == "==") {
      return (y1 == y2 || (abs(y1 - y2) == 1));
    }
    if (oper == "!=") {
      return (!(y1 == y2 || (abs(y1 - y2) == 1)));
    }
  }
};

#endif //EX3__EXPRESSIONHANDLING_H_