#ifndef HW2_CARDEALERSHIPMANAGER_H
#define HW2_CARDEALERSHIPMANAGER_H
#include "UnionFind.h"

class CarDealershipManager {
public:
    UnionFind system;
    int counter;

    CarDealershipManager(): counter(0){}

    void AddAgency();

    void SellCar(int agencyID, int typeID, int k);

    void UniteAgencies(int agencyID1, int agencyID2);

    void GetlthSoldType(int agencyID, int* res);


};


#endif //HW2_CARDEALERSHIPMANAGER_H
