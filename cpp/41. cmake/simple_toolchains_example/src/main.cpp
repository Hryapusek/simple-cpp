#include <iostream>

#define Q(x) #x
#define QUOTE(x) Q(x)

int main()
{
  std::cout << QUOTE(COMPILER_NAME_s0) << std::endl;
  return 0;
}
