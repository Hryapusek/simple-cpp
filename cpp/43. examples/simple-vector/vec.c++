#include <cstddef>

/*
  Box(T value) : value_(value) {
      // value_ = value;
  }
*/

template< typename T >
class Vec
{
public:
  Vec() :
    m_data {nullptr},
    m_size {0}
  {}

  Vec(size_t sz)
  {
    this->m_size = sz;
    // T * arr = (T *)malloc(sizeof(T) * sz)
    // new (arr) ();
    // new (arr + 1) ();
    // ... sz
    this->m_data = new T [sz]; // sz * sizeof(T)
  }

  Vec(size_t sz, T obj)
  {
    this->m_size = sz;
    this->m_data = new T[sz];
    for (size_t i = 0; i < sz; i++)
    {
        this->m_data[i] = obj;
    }
  }

  void push_back(T obj)
  {
    T * tmp = new T[this->m_size + 1];
    for (size_t i = 0; i < this->m_size; i++)
    {
        tmp[i] = this->m_data[i];
    }
    tmp[this->m_size] = obj;
    delete[] this->m_data;
    this->m_data = tmp;
    this->m_size++;
  }

  ~Vec()
  {
    delete[] this->m_data;
  }

private:
  T * m_data;
  size_t m_size;
};
