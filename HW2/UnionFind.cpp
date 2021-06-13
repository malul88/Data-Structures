#include "UnionFind.h"

void UnionFind::Union(UpTreeNode<int, Agency *> *v, UpTreeNode<int, Agency *> *w) {
    if (v == w) {
        return;
    }
    int m1 = v->data->num_of_cars;
    int m2 = w->data->num_of_cars;
    if (m2 == 0) {
        delete (w->data);
        w->data = nullptr;
        w->parent = v;
        return;
    } else if (m1 == 0) {
        delete (v->data);
        v->data = nullptr;
        v->parent = w;
        return;
    }
    RankTree<PriorityBySale, int> *cars = new RankTree<PriorityBySale, int>;
    UniteTrees<RankTree<PriorityBySale, int>, PriorityBySale>(v, w, CARS, cars);
    RankTree<int, int> *id_cars = new RankTree<int, int>;
    UniteTrees<RankTree<int, int>, PriorityByType>(v, w, ID_CARS, id_cars);

    // Uniting by the smaller agency
    if (m1 > m2) {
        Agency *new_agency = new Agency(v->data->agencyID, v->data->num_of_cars);
        new_agency->cars = cars;
        new_agency->id_cars = id_cars;
        Agency *old_agency = v->data;
        v->data = new_agency;
        delete old_agency;
        delete (w->data);
        w->data = nullptr;
        w->parent = v;
        v->data->num_of_cars += m2;
    } else {
        Agency *new_agency = new Agency(w->data->agencyID, w->data->num_of_cars);
        new_agency->cars = cars;
        new_agency->id_cars = id_cars;
        Agency* old_agency = w->data;
        w->data = new_agency;
        delete old_agency;
        delete (v->data);
        v->data = nullptr;
        v->parent = w;
        w->data->num_of_cars += m1;
    }
}

UpTreeNode<int, Agency *> *UnionFind::find(int AgencyID) {
    if (AgencyID >= agencies->count) {
        throw KeyNotExist();
    }
    UpTreeNode<int, Agency *> *a = agencies->array[AgencyID];
    return getTopAndShrink(a);
}

UpTreeNode<int, Agency *> *UnionFind::getTopAndShrink(UpTreeNode<int, Agency *> *v) {
    if (v->parent == nullptr) {
        return v;
    } else if (v->parent->parent == nullptr) {
        return v->parent;
    }
    UpTreeNode<int, Agency *> *root = v;
    while (root->parent) {
        root = root->parent;
    }
    UpTreeNode<int, Agency *> *temp = v;
    while (temp) {
        temp = temp->parent;
        v->parent = root;
    }
    return root;
}

void UnionFind::sellCar(int AgencyID, int typeID, int k) {
    int *data = nullptr;
    Agency *agency = find(AgencyID)->data;
    if (!agency) {
        throw KeyNotExist();
    }
    if (agency->id_cars->head != nullptr) {
        data = agency->id_cars->Find(typeID);
        if (data != nullptr) {
            PriorityBySale old_ps(*data, typeID);
            PriorityBySale new_ps(*data + k, typeID);
            agency->id_cars->Remove(typeID);
            agency->cars->Remove(old_ps);
            agency->cars->Add(new_ps, new_ps.num_of_sales);
            agency->id_cars->Add(typeID, new_ps.num_of_sales);
        } else {
            PriorityBySale new_ps(k, typeID);
            agency->id_cars->Add(typeID, new_ps.num_of_sales);
            agency->cars->Add(new_ps, new_ps.num_of_sales);
            agency->num_of_cars++;
        }
    } else {
        PriorityBySale new_ps(k, typeID);
        agency->id_cars->Add(typeID, new_ps.num_of_sales);
        agency->cars->Add(new_ps, new_ps.num_of_sales);
        agency->num_of_cars++;
    }
}

int UnionFind::findCarByIndex(int agencyID, int i) {
    Agency *agency = (find(agencyID))->data;
    if (!agency || i > agency->num_of_cars) {
        throw KeyNotExist();
    }
    TreeNode<PriorityBySale, int> *node = agency->cars->findElementByIndex(agency->cars->head, i);

    if (node) {
        return node->key.typeID;
    } else {
        throw KeyNotExist();
    }
}

template<class C, class T>
void UnionFind::UniteTrees(UpTreeNode<int, Agency *> *v, UpTreeNode<int, Agency *> *w, int type, C *c) {
    int m1 = v->data->num_of_cars;
    int m2 = w->data->num_of_cars;
    // Creating two arrays and put the sorted cars into the arrays
    T *array1 = new T[m1];
    T *array2 = new T[m2];
    int counter = 0;
    // Check which tree for union
    if (type == CARS) {
        v->data->treeToArray(v->data->cars->head, (PriorityBySale *) array1, &counter);
        counter = 0;
        w->data->treeToArray(w->data->cars->head, (PriorityBySale *) array2, &counter);
    } else if (type == ID_CARS) {
        v->data->treeToArray(v->data->id_cars->head, (PriorityByType *) array1, &counter);
        counter = 0;
        w->data->treeToArray(w->data->id_cars->head, (PriorityByType *) array2, &counter);
    }
    // Create third array in the size m1 + m2 for merging both of them
    // into one array
    T *array3 = new T[m1 + m2];
    // Merge two sorted arrays
    w->data->mergeArrays(array1, array2, m1, m2, array3);
    v->data->arrayToTree(array3, m1 + m2, c);
    // Now we have the tree which have all the unionised cars inside "tree"
    delete[] array1;
    delete[] array2;
    delete[] array3;
}

UpTreeNode<int, Agency *> *UnionFind::shrink(UpTreeNode<int, Agency *> *v) {
    if (v->parent == nullptr) {
        return v;
    }
    v->parent = shrink(v->parent);
    return v;
}

