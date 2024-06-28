import os
import glob

methods = ["solve_hillClimbing", "solve_tabu"]

class ExperimentData:
    def __init__(self, filename, length, color, iteration, max_value, min_time, avg_value, avg_time, solutions):
        self.filename = filename
        self.length = length
        self.color = color
        self.iteration = iteration
        self.max_value = max_value
        self.min_time = min_time
        self.avg_value = avg_value
        self.avg_time = avg_time
        self.solutions = solutions

def read_data_from_file(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()

    solutions = []
    sumV = 0
    sumT = 0
    minT = -1
    maxV = 0

    i = 0
    while i < len(lines):
        correct = lines[i].strip().split()
        solution = lines[i+1].strip().split()
        correctPosition = list(map(int, lines[i+2].strip().split()))
        correctValue = int(lines[i+3].strip())
        time = int(lines[i+4].strip())

        solutions.append({
            'correct': correct,
            'solution': solution,
            'correctPosition': correctPosition,
            'correctValue': correctValue,
            'time': time
        })

        maxV = max(maxV, correctValue)
        minT = min(minT, time)
        sumV += correctValue
        sumT += time

        i += 5

    avgV = sumV / len(solutions)
    avgT = sumT / len(solutions)

    # Extracting parameters from filename
    filename_parts = os.path.basename(filename).split('_')
    length = filename_parts[2]
    color = filename_parts[3]
    iteration = filename_parts[4].split('.')[0]
    avgV = sumV / len(solutions)
    avgT = sumT / len(solutions)
    return ExperimentData(os.path.basename(filename), length, color, iteration, maxV, minT, avgV, avgT, solutions)

data_folder = './data/experiment/'

experiment_data_dict = {method: [] for method in methods}

for method in methods:
    method_folder = os.path.join(data_folder, method)
    data_files = glob.glob(os.path.join(method_folder, 'results_*.txt'))
    for data_file in data_files:
        experiment_data = read_data_from_file(data_file)
        experiment_data_dict[method].append(experiment_data)

# Display loaded data
for method, data_list in experiment_data_dict.items():
    print(f"Method: {method}")
    for data in data_list:
        print(f"Filename: {data.filename}")
        print(f"Length: {data.length}, Color: {data.color}, Iteration: {data.iteration}")
        print(f"Max Value: {data.max_value}, Min Time: {data.min_time}")
        print(f"Avg Value: {data.avg_value}, Avg Time: {data.avg_time}")
        print(f"Solutions:")
        for idx, solution in enumerate(data.solutions, 1):
            print(f"  Solution {idx}:")
            print(f"    Correct: {solution['correct']}")
            print(f"    Solution: {solution['solution']}")
            print(f"    Correct Position: {solution['correctPosition']}")
            print(f"    Correct Value: {solution['correctValue']}")
            print(f"    Time: {solution['time']}")
        print()
