#include"library.h"
#include"DS.h"
void *Init() {
    DS *Ds = new DS();
    return (void*)Ds;
}
StatusType AddCarType(DS *Ds, int typeID, int numOfModels) {
    if (!Ds){
        return INVALID_INPUT;
    }
    (Ds)-> addCarType(typeID, numOfModels);
    return SUCCESS;
}
