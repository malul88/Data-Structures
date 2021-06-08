
#include "DynamicArray.h"

template<class T>
void DynamicArray<T>::add(const T &t) {
    if (count == size){
        growSize();
    }
    array[count] = t;
    count++;
}

template<class T>
void DynamicArray<T>::growSize() {
    T* temp = nullptr;
    if (count == size) {
        temp = new T[size * EXPAND_RATE];
        for (int i = 0; i < size; ++i) {
            temp[i] = array[i];
        }
    }
    delete array;
    array = temp;
    size = size * EXPAND_RATE;
}

template<class T>
void DynamicArray<T>::shrinkSize() {
    T* temp = nullptr;
    if (count > 0){
        temp = new T[count];
        for (int i = 0; i <count ; ++i) {
            temp[i] = array[i];
        }
        size = count;
        delete array;
        array = temp;
    }
}

template<class T>
void DynamicArray<T>::addAt(int index, const T &t) {
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

template<class T>
void DynamicArray<T>::remove() {
    if (count > 0){
        array[count -1] = nullptr;
        count --;
    }
}

template<class T>
void DynamicArray<T>::removeAt(int index) {
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

template<class T>
T DynamicArray<T>::operator[](int k) {
    return array[k];
}





