#ifndef MEVNE_HW1_TREE_H
#define MEVNE_HW1_TREE_H

#include <stdlib.h>
#include <stdexcept>
#include "Execption.h"

#define LROLL 2
#define RROLL -2
#define NULL_HEIGHT -1

template<class KEY, class DATA>
class Node {
public:
    KEY keyNode;
    DATA dataNode;
    int heightNode;
    Node *leftSon;
    Node *rightSon;
    Node *parentNode;
    int rankNode;
//    int sum_power;

    Node() :
            keyNode(), dataNode(), heightNode(0), leftSon(NULL), rightSon(NULL),
            parentNode(NULL), rankNode(0){ // sum_power(0)
    }

    Node(KEY key, DATA data) :
            keyNode(key), dataNode(data), heightNode(0), leftSon(NULL), rightSon(NULL),
            parentNode(
                    NULL) {
    }

    bool operator<(Node &node) const {
        return keyNode < (node.keyNode);
    }

    bool operator>(Node &node) const {
        return keyNode > (node.keyNode);
    }

    bool operator==(Node &node) const {
        return keyNode == (node.keyNode);
    }

    bool operator!=(Node &node) const {
        return keyNode != (node.keyNode);
    }
};

template<class KEY, class DATA>
class AVLTree {
public:
    Node<KEY, DATA>* AVLhead;
    int AVLnodesCounter;
    Node<KEY, DATA>* AVLhighestNode;
    Node<KEY, DATA>* AVLlowestNode;

    AVLTree() :
            AVLhead(NULL), AVLnodesCounter(0), AVLhighestNode(NULL), AVLlowestNode(NULL) {
    };

    ~AVLTree();

//    int AVLgetSize() const {
//        return this->AVLnodesCounter;
//    }

    DATA* AVLfindData(const KEY &key);
    // returns the node with the given keyNode , if not found NULL

    DATA* AVLaddNode(const KEY &key, const DATA &data);
    // adds a node with the given keyNode and dataNode to the tree
    // if the keyNode is already in ,throws KEY_ALREADY_EXIST

    void AVLremoveNodeByKey(const KEY &key);
    // removes the node with the given keyNode if found
    // else it throws KEY_NOT_EXIST

    void AVLinOrder(KEY *array, int *iterator);

    // does inorder on the tree and returns the results in arr,arr must be already allocated
    // and must have enough space ,iterator marks the index from which the filling of the
    // arr starts , and in the end will hold the index of the last

//    template<class Function>
//    void BackOrder(Function &func, DATA *arr);
//    // does the opposite od in order on all nodes using a given function class
//
//    template<class Function>
//    void BackOrder(Function &func);

    KEY& AVLgetMaxKey() const {
        this->AVLisEmpty();
        return AVLhighestNode->keyNode;
    }
    //returns the maximum keyNode , if the tree is empty
    // throws TREE_EMPTY

//    KEY& GetMinKey() const {
//        this->AVLisEmpty();
//        return AVLlowestNode->keyNode;
//    }
    //returns the minimum keyNode , if the tree is empty
    // throws TREE_EMPTY

//    DATA &GetMaxData() const {
//        this->AVLisEmpty();
//        return AVLhighestNode->dataNode;
//    }
    //returns the maximum's keyNode dataNode , if the tree is empty
    // throws TREE_EMPTY

//    DATA &GetMinData() const {
//        this->AVLisEmpty();
//        return AVLlowestNode->dataNode;
//    }
    //returns the minimum's keyNode dataNode , if the tree is empty
    // throws TREE_EMPTY

    Node<KEY, DATA>* AVLgetHead() {
        return AVLhead;
    }
    // returns the AVLhead of the tree

    /**** Functions*****/
    void LLroling(Node<KEY, DATA> &);
    // performs an LLroling roll on the given node

    void RRroling(Node<KEY, DATA> &);
    // performs an RRroling roll on the given node

    void LRrolling(Node<KEY, DATA> &);
    // performs an LRrolling roll on the given node

    void RLrolling(Node<KEY, DATA> &);
    // performs an RLrolling roll on the given node

