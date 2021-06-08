#ifndef HW2_DYNAMICARRAY_H
#define HW2_DYNAMICARRAY_H

template<class T>
class DynamicArray {
public:
    // create three variable array[] is a array,
    // count will deal with no of element add by you and
    // size will with size of array[]
    T* array;
    int count, size;
    const int INITIAL_SIZE = 10;
    const int EXPAND_RATE = 2;

    DynamicArray(): count(0), size(INITIAL_SIZE){
        array = new T*[INITIAL_SIZE];
    }
    ~DynamicArray(){
        delete array;
    }

    // function add an element at the end of array
    void add(const T& t);

    void growSize();

    void shrinkSize();

    // function add an element at given index
    void addAt(int index, const T& t);

    // function remove last element or put
    // zero at last index
    void remove();

    // function shift all element of right
    // side from given index in left
    void removeAt(int index);

    T operator[](int k);
};




#endif //HW2_DYNAMICARRAY_H
