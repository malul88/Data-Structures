#include"library2.h"
#include "Execption.h"
#include"CarDealershipManager.h"


void *Init() {
    CarDealershipManager *DS = new CarDealershipManager();
    return (void*)DS;
}
StatusType AddAgency(void *DS){
    if (!DS) {
        return INVALID_INPUT;
    }
    try {
        ((CarDealershipManager*)DS)->AddAgency();
    } catch (Exception &e) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType SellCar(void *DS, int agencyID, int typeID, int k){
    if (!DS || agencyID < 0 || k <= 0){
        return INVALID_INPUT;
    }
    try {
        ((CarDealershipManager*)DS)->SellCar(agencyID, typeID, k);
    } catch (Exception &e) {
        return FAILURE;
    } catch (...) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;

}
StatusType UniteAgencies(void *DS, int agencyID1, int agencyID2){
    if (!DS || agencyID1 < 0 || agencyID2 < 0){
        return INVALID_INPUT;
    }
    try {
        ((CarDealershipManager*)DS)->UniteAgencies(agencyID1, agencyID2);
    } catch (Exception &e) {
        return FAILURE;
    } catch (...) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType GetIthSoldType(void *DS, int agencyID, int i, int* res){
    if (!DS || agencyID < 0 || i < 0 || res == NULL){
        return INVALID_INPUT;
    }
    try {
        ((CarDealershipManager*)DS)->GetIthSoldType(agencyID,i,res);
    } catch (Exception &e) {
        return FAILURE;
    } catch (...) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}
void Quit(void** DS){
    (*(CarDealershipManager **) DS)->Quit();
    delete ((CarDealershipManager *) *DS);
    *DS = nullptr;
}
