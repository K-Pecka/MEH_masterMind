#ifndef MEH_PJWSTK_MASTERMIND_TABU_H
#define MEH_PJWSTK_MASTERMIND_TABU_H

#include "../../masterMind/MasterMind.h"
#include <set>
#include <deque>

using color_set =std::set<solution_t>;
std::ostream& operator<<(std::ostream& o, const color_set& result);

class MasterMind_tabu : public MasterMind {
public:
    MasterMind_tabu() = default;
    explicit MasterMind_tabu(Config configGame) : MasterMind(std::move(configGame)) {}
    void addToTabu(const solution_t&);
    bool isInTabu(const solution_t&);
    std::vector<solution_t> neighborsInTabu(const std::vector<solution_t>&);
    solution_t solve() override;
private:
    color_set tabu;
    std::deque<solution_t> solutionHistory;
    size_t tabu_size = 100;
};


#endif //MEH_PJWSTK_MASTERMIND_TABU_H
