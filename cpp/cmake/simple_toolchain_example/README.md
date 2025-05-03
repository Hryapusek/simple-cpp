# Windows
```sh
BUILD_DIR=mingw_build
mkdir $BUILD_DIR
cmake -S . -B $BUILD_DIR -DCMAKE_TOOLCHAIN_FILE=mingw_toolchain.cmake
cmake --build $BUILD_DIR
```


# Clang
```sh
BUILD_DIR=clang_build
mkdir $BUILD_DIR
cmake -S . -B $BUILD_DIR -DCMAKE_TOOLCHAIN_FILE=clang_toolchain.cmake
cmake --build $BUILD_DIR
```

# GNU
```sh
BUILD_DIR=gnu_build
mkdir $BUILD_DIR
cmake -S . -B $BUILD_DIR -DCMAKE_TOOLCHAIN_FILE=gnu_toolchain.cmake
cmake --build $BUILD_DIR
```
