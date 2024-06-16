cmake_minimum_required(VERSION 3.27)
project(MEH_pjwstk)

set(CMAKE_CXX_STANDARD 23)

add_executable(MEH_pjwstk main.cpp
        meh_solution/MasterMind.cpp
        MasterMindSolution/MasterMind_BF.cpp
        MasterMindSolution/MasterMind_hill_climbing.cpp
        MasterMindSolution/MasterMind_hill_climbing.h
        MasterMindSolution/MasterMind_hill_climbing.h
        MasterMindSolution/MasterMind_random.cpp
        MasterMindSolution/MasterMind_random.h
        MasterMindSolution/MasterMind_random.h)
