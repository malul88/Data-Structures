//
// Created by yoav malul on 08/05/2017.
//

#ifndef MEVNE_HW1_TREE_H
#define MEVNE_HW1_TREE_H

#include <stdlib.h>
#include <stdexcept>
#include "Execption.h"

#define LROLL 2
#define RROLL -2
#define NULL_HEIGHT -1


template<class KEY, class DATA>
class TreeNode {
public:
    KEY key;
    DATA data;
    int height;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    int rank;
    int sum_power;

    TreeNode() :
            key(), data(), height(0), left(NULL), right(NULL),
            parent(NULL),rank(0),sum_power(0) {
    }

    TreeNode(KEY key, DATA data) :
            key(key), data(data), height(0), left(NULL), right(NULL),
            parent(
                    NULL) {
    }

    bool operator<(TreeNode &node) const {
        return key < (node.key);
    }

    bool operator>(TreeNode &node) const {
        return key > (node.key);
    }

    bool operator<=(TreeNode &node) const {
        return key <= (node.key);
    }

    bool operator>=(TreeNode &node) const {
        return key >= (node.key);
    }

    bool operator==(TreeNode &node) const {
        return key == (node.key);
    }

    bool operator!=(TreeNode &node) const {
        return key != (node.key);
    }
};

template<class KEY, class DATA>
class AVLTree {
public:
    AVLTree() :
            head(NULL), NumOfNodes(0), max(NULL), min(NULL) {
    };
    ~AVLTree();

    int GetSize() const {
        return this->NumOfNodes;
    }


    DATA *Find(const KEY &key);
    // returns the node with the given key , if not found NULL

    DATA *Add(const KEY &key, const DATA &data);
    // adds a node with the given key and data to the tree
    // if the key is already in ,throws KEY_ALREADY_EXIST

    void Remove(const KEY &key);
    // removes the node with the given key if found
    // else it throws KEY_NOT_EXIST

    void InOrder(KEY *arr, int *iterator);

    // does inorder on the tree and returns the results in arr,arr must be already allocated
    // and must have enough space ,iterator marks the index from which the filling of the
    // arr starts , and in the end will hold the index of the last

    template<class Function>
    void BackOrder(Function &func,DATA* arr);
    // does the opposite od in order on all nodes using a given function class

    template<class Function>
    void BackOrder(Function &func);

    KEY &GetMaxKey() const {
        this->CheckEmptyTree();
        return max->key;
    }
    //returns the maximum key , if the tree is empty
    // throws TREE_EMPTY

    KEY &GetMinKey() const {
        this->CheckEmptyTree();
        return min->key;
    }
    //returns the minimum key , if the tree is empty
    // throws TREE_EMPTY

    DATA &GetMaxData() const {
        this->CheckEmptyTree();
        return max->data;
    }
    //returns the maximum's key data , if the tree is empty
    // throws TREE_EMPTY

    DATA &GetMinData() const {
        this->CheckEmptyTree();
        return min->data;
    }
    //returns the minimum's key data , if the tree is empty
    // throws TREE_EMPTY

    TreeNode<KEY, DATA> *GetHead() {
        return head;
    }
    // returns the head of the tree
//    void UpdateMax
    TreeNode<KEY, DATA> *head;
    int NumOfNodes;
    TreeNode<KEY, DATA> *max;
    TreeNode<KEY, DATA> *min;

    /**** Functions*****/
    void LL(TreeNode<KEY, DATA> &);
    // performs an LL roll on the given node

    void RR(TreeNode<KEY, DATA> &);
    // performs an RR roll on the given node

    void LR(TreeNode<KEY, DATA> &);
    // performs an LR roll on the given node

    void RL(TreeNode<KEY, DATA> &);
    // performs an RL roll on the given node

    TreeNode<KEY, DATA> *FindPlace(const KEY &key,int x) const;
    // returns  the node with the given key , if he is not found
    // returns the node that should be his parent,returns NULL if the tree is empty

    static int height(TreeNode<KEY, DATA> *v);
    //function to return the height of a node,if NULL return -1

    static void UpdateHeight(TreeNode<KEY, DATA> *v);
    //function that updates the height of a node

    static int BF(TreeNode<KEY, DATA> &v);
    //function to calculate the BF of a node

