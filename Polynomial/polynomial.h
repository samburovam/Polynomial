#ifndef _POLINOMIAL_H_
#define _POLINOMIAL_H_

#include <iostream>
#include "monom.h"
#include "list.h"

using namespace std;

class TPolynomial : public TList<TMonomData>
{
public:
  TPolynomial();
  TPolynomial(TPolynomial& _v);
  ~TPolynomial();

  TPolynomial& operator+= (TMonom& _v);

  TPolynomial operator+ (TPolynomial& _v);
  TPolynomial operator- (TPolynomial& _v);
};
#endif // _POLINOMIAL_H_
