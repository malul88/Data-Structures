
#ifndef HW1_DS_H
#define HW1_DS_H
#include <exception>
#include "AVLTree.h"
#include "carModel.h"
#include "car_type.h"
#include "Execption.h"


class DS {
public:
    AVLTree<int,carType> types; //1
    AVLTree<int,carModel*> all_models; //2
    AVLTree<int,AVLTree<int,carModel*>> all_zero_models; //3
    carModel* best_seller;
    const int SALE_GRADE = 10;

    void addCarType(int typeID, int num_of_models);
    void removeCarType(int typeID, int modelID);
    void sellCar(int typeID, int modelID);
};




#endif //HW1_DS_H