    TreeNode<KEY, DATA> *TreeRemove(TreeNode<KEY, DATA> *v);
    //removes the given node from the tree and returns his parent

    void SwapWithFollowing(TreeNode<KEY, DATA> &v);
    //swaps the given node with the smallest node that is bigger that it

    void DoRoll(TreeNode<KEY, DATA> *v);
    // does the needed roll on v according to it's BF

    void RemoveLeaf(TreeNode<KEY, DATA> &v);
    //removes a node that is a leaf

    void RemoveOneSonNode(TreeNode<KEY, DATA> &v);
    //removes a node that have only one son from the tree

    static TreeNode<KEY, DATA> *FindFollowingNode(TreeNode<KEY, DATA> *v);
    //return the smallest node that is bigger than v

    static TreeNode<KEY, DATA> *FindPreviousNode(TreeNode<KEY, DATA> *v);
    //return the biggest node that is smaller than v

    void CheckEmptyTree() const;
    //if the tree is empty throws TREE_EMPTY else doesnt do any thing

    void SwitchNodesForParent(TreeNode<KEY, DATA> *parent,
                              TreeNode<KEY, DATA> *son);
    // switches the places of the nodes parent and son
    // parent must be the parent of son

    void SwitchNodes(TreeNode<KEY, DATA> *highernode,
                     TreeNode<KEY, DATA> *lowernode);
    //switches the places of the nodes highernode and lowernode

    static void UpdateParentforSons(TreeNode<KEY, DATA> *node);
    // updates the parent pointer in the sones of the given node

    void SwitchSon(TreeNode<KEY, DATA> *v1, TreeNode<KEY, DATA> *v2);
    //lets v2 become the son of v1's parent instead of v1

    void InOrder(TreeNode<KEY, DATA> *v, KEY *arr, int *i);
    //does inorder on the tree of v and returns the keys in array,array must be allocated TODO

    void removeTree(TreeNode<KEY,DATA> * head);

    void completeTree(TreeNode<KEY, DATA> *v, int h);

    void makeTreeAlmostComplete(TreeNode<KEY, DATA> *v, int h, int *leafs_to_del);



    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class Function>
    void BackOrderRec(TreeNode<KEY, DATA> *v, Function& func,
                      DATA* arr);
    // does the opposite of inorder on all the nodes using a given function class
    //basel functions

    template<class Function>
    void BackOrderRec(TreeNode<KEY, DATA> *v,Function& func);
    ///////////////////////////////////////////////////////////////////////////////////////////

    static void TreeDeleteAux(TreeNode<KEY, DATA> *head);
    // deletes the tree that starts with the given head
    // in case the head is NULL does nothing

    /**** Functions*****/

};

