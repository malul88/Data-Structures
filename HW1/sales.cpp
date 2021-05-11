//
// Created by Michael Malul on 11/05/2021.
//

#include "sales.h"

bool PriorityBySale::operator>(PriorityBySale p) const {
    if (num_of_sales > p.num_of_sales){
        return true;
    } else if (num_of_sales < p.num_of_sales){
        return false;
    } else {
        if (typeID < p.typeID){
            return true;
        } else if (typeID > p.typeID){
            return false;
        } else {
            return modelID < p.modelID;
        }
    }
}
bool PriorityBySale::operator<(PriorityBySale p) const {
    if (num_of_sales < p.num_of_sales){
        return true;
    } else if (num_of_sales > p.num_of_sales){
        return false;
    } else {
        if (typeID > p.typeID){
            return true;
        } else if (typeID < p.typeID){
            return false;
        } else {
            return modelID > p.modelID;
        }
    }
}

bool PriorityBySale::operator==(PriorityBySale p) const {
    return num_of_sales == p.num_of_sales && typeID == p.typeID && modelID == p.modelID;
}

bool PriorityBySale::operator!=(PriorityBySale p) const {
    return !(*this == p);
}
