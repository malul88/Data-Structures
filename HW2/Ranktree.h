#ifndef HW2_WET_RankTREE_H
#define HW2_WET_RankTREE_H

#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include "Execption.h"



#define LROLL 2
#define RROLL -2
#define NULL_HEIGHT -1


template<class KEY, class DATA>
class TreeNode {
public:
    int Rank;
    int sum_power;
    int power;
    KEY key;
    DATA data;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    TreeNode() :
    key(), data(), height(0), left(nullptr), right(nullptr), parent(nullptr)
             {Rank=1;
                 power=0;
                 sum_power=0;
    }
    TreeNode(KEY key, DATA data,int power) :
     key(key), data(data), height(0), left(nullptr), right(nullptr), parent(
            nullptr)  {Rank=1;
        this->power=power;
        sum_power=power;
    }

    bool operator<(TreeNode &node) const {
        return key < (node.key);
    }

    bool operator>(TreeNode &node) const {
        return key > (node.key);
    }

    bool operator==(TreeNode &node) const {
        return key == (node.key);
    }

    bool operator!=(TreeNode &node) const {
        return key != (node.key);
    }
};

template<class KEY, class DATA>
class RankTree {
public:

    RankTree() :
            head(nullptr), NumOfNodes(0), max(nullptr), min(nullptr) {
    }
    ;
    ~RankTree();

    int GetSize() const {
        return this->NumOfNodes;
    }
    void UpdateMaxMinKey(TreeNode<KEY, DATA> *v){
        max=v;
        min=v;
    }
    DATA* Find(const KEY& key);
    // returns the node with the given key , if not found NULL

    DATA* Add(const KEY& key, const DATA& data,int power = 0);
    // adds a node with the given key and data to the tree
    // if the key is already in ,throws KEY_ALREADY_EXIST

    void Remove(const KEY& key,int power = 0);
    // removes the node with the given key if found
    // else it throws KEY_NOT_EXIST

    void InOrder(KEY* arr, int* iterator);	//TODO
    // does inorder on the tree and returns the results in arr,arr must be already allocated
    //  and must have enough space ,iterator marks the index from which the filling of the
    // arr starts , and in the end will hold the index of the last TODO
   void  UpdateRank(){
        UpdateRankAux(head);
    }

    template<class Function>
    void BackOrder(Function &func,DATA* arr);
    // does the opposite od in order on all nodes using a given function class

    template<class Function>
    void BackOrder(Function &func);
    // does the opposite od in order on all nodes using a given function class

    void GetAllPower(int index,int* sum) {
                GetAllPowerAux(index,head,sum);

    }
    void SetHead(TreeNode<KEY, DATA>* node){
        head=node;
    }

    void GetAllPowerAux(int index,TreeNode<KEY, DATA>* node,int* sum);
    KEY& GetMaxKey() const {
        this->CheckEmptyTree();
        return max->key;
    }
    //returns the maximum key , if the tree is empty
    // throws TREE_EMPTY

    KEY& GetMinKey() const {
        this->CheckEmptyTree();
        return min->key;
    }
    //returns the minimum key , if the tree is empty
    // throws TREE_EMPTY

    DATA& GetMaxData() const {
        this->CheckEmptyTree();
        return max->data;
    }
    //returns the maximum's key data , if the tree is empty
    // throws TREE_EMPTY

    DATA& GetMinData() const {
        this->CheckEmptyTree();
        return min->data;
    }
    //returns the minimum's key data , if the tree is empty
    // throws TREE_EMPTY

    TreeNode<KEY, DATA>* GetHead() {
        return head;
    }
    // returns the head of the tree


    TreeNode<KEY, DATA>* head;
    int NumOfNodes;
    TreeNode<KEY, DATA>* max;
    TreeNode<KEY, DATA>* min;

    /**** Functions*****/
    void UpdateRankAux(TreeNode<KEY,DATA>* v){

        if (!v) {
            //NumOfNodes=0;
            return;
        }

        UpdateRankAux(v->right);
        UpdateRankAux(v->left);
        NumOfNodes++;
        if(v->left){
            v->Rank+=v->left->Rank;
            v->sum_power+=v->left->sum_power;
            v->left->parent=v;
        }
        if(v->right){
            v->Rank+=v->right->Rank;
            v->sum_power+=v->right->sum_power;
            v->right->parent=v;

        }
        if (*(v->key) > *GetMaxKey()) {
            max = v;
        }
        if (*(v->key) < *GetMinKey()) {
            min = v;
        }
        UpdateHeight(v);

    }
    void LL(TreeNode<KEY, DATA>&);
    // performs an LL roll on the given node