template<class T>
void Swap(T &a, T &b) {
    T temp = b;
    b = a;
    a = temp;
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::Remove(const KEY &key) {
    TreeNode<KEY, DATA> *v = FindPlace(key,-1);
    if (v == NULL || (v->key) != key) {    // The key isn't in the tree
        throw KeyNotExist();
    }
    TreeNode<KEY, DATA> *parent = TreeRemove(v); // Removing
    this->NumOfNodes--;
    // Now we do the Rolling to keep the tree avl
    DoRoll(parent);
    return;
}

template<class KEY, class DATA>
TreeNode<KEY, DATA> *AVLTree<KEY, DATA>::TreeRemove(TreeNode<KEY, DATA> *v) {
    TreeNode<KEY, DATA> *parent;
    if (!v) {
        return NULL;
    }
    if ((v->key) == (max->key)) {
        max = FindPreviousNode(max);
    }
    if ((v->key) == (min->key)) {
        min = FindFollowingNode(min);
    }
    if (height(v) == 0) {
        parent = v->parent;
        RemoveLeaf(*v);
        delete v;

        return parent;
    }
    if (v->right == NULL || v->left == NULL) {
        parent = v->parent;
        RemoveOneSonNode(*v);
        delete v;
        return parent;
    }
    SwapWithFollowing(*v);
    return TreeRemove(v); //now v is a leaf or a one son node
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::SwapWithFollowing(TreeNode<KEY, DATA> &v) {
    TreeNode<KEY, DATA> *following = FindFollowingNode(&v);
    SwitchNodes(&v,
                following); //following is definitely lower than v because v has 2 sons
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::UpdateParentforSons(TreeNode<KEY, DATA> *parent) {
    if (parent == NULL) {
        return;
    }
    if (parent->left) {
        parent->left->parent = parent;
    }
    if (parent->right) {
        parent->right->parent = parent;
    }
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::SwitchNodesForParent(TreeNode<KEY, DATA> *parent,
                                              TreeNode<KEY, DATA> *son) {
    if (parent == NULL || son == NULL) {
        return;
    }

    Swap(parent->height, son->height);
    if (parent->right == son) {
        Swap(parent->left, son->left);
        parent->right = son->right;
        son->right = parent;
    } else {
        Swap(parent->right, son->right);
        parent->left = son->left;
        son->left = parent;
    }
    SwitchSon(parent, son);
    // makes the parent of the parent point to the son
    son->parent = parent->parent;
    UpdateParentforSons(parent);
    UpdateParentforSons(son);
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::SwitchNodes(TreeNode<KEY, DATA> *highernode,
                                     TreeNode<KEY, DATA> *lowernode) {
    if (highernode == lowernode->parent) {
        SwitchNodesForParent(highernode, lowernode);
        return;
    }

    Swap(highernode->height, lowernode->height);
    Swap(highernode->left, lowernode->left);
    Swap(highernode->right, lowernode->right);
    SwitchSon(highernode, lowernode);
    // makes the parent of highernode point to lowernode
    SwitchSon(lowernode, highernode);
    // makes the parent of lowernode  point to highernode

    Swap(lowernode->parent, highernode->parent);
    // makes sure to change the parent ptr in highernode and lowernode to their new parents
    UpdateParentforSons(highernode);
    UpdateParentforSons(lowernode);
    // updates the parent ptr of the sons of the two nodes
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::SwitchSon(TreeNode<KEY, DATA> *v1,
                                   TreeNode<KEY, DATA> *v2) {
    if (v1->parent != NULL) {
        if (v1->parent->right == v1) {
            v1->parent->right = v2;
        } else {
            v1->parent->left = v2;
        }
    } else {
        head = v2;
    }
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::RemoveLeaf(TreeNode<KEY, DATA> &v) {
    SwitchSon(&v, NULL);
    // makes the parent of v point to NULL
    // if v is head then head=NULL
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::RemoveOneSonNode(TreeNode<KEY, DATA> &v) {

    TreeNode<KEY, DATA> *son = v.right != NULL ? v.right : v.left;
    SwitchSon(&v, son); //let son become the son of the parent of v
    if(son){
        son->parent = v.parent;
        UpdateHeight(v.parent);
    }

}

template<class KEY, class DATA>
TreeNode<KEY, DATA> *AVLTree<KEY, DATA>::FindFollowingNode(
        TreeNode<KEY, DATA> *v) {
    TreeNode<KEY, DATA> *w = v->right; //w is bigger than v
    if (w == NULL) {
        return v->parent;
    }
    TreeNode<KEY, DATA> *following = w;
    while (w != NULL) {
        following = w;
        w = w->left; //get the smallest w
    }
    return following;
}

template<class KEY, class DATA>
TreeNode<KEY, DATA> *AVLTree<KEY, DATA>::FindPreviousNode(
        TreeNode<KEY, DATA> *v) {
    TreeNode<KEY, DATA> *w = v->left; //w is bigger than v
    if (w == NULL) {
        return v->parent;
    }
    TreeNode<KEY, DATA> *prev = w;
    while (w != NULL) {
        prev = w;
        w = w->right; //get the smallest w
    }
    return prev;
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::DoRoll(TreeNode<KEY, DATA> *v) {
    while (v != NULL) {
        int heightBefore = height(v);
        UpdateHeight(v);
        int bf = BF(*v);
        TreeNode<KEY, DATA> *parent = v->parent;
        if (bf == LROLL) {
            if (BF(*v->left) >= 0) {
                LL(*v);
            } else {
                LR(*v);
            }
        }
        if (bf == RROLL) {
            if (BF(*v->right) <= 0) {
                RR(*v);
            } else {
                RL(*v);
            }
        }
        if (height(v) == heightBefore) {
            return; //the height didnt change so the tree is still avl
        }
        v = parent;
    }
    return;
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::RR(TreeNode<KEY, DATA> &v) {
    TreeNode<KEY, DATA> *rightSon = v.right;
    if ((head->key) == (v.key)){
        head = rightSon;
    }

    //change sons of v and his right son
    v.right = rightSon->left;
    if (rightSon->left != NULL) {
        rightSon->left->parent = &v; //TODO check here
    }
    rightSon->left = &v;
    UpdateHeight(&v);
    UpdateHeight(rightSon);

    //change the son of the parent of v to be rightSon
    SwitchSon(&v, rightSon);
    UpdateHeight(v.parent);
    //change parents of v and his right son
    rightSon->parent = v.parent;
    v.parent = rightSon;
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::LL(TreeNode<KEY, DATA> &node) {
    TreeNode<KEY, DATA> *leftson = node.left;
    if ((head->key) == (node.key)) {
        head = leftson;
    }

    //change the sons of the nodes
    node.left = leftson->right;
    if (leftson->right != NULL) {
        leftson->right->parent = &node;
    }
    leftson->right = &node;

    UpdateHeight(&node);
    UpdateHeight(leftson);

    // changing the parents
    SwitchSon(&node, leftson);
    UpdateHeight(node.parent);

    leftson->parent = node.parent;
    node.parent = leftson;

}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::RL(TreeNode<KEY, DATA> &v) {
    LL(*v.right);
    RR(v);
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::LR(TreeNode<KEY, DATA> &node) {
    RR(*node.left);
    LL(node);
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::UpdateHeight(TreeNode<KEY, DATA> *v) {
    if (v == NULL) {
        return;
    }
    v->height = 1 + std::max(height(v->right), height(v->left));
}

template<class KEY, class DATA>
int AVLTree<KEY, DATA>::height(TreeNode<KEY, DATA> *v) {
    if (v == NULL) {
        return NULL_HEIGHT;
    }
    return v->height;
}

template<class KEY, class DATA>
int AVLTree<KEY, DATA>::BF(TreeNode<KEY, DATA> &v) {
    return height(v.left) - height(v.right);
}

template<class KEY, class DATA>
template<class Function>
void AVLTree<KEY, DATA>::BackOrder(Function &func, DATA* arr) {
    BackOrderRec(head, func, arr);
}

template<class KEY, class DATA>
template<class Function>
void AVLTree<KEY, DATA>::BackOrder(Function &func) {
    BackOrderRec(head, func);
}


template<class KEY, class DATA>
template<class Function>
void AVLTree<KEY, DATA>::BackOrderRec(TreeNode<KEY, DATA> *v, Function& func,
                                      DATA* arr){
    if (!v) {
        return;
    }
    BackOrderRec(v->right, func,arr);
    func(v->data,arr);
    BackOrderRec(v->left, func,arr);
}

template<class KEY, class DATA>
template<class Function>
void AVLTree<KEY, DATA>::BackOrderRec(TreeNode<KEY, DATA> *v, Function& func){
    if (!v) {
        return;
    }
    BackOrderRec(v->right, func);
    if(v->key!=NULL) {
        func(v->key, v->data);
    }
    BackOrderRec(v->left, func);
}


template<class KEY, class DATA>
void AVLTree<KEY, DATA>::InOrder(KEY *arr, int *iterator) {
    if (arr == NULL || iterator == NULL) {
        return;
    }
    InOrder(head, arr, iterator);
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::InOrder(TreeNode<KEY, DATA> *v, KEY *arr,
                                 int *i){
    if (!v) {
        return;
    }
    InOrder(v->left, arr, i);
    arr[*i] = v->key;
    (*i)++;
    InOrder(v->right, arr, i);
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::CheckEmptyTree() const {
    if (NumOfNodes == 0) {
        throw TreeEmpty();
    }
}

//basel functions

template<class KEY, class DATA>
AVLTree<KEY, DATA>::~AVLTree<KEY, DATA>() {
    TreeDeleteAux(head);
    return;
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::TreeDeleteAux(TreeNode<KEY, DATA> *head) {
    if (head == NULL) {
        return;
    }
    TreeDeleteAux(head->left);
    TreeDeleteAux(head->right);
    delete (head);
    return;
}

template<class KEY, class DATA>
DATA *AVLTree<KEY, DATA>::Find(const KEY &key) {
    TreeNode<KEY, DATA> *node = FindPlace(key,0);
    if (node == NULL || (node->key) != key) { // then the key is not in the tree
        return NULL;
    }
    return &node->data;
}

template<class KEY, class DATA>
DATA *AVLTree<KEY, DATA>::Add(const KEY &key, const DATA &data) {
    TreeNode<KEY, DATA> *parent = FindPlace(key,1);
    if (parent != NULL && (parent->key) == key) { // then the key is in the tree
        throw KeyAlreadyExist();
    }
    TreeNode<KEY, DATA> *newkey = new TreeNode<KEY, DATA>(key, data);
    if (parent == NULL) {
        head = newkey;
        newkey->parent = NULL;
        NumOfNodes++;
        max = newkey;
        min = newkey;
        return &newkey->data;
    }
    if (key > (parent->key)) {
        parent->right = newkey;
    } else {
        parent->left = newkey;
    }
    newkey->parent = parent;
    NumOfNodes++;
    if ((newkey->key) > (max->key)) {
        max = newkey;
    }
    if ((newkey->key) < (min->key)) {
        min = newkey;
    }
    DoRoll(parent);    // checks the route of entering and makes all the changes to guarantee the tree is AVL
    return &newkey->data;
}

template<class KEY, class DATA>
TreeNode<KEY, DATA> *AVLTree<KEY, DATA>::FindPlace(const KEY &key,int x) const {
    TreeNode<KEY, DATA> *current = head;
    TreeNode<KEY, DATA> *parent = NULL;
    while (current != NULL) {

        if (key == (current->key)) {
            return current;
        }
        parent = current;
        if (key > (current->key)) {
            current->rank+=x;
            current = current->right;
        } else {
            current->rank+=x;
            current = current->left;
        }
    }
    return parent;
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::removeTree(TreeNode<KEY,DATA> * v) {
    if (v == nullptr) {
        return;
    }
    removeTree(v->left);
    removeTree(v->right);
    delete v;
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::completeTree(TreeNode<KEY, DATA> *v, int h) {
    if (h == 0) {
        return;
    }
    v->left = new TreeNode<KEY, DATA>;
    v->right = new TreeNode<KEY, DATA>;
    v->left->height = h - 1;
    v->right->height = h - 1;
    v->left->parent = v;
    v->right->parent = v;
    completeTree(v->left, h - 1);
    completeTree(v->right, h - 1);
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::makeTreeAlmostComplete(TreeNode<KEY, DATA> *v, int h, int *leafs_to_del) {
    if (v == nullptr || *leafs_to_del == 0) {
        return;
    }
    makeTreeAlmostComplete(v->right, h - 1, leafs_to_del);
    if (h == 1) {
        delete v->right;
        v->right = nullptr;
        *leafs_to_del = *leafs_to_del - 1;
        if (*leafs_to_del > 0) {
            delete v->left;
            v->left = nullptr;
            *leafs_to_del = *leafs_to_del - 1;
        }
    }
    makeTreeAlmostComplete(v->left, h - 1, leafs_to_del);

}


//void PathSumPower(int k, int* sum, RankNode* root) {
//    if (k > root->sub_size) {
//        (*sum) += root->sumPower;
//    }
//    GetPower get;
//    if (!root->left) {
//        if (k == 1) {
//            (*sum) += root->right->sumPower + get(root->data);
//            return;
//        }
//        if (k == 2) {
//            (*sum) += root->right->sumPower;
//        }
//    }
//    if (root->left->sub_size == k - 1) {
//        if (!root->right) {
//            (*sum) += get(root->data);
//            return;
//        }
//        (*sum) += root->right->sumPower + get(root->data);
//        return;
//    }
//    if (root->left->sub_size > k - 1) {
//        if (!root->right) {
//            (*sum) += get(root->data);
//            PathSumPower(k, sum, root->left);
//            return;
//        }
//        (*sum) += root->right->sumPower + get(root->data);
//        PathSumPower(k, sum, root->left);
//        return;
//    }
//    if (root->left->sub_size < k - 1) {
//        PathSumPower(k - (root->left->sub_size) - 1, sum, root->left);
//        return;
//    }
//    return;
//}

#endif //MEVNE_HW1_TREE_H
