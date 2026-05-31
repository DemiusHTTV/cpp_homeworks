cmake_minimum_required(VERSION 3.10)

project(Sudoku)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sudoku
    main.cpp
    Sudoku.cpp
)