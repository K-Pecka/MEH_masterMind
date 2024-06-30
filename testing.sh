#cmake-build-debug/MEH_pjwstk.exe -m "solve_hillClimbing" -param "deterministiC" -l 10 -i 10000 -p "./data/color.txt" -c 0 >> results.txt
#cmake-build-debug/MEH_pjwstk.exe -m "solve_genetic" -param "random" "max_generation" -GA 5 20 150 -p "./data/color.txt" >> results.txt
cmake-build-debug/MEH_pjwstk.exe -m "solve_genetic" -param "swap" -GA 20 1500 20 -p "./data/color.txt" > results.txt
#cmake-build-debug/MEH_pjwstk.exe -m "solve_hillClimbing" -param "deterministiC" -l 10 -i 10000 -p "./data/color.txt" > results.txt