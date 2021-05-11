
#ifndef HW1_CAR_TYPE_H
#define HW1_CAR_TYPE_H

#include "carModel.h"


class carType {
public:
    int typeID;
    int num_of_models;
    carModel **models;
    carModel *best_seller;


    carType() : models(nullptr), best_seller(nullptr) {};

    carType(int typeID, int num_of_models) : typeID(typeID), num_of_models(num_of_models),
                                             best_seller(nullptr) {
        carModel** array_of_models = new carModel *[num_of_models];
        this->models = array_of_models;
    }

    ~carType() {
        delete[]this->models;
        delete this;
    }

    bool operator<(const carType &cartype) const;

    bool operator==(const carType &cartype) const;

    bool operator!=(const carType &cartype) const;


};


#endif //HW1_CAR_TYPE_H
