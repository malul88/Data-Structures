#ifndef HW2_UNIONFIND_H
#define HW2_UNIONFIND_H

#include "Agency.h"
#include "DynamicArray.h"
#include "UpTree.h"

class UnionFind {
public:
    DynamicArray<UpTreeNode<int, Agency *> *>* agencies;
    const int CARS = 1;
    const int ID_CARS = 2;

    UnionFind(){
        agencies = new DynamicArray<UpTreeNode<int, Agency *> *>;
    }
    ~UnionFind(){
        delete agencies;
    }

    void Union(UpTreeNode<int, Agency *> *v, UpTreeNode<int, Agency *> *w);

    UpTreeNode<int, Agency *> *find(int AgencyID);

    UpTreeNode<int, Agency *> *getTopAndShrink(UpTreeNode<int, Agency *> *v);

    void sellCar(int AgencyID, int typeID, int k);

    int findCarByIndex(int agencyID, int i);

    template<class C,class T>
    void UniteTrees(UpTreeNode<int, Agency *> *v, UpTreeNode<int, Agency *> *w, int type,C* c);

    UpTreeNode<int, Agency *> * shrink(UpTreeNode<int, Agency *> *v);
};


#endif //HW2_UNIONFIND_H
