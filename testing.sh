cmake-build-debug/MEH_pjwstk.exe -m "solve_random" -l 15 -i 1000 -p "./data/color.txt" >> results.txt
cmake-build-debug/MEH_pjwstk.exe -m "solve_BF" -l 15 -i 1000 -p "./data/color.txt" >> results.txt
cmake-build-debug/MEH_pjwstk.exe -m "solve_hill_climbing" -l 15 -i 1000 -p "./data/color.txt" >> results.txt