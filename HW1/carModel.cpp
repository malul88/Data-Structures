
#include "carModel.h"

bool carModel::operator<(const carModel &carModel) const {
    return modelID < carModel.modelID;
}

bool carModel::operator>(const carModel &carModel) const {
    return modelID > carModel.modelID;
}

bool carModel::operator==(const carModel &carModel) const {
    return modelID == carModel.modelID;
}

bool carModel::operator!=(const carModel &carModel) const {
    return modelID != carModel.modelID;
}

void carModel::complainModel(int t) {
    grade -= (100/t);
    complains += 1;
}

