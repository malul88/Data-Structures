
#ifndef HW1_DS_H
#define HW1_DS_H

#include <exception>
#include "AVLTree.h"
#include "carModel.h"
#include "car_type.h"
#include "Execption.h"
#include "grade.h"
#include "sales.h"
#include "math.h"


class DS {
public:
    AVLTree<int, carType > types; //1
    AVLTree<PriorityByGrade, carModel *> all_models; //2
    AVLTree<int, AVLTree<int, carModel *>> all_zero_models; //3
    AVLTree<PriorityBySale, carModel *> best_seller; //4
    const int SALE_GRADE = 10;

    void addCarType(int typeID, int num_of_models);

    void removeCarType(int typeID);

    void sellCar(int typeID, int modelID);

    void fillTreeWithInorder(TreeNode<int, carModel *> *v, int typeId, int num_of_models,
                             int *current_model, carType* carType);

    void buildTreeAndAdd(int typeID, int num_of_models, carType* carType);

    void updateBestSellerByType(carType* type, int modelID);

};


#endif //HW1_DS_H
