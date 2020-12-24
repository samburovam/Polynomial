#include "polynomial.h"
#include <gtest.h>

TEST(TPolynomial, can_create_polynomial)
{
  ASSERT_NO_THROW(TPolynomial P1);
}

TEST(TPolynomial, can_copy_polynomial)
{
  TPolynomial P1;

  ASSERT_NO_THROW(TPolynomial P2(P1));
}

TEST(TPolynomial, operator_plus_equal)
{
  TMonom m1(new double[3]{ 1, 2, 3 }, 3, 1);
  TPolynomial P1;

  ASSERT_NO_THROW(P1 += m1);
}

TEST(TPolynomial, operator_plus)
{
  TMonom m1(new double[3]{ 1, 2, 3 }, 3, 1);
  TMonom m2(new double[3]{ 3, 2, 1 }, 3, 1);
  TPolynomial P1, P2;

  P1 += m1;
  P2 += m2;

  ASSERT_NO_THROW(P2 + P1);
}

TEST(TPolynomial, operator_minus)
{
  TMonom m1(new double[3]{ 1, 2, 3 }, 3, 1);
  TMonom m2(new double[3]{ 3, 2, 1 }, 3, 1);
  TPolynomial P1, P2;

  P1 += m1;
  P2 += m2;

  ASSERT_NO_THROW(P2 - P1);
}


