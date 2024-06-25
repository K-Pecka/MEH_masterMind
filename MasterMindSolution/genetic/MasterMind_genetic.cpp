#include "MasterMind_genetic.h"
#include <functional>

color_t MasterMind_genetic::goal() {

    std::cout<<config.GAConfig.generation<<std::endl;
    std::cout<<config.GAConfig.population<<std::endl;
    std::cout<<config.GAConfig.eliteSize<<std::endl;

    int populationSize = config.GAConfig.population;
    int eliteSize = config.GAConfig.eliteSize;

    auto crossover =[&](const color_t& p1, const color_t& p2) ->color_t {
                if (isInParams(Param::DOUBLE_POINT)) {
                    return crossoverDoublePoint(p1, p2);
                } else {
                    return crossoverSinglePoint(p1, p2);
                }
    };
    auto mutate = [&](color_t& ind) -> void {
        if (isInParams(Param::SWAP)) {
            mutateSwap(ind);
        } else {
            mutateRandom(ind);
        }
    };
    auto terminationCondition = [&]() -> bool {
        if (isInParams(Param::MAX_GENERATIONS)) {
            return terminationConditionGenerations();
        } else {
            return terminationConditionFitness();
        }
    };
    auto population = initializePopulation(populationSize);
    setSolution(theBestNeighbor(population));
    generation = 0;

    while (!terminationCondition()) {
        std::vector<color_t> newPopulation = selectElites(population, eliteSize);

        while (newPopulation.size() < populationSize) {
            color_t parent1 = selectParent(population);
            color_t parent2 = selectParent(population);

            color_t offspring = crossover(parent1, parent2);

            mutate(offspring);

            newPopulation.push_back(offspring);
        }

        population = newPopulation;
        betterSolution(theBestNeighbor(population));
        generation++;
    }
    std::cout<<generation<<std::endl;
    return getSolution();
}

std::vector<color_t> MasterMind_genetic::initializePopulation(int populationSize) {
    std::vector<color_t> population;
    for (int i = 0; i < populationSize; ++i) {
        population.push_back(generateRandomSolution());
    }
    return population;
}

color_t MasterMind_genetic::selectParent(const std::vector<color_t>& population) {
    return population[randomInt(0, population.size() - 1)];
}


color_t MasterMind_genetic::crossoverSinglePoint(const color_t& parent1, const color_t& parent2) {
    int crossoverPoint = randomInt(0, config.codeLength - 1);
    color_t offspring = parent1;
    for (int i = crossoverPoint; i < config.codeLength; ++i) {
        offspring[i] = parent2[i];
    }
    return offspring;
}

color_t MasterMind_genetic::crossoverDoublePoint(const color_t& parent1, const color_t& parent2) {

    size_t size = parent1.size();
    int point1 = randomInt(0, (int)size - 1);
    int point2 = randomInt(0, (int)size - 1);

    if (point1 > point2) {
        std::swap(point1, point2);
    }

    color_t offspring(size);

    for (int i = 0; i < size; ++i) {
        if (i >= point1 && i <= point2) {
            offspring[i] = parent2[i];
        } else {
            offspring[i] = parent1[i];
        }
    }

    return offspring;
}

void MasterMind_genetic::mutateSwap(color_t& individual) {
    int index1 = randomInt(0, config.codeLength - 1);
    int index2 = randomInt(0, config.codeLength - 1);
    std::swap(individual[index1], individual[index2]);
}

void MasterMind_genetic::mutateRandom(color_t& individual) {
    int index = randomInt(0, config.codeLength - 1);
    individual[index] = possibleColors.colors[randomColor()];
}

bool MasterMind_genetic::terminationConditionGenerations() {
        return generation >= config.GAConfig.generation;
}

bool MasterMind_genetic::terminationConditionFitness() {
    return checkColor(getSolution()) == config.codeLength;
}

std::vector<color_t> MasterMind_genetic::selectElites(const std::vector<color_t>& population, int eliteSize) {
    std::vector<color_t> elites(population);
    std::sort(elites.begin(), elites.end(), [this](const color_t& a, const color_t& b) {
        return checkColor(a) > checkColor(b);
    });
    elites.resize(eliteSize);
    return elites;
}