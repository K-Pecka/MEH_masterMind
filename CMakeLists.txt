cmake_minimum_required(VERSION 3.27)
project(MEH_pjwstk)

set(CMAKE_CXX_STANDARD 23)

add_executable(MEH_pjwstk main.cpp
        masterMind/MasterMind.cpp
        MasterMindSolution/bruteForce/MasterMind_bruteForce.cpp
        MasterMindSolution/hillClimbing/MasterMind_hillClimbing.cpp
        MasterMindSolution/random/MasterMind_random.cpp
        MasterMindSolution/tabu/MasterMind_tabu.cpp
        MasterMindSolution/annealing/MasterMind_annealing.cpp
        MasterMindSolution/genetic/MasterMind_genetic.cpp
)
