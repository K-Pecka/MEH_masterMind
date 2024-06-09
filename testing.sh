for METHOD in solve_hill_climbing solve_tabu solve_tabu_list solve_sim_annealing solve_random solve_random_n; do
  cmake-build-debug/MEH_pjwstk.exe $METHOD >> results.txt
done