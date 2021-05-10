//
// Created by Michael Malul on 03/05/2021.
//

#include "car_type.h"


bool carType::operator<(const carType &cartype) const {
    return typeID < cartype.typeID;
}

bool carType::operator==(const carType &cartype) const {
    return typeID == cartype.typeID;
}

bool carType::operator!=(const carType &cartype) const {
    return typeID != cartype.typeID;
}
