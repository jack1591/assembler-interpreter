cmake_minimum_required(VERSION 3.10)
project(assembler-interprseter)

# Укажите стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавьте основной файл main.cpp
add_executable(main assembler.cpp interpreter.cpp main.cpp)

# Добавьте googletest
add_subdirectory(googletest)

# Создайте тестовую цель (например, tests)
add_executable(tests test_main.cpp)

# Свяжите тесты с библиотеками gtest
target_link_libraries(tests PRIVATE gtest gtest_main)