#include "polynomial.h"

TPolynomial::TPolynomial() : TList<TMonomData>()
{
}

TPolynomial::TPolynomial(TPolynomial& _v) : TList<TMonomData>(_v)
{
}

TPolynomial::~TPolynomial()
{
}

TPolynomial& TPolynomial::operator+=(TMonom& _v)
{
  if (this->root == nullptr)
  {
    this->root = _v.Clone();
    this->end = this->root;
  }
  else
  {
    TMonom* temp_1 = static_cast<TMonom*>(this->root);
    
    while (temp_1 != nullptr)
    {
      if (*temp_1 == _v)
        temp_1->SetK(temp_1->GetK() +_v.GetK());
      else
      {
        TMonom* temp_2 = _v.Clone();
        if (*temp_1 < _v)
        {
          temp_2->SetPrev(temp_1->GetPrev());
          temp_2->SetNext(temp_1);

          if (temp_1->GetPrev() != nullptr)
            temp_1->GetPrev()->SetNext(temp_2);
          else
            this->root = temp_2;

          temp_1->SetPrev(temp_2);
          return *this;
        }
        else
        {
          if (temp_1->GetNext() == nullptr)
          {
            temp_2->SetPrev(temp_1);
            temp_1->SetNext(temp_2);
            this->end = temp_2;
            return *this;
          }
          else
            temp_1 = static_cast<TMonom*>(temp_1->GetNext());
        }
      }
    }
  }
  return *this;
}

TPolynomial TPolynomial::operator+(TPolynomial& _v)
{
  if (_v.root == nullptr || root == nullptr)
    throw -1;

  TPolynomial res;
  TMonom* temp_1 = static_cast<TMonom*>(_v.root);
  TMonom* temp_2 = static_cast<TMonom*>(root); 
  TMonom* r = nullptr;

  while (temp_1 != nullptr && temp_2 != nullptr)
  {
    TMonom temp_3;
    if (*temp_1 == *temp_2)
    {
      temp_3 = ((*temp_1) + (*temp_2))[0]; 
      temp_1 = static_cast<TMonom*>(temp_1->GetNext());
      temp_2 = static_cast<TMonom*>(temp_2->GetNext());
    }
    else if (*temp_1 < *temp_2)
    {
      temp_3 = *temp_2;
      temp_2 = static_cast<TMonom*>(temp_2->GetNext());
    }
    else
    {
      temp_3 = *temp_1;
      temp_1 = static_cast<TMonom*>(temp_1->GetNext());
    }

    if (r == nullptr)
    {
      res += temp_3;
      r = static_cast<TMonom*>(res.root);
    }
    else
    {
      r->SetNext(temp_3.Clone());
      r->GetNext()->SetPrev(static_cast<TMonom*>(r));
      r = static_cast<TMonom*>(r->GetNext());
    }
  }
  if (temp_1 != nullptr)
  {
    while (temp_1 != nullptr)
    {
      r->SetNext(new TMonom(*temp_1));
      r->GetNext()->SetPrev(r);
      r = static_cast<TMonom*>(r->GetNext());
      temp_1 = static_cast<TMonom*>(temp_1->GetNext());
    }
  }
  else if (temp_2 != nullptr)
  {
    while (temp_2 != nullptr)
    {
      r->SetNext(new TMonom(*temp_2));
      r->GetNext()->SetPrev(r);
      r = static_cast<TMonom*>(r->GetNext());
      temp_1 = static_cast<TMonom*>(temp_2->GetNext());
    }
  }
  return res;
}

TPolynomial TPolynomial::operator-(TPolynomial& _v)
{
  {
    if (_v.root == nullptr || root == nullptr)
      throw -1;

    TPolynomial res;
    TMonom* temp_1 = static_cast<TMonom*>(_v.root);
    TMonom* temp_2 = static_cast<TMonom*>(root);
    TMonom* r = nullptr;

    while (temp_1 != 0 && temp_2 != 0)
    {
      TMonom temp_3;
      if (*temp_1 == *temp_2)
      {
        temp_3 = ((*temp_1) - (*temp_2))[0];
        temp_1 = static_cast<TMonom*>(temp_1->GetNext());
        temp_2 = static_cast<TMonom*>(temp_2->GetNext());
      }
      else if (*temp_1 > *temp_2)
      {
        temp_3 = *temp_1;
        temp_1 = static_cast<TMonom*>(temp_1->GetNext());
      }
      else
      {
        temp_3 = *temp_2;
        temp_2 = static_cast<TMonom*>(temp_2->GetNext());
      }

      if (r == 0)
      {
        res += temp_3;
        r = static_cast<TMonom*>(res.root);
      }
      else
      {
        r->SetNext(temp_3.Clone());
        r->GetNext()->SetPrev(static_cast<TMonom*>(r));
        r = static_cast<TMonom*>(r->GetNext());
      }
    }
    if (temp_1 != nullptr)
    {
      while (temp_1 != nullptr)
      {
        r->SetNext(new TMonom(*temp_1));
        r->GetNext()->SetPrev(r);
        r = static_cast<TMonom*>(r->GetNext());
        temp_1 = static_cast<TMonom*>(temp_1->GetNext());
      }
    }
    else if (temp_2 != nullptr)
    {
      while (temp_2 != nullptr)
      {
        r->SetNext(new TMonom(*temp_2));
        r->GetNext()->SetPrev(r);
        r = static_cast<TMonom*>(r->GetNext());
        temp_1 = static_cast<TMonom*>(temp_2->GetNext());
      }
    }
    return res;
  }
}