    void RR(TreeNode<KEY, DATA>&);
    // performs an RR roll on the given node

    void LR(TreeNode<KEY, DATA>&);
    // performs an LR roll on the given node

    void RL(TreeNode<KEY, DATA>&);
    // performs an RL roll on the given node

    TreeNode<KEY, DATA>* FindPlace(const KEY& key,int x,int power) const;
    // returns  the node with the given key , if he is not found
    // returns the node that should be his parent,returns NULL if the tree is empty

    static int height(TreeNode<KEY, DATA>* v);
    //function to return the height of a node,if null return -1

    static void UpdateHeight(TreeNode<KEY, DATA>* v);
    //function that updates the height of a node

    static int BF(TreeNode<KEY, DATA>& v);
    //function to calculate the BF of a node

    TreeNode<KEY, DATA>* TreeRemove(TreeNode<KEY, DATA>* v);
    //removes the given node from the tree and returns his parent

    void SwapWithFollowing(TreeNode<KEY, DATA>& v);
    //swaps the given node with the smallest node that is bigger that it

    void DoRoll(TreeNode<KEY, DATA>* v);
    // does the needed roll on v according to it's BF

    void RemoveLeaf(TreeNode<KEY, DATA>& v);
    //removes a node that is a leaf

    void RemoveOneSonNode(TreeNode<KEY, DATA>& v);
    //removes a node that have only one son from the tree

    static TreeNode<KEY, DATA>* FindFollowingNode(TreeNode<KEY, DATA>* v);
    //return the smallest node that is bigger than v

    static TreeNode<KEY, DATA>* FindPreviousNode(TreeNode<KEY, DATA>* v);
    //return the biggest node that is smaller than v

    void CheckEmptyTree() const;
    //if the tree is empty throws TREE_EMPTY else doesnt do any thing

    void SwitchNodesForParent(TreeNode<KEY, DATA>* parent,
                              TreeNode<KEY, DATA>* son);
    // switches the places of the nodes parent and son
    // parent must be the parent of son

    void SwitchNodes(TreeNode<KEY, DATA>* highernode,
                     TreeNode<KEY, DATA>* lowernode);
    //switches the places of the nodes highernode and lowernode

    static void UpdateParentforSons(TreeNode<KEY, DATA>* node);
    // updates the parent pointer in the sones of the given node

    void SwitchSon(TreeNode<KEY, DATA>* v1, TreeNode<KEY, DATA>* v2);
    //lets v2 become the son of v1's parent instead of v1

    void InOrder(TreeNode<KEY, DATA>* v, KEY* arr, int* i);	//TODO
    //does inorder on the tree of v and returns the keys in array,array must be allocated TODO

    template<class Function>
    void BackOrderRec(TreeNode<KEY, DATA> *v, Function& func,
                      DATA* arr);
    // does the opposite of inorder on all the nodes using a given function class
    //basel functions
    template<class Function>
    void BackOrderRec(TreeNode<KEY, DATA> *v,Function& func);
    static void TreeDeleteAux(TreeNode<KEY, DATA>* head);
    // deletes the tree that starts with the given head
    // in case the head is null does nothing

    /**** Functions*****/

    void MakeComleteTree(TreeNode<KEY, DATA> *v, int h);

    void MakeAlmostComplete(TreeNode<KEY, DATA> *n, int h, int *leafs_to_del);

    void RankTheTree(TreeNode<KEY, DATA>* v);

    TreeNode<KEY, DATA> * findElementByIndex(TreeNode<KEY,DATA>* v, int key);

    int n(TreeNode<KEY,DATA>* v);

};


template<class T>
void SwapR(T& a, T& b) {
    T temp = b;
    b = a;
    a = temp;
}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::Remove(const KEY& key,int power) {
    TreeNode<KEY, DATA>* v = FindPlace(key,0,0);
    if (v == nullptr || (v->key) != key) {    //the key isnt in the tree
        throw KeyNotExist();
    }
    int temp = -1*power;
    FindPlace(v->key,-1,temp);
    TreeNode<KEY, DATA>* parent = TreeRemove(v); //removing
    this->NumOfNodes--;
    //now we do the rolling to keep the tree avl

    DoRoll(parent);
    return;
}

