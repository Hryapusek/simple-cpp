#include <dependency/api.h>
#include <dependency/impl.h>

namespace dependency
{
  int add(int a, int b)
  {
    return add_impl(a, b);
  }
}
