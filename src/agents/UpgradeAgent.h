#ifndef TEAM3_UPGRADEAGENT_H
#define TEAM3_UPGRADEAGENT_H

#include "TrainsAgent.h"
#include <graph-components/Hometown.h>

class UpgradeAgent {
private:
    const int maxHijackers = 19;
    const int secondLevelPrice = 60;
    bool isFirstUpgradeMade;
public:
    UpgradeAgent();

    std::vector<int32_t> upgradeTown(Hometown* home);
    std::vector<int32_t> upgradeTrains(Hometown* home, int hijackersCount);
};


#endif //TEAM3_UPGRADEAGENT_H
