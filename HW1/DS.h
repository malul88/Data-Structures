
#ifndef HW1_DS_H
#define HW1_DS_H

#include <exception>
#include "AVLTree.h"
#include "carModel.h"
#include "car_type.h"
#include "Execption.h"
#include <exception>
#include "grade.h"
#include "sales.h"
#include "math.h"


class DS {
public:
    AVLTree<int, carType* > types; //1
    AVLTree<PriorityByGrade, carModel *> all_models; //2
    AVLTree<int, AVLTree<int, carModel *>*> all_zero_models; //3
    AVLTree<PriorityBySale, carModel *> best_seller; //4
    const int SALE_GRADE = 10;
    int total_cars;
    bool been_in_zero;

    DS(): total_cars(0) , been_in_zero(false){}

    void addCarType(int typeID, int num_of_models);

    void removeCarType(int typeID);

    void sellCar(int typeID, int modelID);

    void makeComplaint(int typeID, int modelID, int t);

    void getBestSellerModelByType(int typeID, int* modelID);

    void getWorstModels(int num_of_models, int* types,int * models);

    void fillTreeWithInorder(Node<int, carModel *> *v, int typeId, int num_of_models,
                             int *current_model, carType* carType);

    void inorderAllModels(Node<PriorityByGrade,carModel*> * v , int num_of_models, int* car_types, int * models, int* counter);

    void inorderAllZeroTypes(Node<int, AVLTree<int, carModel *>*> * v, int num_of_models, int *car_types, int *models, int* counter);

    void inorderAllZeroModels(Node<int,carModel*> * v, int num_of_models, int *car_types, int *models, int* counter);

    void quit();

    void postOrderDelete(Node<int, carType*> * v);

    void modelsPostOrderDelete(Node<int, carModel*> * v);

    void typesPostOrderDelete(Node<int, AVLTree<int, carModel*>*> * v);

    void buildTreeAndAdd(int typeID, int num_of_models, carType* carType);

    void updateBestSellerByType(carType* type, int modelID);
};


#endif //HW1_DS_H
