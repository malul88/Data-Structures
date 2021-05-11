
#include "DS.h"

void DS::addCarType(int typeID, int num_of_models) {
    carType car(typeID,num_of_models); // a new car type
    AVLTree<int,carModel*> zero_new_models;
    for (int i = 0; i < num_of_models ; ++i) {    // making a model tree
        auto* model = new carModel(typeID,i);
        zero_new_models.Add(i,model);
        car.models[i] = model;                    // add the address to the array in carType
    }
    all_zero_models.Add(typeID,zero_new_models);
    types.Add(typeID,car);
}
void deleteModel(carModel* carModel){
    delete carModel;
}

void DS::removeCarType(int typeID, int modelID) {
    AVLTree<int,carModel*>* zeroed_models = all_zero_models.Find(typeID);
    zeroed_models->BackOrder(deleteModel);
    zeroed_models->TreeRemove(zeroed_models->GetHead());
    all_zero_models.Remove(typeID);
    types.Remove(typeID);
}

void DS::sellCar(int typeID, int modelID) {
    carType* car = types.Find(typeID);
    car->models[modelID]->grade+= SALE_GRADE;
    if (car->models[modelID]->zeroed) {
        all_models.Add(car->models[modelID]->grade, car->models[modelID]);
        all_zero_models.Find(typeID)->Remove(modelID); //todo check return error
    } else {

    }

}



