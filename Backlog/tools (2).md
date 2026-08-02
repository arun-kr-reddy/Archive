# tools
- [cmake](#cmake)

## links  <!-- omit from toc -->
- [clang format](https://clang.llvm.org/docs/ClangFormatStyleOptions.html)
- [cmake](https://codevion.github.io/#!cpp/cmake.md)
- [makefile](https://makefiletutorial.com/)

## cmake
- **cmake:** *CMakeLists.txt* used to generate standard build files (makefiles or MSVC project)  
  ```cmake
  cmake_minimum_required(VERSION 3.10)
  set(CMAKE_CXX_STANDARD 11)

  set(SOURCES main.cpp)             # set variable
  include_directories(./include)    # header path
  project(test_project)             # project name
  add_subdirectory(subdir)          # include subdir cmakelists
  add_executable(main_exe SOURCES)  # executable target
  ```
- **library:**
  ```cmake
  add_library(mylib STATIC lib.cpp)            # create lib
  find_library(PTHREAD_LIB pthread)            # find system lib
  find_library(CUSTOM_LIB myLib PATHS <path>)  # find custom lib at path
  target_link_libraries(main_exe ${PTHREAD_LIB} ${CUSTOM_LIB})  # include lib
  ```