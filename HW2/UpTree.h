
#ifndef HW2_UPTREE_H
#define HW2_UPTREE_H



template<class KEY, class DATA>
class UpTreeNode {
public:
    KEY key;
    DATA data;
    UpTreeNode* parent;
    UpTreeNode() :
            key(), data(), parent(nullptr){}

    UpTreeNode(KEY key, DATA data) :
            key(key), data(data),parent(nullptr) {}

    bool operator<(UpTreeNode &node) const {
        return key < (node.key);
    }

    bool operator>(UpTreeNode &node) const {
        return key > (node.key);
    }
    bool operator==(UpTreeNode &node) const {
        return key == (node.key);
    }

    bool operator!=(UpTreeNode &node) const {
        return key != (node.key);
    }
};


#endif //HW2_UPTREE_H
