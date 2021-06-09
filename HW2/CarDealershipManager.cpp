#include "CarDealershipManager.h"


void CarDealershipManager::AddAgency() {
    Agency* newA = new Agency(counter,0);
    UpTreeNode<int,Agency*>* newTree = new UpTreeNode<int,Agency*>(counter++,newA);
    newTree->parent = nullptr;
    system.agencies->add(newTree);
}

void CarDealershipManager::SellCar(int agencyID, int typeID, int k) {
    system.sellCar(agencyID,typeID,k);
}

void CarDealershipManager::UniteAgencies(int agencyID1, int agencyID2) {
    system.Union(system.find(agencyID1),system.find(agencyID2));
}

void CarDealershipManager::GetlthSoldType(int agencyID,int i, int *res) {
    *res = system.findCarByIndex(agencyID,i);
}

void CarDealershipManager::Quit() {
    for (int i = 0; i <counter ; ++i) {
        UpTreeNode<int, Agency*> * node = system.agencies->array[i];
        if (node->data){
            delete node->data;
            node->data = nullptr;
        }
        delete node;


    }

}
