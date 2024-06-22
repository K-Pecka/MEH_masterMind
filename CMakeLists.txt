cmake_minimum_required(VERSION 3.27)
project(MEH_pjwstk)

set(CMAKE_CXX_STANDARD 23)

add_executable(MEH_pjwstk main.cpp
        meh_solution/MasterMind.cpp
        MasterMindSolution/MasterMind_BF.cpp
        MasterMindSolution/MasterMind_hillClimbing.cpp
        MasterMindSolution/MasterMind_hillClimbing.h
        MasterMindSolution/MasterMind_hillClimbing.h
        MasterMindSolution/MasterMind_random.cpp
        MasterMindSolution/MasterMind_random.h
        MasterMindSolution/MasterMind_random.h
        MasterMindSolution/MasterMind_tabu.cpp
        MasterMindSolution/MasterMind_tabu.h
        MasterMindSolution/MasterMind_annealing.cpp
        MasterMindSolution/MasterMind_annealing.h
        MasterMindSolution/MasterMind_annealing.cpp)
