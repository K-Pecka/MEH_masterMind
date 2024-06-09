cmake_minimum_required(VERSION 3.27)
project(MEH_pjwstk)

set(CMAKE_CXX_STANDARD 23)

add_executable(MEH_pjwstk main.cpp
        meh_solution/Meh_solution.cpp
        MasterMind/MasterMind.cpp)