    Node<KEY, DATA>* AVLfindNode(const KEY &key, int y) const;
    // returns  the node with the given keyNode , if he is not found
    // returns the node that should be his parentNode,returns NULL if the tree is empty

    static int nodeGetHeight(Node<KEY, DATA> *currentNode);
    //function to return the heightNode of a node,if NULL return -1

    static void nodeUpdateHeight(Node<KEY, DATA> *currentNode);
    //function that updates the heightNode of a node

    static int AVLbalanceFactorOfNode(Node<KEY, DATA> &currentNode);
    //function to calculate the AVLbalanceFactorOfNode of a node

    Node<KEY, DATA>* AVLremoveNode(Node<KEY, DATA> *currentNode);
    //removes the given node from the tree and returns his parentNode

    void AVLswapWithNext(Node<KEY, DATA> &v);
    //swaps the given node with the smallest node that is bigger that it

    void AVLrollFunction(Node<KEY, DATA> *currentNode);
    // does the needed roll on current Node according to it's AVLbalanceFactorOfNode

    void AVLremoveLeaf(Node<KEY, DATA> &currentNode);
    //removes a node that is a leaf

    void AVLremoveOneSonNode(Node<KEY, DATA> &currentNode);
    //removes a node that have only one son from the tree

    static Node<KEY, DATA>* AVLfindNextNode(Node<KEY, DATA> *currentNode);
    //return the smallest node that is bigger than current Node.

    static Node<KEY, DATA>* AVLfindPreviousNode(Node<KEY, DATA> *currentNode);
    //return the biggest node that is smaller than current Node.

    void AVLisEmpty() const;
    //if the tree is empty throws TREE_EMPTY else doesnt do any thing

    void AVLswitchNodesForParent(Node<KEY, DATA> *parent,
                                 Node<KEY, DATA> *son);
    // switches the places of the nodes parentNode and son
    // parentNode must be the parentNode of son

    void AVLswitchNodes(Node<KEY, DATA> *highernode,
                        Node<KEY, DATA> *lowernode);
    //switches the places of the nodes highernode and lowernode

    static void AVLupdateParentforSons(Node<KEY, DATA> *node);
    // updates the parentNode pointer in the sons of the given node

    void AVLswitchSon(Node<KEY, DATA> *n1, Node<KEY, DATA> *n2);
    //lets n2 become the son of n1's parentNode instead of n1

    void AVLinOrder(Node<KEY, DATA> *currentNode, KEY *array, int *i);
    //does inorder on the tree of current Node and returns the keys in array,array must be allocated TODO

    void AVLremove(Node<KEY, DATA> *head);

    void AVLdoComplete(Node<KEY, DATA> *n, int h);

    void AVLdoAlmostComplete(Node<KEY, DATA> *n, int h, int *leafs_to_del);

    /////////////////////////////////////////////////////////////////////////////////////////////

//    template<class Function>
//    void BackOrderRec(Node<KEY, DATA> *v, Function &func,
//                      DATA *arr); //להוריד
//    // does the opposite of inorder on all the nodes using a given function class
//    //basel functions
//
//    template<class Function>
//    void BackOrderRec(Node<KEY, DATA> *v, Function &func); //להוריד

    ///////////////////////////////////////////////////////////////////////////////////////////

    static void AVLdeleteByHead(Node<KEY, DATA> *head);
    // deletes the tree that starts with the given AVLhead
    // in case the AVLhead is NULL does nothing

    /**** Functions*****/

};

