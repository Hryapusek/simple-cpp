#include <iostream>
#include <fmt/format.h>

#define Q(x) #x
#define QUOTE(x) Q(x)

int main()
{
  fmt::println("Hello, {} from {}!", "world", QUOTE(COMPILER_NAME_s0));
  return 0;
}
