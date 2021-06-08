
#include "CarDealershipManager.h"

void CarDealershipManager::AddAgency() {
    Agency* newA = new Agency(counter,0);
    UpTreeNode<int,Agency*>* newTree = new UpTreeNode<int,Agency*>(counter,newA);
    newTree->parent = nullptr;
    system.agencies.add(newTree);
    system.agencies_group.add(newA);
}

void CarDealershipManager::SellCar(int agencyID, int typeID, int k) {
    system.sellCar(agencyID,typeID,k);
}

void CarDealershipManager::UniteAgencies(int agencyID1, int agencyID2) {
    system.Union(system.find(agencyID1),system.find(agencyID2));
}
