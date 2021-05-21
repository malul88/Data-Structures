#include "DS.h"

void DS::addCarType(int typeID, int num_of_models) {
    carType *new_car = new carType(typeID, num_of_models);            // A new Car type
    buildTreeAndAdd(typeID, num_of_models, new_car);          // AVLaddNode a sub tree with all models to zero_models
    types.AVLaddNode(typeID, new_car);         // AVLaddNode the type of the Car to the types tree
    total_cars += num_of_models;
}

void deleteModel(carModel *carModel) {
    delete carModel;
}

void DS::removeCarType(int typeID) {
    carType **type = types.AVLfindData(typeID);
    if (!type) {
        throw KeyNotExist();
    }
    total_cars -= (*type)->num_of_models;
    for (int i = 0; i < (*type)->num_of_models; ++i) {
        PriorityBySale ps((*type)->models[i]->num_of_sales, (*type)->typeID, (*type)->models[i]->modelID);
        PriorityByGrade pg((*type)->models[i]->grade, (*type)->typeID, (*type)->models[i]->modelID);
        if (best_seller.AVLfindData(ps) != NULL) {
            best_seller.AVLremoveNodeByKey(ps);
        }
        if (all_models.AVLfindData(pg)) {
            all_models.AVLremoveNodeByKey(pg);
        }
        delete (*type)->models[i];
    }
    AVLTree<int, carModel *> **zeroed_models = all_zero_models.AVLfindData(typeID); // Sub_tree of all_zero_models
    (*zeroed_models)->AVLremove((*zeroed_models)->AVLgetHead());
    all_zero_models.AVLremoveNodeByKey(typeID);
    types.AVLremoveNodeByKey(typeID);

}

void DS::sellCar(int typeID, int modelID) {
    carType **type = types.AVLfindData(typeID);
    if (!type || (*type)->num_of_models <= modelID) {
        throw KeyNotExist();
    }
    bool is_zero = (*type)->models[modelID]->grade == 0;
    bool is_saled = (*type)->models[modelID]->num_of_sales != 0;
    if (!is_zero) {                       // If not in zero models (remove from models)
        PriorityByGrade old_pg((*type)->models[modelID]->grade, (*type)->models[modelID]->typeID,
                               (*type)->models[modelID]->modelID);
        all_models.AVLremoveNodeByKey(old_pg);
    } else {                       // If is in zero models (needs to remove)
        AVLTree<int, carModel *> **current_zero_tree = all_zero_models.AVLfindData(typeID);
        (*current_zero_tree)->AVLremoveNodeByKey(modelID);
    }
    if (is_saled) {   // If been sales before (remove from best seller)
        PriorityBySale old_ps((*type)->models[modelID]->num_of_sales, (*type)->models[modelID]->typeID,
                              (*type)->models[modelID]->modelID);
        best_seller.AVLremoveNodeByKey(old_ps);
    }
    (*type)->models[modelID]->grade += SALE_GRADE;
    (*type)->models[modelID]->num_of_sales += 1;
    if ((*type)->models[modelID]->grade == 0) {  // if moves to zero models from all models
        AVLTree<int, carModel *> **current_zero_tree = all_zero_models.AVLfindData(typeID);
        (*current_zero_tree)->AVLaddNode(modelID, (*type)->models[modelID]);
    } else {  // if not zero to not zero
        PriorityByGrade new_pg((*type)->models[modelID]->grade, (*type)->models[modelID]->typeID,
                               (*type)->models[modelID]->modelID);
        all_models.AVLaddNode(new_pg, (*type)->models[modelID]);
    } // Always put in Best seller regardless
    PriorityBySale new_ps((*type)->models[modelID]->num_of_sales, (*type)->models[modelID]->typeID,
                          (*type)->models[modelID]->modelID);
    best_seller.AVLaddNode(new_ps, (*type)->models[modelID]);
    updateBestSellerByType((*type), modelID);
}


void DS::fillTreeWithInorder(Node<int, carModel *> *v, int typeID, int num_of_models,
                             int *current_model, carType *carType) {
    if (*current_model == num_of_models || v == nullptr) {
        return;
    }
    fillTreeWithInorder(v->leftSon, typeID, num_of_models, current_model, carType);
    v->keyNode = *current_model;
    carModel *car = new carModel(typeID, *current_model);
    v->dataNode = car;
    carType->models[*current_model] = car;
    *current_model = *current_model + 1;
    fillTreeWithInorder(v->rightSon, typeID, num_of_models, current_model, carType);
}

