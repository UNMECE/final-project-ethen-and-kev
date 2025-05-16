#include "acequia_manager.h"
#include <iostream>

void solveProblems(AcequiaManager& manager) {
    auto canals = manager.getCanals();

    while (!manager.isSolved && manager.hour < 101) {
        for (int i = 0; i < canals.size(); i++) {
            Region* dest = canals[i]->destinationRegion;

            double deficit = dest->waterNeed - dest->waterLevel;

            if (!dest->isFlooded && deficit > 0) {
                canals[i]->toggleOpen(true);

                double flowRate = (deficit > 20) ? 0.9 : (deficit > 10) ? 0.6 : 0.3;
                canals[i]->setFlowRate(flowRate);
            } else {
                canals[i]->toggleOpen(false);
            }
        }
        manager.nexthour();
    }
}
