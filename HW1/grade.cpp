//
// Created by Michael Malul on 11/05/2021.
//

#include "grade.h"

bool PriorityByGrade::operator<(PriorityByGrade p) const {
    if (grade < p.grade) {
        return true;
    } else if (grade > p.grade) {
        return false;
    } else {
        if (typeID < p.typeID) {
            return true;
        } else if (typeID > p.typeID) {
            return false;
        } else
            return modelID < p.modelID;
    }
}

bool PriorityByGrade::operator>(PriorityByGrade p) const {
    if (grade > p.grade) {
        return true;
    } else if (grade < p.grade) {
        return false;
    } else {
        if (typeID > p.typeID) {
            return true;
        } else if (typeID < p.typeID) {
            return false;
        } else
            return modelID > p.modelID;
    }
}

bool PriorityByGrade::operator==(PriorityByGrade p) const {
    return grade == p.grade && typeID == p.typeID && modelID == p.modelID;
}

bool PriorityByGrade::operator!=(PriorityByGrade p) const {
    return !(*this == p);
}
