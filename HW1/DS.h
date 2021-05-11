
#ifndef HW1_DS_H
#define HW1_DS_H
#include <exception>
#include "AVLTree.h"
#include "carModel.h"
#include "car_type.h"
#include "Execption.h"


class DS {
public:
    AVLTree<int,carType> types;
    AVLTree<int,carModel*> all_models;
    AVLTree<int,AVLTree<int,carModel*>> all_zero_models;
    carModel* best_seller;
    const int SALE_GRADE = 10;

    void addCarType(int typeID, int num_of_models);
    void removeCarType(int typeID, int modelID);
    void sellCar(int typeID, int modelID);
};




#endif //HW1_DS_H
