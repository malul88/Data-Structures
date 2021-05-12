#include "DS.h"

void DS::addCarType(int typeID, int num_of_models) {
    carType new_car =  carType(typeID, num_of_models);            // a new car type
    buildTreeAndAdd(typeID,num_of_models,&new_car);          // add a sub tree with all models to zero_models
    types.Add(typeID, new_car);         // add the type of the car to the types tree
}
void deleteModel(carModel *carModel) {
    delete carModel;
}

void DS::removeCarType(int typeID) {
    carType *car = types.Find(typeID);
    for (int i = 0; i < car->num_of_models ; ++i) {
        PriorityBySale ps(car->models[i]->num_of_sales,car->typeID,car->models[i]->modelID);
        PriorityByGrade pg(car->models[i]->grade,car->typeID,car->models[i]->modelID);
        best_seller.Remove(ps);
        all_models.Remove(pg);
        delete car->models[i];
    }
    AVLTree<int, carModel *> *zeroed_models = all_zero_models.Find(typeID); //sub_tree of all_zero_models
    zeroed_models->TreeRemove(zeroed_models->GetHead());
    all_zero_models.Remove(typeID);
    types.Remove(typeID);
}

void DS::sellCar(int typeID, int modelID) {
    carType *car = types.Find(typeID);
    car->models[modelID]->grade += SALE_GRADE;
    car->models[modelID]->num_of_sales += 1;
    if (car->models[modelID]->zeroed) {
        all_models.Add(car->models[modelID]->grade, car->models[modelID]);
        all_zero_models.Find(typeID)->Remove(modelID); //todo check return error
    } else {

    }

}

void DS::fillTreeWithInorder(TreeNode<int, carModel *> *v, int typeID, int num_of_models,
                             int *current_model, carType* carType) {
    if (*current_model == num_of_models) {
        return;
    }
    fillTreeWithInorder(v->left, typeID, num_of_models, current_model,carType);
    v->key = *current_model;
    carModel* car = new carModel(typeID, *current_model);
    v->data = car;
    carType->models[*current_model] = car;
    *current_model = *current_model + 1;
    fillTreeWithInorder(v->right, typeID, num_of_models, current_model, carType);
}

void DS::buildTreeAndAdd(int typeID, int num_of_models,carType* carType) {
    AVLTree<int, carModel *> zero_new_models;
    zero_new_models.NumOfNodes = num_of_models;
    int h = log((double) num_of_models);                      //height of the tree
    zero_new_models.head->height = h;
    int leafs_to_del = num_of_models;
    int current_model = 0;
    zero_new_models.completeTree(zero_new_models.head, h); //making complete tree
    zero_new_models.makeTreeAlmostComplete(zero_new_models.head, h, &leafs_to_del);  // deleting the reserved leafs from the right
    fillTreeWithInorder(zero_new_models.head, typeID, num_of_models, &current_model,carType); // filling the tree with car models by inorder
    zero_new_models.max = zero_new_models.head;
    zero_new_models.min = zero_new_models.head;
    all_zero_models.Add(typeID, zero_new_models);
}



