#ifndef MEH_PJWSTK_MASTERMIND_TABU_H
#define MEH_PJWSTK_MASTERMIND_TABU_H

#include "../meh_solution/MasterMind.h"
#include <set>
#include <list>

using color_set =std::set<color_t>;
std::ostream& operator<<(std::ostream& o, const color_set& result);

class MasterMind_tabu : public MasterMind {
public:
    MasterMind_tabu() = default;
    explicit MasterMind_tabu(Config configGame) : MasterMind(std::move(configGame)) {}
    void addToTabu(const color_t&);
    bool isInTabu(const color_t&);
    color_t goal() override;
private:
    color_set tabu;
};


#endif //MEH_PJWSTK_MASTERMIND_TABU_H
