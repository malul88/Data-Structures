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
    carType *type = types.Find(typeID);
    for (int i = 0; i < type->num_of_models ; ++i) {
        PriorityBySale ps(type->models[i]->num_of_sales,type->typeID,type->models[i]->modelID);
        PriorityByGrade pg(type->models[i]->grade,type->typeID,type->models[i]->modelID);
        best_seller.Remove(ps);
        all_models.Remove(pg);
        delete type->models[i];
    }
    AVLTree<int, carModel *> *zeroed_models = all_zero_models.Find(typeID); //sub_tree of all_zero_models
    zeroed_models->TreeRemove(zeroed_models->GetHead());
    all_zero_models.Remove(typeID);
    types.Remove(typeID);
}

void DS::sellCar(int typeID, int modelID) {
    carType *type = types.Find(typeID);
    bool is_zero = type->models[modelID]->grade == 0;
    bool is_saled = type->models[modelID]->num_of_sales != 0;
    if (!is_zero){
        PriorityByGrade old_pg(type->models[modelID]->grade,type->models[modelID]->typeID,
                               type->models[modelID]->modelID);
        all_models.Remove(old_pg);
    } else {

    }
    if (is_saled){
        PriorityBySale old_ps(type->models[modelID]->num_of_sales,type->models[modelID]->typeID,
                       type->models[modelID]->modelID);
        best_seller.Remove(old_ps);
    }
    type->models[modelID]->grade += SALE_GRADE;
    type->models[modelID]->num_of_sales += 1;
    if (type->models[modelID]->grade == 0){
        AVLTree<int, carModel *>* current_zero_tree = all_zero_models.Find(typeID);
        current_zero_tree->Add(modelID,type->models[modelID]);
    } else {
        PriorityByGrade new_pg(type->models[modelID]->grade,type->models[modelID]->typeID,
                               type->models[modelID]->modelID);
        all_models.Add(new_pg,type->models[modelID]);
    }
    PriorityBySale new_ps(type->models[modelID]->num_of_sales,type->models[modelID]->typeID,
                          type->models[modelID]->modelID);
    best_seller.Add(new_ps,type->models[modelID]);
    updateBestSellerByType(type,modelID);
}


void DS::fillTreeWithInorder(TreeNode<int, carModel *> *v, int typeID, int num_of_models,
                             int *current_model, carType* carType) {
    if (*current_model == num_of_models || v == nullptr) {
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
    int h = log2((double) num_of_models);                      //height of the tree
    zero_new_models.head->height = h;
    int leafs_to_del = pow(2,h+1)- num_of_models -1;
    int current_model = 0;
    zero_new_models.completeTree(zero_new_models.head, h); //making complete tree
    zero_new_models.makeTreeAlmostComplete(zero_new_models.head, h, &leafs_to_del);  // deleting the reserved leafs from the right
    fillTreeWithInorder(zero_new_models.head, typeID, num_of_models, &current_model,carType); // filling the tree with car models by inorder
    zero_new_models.max = zero_new_models.head;
    zero_new_models.min = zero_new_models.head;
    all_zero_models.Add(typeID, zero_new_models);
}

void DS::updateBestSellerByType(carType *type, int modelID) {
    if (type->best_seller != modelID && type->models[modelID]->num_of_sales > type->best_num_of_sales ||
        type->best_seller > modelID && type->best_num_of_sales == type->models[modelID]->num_of_sales){
        type->best_seller = modelID;
        type->best_num_of_sales = type->models[modelID]->num_of_sales;
    } else if (type->best_seller == modelID){
        type->best_num_of_sales = type->models[modelID]->num_of_sales;
    }

}



