
#include "SalesKey.h"

bool PriorityBySale::operator>(PriorityBySale p) const {
    if (num_of_sales > p.num_of_sales){
        return true;
    } else if (num_of_sales == p.num_of_sales){
        if (typeID > p.typeID){
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool PriorityBySale::operator<(PriorityBySale p) const {
    if (num_of_sales < p.num_of_sales){
        return true;
    } else if (num_of_sales == p.num_of_sales){
        if (typeID < p.typeID){
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool PriorityBySale::operator==(PriorityBySale p) const {
    return (num_of_sales == p.num_of_sales) && (typeID == p.typeID);
}

bool PriorityBySale::operator!=(PriorityBySale p) const {
    return (num_of_sales != p.num_of_sales) || (typeID != p.typeID);
}
