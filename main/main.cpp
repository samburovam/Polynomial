#include <iostream>
#include "polynomial.h"
#include "list.h"
using namespace std;

int main()
{

  TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
  TMonom b(new double[3]{ 1, 2, 3 }, 3, 1);
  TMonom c(new double[3]{ 1, 1, 1 }, 3, 1);
  TMonom d(new double[3]{ 2, 2, 2 }, 3, 1);

  TPolynomial P1, P2;
  P1 += b;
  P1 += c;

  P2 += a;
  P2 += d;
  return 0;
}

