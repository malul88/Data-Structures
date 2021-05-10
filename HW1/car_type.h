
#ifndef HW1_CAR_TYPE_H
#define HW1_CAR_TYPE_H


class carType {
public:
    int typeID;
    int num_of_models;
    void** models;
    void* best_seller;
    carType(): models(nullptr), best_seller(nullptr) {};
    carType(int typeID, int num_of_models) : typeID(typeID), num_of_models(num_of_models){
        void** res = new void* [num_of_models]; //todo put car models
        this->models = res;
    }
    ~carType(){
        delete []this->models;
        delete this;
    }

    bool operator<(const carType& cartype) const;
    bool operator==(const carType& cartype) const;
    bool operator!=(const carType& cartype) const;




};


#endif //HW1_CAR_TYPE_H
