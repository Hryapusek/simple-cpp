set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Specify the compiler for C and C++
set(CMAKE_C_COMPILER clang-14)
set(CMAKE_CXX_COMPILER clang++-14)

# Optionally, specify the path to the Clang toolchain
set(CMAKE_FIND_ROOT_PATH /usr/lib/llvm-14)

# Set the mode for finding programs, libraries, and includes
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

