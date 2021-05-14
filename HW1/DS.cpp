#include "DS.h"

void DS::addCarType(int typeID, int num_of_models) {
    carType* new_car = new carType(typeID, num_of_models);            // a new car type
    buildTreeAndAdd(typeID, num_of_models, new_car);          // add a sub tree with all models to zero_models
    types.Add(typeID, new_car);         // add the type of the car to the types tree
    total_cars += num_of_models;
}

void deleteModel(carModel *carModel) {
    delete carModel;
}

void DS::removeCarType(int typeID) {
    carType **type = types.Find(typeID);
    if (!type){
        throw KeyNotExist();
    }
    total_cars -= (*type)->num_of_models;
    for (int i = 0; i < (*type)->num_of_models; ++i) {
        PriorityBySale ps((*type)->models[i]->num_of_sales, (*type)->typeID, (*type)->models[i]->modelID);
        PriorityByGrade pg((*type)->models[i]->grade, (*type)->typeID, (*type)->models[i]->modelID);
        if (best_seller.Find(ps) != NULL) {
            best_seller.Remove(ps);
        }
        if (all_models.Find(pg)) {
            all_models.Remove(pg);
        }
        delete (*type)->models[i];
    }
    AVLTree<int, carModel *> ** zeroed_models = all_zero_models.Find(typeID); //sub_tree of all_zero_models
    (*zeroed_models)->removeTree((*zeroed_models)->GetHead());
    all_zero_models.Remove(typeID);
    types.Remove(typeID);

}

void DS::sellCar(int typeID, int modelID) {
    carType **type = types.Find(typeID);
    if (!type || (*type)->num_of_models <= modelID){
        throw KeyNotExist();
    }
    bool is_zero = (*type)->models[modelID]->grade == 0;
    bool is_saled = (*type)->models[modelID]->num_of_sales != 0;
    if (!is_zero) {                       // if not in  zero models (remove from models)
        PriorityByGrade old_pg((*type)->models[modelID]->grade, (*type)->models[modelID]->typeID,
                               (*type)->models[modelID]->modelID);
        all_models.Remove(old_pg);
    } else {                       // if is in zero models (needs to remove)
        AVLTree<int, carModel *> **current_zero_tree = all_zero_models.Find(typeID);
        (*current_zero_tree)->Remove(modelID);
    }
    if (is_saled) {   // if been sales before (remove from best seller)
        PriorityBySale old_ps((*type)->models[modelID]->num_of_sales, (*type)->models[modelID]->typeID,
                              (*type)->models[modelID]->modelID);
        best_seller.Remove(old_ps);
    }
    (*type)->models[modelID]->grade += SALE_GRADE;
    (*type)->models[modelID]->num_of_sales += 1;
    if ((*type)->models[modelID]->grade == 0) {  // if moves to zero models from all models
        AVLTree<int, carModel *> **current_zero_tree = all_zero_models.Find(typeID);
        (*current_zero_tree)->Add(modelID, (*type)->models[modelID]);
    } else {  // if not zero to not zero
        PriorityByGrade new_pg((*type)->models[modelID]->grade, (*type)->models[modelID]->typeID,
                               (*type)->models[modelID]->modelID);
        all_models.Add(new_pg, (*type)->models[modelID]);
    } // always put in best seller regardless
    PriorityBySale new_ps((*type)->models[modelID]->num_of_sales, (*type)->models[modelID]->typeID,
                          (*type)->models[modelID]->modelID);
    best_seller.Add(new_ps, (*type)->models[modelID]);
    updateBestSellerByType((*type), modelID);
}


void DS::fillTreeWithInorder(TreeNode<int, carModel *> *v, int typeID, int num_of_models,
                             int *current_model, carType *carType) {
    if (*current_model == num_of_models || v == nullptr) {
        return;
    }
    fillTreeWithInorder(v->left, typeID, num_of_models, current_model, carType);
    v->key = *current_model;
    carModel *car = new carModel(typeID, *current_model);
    v->data = car;
    carType->models[*current_model] = car;
    *current_model = *current_model + 1;
    fillTreeWithInorder(v->right, typeID, num_of_models, current_model, carType);
}

void DS::buildTreeAndAdd(int typeID, int num_of_models, carType *carType) {
    AVLTree<int, carModel *>* zero_new_models = new AVLTree<int, carModel *>;
    zero_new_models->NumOfNodes = num_of_models;
    int h = log2((double) num_of_models);                      //height of the tree
    int leafs_to_del = pow(2, h + 1) - num_of_models - 1;
    int current_model = 0;
    TreeNode<int, carModel*>* head = new TreeNode<int, carModel*>;
    zero_new_models->head = head;
    zero_new_models->head->height = h;
    zero_new_models->completeTree(zero_new_models->head, h); //making complete tree
    zero_new_models->makeTreeAlmostComplete(zero_new_models->head, h, &leafs_to_del);  // deleting the reserved leafs from the right
    fillTreeWithInorder(zero_new_models->head, typeID, num_of_models, &current_model, carType); // filling the tree with car models by inorder
    zero_new_models->max = zero_new_models->head;
    zero_new_models->min = zero_new_models->head;
    all_zero_models.Add(typeID, zero_new_models);
}