template<class KEY, class DATA>
TreeNode<KEY, DATA>* RankTree<KEY, DATA>::TreeRemove(TreeNode<KEY, DATA>* v) {
    TreeNode<KEY, DATA>* parent;
    if (!v) {
        return nullptr;
    }
    if (max&& (v->key) == (max->key)) {
        max = FindPreviousNode(max);
    }
    if (min&& (v->key) == (min->key)) {
        min = FindFollowingNode(min);
    }
    if (height(v) == 0) {
        parent = v->parent;
        RemoveLeaf(*v);
        //delete(v->data);
        delete v;
        if(parent) {
            parent->Rank = 1;
            parent->sum_power = parent->power;
            if (parent->right) {
                parent->Rank += parent->right->Rank;
                parent->sum_power += parent->right->sum_power;
            }
            if (parent->left) {
                parent->Rank += parent->left->Rank;
                parent->sum_power += parent->left->sum_power;
            }
        }
        return parent;
    }
    if (v->right == nullptr || v->left == nullptr) {
        parent = v->parent;
        RemoveOneSonNode(*v);
        //delete(v->data);
        delete v;
        if(parent) {
            parent->Rank = 1;
            parent->sum_power = parent->power;
            if (parent->right) {
                parent->Rank += parent->right->Rank;
                parent->sum_power += parent->right->sum_power;
            }
            if (parent->left) {
                parent->Rank += parent->left->Rank;
                parent->sum_power += parent->left->sum_power;
            }
        }
        return parent;
    }
    SwapWithFollowing(*v);
    return TreeRemove(v); //now v is a leaf or a one son node
}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::SwapWithFollowing(TreeNode<KEY, DATA>& v) {
    TreeNode<KEY, DATA>* following = FindFollowingNode(&v);
    SwitchNodes(&v, following); //following is definitely lower than v because v has 2 sons
}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::UpdateParentforSons(TreeNode<KEY, DATA>* parent) {
    if (parent == nullptr) {
        return;
    }
    parent->sum_power=parent->power;
    parent->Rank=1;
    if (parent->left) {
        parent->Rank+=parent->left->Rank;
        parent->sum_power+=parent->left->sum_power;
        parent->left->parent = parent;
    }
    if (parent->right) {
        parent->Rank+=parent->right->Rank;
        parent->sum_power+=parent->right->sum_power;
        parent->right->parent = parent;
    }
}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::SwitchNodesForParent(TreeNode<KEY, DATA>* parent,
                                              TreeNode<KEY, DATA>* son) {
    if (parent == nullptr || son == nullptr) {
        return;
    }

    SwapR(parent->height, son->height);
    if (parent->right == son) {
        SwapR(parent->left, son->left);
        parent->right = son->right;
        son->right = parent;
    } else {
        SwapR(parent->right, son->right);
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
void RankTree<KEY, DATA>::SwitchNodes(TreeNode<KEY, DATA>* highernode,
                                     TreeNode<KEY, DATA>* lowernode) {
    if (highernode == lowernode->parent) {
        SwitchNodesForParent(highernode, lowernode);
        return;
    }

    SwapR(highernode->height, lowernode->height);
//    SwapR(highernode->Rank,lowernode->Rank);
//    highernode->sum_power-=highernode->power;
//    SwapR(highernode->sum_power,lowernode->sum_power);
    SwapR(highernode->left, lowernode->left);
    SwapR(highernode->right, lowernode->right);
    SwitchSon(highernode, lowernode);
    // makes the parent of highernode point to lowernode
    SwitchSon(lowernode, highernode);
    // makes the parent of lowernode  point to highernode

    SwapR(lowernode->parent, highernode->parent);
    // makes sure to change the parent ptr in highernode and lowernode to their new parents
    UpdateParentforSons(highernode);
    UpdateParentforSons(lowernode);
    // updates the parent ptr of the sons of the two nodes
}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::SwitchSon(TreeNode<KEY, DATA>* v1,
                                   TreeNode<KEY, DATA>* v2) {
    if (v1->parent != nullptr) {
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
void RankTree<KEY, DATA>::RemoveLeaf(TreeNode<KEY, DATA>& v) {
    SwitchSon(&v, nullptr);
    // makes the parent of v point to NULL
    // if v is head then head=NULL
}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::RemoveOneSonNode(TreeNode<KEY, DATA>& v) {

    TreeNode<KEY, DATA>* son = v.right != nullptr ? v.right : v.left;
    SwitchSon(&v, son); //let son become the son of the parent of v
    if (son)
    son->parent = v.parent;
    UpdateHeight(v.parent);

}

template<class KEY, class DATA>
TreeNode<KEY, DATA>* RankTree<KEY, DATA>::FindFollowingNode(
        TreeNode<KEY, DATA>* v) {
    TreeNode<KEY, DATA>* w = v->right; //w is bigger than v
    if (w == nullptr) {
        return v->parent;
    }
    TreeNode<KEY, DATA>* following = w;
    while (w != nullptr) {
        following = w;
        w = w->left; //get the smallest w
    }
    return following;
}

template<class KEY, class DATA>
TreeNode<KEY, DATA>* RankTree<KEY, DATA>::FindPreviousNode(
        TreeNode<KEY, DATA>* v) {
    TreeNode<KEY, DATA>* w = v->left; //w is bigger than v
    if (w == nullptr) {
        return v->parent;
    }
    TreeNode<KEY, DATA>* prev = w;
    while (w != nullptr) {
        prev = w;
        w = w->right; //get the smallest w
    }
    return prev;
}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::DoRoll(TreeNode<KEY, DATA>* v) {
    while (v != nullptr) {
        int heightBefore = height(v);
        UpdateHeight(v);
        int bf = BF(*v);
        TreeNode<KEY, DATA>* parent = v->parent;
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
            v->Rank = 1;
            v->sum_power = v->power;
            if (v->right) {
                v->Rank += v->right->Rank;
                v->sum_power += v->right->sum_power;
            }
            if (v->left) {
                v->Rank += v->left->Rank;
                v->sum_power += v->left->sum_power;
            }
            if(parent) {
            parent->Rank = 1;
            parent->sum_power = parent->power;
            if (parent->right) {
                parent->Rank += parent->right->Rank;
                parent->sum_power += parent->right->sum_power;
            }
            if (parent->left) {
                parent->Rank += parent->left->Rank;
                parent->sum_power += parent->left->sum_power;
            }
        }
            return; //the height didnt change so the tree is still avl
        }
        v = parent;

    }
    return;
}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::RR(TreeNode<KEY, DATA>& v) {
    TreeNode<KEY, DATA>* rightSon = v.right;
    if ((head->key) == (v.key)){
        head = rightSon;
    }

    //change sons of v and his right son
    v.right = rightSon->left;
    if (rightSon->left != nullptr) {
        rightSon->left->parent = &v; //TODO check here
    }
    rightSon->left = &v;
    UpdateHeight(&v);
    //v.Rank=v.left->Rank+v.right->Rank+1;
    UpdateHeight(rightSon);
    //rightSon->Rank=rightSon->left->Rank+rightSon->right->Rank+1;
    //change the son of the parent of v to be rightSon
    SwitchSon(&v, rightSon);
    UpdateHeight(v.parent);
    //v.parent->Rank=v.parent->left->Rank+v.parent->right->Rank+1;
    //change parents of v and his right son
    rightSon->parent = v.parent;
    v.parent = rightSon;
    v.Rank=1;
   v.sum_power=v.power;
    if(v.right){
        v.Rank+=v.right->Rank;
        v.sum_power+=v.right->sum_power;
    }
    if(v.left){
        v.Rank+=v.left->Rank;
        v.sum_power+=v.left->sum_power;
    }
    rightSon->Rank=1;
    rightSon->sum_power=rightSon->power;
    if(rightSon->right){
        rightSon->Rank+=rightSon->right->Rank;
        rightSon->sum_power+=rightSon->right->sum_power;
    }
    if(rightSon->left){
        rightSon->Rank+=rightSon->left->Rank;
        rightSon->sum_power+=rightSon->left->sum_power;

    }
}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::LL(TreeNode<KEY, DATA>& node) {
    TreeNode<KEY, DATA>* leftson = node.left;
    if ((head->key) == (node.key)) {
        head = leftson;
    }

    //change the sons of the nodes
    node.left = leftson->right;
    if (leftson->right != nullptr) {
        leftson->right->parent = &node;
    }
    leftson->right = &node;

    UpdateHeight(&node);
  //  node.Rank=node.left->Rank+node.right->Rank+1;
    UpdateHeight(leftson);
    //leftson->Rank=leftson->left->Rank+leftson->right->Rank+1;
    // changing the parents
    SwitchSon(&node, leftson);
    UpdateHeight(node.parent);
    //node.parent->Rank=node.parent->left->Rank+node.parent->right->Rank+1;
    leftson->parent = node.parent;
    node.parent = leftson;
    node.Rank=1;
    node.sum_power=node.power;
    if(node.right){
        node.Rank+=node.right->Rank;
        node.sum_power+=node.right->sum_power;
    }
    if(node.left){
        node.Rank+=node.left->Rank;
        node.sum_power+=node.left->sum_power;
    }
    leftson->Rank=1;
    leftson->sum_power=leftson->power;
    if(leftson->right){
        leftson->Rank+=leftson->right->Rank;
        leftson->sum_power+=leftson->right->sum_power;
    }
    if(leftson->left){
        leftson->Rank+=leftson->left->Rank;
        leftson->sum_power+=leftson->left->sum_power;
    }



}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::RL(TreeNode<KEY, DATA>& v) {
    LL(*v.right);
    RR(v);
}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::LR(TreeNode<KEY, DATA>& node) {
    RR(*node.left);
    LL(node);
}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::UpdateHeight(TreeNode<KEY, DATA>* v) {
    if (v == nullptr) {
        return;
    }
    v->height = 1 + std::max(height(v->right), height(v->left));
}

template<class KEY, class DATA>
int RankTree<KEY, DATA>::height(TreeNode<KEY, DATA>* v) {
    if (v == nullptr) {
        return NULL_HEIGHT;
    }
    return v->height;
}

template<class KEY, class DATA>
int RankTree<KEY, DATA>::BF(TreeNode<KEY, DATA>& v) {
    return height(v.left) - height(v.right);
}

template<class KEY, class DATA>
template<class Function>
void RankTree<KEY, DATA>::BackOrder(Function &func, DATA* arr) {
    BackOrderRec(head, func, arr);
}

template<class KEY, class DATA>
template<class Function>
void RankTree<KEY, DATA>::BackOrder(Function& func) {
    BackOrderRec(head, func);
}


template<class KEY, class DATA>
template<class Function>
void RankTree<KEY, DATA>::BackOrderRec(TreeNode<KEY, DATA> *v, Function& func,
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
void RankTree<KEY, DATA>::BackOrderRec(TreeNode<KEY, DATA> *v, Function& func){
    if (!v) {
        return;
    }
    BackOrderRec(v->right, func);
    func(v->key,v->data);
    if(v&&v->key) {
        if ((v->key) > GetMaxKey()) {
            max = v;
        }
        if ((v->key) < GetMinKey()) {
            min = v;
        }
    }
    BackOrderRec(v->left, func);
}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::InOrder(KEY* arr, int* iterator) {
    if (arr == NULL || iterator==nullptr ) {
        return;
    }
    InOrder(head, arr, iterator);
}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::InOrder(TreeNode<KEY, DATA>* v, KEY* arr, int* i) {
    if (!v) {
        return;
    }
    InOrder(v->left, arr, i);
    arr[*i] = v->key;
    (*i)++;
    InOrder(v->right, arr, i);
}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::CheckEmptyTree() const {
   if (NumOfNodes == 0) {
        throw TreeEmpty();
    }
}

//basel functions

template<class KEY, class DATA>
RankTree<KEY, DATA>::~RankTree<KEY, DATA>() {
    TreeDeleteAux(head);
    return;
}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::TreeDeleteAux(TreeNode<KEY, DATA>* head) {
    if (head == nullptr) {
        return;
    }
    TreeDeleteAux(head->left);
    TreeDeleteAux(head->right);
    delete (head);
    return;
}

template<class KEY, class DATA>
DATA* RankTree<KEY, DATA>::Find(const KEY& key) {
    TreeNode<KEY, DATA>* node = FindPlace(key,0,0);
    if (node == nullptr || (node->key) != key) { // then the key is not in the tree
        return nullptr;
    }
    return &node->data;
}

template<class KEY, class DATA>
DATA* RankTree<KEY, DATA>::Add(const KEY& key, const DATA& data,int power) {
    TreeNode<KEY, DATA>* parent = FindPlace(key,0,0);
    if (parent != nullptr && (parent->key) == key) { // then the key is in the tree
        throw KeyAlreadyExist();
    }
    TreeNode<KEY, DATA>* newkey = new TreeNode<KEY, DATA>(key, data,power);
    if (parent == nullptr) {
        head = newkey;
        newkey->parent = nullptr;
        NumOfNodes++;
        max = newkey;
        min = newkey;
        return &newkey->data;
    }
    if ( (key) > (parent->key)) {
        parent->right = newkey;
    } else {
        parent->left = newkey;
    }
    newkey->parent = parent;
    NumOfNodes++;
    if (max && (newkey->key) > (max->key)) {
        max = newkey;
    }
    if (min && (newkey->key) < (min->key)) {
        min = newkey;
    }

   FindPlace(key,1,power);
    DoRoll(parent);	// checks the route of entering and makes all the changes to guarantee the tree is AVL
    return &newkey->data;
}

template<class KEY, class DATA>
TreeNode<KEY, DATA>* RankTree<KEY, DATA>::FindPlace(const KEY& key,int x,
                                                   int power) const {
    TreeNode<KEY, DATA>* current = head;
    TreeNode<KEY, DATA>* parent = nullptr;
    while (current != nullptr) {

        if (key == (current->key)) {
            return current;
        }
        parent = current;
        if ((key) > (current->key)) {
           current->sum_power+=power;
            current->Rank+=x;
            current = current->right;
        } else {
            current->sum_power+=power;
            current->Rank+=x;
            current = current->left;
        }
    }
    return parent;
}






template<class KEY, class DATA>
void RankTree<KEY,DATA>::GetAllPowerAux(int index, TreeNode<KEY, DATA>* node,int* sum) {
    if (index > node->Rank) {
        *sum += node->sum_power;
        return;
    }
    if (!node->left) {
        if (index == 1) {
            if(!node->right){
                *sum+=node->power;
                return;
            }
            (*sum) += node->right->sum_power + node->power;
            return;
        }
        if (index == 2) {
            if(node->right) {
                *sum += node->right->sum_power;
            }
            if(node->left) {
                *sum += node->left->sum_power;
            }
            return;
        }
    }
    if (node->left->Rank == index - 1) {
        if (!node->right) {
            *sum += node->power;
            return;
        }
        *sum+=node->right->sum_power+node->power;
        return;
    }
    if(node->left->Rank>index-1){
     if(!node->right){
      *sum+=node->power;
         GetAllPowerAux(index,node->left,sum);
         return;
     }
        *sum+=node->power+node->right->sum_power;
        GetAllPowerAux(index,node->left,sum);
        return;
    }

    if(node->left->Rank < index-1){
        GetAllPowerAux(index-(node->left->Rank)-1, node->right, sum);
        return;
    }
    return;
}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::MakeComleteTree(TreeNode<KEY, DATA> *v, int h) {
    if (h == 0) {
        return;
    }
    v->left = new TreeNode<KEY, DATA>;
    v->right = new TreeNode<KEY, DATA>;
    v->left->height = h - 1;
    v->right->height = h - 1;
    v->left->parent = v;
    v->right->parent = v;
    MakeComleteTree(v->left, h - 1);
    MakeComleteTree(v->right, h - 1);
}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::MakeAlmostComplete(TreeNode<KEY, DATA> *n, int h, int *leafs_to_del) {
    if (n == nullptr || *leafs_to_del == 0) {
        return;
    }
    MakeAlmostComplete(n->right, h - 1, leafs_to_del);
    if (h == 1) {
        delete n->right;
        n->right = nullptr;
        *leafs_to_del = *leafs_to_del - 1;
        if (*leafs_to_del > 0) {
            delete n->left;
            n->left = nullptr;
            *leafs_to_del = *leafs_to_del - 1;
        }
    }
    MakeAlmostComplete(n->left, h - 1, leafs_to_del);
}

template<class KEY, class DATA>
void RankTree<KEY, DATA>::RankTheTree(TreeNode<KEY, DATA> *v) {
    if (v == nullptr){
        return;
    }
    RankTheTree(v->left);
    RankTheTree(v->right);
    if (v->left != nullptr && v->right != nullptr){
        v->Rank = 1 + v->left->Rank + v->right->Rank;
    } else if (v->left != nullptr && v->right == nullptr){
        v->Rank = 1 + v->left->Rank;
    }else if (v->left == nullptr && v->right != nullptr){
        v->Rank = 1 + v->right->Rank;
    } else {
        v->Rank = 1;
    }
}

template<class KEY, class DATA>
TreeNode<KEY, DATA> * RankTree<KEY, DATA>::findElementByIndex(TreeNode<KEY, DATA> *v, int k) {
    k++;
    while(v != nullptr){
        if (n(v->left) == k-1){
            return v;
        } else if (n(v->left) > k-1){
            v = v->left;
            continue;
        } else {
            k = k - n(v->left) -1;
            v = v->right;
            continue;
        }
    }
    return nullptr;
}

template<class KEY, class DATA>
int RankTree<KEY, DATA>::n(TreeNode<KEY, DATA> *v) {
    if (!v){
        return 0;
    } else {
        return v->Rank;
    }
}


#endif //HW2_WET_RankTREE_H