void DS::buildTreeAndAdd(int typeID, int num_of_models, carType *carType) {
    AVLTree<int, carModel *> *zero_new_models = new AVLTree<int, carModel *>;
    zero_new_models->AVLnodesCounter = num_of_models;
    int h = log2((double) num_of_models);                      //heightNode of the tree
    int leafs_to_del = pow(2, h + 1) - num_of_models - 1;
    int current_model = 0;
    Node<int, carModel *> *head = new Node<int, carModel *>;
    zero_new_models->AVLhead = head;
    zero_new_models->AVLhead->heightNode = h;
    zero_new_models->AVLdoComplete(zero_new_models->AVLhead, h); //making complete tree
    zero_new_models->AVLdoAlmostComplete(zero_new_models->AVLhead, h, &leafs_to_del);  // deleting the reserved leafs from the rightSon
    fillTreeWithInorder(zero_new_models->AVLhead, typeID, num_of_models, &current_model, carType); // filling the tree with car models by inorder
    zero_new_models->AVLmaxNodeByKey = zero_new_models->AVLhead;
    zero_new_models->AVLminNodeByKey = zero_new_models->AVLhead;
    all_zero_models.AVLaddNode(typeID, zero_new_models);
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
    carType **type = types.AVLfindData(typeID);
    if (!type || (*type)->num_of_models <= modelID) {
        throw KeyNotExist();
    }
    PriorityByGrade old_pg((*type)->models[modelID]->grade, typeID, modelID);
    (*type)->models[modelID]->complainModel(t);
    PriorityByGrade new_pg((*type)->models[modelID]->grade, typeID, modelID);
    if (old_pg.grade == 0) {
        if (new_pg.grade == 0) {
            return;
        } else {
            AVLTree<int, carModel *> **current_zero_tree = all_zero_models.AVLfindData(typeID);
            (*current_zero_tree)->AVLremoveNodeByKey(modelID);
            all_models.AVLaddNode(new_pg, (*type)->models[modelID]);
        }
    } else {
        all_models.AVLremoveNodeByKey(old_pg);
        if (new_pg.grade == 0) {
            AVLTree<int, carModel *> **current_zero_tree = all_zero_models.AVLfindData(typeID);
            (*current_zero_tree)->AVLaddNode(modelID, (*type)->models[modelID]);
        } else {
            all_models.AVLaddNode(new_pg, (*type)->models[modelID]);
        }
    }
}

void DS::getBestSellerModelByType(int typeID, int *modelID) {
    if (typeID == 0) {
        *modelID = best_seller.AVLgetMaxKey().modelID;
    } else {
        carType **type = types.AVLfindData(typeID);
        if (!type) {
            throw KeyNotExist();
        }
        *modelID = (*type)->best_seller;
    }
}

void DS::getWorstModels(int num_of_models, int *car_types, int *models) {
    if (num_of_models > total_cars) {
        throw NotEnoughCars();
    }
    int counter = 0;
    int *cat_types_ptr = car_types;
    int *models_ptr = models;
    if (all_models.AVLhead) { // Check if All models tree is empty
        inorderAllModels(all_models.AVLhead, num_of_models, cat_types_ptr, models_ptr, &counter);
    } else {
        inorderAllZeroTypes(all_zero_models.AVLhead, num_of_models, cat_types_ptr, models_ptr, &counter);
    }
    been_in_zero = false;
}

void DS::inorderAllModels(Node<PriorityByGrade, carModel *> *v, int num_of_models, int *car_types, int *models, int *counter) {
    if (v == nullptr || *counter >= num_of_models) {
        return;
    }
    inorderAllModels(v->leftSon, num_of_models, car_types, models, counter);
    if (v->dataNode->grade > 0 && !been_in_zero) {
        Node<int, AVLTree<int, carModel *> *> *head = all_zero_models.AVLhead;
        inorderAllZeroTypes(head, num_of_models, car_types, models, counter);
    }
    if (*counter >= num_of_models) {
        return;
    } else {
        car_types[*counter] = v->dataNode->typeID;
        models[*counter] = v->dataNode->modelID;
        *counter = *counter + 1;
    }
    inorderAllModels(v->rightSon, num_of_models, car_types, models, counter);
}

void DS::inorderAllZeroTypes(Node<int, AVLTree<int, carModel *> *> *v, int num_of_models, int *car_types, int *models, int *counter) {
    if (v == nullptr || *counter >= num_of_models) {
        been_in_zero = true;
        return;
    }
    inorderAllZeroTypes(v->leftSon, num_of_models, car_types, models, counter);
    inorderAllZeroModels(v->dataNode->AVLhead, num_of_models, car_types, models, counter);
    inorderAllZeroTypes(v->rightSon, num_of_models, car_types, models, counter);
}

void DS::inorderAllZeroModels(Node<int, carModel *> *v, int num_of_models, int *car_types, int *models, int *counter) {
    if (v == nullptr || *counter >= num_of_models) {
        return;
    }
    inorderAllZeroModels(v->leftSon, num_of_models, car_types, models, counter);
    if (*counter >= num_of_models) {
        return;
    } else {
        car_types[*counter] = v->dataNode->typeID;
        models[*counter] = v->dataNode->modelID;
        *counter = *counter + 1;
    }
    inorderAllZeroModels(v->rightSon, num_of_models, car_types, models, counter);
}

void DS::quit() {
    postOrderDelete(types.AVLhead); // TODO delete all sub-trees in all zero models.
    typesPostOrderDelete(all_zero_models.AVLhead);
}

void DS::postOrderDelete(Node<int, carType *> *v) {
    if (v == nullptr) {
        return;
    }
    postOrderDelete(v->leftSon);
    postOrderDelete(v->rightSon);
    for (int i = 0; i < v->dataNode->num_of_models; ++i) {
        delete v->dataNode->models[i];
    }
    delete v;
}

void DS::modelsPostOrderDelete(Node<int, carModel *> *v) {
    if (v == nullptr){
        return;
    }
    modelsPostOrderDelete(v->leftSon);
    modelsPostOrderDelete(v->rightSon);
    delete v;
}

void DS::typesPostOrderDelete(Node<int, AVLTree<int, carModel*>*> * v) {
    if (v == nullptr){
        return;
    }
    typesPostOrderDelete(v->leftSon);
    typesPostOrderDelete(v->rightSon);
    //modelsPostOrderDelete(v->dataNode->AVLhead);
    delete v->dataNode;
}
