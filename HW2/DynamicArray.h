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

    DynamicArray(): count(0), size(10){
        array = new T[INITIAL_SIZE];
    }
    ~DynamicArray(){
        delete[] array;
    }

    // function add an element at the end of array
    void add(T& t) {
        if (count == size){
            growSize();
        }
        array[count] = t;
        count++;
    }
    void growSize(){
        T* temp = nullptr;
        if (count == size) {
            temp = new T[size * EXPAND_RATE];
            for (int i = 0; i < size; ++i) {
                temp[i] = array[i];
            }
        }
        delete []array;
        array = temp;
        size = size * EXPAND_RATE;
    }

    void shrinkSize(){
        T* temp = nullptr;
        if (count > 0){
            temp = new T[count];
            for (int i = 0; i <count ; ++i) {
                temp[i] = array[i];
            }
            size = count;
            delete []array;
            array = temp;
        }
    }

    // function add an element at given index
    void addAt(int index, const T& t){
        if (count == size){
            growSize();
        }
        // Shift all elements right from given index
        for (int i = count - 1; i >= index ; i--) {
            array[i +1] = array[i];
        }

        // Insert data at given index
        array[index] = t;
        count++;
    }

    // function remove last element or put
    // zero at last index
    void remove(){
        if (count > 0){
            array[count -1] = nullptr;
            count --;
        }
    }

    // function shift all element of right
    // side from given index in left
    void removeAt(int index){
        if (count > 0){
            for (int i = index; i < count -1 ; ++i) {
                // Shift all elements of right side
                // from given index in left
                array[i] = array[i+1];
            }
            array[count -1] = nullptr;
            count--;
        }
    }

    T operator[](int k){
        return array[k];
    }
};




#endif //HW2_DYNAMICARRAY_H
