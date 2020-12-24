#include "monom.h"
#include <gtest.h>

TEST(TMonom, can_create_monom)
{
  ASSERT_NO_THROW(TMonom m1(new double[3]{ 1, 2, 3 }, 3, 1));
}

TEST(TMonom, can_non_create_monom_with_negative_dim)
{
  ASSERT_ANY_THROW(TMonom m1(new double[3]{1, 2, 3}, -3, 1));
}

TEST(TMonom, can_create_monom_with_negative_k)
{
  ASSERT_NO_THROW(TMonom m1(new double[3]{ 1, 2, 3 }, 3, -1));
}

TEST(TMonom, equal_deg)
{
  ASSERT_NO_THROW(TMonom m1(new double[3]{ 3, 3, 3 }, 3, -1));
}

TEST(TMonom, negative_and_zero_deg)
{
  ASSERT_NO_THROW(TMonom m1(new double[3]{ -3, -3, 0 }, 3, 1));
}

TEST(TMonom, can_copy_monom)
{
  TMonom m1(new double[3]{ 1, 2, 3 }, 3, 1);

  ASSERT_NO_THROW(TMonom m2(m1));
}

TEST(TMonom, can_assign_monom)
{
  TMonom m1(new double[3]{ 1, 2, 3 }, 3, 1);

  ASSERT_NO_THROW(TMonom m2 = m1);
}

TEST(TMonom, can_get_k)
{
  TMonom m1(new double[3]{ 1, 2, 3 }, 3, 5);
  EXPECT_EQ(5, m1.GetK());
}

TEST(TMonom, can_get_dim)
{
  TMonom m1(new double[3]{ 1, 2, 3 }, 3, 1);

  EXPECT_EQ(3, m1.GetDim());
}

TEST(TMonom, can_set_k)
{
  TMonom m1(new double[3]{ 1, 2, 3 }, 3, 1);

  m1.SetK(5);

  EXPECT_EQ(5, m1.GetK());
}

TEST(TMonom, can_set_dim)
{
  TMonom m1(new double[3]{ 1, 2, 3 }, 3, 1);

  m1.SetDim(10);

  EXPECT_EQ(10, m1.GetDim());
}

TEST(TMonom, can_get_elem_data)
{
  TMonom m1(new double[3]{ 1, 2, 3 }, 3, 1);

  EXPECT_EQ(1, m1[0]);
}

TEST(TMonom, operator_multiply)
{
  TMonom m1(new double[3]{ 1, 2, 3 }, 3, 1);
  TMonom m2(new double[3]{ 3, 2, 1 }, 3, 1);
  TMonom c;

  ASSERT_NO_THROW(m2 * m1);
}

TEST(TMonom, operator_division)
{
  TMonom m1(new double[3]{ 1, 2, 3 }, 3, 1);
  TMonom m2(new double[3]{ 3, 2, 1 }, 3, 1);

  ASSERT_NO_THROW(m1 / m2);
}

TEST(TMonom, operator_plus)
{
  TMonom m1(new double[1]{ 3 }, 1, 1);
  TMonom m2(new double[1]{ 1 }, 1, 1);
  TMonom* c;

  ASSERT_NO_THROW(c = (m1 + m2));
}

TEST(TMonom, operator_equality)
{
  TMonom m1(new double[3]{ 1, 2, 3 }, 3, 1);
  TMonom m2(new double[3]{ 1, 2, 3 }, 3, 1);

  EXPECT_EQ(true, m1 == m2);
}

TEST(TMonom, operator_not_equality)
{
  TMonom m1(new double[3]{ 1, 2, 3 }, 3, 1);
  TMonom m2(new double[3]{ 1, 2, 3 }, 3, 1);

  EXPECT_EQ(false, m1 != m2);
}

TEST(TMonom, operator_minus)
{
  TMonom m1(new double[3]{ 1, 2, 3 }, 3, 1);
  TMonom m2(new double[3]{ 3, 2, 1 }, 3, 1);
  TMonom* c;

  ASSERT_NO_THROW(c = (m2 - m1));
}

TEST(TMonom, operator_more)
{
  TMonom m1(new double[3]{ 1, 2, 3 }, 3, 1);
  TMonom m2(new double[3]{ 3, 2, 1 }, 3, 1);

  EXPECT_EQ(false, m1 > m2);
}

TEST(TMonom, operator_less)
{
  TMonom m1(new double[3]{ 1, 2, 3 }, 3, 1);
  TMonom m2(new double[3]{ 3, 2, 1 }, 3, 1);

  EXPECT_EQ(true, m1 < m2);
}