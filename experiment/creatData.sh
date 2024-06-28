N=10
exe_path="./../cmake-build-debug/MEH_pjwstk.exe"
des_path="./data/experiment/"

lengths=(
  "5"
  "10"
  "30"
  "100"
)
iterations=(
  "1000"
)
colors=(
    "5"
    "10"
    "25"
    "30"
  )
methods=(
  "solve_hillClimbing"
  "solve_tabu"
)
for method in "${methods[@]}"; do
  rm -rf "${des_path}${method}"
  mkdir -p "${des_path}${method}"
done
for color in "${colors[@]}"; do
  for len in "${lengths[@]}"; do
    for iter in "${iterations[@]}"; do
      for method in "${methods[@]}"; do
        echo "Uruchamianie eksperymentu: metoda=$method, długość=$len, iteracje=$iter, ilośćKolorów = $color"
        experiment="-m $method -param deterministic -l $len -i $iter -p ${des_path}color/color_${color}.txt"
        for ((i=1; i<=N; i++)); do
          echo "> $method iteracja: $i"
          $exe_path $experiment >> "${des_path}${method}/results_${method}_${len}_${color}_${iter}.txt"
        done
      done
    done
  done
done