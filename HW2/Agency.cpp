
#include "Agency.h"


void Agency::treeToArray(TreeNode<PriorityBySale, int> *v, PriorityBySale *array, int *counter) {
    if (v == nullptr) {
        return;
    }
    treeToArray(v->left, array, counter);
    array[*counter] = v->key;
    (*counter)++;
    treeToArray(v->right, array, counter);
}


void Agency::mergeArrays(PriorityBySale *arr1, PriorityBySale *arr2, int n1, int n2, PriorityBySale *arr3) {
    int i = 0, j = 0, k = 0;
    // Traverse both array
    while (i < n1 && j < n2) {
        // Check if current element of first
        // array is smaller than current element
        // of second array. If yes, store first
        // array element and increment first array
        // index. Otherwise do same with second array
        if (arr1[i] < arr2[j])
            arr3[k++] = arr1[i++];
        else
            arr3[k++] = arr2[j++];
    }
    // Store remaining elements of first array
    while (i < n1)
        arr3[k++] = arr1[i++];
    // Store remaining elements of second array
    while (j < n2)
        arr3[k++] = arr2[j++];
}

void Agency::arrayToTree(PriorityBySale *array, int m, RankTree<PriorityBySale, int> *t) {
    int h = log2((double) m);                      //heightNode of the tree
    int leafs_to_del = pow(2, h + 1) - m - 1;
    int current_car = 0;
    TreeNode<PriorityBySale, int> *head_ = new TreeNode<PriorityBySale, int>;
    t->head = head_;
    head_->height = h;
    t->NumOfNodes = m;
    t->max = head_;
    t->min = head_;
    t->MakeComleteTree(t->head, h);
    t->MakeAlmostComplete(t->head, h, &leafs_to_del);
    t->RankTheTree(t->head);
    fillTreeWithInorder(t->head, m, &current_car, array);
}


void Agency::fillTreeWithInorder(TreeNode<PriorityBySale, int> *v, int m, int *current_car, PriorityBySale *array) {
    if (*current_car == m || v == nullptr) {
        return;
    }
    fillTreeWithInorder(v->left, m, current_car, array);
    v->key = array[*current_car];
    v->data = array[*current_car].num_of_sales;
    *current_car = *current_car + 1;
    fillTreeWithInorder(v->right, m, current_car, array);
}

void Agency::sellCar(int typeID, int k) {

}

void Agency::treeToArray(TreeNode<int, int> *v, PriorityByType *array, int *counter) {
    if (v == nullptr) {
        return;
    }
    treeToArray(v->left, array, counter);
    array[*counter].typeID = v->key;
    array[*counter].num_of_sales = v->data;
    (*counter)++;
    treeToArray(v->right, array, counter);
}

void Agency::mergeArrays(PriorityByType *arr1, PriorityByType *arr2, int n1, int n2, PriorityByType *arr3) {
    int i = 0, j = 0, k = 0;
    // Traverse both array
    while (i < n1 && j < n2) {
        // Check if current element of first
        // array is smaller than current element
        // of second array. If yes, store first
        // array element and increment first array
        // index. Otherwise do same with second array
        if (arr1[i] < arr2[j])
            arr3[k++] = arr1[i++];
        else
            arr3[k++] = arr2[j++];
    }
    // Store remaining elements of first array
    while (i < n1)
        arr3[k++] = arr1[i++];
    // Store remaining elements of second array
    while (j < n2)
        arr3[k++] = arr2[j++];
}

void Agency::arrayToTree(PriorityByType *array, int m, RankTree<int, int> *t) {
    int h = log2((double) m);                      // heightNode of the tree
    int leafs_to_del = pow(2, h + 1) - m - 1;
    int current_car = 0;
    TreeNode<int, int> *head_ = new TreeNode<int, int>;
    t->head = head_;
    head_->height = h;
    t->NumOfNodes = m;
    t->max = head_;
    t->min = head_;
    t->MakeComleteTree(t->head, h);
    t->MakeAlmostComplete(t->head, h, &leafs_to_del);
    t->RankTheTree(t->head);
    fillTreeWithInorder(t->head, m, &current_car, array);
}

void Agency::fillTreeWithInorder(TreeNode<int, int> *v, int m, int *current_car, PriorityByType *array) {
    if (*current_car == m || v == nullptr) {
        return;
    }
    fillTreeWithInorder(v->left, m, current_car, array);
    v->key = array[*current_car].typeID;
    v->data = array[*current_car].num_of_sales;
    *current_car = *current_car + 1;
    fillTreeWithInorder(v->right, m, current_car, array);
}


