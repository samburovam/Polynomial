#ifndef _LIST_
#define _LIST_
#include <iostream>

using namespace std;

template <class T>
class TListElem
{
protected:
  T data;
  TListElem* next = 0;
  TListElem* prev = 0;
public:
  TListElem();
  TListElem(T _data);
  ~TListElem();

  T GetData();
  TListElem* GetNext();
  TListElem* GetPrev();

  virtual TListElem<T>* Clone();


  void SetData(T _data);
  void SetNext(TListElem* _next);
  void SetPrev(TListElem* _prev);
  
  template <class T1>
  friend ostream& operator<< (ostream& ostr, const TListElem<T1>& A);
  template <class T1>
  friend istream& operator>> (istream& istr, TListElem<T1> A);
};

template <class T>
class TList
{
protected:
  TListElem<T>* root = nullptr; // корень списка
  TListElem<T>* end = nullptr;  // конец списка (индекс последнего элемента)
  int count; // количество элементов списка
   
public:
  TList();  // конструктор по умолчанию
  TList(TList<T>& _v); // конструктор копирования
 ~TList();

  virtual TList<T>& operator =(TList<T>& _v); // оператор присваивания

  void InsFirst(T d); // запись элемента в стек
  void InsLast(T d); 
  void Ins(TListElem<T>* e, T d); // вставка элемента в список после указанного элемента

  TListElem<T>* GetFirst(); // извлечь элемент
  TListElem<T>* GetLast(); 

  void DelFirst();
  void DelLast();
  void Del(TListElem<T>* e);

  template <class T1>
  friend ostream& operator<< (ostream& ostr, const TList<T1>& A);
  template <class T1>
  friend istream& operator>> (istream& istr, TList<T1>& A);

  bool IsFull() const;
  bool IsEmpty() const; 
  int GetCount(); // количество элементов
};

template<class T1>
inline ostream& operator<<(ostream& ostr, const TListElem<T1>& A)
{
  return ostr << A.data;
}

template<class T1>
inline istream& operator>>(istream& istr, TListElem<T1> A)
{
  return istr >> A.data;
}

template <class T1>
ostream& operator<< (ostream& ostr, const TList<T1>& A)
{
  TListElem<T1>* i = A.root;
  while (i != 0)
  {
    ostr << *i << endl;
    i = i->GetNext();
  }
  return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TList<T1>& A) 
{
  int count;
  istr >> count;
  for (int i = 0; i < A.count; i++) 
  {
    T1 d;
    istr >> d;
    A.InsLast(d);
  }
  return istr;
}

template<class T>
inline TList<T>::TList()
{
  root = nullptr;
  end = nullptr;
  count = 0;
}

template <class T>
TList<T>::TList(TList<T>& _v)
{
  count = _v.count;

  TListElem<T>* i = _v.root; // индекс пришедшего списка
  TListElem<T>* j = this->root; // корень несуществующего списка
  TListElem<T>* p = 0; // указатель на предка

  root = nullptr;
  end = nullptr;

  while (i != 0) // копируем список
  {
    j = i->Clone();
    j->SetNext(0);
    if (p != 0)
    {
      p->SetNext(j);
      j->SetPrev(p);
    }

    p = j; // переход

    if (root == 0)
      root = j;

    end = j;
    i = i->GetNext();
  }
}

template <class T>
TList<T>::~TList()
{
  if (this->root != nullptr)
  {
    TListElem<T>* i = this->root;
    TListElem<T>* p = nullptr;

    while (i != nullptr)
    {
      p = i;
      i = i->GetNext();
      delete p;
    }

    this->root = nullptr;
    this->end = nullptr;
    count = 0;
  }
}

template <class T>
TList<T>& TList<T>::operator =(TList<T>& _v)
{
  if (this == &_v)
    return *this;

  if (this->root != nullptr)
  {
    TListElem<T>* i = this->root;
    TListElem<T>* p = nullptr;

    while (i != nullptr)
    {
      p = i;
      i = i->GetNext();
      delete p;
    }

    this->root = nullptr;
    this->end = nullptr;
    count = 0;
  }

  count = _v.count;

  TListElem<T>* i = _v.root;
  TListElem<T>* j = this->root;
  TListElem<T>* p = nullptr;

  while (i != nullptr)
  {
    j = i->Clone();
    j->SetNext(0);
    if (p != nullptr)
    {
      p->SetNext(j);
      j->SetPrev(p);
    }

    p = j;

    if (root == nullptr)
      root = j;

    end = j;
    i = i->GetNext();
  }

  return *this;
}

template<class T>
void TList<T>::InsFirst(T d)
{
  if (this->IsFull())
    throw -1;

  TListElem<T>* temp = d.Clone();
  temp->SetNext(root);
  root = temp;
  if (end == 0)
    end = temp;
  count++;
}

template<class T>
void TList<T>::InsLast(T d)
{
  if (this->IsFull())
    throw -1;

  if (end == nullptr)
    end = d.Clone();
  else
  {
    TListElem<T>* temp = d.Clone();
    end->SetNext(temp);
    end = temp;
  }
  if (root == nullptr)
    root = end;
  count++;
}

template<class T>
void TList<T>::Ins(TListElem<T>* e, T d)
{
  TListElem<T>* temp = d.Clone();
  temp->SetNext(e->GetNext());
  temp->SetPrev(e);
  e->GetNext()->SetPrev(temp);
  e->SetNext(temp);
  count++;
}

template<class T>
bool TList<T>::IsFull(void) const
{
  try
  {
    TListElem<T>* temp = new TListElem<T>(1);
    delete temp;
    return false;
  }
  catch (...)
  {
    return true;
  }
}

template<class T>
bool TList<T>::IsEmpty(void) const
{
  return count == 0;
}


template<class T>
TListElem<T>* TList<T>::GetFirst()
{
  return root;
}

template<class T>
TListElem<T>* TList<T>::GetLast()
{
  return end;
}

template<class T>
void TList<T>::DelFirst()
{
  TListElem<T>* i = this->root;
  root = root->GetNext();
  count--;
  delete i;
}

template<class T>
void TList<T>::DelLast()
{
  TListElem<T>* i = this->end;
  end = root->GetPrev();
  count--;
  delete i;
}

template<class T>
void TList<T>::Del(TListElem<T>* e)
{
  e->GetPrev()->SetNext(e->GetNext());
  e->GetNext()->SetPrev(e->GetPrev());

  count--;
  delete e;
}

template<class T>
int TList<T>::GetCount()
{
  return count;
}

template<class T>
TListElem<T>::TListElem()
{
  data = 0;
  next = nullptr;
  prev = nullptr;
}

template<class T>
TListElem<T>::TListElem(T _data)
{
  data = _data;
  next = nullptr;
  prev = nullptr;
}

template<class T>
TListElem<T>::~TListElem()
{
  next = nullptr;
  prev = nullptr;
}

template<class T>
T TListElem<T>::GetData()
{
  return data;
}

template<class T>
TListElem<T>* TListElem<T>::GetNext()
{
  return next;
}

template<class T>
TListElem<T>* TListElem<T>::GetPrev()
{
  return prev;
}

template<class T>
void TListElem<T>::SetData(T _data)
{
  data = _data;
}

template<class T>
void TListElem<T>::SetNext(TListElem* _next)
{
  next = _next;
}

template<class T>
void TListElem<T>::SetPrev(TListElem* _prev)
{
  prev = _prev;
}

template<class T>
TListElem<T>* TListElem<T>::Clone()
{
  TListElem<T>* res = new TListElem<T>(*this);
  return res;
}
#endif // !_LIST_H_