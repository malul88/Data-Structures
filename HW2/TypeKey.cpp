#include "TypeKey.h"



bool PriorityByType::operator>(PriorityByType &p) const {
    return typeID > p.typeID;
}

bool PriorityByType::operator<(PriorityByType &p) const {
    return typeID < p.typeID;
}

bool PriorityByType::operator==(PriorityByType &p) const {
    return typeID == p.typeID;
}

bool PriorityByType::operator!=(PriorityByType &p) const {
    return typeID != p.typeID;
}
