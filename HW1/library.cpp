#include"library.h"
#include"DS.h"

void *Init() {
    DS *Ds = new DS();
    return (void *) Ds;
}

StatusType AddCarType(void *Ds, int typeID, int numOfModels) {
    if (!Ds || numOfModels <= 0 || typeID <= 0) {
        return INVALID_INPUT;
    }
    try {
        ((DS *) Ds)->addCarType(typeID, numOfModels);
    } catch (Exception &e) {
        return FAILURE;
    } catch (...) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType RemoveCarType(void *Ds, int typeID) {
    if (!Ds || typeID <= 0) {
        return INVALID_INPUT;
    }
    try {
        ((DS *) Ds)->removeCarType(typeID);
    } catch (Exception &e) {
        return FAILURE;
    } catch (...) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType SellCar(void *Ds, int typeID, int modelID) {
    if (!Ds || typeID <= 0 || modelID < 0) {
        return INVALID_INPUT;
    }
    try {
        ((DS *) Ds)->sellCar(typeID, modelID);
    } catch (Exception &e) {
        return FAILURE;
    } catch (...) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType MakeComplaint(void *Ds, int typeID, int modelID, int t) {
    if (!Ds || typeID <= 0 || modelID < 0) {
        return INVALID_INPUT;
    }
    try {
        ((DS *) Ds)->makeComplaint(typeID, modelID, t);
    } catch (Exception &e) {
        return FAILURE;
    } catch (...) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;

}

StatusType GetBestSellerModelByType(void *Ds, int typeID, int *modelID) {
    if (!Ds || typeID < 0) {
        return INVALID_INPUT;
    }
    try {
        ((DS *) Ds)->getBestSellerModelByType(typeID, modelID);
    } catch (Exception &e) {
        return FAILURE;
    } catch (...) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetWorstModels(void *Ds, int numOfModels, int *types, int *models) {
    if (!Ds || numOfModels <= 0) {
        return INVALID_INPUT;
    }
    try {
        ((DS *) Ds)->getWorstModels(numOfModels, types, models);
    } catch (Exception &e) {
        return FAILURE;
    } catch (...) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

void Quit(void **Ds) {
    (*(DS **) Ds)->quit();
    (*(DS **) Ds) = nullptr;
}