void DS::updateBestSellerByType(carType *type, int modelID) {
    if ((type->best_seller != modelID && type->models[modelID]->num_of_sales > type->best_num_of_sales) ||
            (type->best_seller > modelID && type->best_num_of_sales == type->models[modelID]->num_of_sales)) {
        type->best_seller = modelID;
        type->best_num_of_sales = type->models[modelID]->num_of_sales;
    } else if (type->best_seller == modelID) {
        type->best_num_of_sales = type->models[modelID]->num_of_sales;
    }

}

void DS::makeComplaint(int typeID, int modelID, int t) {
    carType **type = types.Find(typeID);
    if (!type){
        throw KeyNotExist();
    }
    PriorityByGrade old_pg((*type)->models[modelID]->grade, typeID, modelID);
    (*type)->models[modelID]->complainModel(t);
    PriorityByGrade new_pg((*type)->models[modelID]->grade, typeID, modelID);
    if (old_pg.grade == 0) {
        if (new_pg.grade == 0) {
            return;
        } else {
            AVLTree<int, carModel *> **current_zero_tree = all_zero_models.Find(typeID);
            (*current_zero_tree)->Remove(modelID);
            all_models.Add(new_pg, (*type)->models[modelID]);
        }

    } else {
        all_models.Remove(old_pg);
        if (new_pg.grade == 0) {
            AVLTree<int, carModel *> **current_zero_tree = all_zero_models.Find(typeID);
            (*current_zero_tree)->Add(modelID, (*type)->models[modelID]);
        } else {
            all_models.Add(new_pg, (*type)->models[modelID]);
        }
    }
}

void DS::getBestSellerModelByType(int typeID, int *modelID) {
    if (typeID == 0){
        *modelID = best_seller.GetMaxKey().modelID;
    } else{
        carType **type = types.Find(typeID);
        if (!type){
            throw KeyNotExist();
        }
        *modelID = (*type)->best_seller;
    }
}

void DS::getWorstModels(int num_of_models, int *car_types, int *models) {
    if (num_of_models > total_cars){
        throw NotEnoughCars();
    }
    int counter = 0;
    int * cat_types_ptr = car_types;
    int * models_ptr = models;
    if (all_models.head){ // Check if All models tree is empty
        inorderAllModels(all_models.head,num_of_models, cat_types_ptr, models_ptr, &counter);
    } else {
        inorderAllZeroTypes(all_zero_models.head, num_of_models, cat_types_ptr, models_ptr, &counter);
    }
}

void DS::inorderAllModels(TreeNode<PriorityByGrade, carModel *> *v, int num_of_models, int *car_types, int *models, int *counter) {
    if (v == nullptr || *counter >= num_of_models){
        return;
    }
    inorderAllModels(v->left, num_of_models, car_types, models, counter);
    if (v->data->grade > 0){
        TreeNode<int,AVLTree<int, carModel*>*> *head = all_zero_models.head;
        inorderAllZeroTypes(head, num_of_models, car_types, models, counter);
    }
    if (*counter >= num_of_models){
        return;
    } else {
        car_types[*counter] = v->data->typeID;
        models[*counter] = v->data->modelID;
        *counter = * counter +1;
    }
    inorderAllModels(v->right, num_of_models, car_types, models, counter);
}

void DS::inorderAllZeroTypes(TreeNode<int, AVLTree<int, carModel *>*> *v, int num_of_models, int *car_types, int *models, int *counter) {
    if (v == nullptr || *counter >= num_of_models){
        return;
    }
    inorderAllZeroTypes(v->left, num_of_models, car_types, models, counter);
    inorderAllZeroModels(v->data->head, num_of_models, car_types, models, counter);
    inorderAllZeroTypes(v->right, num_of_models, car_types, models, counter);
}

void DS::inorderAllZeroModels(TreeNode<int, carModel *> *v, int num_of_models, int *car_types, int *models, int *counter) {
    if (v == nullptr || *counter >= num_of_models){
        return;
    }
    inorderAllZeroModels(v->left, num_of_models, car_types, models, counter);
    if (*counter >= num_of_models){
        return;
    } else {
        car_types[*counter] = v->data->typeID;
        models[*counter] = v->data->modelID;
        *counter = * counter + 1;
    }
    inorderAllZeroModels(v->right, num_of_models, car_types, models, counter);
}

void DS::quit() {
    postOrderDelete(types.head);
}

void DS::postOrderDelete(TreeNode<int, carType* >* v) {
    if (v == nullptr){
        return;
    }
    postOrderDelete(v->left);
    postOrderDelete(v->right);
    for (int i = 0; i < v->data->num_of_models ; ++i) {
        delete v->data->models[i];
    }
    delete v;
}





