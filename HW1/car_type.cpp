
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
