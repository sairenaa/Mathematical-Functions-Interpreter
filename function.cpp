#include <iostream>
#include <cmath>

using namespace std;

#include "function.hpp"

bool Constant::check(const vector<char> &v) const {
  return true;
}

bool Variable::check(const vector<char> &v) const {
  for(unsigned i = 0; i< v.size(); i++)
    if(v[i] == _var)
      return true;
  return false;
}

BinOp::~BinOp() {
  delete _e1;
  delete _e2;
}

UnOp::~UnOp() {
  delete _e;
}

bool BinOp::check(const vector<char> &v) const {
  return _e1->check(v) && _e2->check(v);
}

bool UnOp::check(const vector<char> &v) const {
  return _e->check(v);
}

bool Function::check() const {
  return _e->check(_args);
}

Function::~Function() {
  delete _e;
}

void Function::print() const {
  _e->print();
  cout << endl;
}

void Constant::print() const {
  cout << _c;
}

void Variable::print() const {
  cout << _var;
}

void Addition::print() const {
  cout << "(";
  _e1->print();
  cout << ")+(";
  _e2->print();
  cout << ")";
}

void Subtraction::print() const {
  cout << "(";
  _e1->print();
  cout << ")-(";
  _e2->print();
  cout << ")";
}

void Multiplication::print() const {
  cout << "(";
  _e1->print();
  cout << ")*(";
  _e2->print();
  cout << ")";
}

void Division::print() const {
  cout << "(";
  _e1->print();
  cout << ")/(";
  _e2->print();
  cout << ")";
}

void Sin::print() const {
  cout << "sin(";
  _e->print();
  cout << ")";
}

void Cos::print() const {
  cout << "cos(";
  _e->print();
  cout << ")";
}

double Function::value(const vector<double> &v) const {
  if(v.size() != _args.size())
    throw "Incorrect number of arguments";
  map<char, double> t;
  for(unsigned i=0;i<v.size();i++)
    t[_args[i]] = v[i];
  return _e->value(t);
}

double Constant::value(const map<char, double> &t) const {
  return _c;
}

double Variable::value(const map<char, double> &t) const {
  map<char, double>::const_iterator i = t.find(_var);
  return i->second;
}

double Addition::value(const map<char, double> &t) const {
  return _e1->value(t) + _e2->value(t);
}

double Subtraction::value(const map<char, double> &t) const {
  return _e1->value(t) - _e2->value(t);
}

double Multiplication::value(const map<char, double> &t) const {
  return _e1->value(t) * _e2->value(t);
}

double Division::value(const map<char, double> &t) const {
  return _e1->value(t) / _e2->value(t);
}

double Sin::value(const map<char, double> &t) const {
  return sin(_e->value(t));
}

double Cos::value(const map<char, double> &t) const {
  return cos(_e->value(t));
}

Expression* Function::derivative(char var) const {
  return _e->derivative(var);
}

Expression* Constant::derivative(char var) const {
  return new Constant(0);
}

Expression* Variable::derivative(char var) const {
  if(_var == var)
    return new Constant(1);
  return new Constant(0);
}

Expression* Addition::derivative(char var) const {
  return new Addition(_e1->derivative(var), _e2->derivative(var));
}

Expression* Subtraction::derivative(char var) const {
  return new Subtraction(_e1->derivative(var), _e2->derivative(var));
}

Expression* Multiplication::derivative(char var) const {
  return new Addition(new Multiplication(_e1->derivative(var), _e2),
		      new Multiplication(_e1, _e2->derivative(var)));
}

Expression* Division::derivative(char var) const {
  return new Division(new Subtraction(new Multiplication(_e1->derivative(var), _e2), new Multiplication(_e1, _e2->derivative(var))), new Multiplication(_e2, _e2));
}

Expression* Sin::derivative(char var) const {
  return new Multiplication(new Cos(_e), _e->derivative(var));
}

Expression* Cos::derivative(char var) const {
  return new Multiplication(new Multiplication(new Constant(-1), new Sin(_e)), _e->derivative(var));
}
