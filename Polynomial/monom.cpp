#include "monom.h"

TMonom::TMonom(TMonomData _data) : TListElem<TMonomData>(_data)
{
}

TMonom::TMonom(double* _data, int _dim, double _k) : TListElem<TMonomData>()
{
  if (_dim < 0)
    throw -1;
  
  data.dim = _dim;
  data.k = _k;

  if (data.dim > 0)
  {
    data.data = new double[data.dim];
    for (int i = 0; i < data.dim; i++)
      data.data[i] = _data[i];
  }
}

TMonom::TMonom(TMonom& _v) : TListElem<TMonomData>(_v)
{
  prev = nullptr;
  next = nullptr;
}

TMonom::~TMonom()
{
}

bool TMonom::operator==(const TMonom& _v)
{
  if (data.dim != _v.data.dim)
    throw - 1;

  if (data.dim > 0)
  {
    bool flag = true;
    for (int i = 0; i < data.dim; i++)
    {
      if (data.data[i] != _v.data.data[i])
      {
        flag = false;
        break;
      }
    }
    return flag;
  }
  else
  {
    return data.k == _v.data.k;
  }

  return false;
}

bool TMonom::operator!=(const TMonom& _v)
{
  return !this->operator==(_v);
}

TMonomData& TMonom::operator*()
{
  return data;
}

TMonomData& TMonom::operator*(int)
{
  return data;
}

double TMonom::GetK()
{
  return data.k;
}

void TMonom::SetK(double _k)
{
  data.k = _k;
}

int TMonom::GetDim()
{
  return data.dim;
}

void TMonom::SetDim(int _dim)
{
  if (data.dim == _dim)
    return;

  if (_dim < 0)
    throw -1;

  else if (_dim == 0)
  {
    if (data.dim > 0)
      delete[] data.data;
    data.dim = 0;
    data.data = nullptr;
  }
  else
  {
    if (data.dim > 0)
      delete[] data.data;

    data.dim = _dim;
    data.data = new double[data.dim];
    for (int i = 0; i < data.dim; i++)
      data.data[i] = 0;
  }
}

double& TMonom::operator[](int i)
{
  return data.data[i];
}

TMonom& TMonom::operator=(const TMonom& _v)
{
  if (this == &_v)
    return *this;
  next = nullptr;
  prev = nullptr;
  data.k = _v.data.k;

  if (data.dim == _v.data.dim)
  {
    for (int i = 0; i < data.dim; i++)
      data.data[i] = _v.data.data[i];
  }

  else if (_v.data.dim == 0) 
  {
    if (data.dim > 0)
      delete[] data.data;
    data.dim = 0;
    data.data = nullptr;
  }
  else
  {
    if (data.dim > 0)
      delete[] data.data;
    data.dim = _v.data.dim;
    data.data = new double[data.dim];
    for (int i = 0; i < data.dim; i++)
      data.data[i] = _v.data.data[i];
  }
  return *this;
}

TMonom TMonom::operator*(const TMonom& _v)
{
  if (data.dim != _v.data.dim)
    throw -1;

  TMonom temp(*this);
  temp.data.k = data.k * _v.data.k;

  for (int i = 0; i < data.dim; i++)
    temp.data.data[i] = this->data.data[i] + _v.data.data[i];

  return temp;
}

TMonom TMonom::operator/(const TMonom& _v)
{
  if (data.dim != _v.data.dim)
    throw -1;

  TMonom temp(*this);
  temp.data.k = data.k / _v.data.k;

  for (int i = 0; i < data.dim; i++)
    temp.data.data[i] = this->data.data[i] - _v.data.data[i];

  return temp;
}

TMonom* TMonom::operator+(const TMonom& _v)
{
  if (data.dim != _v.data.dim)
    throw -1;

  TMonom* temp = nullptr;

  if (*this == _v)
  {
    temp = new TMonom(*this);
    temp->data.k = this->data.k + _v.data.k;
  }
  else
  {
    temp = new TMonom[2];
    if (*this > _v)
    {
      temp[0] = *this;
      temp[1] = _v;
    }
    else
    {
      temp[0] = _v;
      temp[1] = *this;
    }
  }
  return temp;
}

TMonom* TMonom::operator-(const TMonom& _v)
{
  if (data.dim != _v.data.dim)
    throw -1;

  TMonom* temp = nullptr;

  if (*this == _v)
  {
    temp = new TMonom(*this);
    temp->data.k = this->data.k - _v.data.k;
  }
  else
  {
    temp = new TMonom[2];
    if (*this < _v)
    {
      temp[0] = *this;
      temp[1] = _v;
    }
    else
    {
      temp[0] = _v;
      temp[1] = *this;
    }
  }

  return temp;
}

bool TMonom::operator>(const TMonom& _v)
{
  if (data.dim != _v.data.dim)
    throw - 1;

  if (data.dim > 0)
  {
    for (int i = 0; i < data.dim; i++)
    {
      if (data.data[i] > _v.data.data[i])
      {
        return true;
      }
      else if (data.data[i] < _v.data.data[i])
      {
        return false;
      }
      else
        return false;
    }
  }
  else
  {
    return data.k > _v.data.k;
  }
}

bool TMonom::operator<(const TMonom& _v)
{
  if (data.dim != _v.data.dim)
    throw - 1;

  if (data.dim > 0)
  {
    for (int i = 0; i < data.dim; i++)
    {
      if (data.data[i] < _v.data.data[i])
      {
        return true;
      }
      else if (data.data[i] > _v.data.data[i])
      {
        return false;
      }
      else
        return false;
    }
  }
  else
  {
    return data.k < _v.data.k;
  }
}

istream& operator>>(istream& istr, TMonom A)
{
  int dim = 0;
  if (A.data.dim != 0)
    dim = A.data.dim;
  else
  {
    istr >> dim;
    A.SetDim(dim);
  }

  istr >> A.data.k;

  for (int i = 0; i < dim; i++)
    istr >> A[i];

  return istr;
}

ostream& operator<<(ostream& ostr, const TMonom& A)
{
  ostr << A.data.k;
  for (int i = 0; i < A.data.dim; i++)
    ostr << "* x[" << i << "]^" << A.data.data[i];
  ostr << " ";

  return ostr;
}

TMonomData::TMonomData(int t)
{
  if (t < 0)
    throw -1;
  else if ( t == 0)
  {
    dim = 0;
    data = nullptr;
  }
  else
  {
    data = new double[dim];
    for (int i = 0; i < dim; i++)
      data[i] = 0;
  }
}

TMonomData::TMonomData(double* _data, int _dim, double _k)
{
  if (_dim < 0)
    throw -1;

  dim = _dim;
  k = _k;

  if (dim > 0)
  {
    data = new double[dim];
    for (int i = 0; i < dim; i++)
      data[i] = 0;
  }
}

TMonomData::TMonomData(TMonomData& _v)
{
  dim = _v.dim;
  k = _v.k;

  if (dim > 0)
  {
    data = new double[dim];
    for (int i = 0; i < dim; i++)
      data[i] = _v.data[i];
  }
}

TMonomData::~TMonomData()
{
  if (data != 0)
  {
    delete[] data;
    data = nullptr;
    dim = 0;
    k = 0;
  }
}

TMonom* TMonom::Clone()
{
  TMonom* res = new TMonom(*this);
  return res;
}