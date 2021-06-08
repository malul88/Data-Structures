#ifndef HW2_AGENCY_H
#define HW2_AGENCY_H

#include <cmath>
#include "RankTree.h"
#include "SalesKey.h"
#include "UpTree.h"

class Agency {
public:
    int agencyID, num_of_cars;
    RankTree<PriorityBySale, int> *cars;
    UpTreeNode<int,Agency*> * head;

    Agency(int agencyID, int num_of_cars) : agencyID(agencyID), num_of_cars(num_of_cars) {
        cars = new RankTree<PriorityBySale, int>();
    }

    ~Agency() {
        delete cars;
    }

    Agency(const Agency &a) : agencyID(a.agencyID), num_of_cars(a.num_of_cars) {
        *cars = *a.cars;
    }

    void sellCar(int typeID, int k);

    void treeToArray(TreeNode<PriorityBySale, int> *v, PriorityBySale *array, int *counter);

    // Merge arr1[0..n1-1] and arr2[0..n2-1] into
    // arr3[0..n1+n2-1]
    void mergeArrays(PriorityBySale arr1[], PriorityBySale arr2[], int n1,
                     int n2, PriorityBySale arr3[]);

    void arrayToTree(PriorityBySale *array,int m, RankTree<PriorityBySale, int> *v);

    void fillTreeWithInorder(TreeNode<PriorityBySale, int> *v, int m,
    int *current_model, PriorityBySale *array);
};


#endif //HW2_AGENCY_H