template<class T>
void Swap(T &a, T &b) {
    T temp = b;
    b = a;
    a = temp;
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::AVLremoveNodeByKey(const KEY &key) {
    Node<KEY, DATA> *v = AVLfindNode(key, -1);
    if (v == NULL || (v->keyNode) != key) {    // The keyNode isn't in the tree
        throw KeyNotExist();
    }
    Node<KEY, DATA> *parent = AVLremoveNode(v); // Removing
    this->AVLnodesCounter--;
    // Now we do the Rolling to keep the tree avl
    AVLrollFunction(parent);
    return;
}

template<class KEY, class DATA>
Node<KEY, DATA>* AVLTree<KEY, DATA>::AVLremoveNode(Node<KEY, DATA> *currentNode) {
    Node<KEY, DATA> *parent;
    if (!currentNode) {
        return NULL;
    }
    if ((currentNode->keyNode) == (AVLhighestNode->keyNode)) {
        AVLhighestNode = AVLfindPreviousNode(AVLhighestNode);
    }
    if ((currentNode->keyNode) == (AVLlowestNode->keyNode)) {
        AVLlowestNode = AVLfindNextNode(AVLlowestNode);
    }
    if (nodeGetHeight(currentNode) == 0) {
        parent = currentNode->parentNode;
        AVLremoveLeaf(*currentNode);
        delete currentNode;

        return parent;
    }
    if (currentNode->rightSon == NULL || currentNode->leftSon == NULL) {
        parent = currentNode->parentNode;
        AVLremoveOneSonNode(*currentNode);
        delete currentNode;
        return parent;
    }
    AVLswapWithNext(*currentNode);
    return AVLremoveNode(currentNode); //now currentNode is a leaf or a one son node
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::AVLswapWithNext(Node<KEY, DATA> &v) {
    Node<KEY, DATA> *following = AVLfindNextNode(&v);
    AVLswitchNodes(&v,
                   following); //following is definitely lower than v because v has 2 sons
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::AVLupdateParentforSons(Node<KEY, DATA> *parent) {
    if (parent == NULL) {
        return;
    }
    if (parent->leftSon) {
        parent->leftSon->parentNode = parent;
    }
    if (parent->rightSon) {
        parent->rightSon->parentNode = parent;
    }
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::AVLswitchNodesForParent(Node<KEY, DATA> *parent,
                                                 Node<KEY, DATA> *son) {
    if (parent == NULL || son == NULL) {
        return;
    }

    Swap(parent->heightNode, son->heightNode);
    if (parent->rightSon == son) {
        Swap(parent->leftSon, son->leftSon);
        parent->rightSon = son->rightSon;
        son->rightSon = parent;
    } else {
        Swap(parent->rightSon, son->rightSon);
        parent->leftSon = son->leftSon;
        son->leftSon = parent;
    }
    AVLswitchSon(parent, son);
    // makes the parentNode of the parentNode point to the son
    son->parentNode = parent->parentNode;
    AVLupdateParentforSons(parent);
    AVLupdateParentforSons(son);
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::AVLswitchNodes(Node<KEY, DATA> *highernode,
                                        Node<KEY, DATA> *lowernode) {
    if (highernode == lowernode->parentNode) {
        AVLswitchNodesForParent(highernode, lowernode);
        return;
    }

    Swap(highernode->heightNode, lowernode->heightNode);
    Swap(highernode->leftSon, lowernode->leftSon);
    Swap(highernode->rightSon, lowernode->rightSon);
    AVLswitchSon(highernode, lowernode);
    // makes the parentNode of highernode point to lowernode
    AVLswitchSon(lowernode, highernode);
    // makes the parentNode of lowernode  point to highernode

    Swap(lowernode->parentNode, highernode->parentNode);
    // makes sure to change the parentNode ptr in highernode and lowernode to their new parents
    AVLupdateParentforSons(highernode);
    AVLupdateParentforSons(lowernode);
    // updates the parentNode ptr of the sons of the two nodes
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::AVLswitchSon(Node<KEY, DATA> *n1,
                                      Node<KEY, DATA> *n2) {
    if (n1->parentNode != NULL) {
        if (n1->parentNode->rightSon == n1) {
            n1->parentNode->rightSon = n2;
        } else {
            n1->parentNode->leftSon = n2;
        }
    } else {
        AVLhead = n2;
    }
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::AVLremoveLeaf(Node<KEY, DATA> &currentNode) {
    AVLswitchSon(&currentNode, NULL);
    // makes the parentNode of currentNode point to NULL
    // if currentNode is AVLhead then AVLhead=NULL
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::AVLremoveOneSonNode(Node<KEY, DATA> &currentNode) {

    Node<KEY, DATA> *son = currentNode.rightSon != NULL ? currentNode.rightSon : currentNode.leftSon;
    AVLswitchSon(&currentNode, son); //let son become the son of the parentNode of currentNode
    if (son) {
        son->parentNode = currentNode.parentNode;
        nodeUpdateHeight(currentNode.parentNode);
    }

}

template<class KEY, class DATA>
Node<KEY, DATA>* AVLTree<KEY, DATA>::AVLfindNextNode(
        Node<KEY, DATA> *currentNode) {
    Node<KEY, DATA> *w = currentNode->rightSon; //w is bigger than currentNode
    if (w == NULL) {
        return currentNode->parentNode;
    }
    Node<KEY, DATA> *following = w;
    while (w != NULL) {
        following = w;
        w = w->leftSon; //get the smallest w
    }
    return following;
}

template<class KEY, class DATA>
Node<KEY, DATA>* AVLTree<KEY, DATA>::AVLfindPreviousNode(
        Node<KEY, DATA> *currentNode) {
    Node<KEY, DATA> *w = currentNode->leftSon; //w is bigger than currentNode
    if (w == NULL) {
        return currentNode->parentNode;
    }
    Node<KEY, DATA> *prev = w;
    while (w != NULL) {
        prev = w;
        w = w->rightSon; //get the smallest w
    }
    return prev;
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::AVLrollFunction(Node<KEY, DATA> *currentNode) {
    while (currentNode != NULL) {
        int heightBefore = nodeGetHeight(currentNode);
        nodeUpdateHeight(currentNode);
        int bf = AVLbalanceFactorOfNode(*currentNode);
        Node<KEY, DATA> *parent = currentNode->parentNode;
        if (bf == LROLL) {
            if (AVLbalanceFactorOfNode(*currentNode->leftSon) >= 0) {
                LLroling(*currentNode);
            } else {
                LRrolling(*currentNode);
            }
        }
        if (bf == RROLL) {
            if (AVLbalanceFactorOfNode(*currentNode->rightSon) <= 0) {
                RRroling(*currentNode);
            } else {
                RLrolling(*currentNode);
            }
        }
        if (nodeGetHeight(currentNode) == heightBefore) {
            return; //the heightNode didnt change so the tree is still avl
        }
        currentNode = parent;
    }
    return;
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::RRroling(Node<KEY, DATA> &v) {
    Node<KEY, DATA> *rightSon = v.rightSon;
    if ((AVLhead->keyNode) == (v.keyNode)) {
        AVLhead = rightSon;
    }

    //change sons of v and his rightSon son
    v.rightSon = rightSon->leftSon;
    if (rightSon->leftSon != NULL) {
        rightSon->leftSon->parentNode = &v; //TODO check here
    }
    rightSon->leftSon = &v;
    nodeUpdateHeight(&v);
    nodeUpdateHeight(rightSon);

    //change the son of the parentNode of v to be rightSon
    AVLswitchSon(&v, rightSon);
    nodeUpdateHeight(v.parentNode);
    //change parents of v and his rightSon son
    rightSon->parentNode = v.parentNode;
    v.parentNode = rightSon;
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::LLroling(Node<KEY, DATA> &node) {
    Node<KEY, DATA> *leftson = node.leftSon;
    if ((AVLhead->keyNode) == (node.keyNode)) {
        AVLhead = leftson;
    }

    //change the sons of the nodes
    node.leftSon = leftson->rightSon;
    if (leftson->rightSon != NULL) {
        leftson->rightSon->parentNode = &node;
    }
    leftson->rightSon = &node;

    nodeUpdateHeight(&node);
    nodeUpdateHeight(leftson);

    // changing the parents
    AVLswitchSon(&node, leftson);
    nodeUpdateHeight(node.parentNode);

    leftson->parentNode = node.parentNode;
    node.parentNode = leftson;

}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::RLrolling(Node<KEY, DATA> &v) {
    LLroling(*v.rightSon);
    RRroling(v);
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::LRrolling(Node<KEY, DATA> &node) {
    RRroling(*node.leftSon);
    LLroling(node);
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::nodeUpdateHeight(Node<KEY, DATA> *currentNode) {
    if (currentNode == NULL) {
        return;
    }
    currentNode->heightNode = 1 + std::max(nodeGetHeight(currentNode->rightSon), nodeGetHeight(currentNode->leftSon));
}

template<class KEY, class DATA>
int AVLTree<KEY, DATA>::nodeGetHeight(Node<KEY, DATA> *currentNode) {
    if (currentNode == NULL) {
        return NULL_HEIGHT;
    }
    return currentNode->heightNode;
}

template<class KEY, class DATA>
int AVLTree<KEY, DATA>::AVLbalanceFactorOfNode(Node<KEY, DATA> &currentNode) {
    return nodeGetHeight(currentNode.leftSon) - nodeGetHeight(currentNode.rightSon);
}

//template<class KEY, class DATA>
//template<class Function>
//void AVLTree<KEY, DATA>::BackOrder(Function &func, DATA *arr) {
//    BackOrderRec(AVLhead, func, arr);
//}
//
//template<class KEY, class DATA>
//template<class Function>
//void AVLTree<KEY, DATA>::BackOrder(Function &func) {
//    BackOrderRec(AVLhead, func);
//}
//
//
//template<class KEY, class DATA>
//template<class Function>
//void AVLTree<KEY, DATA>::BackOrderRec(Node<KEY, DATA> *v, Function &func,
//                                      DATA *arr) {
//    if (!v) {
//        return;
//    }
//    BackOrderRec(v->rightSon, func, arr);
//    func(v->dataNode, arr);
//    BackOrderRec(v->leftSon, func, arr);
//}
//
//template<class KEY, class DATA>
//template<class Function>
//void AVLTree<KEY, DATA>::BackOrderRec(Node<KEY, DATA> *v, Function &func) {
//    if (!v) {
//        return;
//    }
//    BackOrderRec(v->rightSon, func);
//    if (v->keyNode != NULL) {
//        func(v->keyNode, v->dataNode);
//    }
//    BackOrderRec(v->leftSon, func);
//}
//

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::AVLinOrder(KEY *array, int *iterator) {
    if (array == NULL || iterator == NULL) {
        return;
    }
    AVLinOrder(AVLhead, array, iterator);
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::AVLinOrder(Node<KEY, DATA> *currentNode, KEY *array,
                                    int *i) {
    if (!currentNode) {
        return;
    }
    AVLinOrder(currentNode->leftSon, array, i);
    array[*i] = currentNode->keyNode;
    (*i)++;
    AVLinOrder(currentNode->rightSon, array, i);
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::AVLisEmpty() const {
    if (AVLnodesCounter == 0) {
        throw TreeEmpty();
    }
}

//basel functions

template<class KEY, class DATA>
AVLTree<KEY, DATA>::~AVLTree<KEY, DATA>() {
    AVLdeleteByHead(AVLhead);
    return;
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::AVLdeleteByHead(Node<KEY, DATA> *head) {
    if (head == NULL) {
        return;
    }
    AVLdeleteByHead(head->leftSon);
    AVLdeleteByHead(head->rightSon);
    delete (head);
    return;
}

template<class KEY, class DATA>
DATA *AVLTree<KEY, DATA>::AVLfindData(const KEY &key) {
    Node<KEY, DATA> *node = AVLfindNode(key, 0);
    if (node == NULL || (node->keyNode) != key) { // then the keyNode is not in the tree
        return NULL;
    }
    return &node->dataNode;
}

template<class KEY, class DATA>
DATA *AVLTree<KEY, DATA>::AVLaddNode(const KEY &key, const DATA &data) {
    Node<KEY, DATA> *parent = AVLfindNode(key, 1);
    if (parent != NULL && (parent->keyNode) == key) { // then the keyNode is in the tree
        throw KeyAlreadyExist();
    }
    Node<KEY, DATA> *newkey = new Node<KEY, DATA>(key, data);
    if (parent == NULL) {
        AVLhead = newkey;
        newkey->parentNode = NULL;
        AVLnodesCounter++;
        AVLhighestNode = newkey;
        AVLlowestNode = newkey;
        return &newkey->dataNode;
    }
    if (key > (parent->keyNode)) {
        parent->rightSon = newkey;
    } else {
        parent->leftSon = newkey;
    }
    newkey->parentNode = parent;
    AVLnodesCounter++;
    if ((newkey->keyNode) > (AVLhighestNode->keyNode)) {
        AVLhighestNode = newkey;
    }
    if ((newkey->keyNode) < (AVLlowestNode->keyNode)) {
        AVLlowestNode = newkey;
    }
    AVLrollFunction(parent);    // checks the route of entering and makes all the changes to guarantee the tree is AVL
    return &newkey->dataNode;
}

template<class KEY, class DATA>
Node<KEY, DATA> *AVLTree<KEY, DATA>::AVLfindNode(const KEY &key, int y) const {
    Node<KEY, DATA> *current = AVLhead;
    Node<KEY, DATA> *parent = NULL;
    while (current != NULL) {

        if (key == (current->keyNode)) {
            return current;
        }
        parent = current;
        if (key > (current->keyNode)) {
            current->rankNode += y;
            current = current->rightSon;
        } else {
            current->rankNode += y;
            current = current->leftSon;
        }
    }
    return parent;
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::AVLremove(Node<KEY, DATA> *v) {
    if (v == nullptr) {
        return;
    }
    AVLremove(v->leftSon);
    AVLremove(v->rightSon);
    delete v;
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::AVLdoComplete(Node<KEY, DATA> *n, int h) {
    if (h == 0) {
        return;
    }
    n->leftSon = new Node<KEY, DATA>;
    n->rightSon = new Node<KEY, DATA>;
    n->leftSon->heightNode = h - 1;
    n->rightSon->heightNode = h - 1;
    n->leftSon->parentNode = n;
    n->rightSon->parentNode = n;
    AVLdoComplete(n->leftSon, h - 1);
    AVLdoComplete(n->rightSon, h - 1);
}

template<class KEY, class DATA>
void AVLTree<KEY, DATA>::AVLdoAlmostComplete(Node<KEY, DATA> *n, int h, int *leafs_to_del) {
    if (n == nullptr || *leafs_to_del == 0) {
        return;
    }
    AVLdoAlmostComplete(n->rightSon, h - 1, leafs_to_del);
    if (h == 1) {
        delete n->rightSon;
        n->rightSon = nullptr;
        *leafs_to_del = *leafs_to_del - 1;
        if (*leafs_to_del > 0) {
            delete n->leftSon;
            n->leftSon = nullptr;
            *leafs_to_del = *leafs_to_del - 1;
        }
    }
    AVLdoAlmostComplete(n->leftSon, h - 1, leafs_to_del);

}


//void PathSumPower(int k, int* sum, RankNode* root) {
//    if (k > root->sub_size) {
//        (*sum) += root->sumPower;
//    }
//    GetPower get;
//    if (!root->leftSon) {
//        if (k == 1) {
//            (*sum) += root->rightSon->sumPower + get(root->dataNode);
//            return;
//        }
//        if (k == 2) {
//            (*sum) += root->rightSon->sumPower;
//        }
//    }
//    if (root->leftSon->sub_size == k - 1) {
//        if (!root->rightSon) {
//            (*sum) += get(root->dataNode);
//            return;
//        }
//        (*sum) += root->rightSon->sumPower + get(root->dataNode);
//        return;
//    }
//    if (root->leftSon->sub_size > k - 1) {
//        if (!root->rightSon) {
//            (*sum) += get(root->dataNode);
//            PathSumPower(k, sum, root->leftSon);
//            return;
//        }
//        (*sum) += root->rightSon->sumPower + get(root->dataNode);
//        PathSumPower(k, sum, root->leftSon);
//        return;
//    }
//    if (root->leftSon->sub_size < k - 1) {
//        PathSumPower(k - (root->leftSon->sub_size) - 1, sum, root->leftSon);
//        return;
//    }
//    return;
//}

#endif //MEVNE_HW1_TREE_H
