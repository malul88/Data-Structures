#ifndef HW2_UNIONFIND_H
#define HW2_UNIONFIND_H

#include "Agency.h"
#include "DynamicArray.h"
#include "UpTree.h"

class UnionFind {
public:
    DynamicArray<UpTreeNode<int, Agency*>*> agencies;
    DynamicArray<Agency*> agencies_group;

    // Tree for all cars in all agencies
    RankTree<int,int> all_cars;

    void Union(UpTreeNode<int, Agency*> * v,UpTreeNode<int, Agency*> * w );

    UpTreeNode<int, Agency*>* find(int AgencyID);

    UpTreeNode<int, Agency *> *getTopAndShrink(UpTreeNode<int, Agency *> *v);

    void sellCar(int AgencyID, int typeID, int k);
};



#endif //HW2_UNIONFIND_H
