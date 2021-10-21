#ifndef __FUNCTION_HPP
#define __FUNCTION_HPP 1

#include <vector>
#include <map>

using namespace std;

class Expression {
public:
  virtual bool check(const vector<char> &v) const = 0;
  virtual void print() const = 0;
  virtual double value(const map<char, double> &t) const = 0;
  virtual Expression* derivative(char var) const = 0;
  virtual ~Expression(){};
};

class Constant : public Expression {
public:
  Constant(double c)
    :_c(c)
  {}
  bool check(const vector<char> &v) const;
  void print() const;
  double value(const map<char, double> &t) const;
  Expression* derivative(char var) const;
private:
  double _c;
};

class Variable : public Expression {
public:
  Variable(char var)
    :_var(var)
  {}
  bool check(const vector<char> &v) const;
  void print() const;
  double value(const map<char, double> &t) const;
  Expression* derivative(char var) const;
private:
  char _var;
};

class BinOp : public Expression {
public:
  BinOp(Expression *e1, Expression *e2)
    :_e1(e1), _e2(e2)
  {}
  ~BinOp();
  bool check(const vector<char> &v) const;
protected:
  Expression *_e1;
  Expression *_e2;
private:
  BinOp(const BinOp&);
  BinOp& operator=(const BinOp&);
};

class UnOp : public Expression {
public:
  UnOp(Expression *e)
    :_e(e)
  {}
  ~UnOp();
  bool check(const vector<char> &v) const;
protected:
  Expression *_e;
private:
  UnOp(const UnOp&);
  UnOp& operator=(const UnOp&);
};

class Addition : public BinOp {
public:
  Addition(Expression *e1, Expression *e2)
    : BinOp(e1, e2)
  {}
  void print() const;
  double value(const map<char, double> &t) const;
  Expression* derivative(char var) const;
};

class Subtraction : public BinOp {
public:
  Subtraction(Expression *e1, Expression *e2)
    : BinOp(e1, e2)
  {}
  void print() const;
  double value(const map<char, double> &t) const;
  Expression* derivative(char var) const;
};

class Multiplication : public BinOp {
public:
  Multiplication(Expression *e1, Expression *e2)
    : BinOp(e1, e2)
  {}
  void print() const;
  double value(const map<char, double> &t) const;
  Expression* derivative(char var) const;
};

class Division : public BinOp {
public:
  Division(Expression *e1, Expression *e2)
    : BinOp(e1, e2)
  {}
  void print() const;
  double value(const map<char, double> &t) const;
  Expression* derivative(char var) const;
};

class Sin : public UnOp {
public:
  Sin(Expression *e)
    : UnOp(e)
  {}
  void print() const;
  double value(const map<char, double> &t) const;
  Expression* derivative(char var) const;
};

class Cos : public UnOp {
public:
  Cos(Expression *e)
    : UnOp(e)
  {}
  void print() const;
  double value(const map<char, double> &t) const;
  Expression* derivative(char var) const;
};

class Function {
public:
  Function(vector<char> args, Expression *e)
    :_args(args), _e(e)
  {}
  ~Function();
  bool check() const;
  void print() const;
  double value(const vector<double> &v) const;
  Expression* derivative(char var) const;
private:
  vector<char> _args;
  Expression *_e;
  Function(const Function&);
  Function& operator=(const Function&);
};

#endif
