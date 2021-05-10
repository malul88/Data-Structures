
#ifndef HW1_DS_H
#define HW1_DS_H
#include <exception>
#include "AVLTree.h"
#include "carModel.h"
#include "car_type.h"

class DS {
public:
    AVLTree<int,carType*> types;
    AVLTree<int,carModel*> all_models;
    AVLTree<int,AVLTree<int,carModel*>> all_zero_models;
    carModel* best_seller;

    void addCarType(int typeID, int num_of_models);
    void removeCarType(int typeID, int modelID);
};




#endif //HW1_DS_H
