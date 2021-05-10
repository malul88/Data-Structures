
#include "DS.h"

void DS::addCarType(int typeID, int num_of_models) {
    auto* car = new carType(typeID,num_of_models); // a new car type
    AVLTree<int,carModel*> zero_new_models;
    for (int i = 0; i < num_of_models ; ++i) {    // making a model tree
        auto* model = new carModel(typeID,i);
        zero_new_models.Add(i,model);
        car->models[i] = model;                    // add the address to the array in carType
    }
    all_zero_models.Add(typeID,zero_new_models);
    types.Add(typeID,car);
}


void DS::removeCarType(int typeID, int modelID) {
    AVLTree<int,carModel*>* zeroed_models = all_zero_models.Find(typeID);
    zeroed_models->TreeRemove(zeroed_models->GetHead());
    all_zero_models.Remove(typeID);
    types.Remove(typeID);
}


