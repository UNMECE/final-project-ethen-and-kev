#include "acequia_manager.h"
#include <iostream>

void solveProblems(AcequiaManager& manager)
{
    auto canals = manager.getCanals();
    auto regions = manager.getRegions();

    while(!manager.isSolved && manager.hour < manager.SimulationMax)
    {
        for(int i = 0; i < canals.size(); i++)
        {
            Region* dest = canals[i]->destinationRegion;

            // If region is flooded, close canal
            if(dest->isFlooded)
            {
                canals[i]->toggleOpen(false);
            }
            // If region needs water or is in drought, open canal at safe flow
            else if(dest->isInDrought || dest->waterLevel < dest->waterNeed)
            {
                canals[i]->toggleOpen(true);
                canals[i]->setFlowRate(0.5); // Moderate flow to avoid flooding
            }
            // Otherwise, close canal
            else
            {
                canals[i]->toggleOpen(false);
            }
        }
        manager.nexthour();
    }
}