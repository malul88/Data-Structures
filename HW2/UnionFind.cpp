#include "UnionFind.h"

void UnionFind::Union(UpTreeNode<int, Agency *> *v, UpTreeNode<int, Agency *> *w) {
    if (v == w){
        return;
    }
    int m1 = v->data->num_of_cars;
    int m2 = w->data->num_of_cars;
    // Creating two arrays and put the sorted cars into the arrays
    PriorityBySale* array1 = new PriorityBySale[m1];
    PriorityBySale* array2 = new PriorityBySale[m2];
    int counter = 0;
    v->data->treeToArray(v->data->cars->head, array1,&counter);
    counter = 0;
    w->data->treeToArray(w->data->cars->head, array2,&counter);
    // Create third array in the size m1 + m2 for merging both of them
    // into one array
    PriorityBySale* array3 = new PriorityBySale[m1 + m2];
    // Merge two sorted arrays
    w->data->mergeArrays(array1, array2, m1, m2, array3);
    RankTree<PriorityBySale,int> * tree = new RankTree<PriorityBySale,int>;
    v->data->arrayToTree(array3, m1+m2, tree);
    // Now we have the tree which have all the unionised cars inside "tree"
    delete(v->data->cars);
    delete(w->data->cars);
    delete[] array1;
    delete[] array2;
    delete[] array3;
    // Uniting by the smaller agency
    if (m1 > m2){
        v->data->cars = tree;
        delete (w->data);
        w->parent = v;
        v->data->num_of_cars += m2;
    } else {
        w->data->cars = tree;
        delete (v->data);
        v->parent = w;
        w->data->num_of_cars += m1;
    }
}

UpTreeNode<int, Agency *> *UnionFind::find(int AgencyID) {
    UpTreeNode<int, Agency*>* a = agencies.array[AgencyID];
    return getTopAndShrink(a);
}

UpTreeNode<int, Agency *> *UnionFind::getTopAndShrink(UpTreeNode<int, Agency *> *v) {
    if (v->parent == nullptr){
        return v;
    }
    v->parent = getTopAndShrink(v->parent); //TODO needs to be checked
    return v;
}

void UnionFind::sellCar(int AgencyID ,int typeID, int k) {
    int * data = nullptr;
    data = all_cars.Find(typeID);
    if (data != nullptr) {
        PriorityBySale old_ps(typeID, *data);
        PriorityBySale new_ps(typeID, *data + k);
        all_cars.Remove(typeID);
        find(AgencyID)->data->cars->Remove(old_ps);
        find(AgencyID)->data->cars->Add(new_ps, new_ps.num_of_sales);
        all_cars.Add(typeID, new_ps.num_of_sales);
    } else {
        PriorityBySale new_ps(typeID, k);
        all_cars.Add(typeID, new_ps.num_of_sales);
        find(AgencyID)->data->cars->Add(new_ps, new_ps.num_of_sales);
    }

}
