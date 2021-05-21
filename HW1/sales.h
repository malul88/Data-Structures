//
// Created by Michael Malul on 11/05/2021.
//

#ifndef HW1_SALES_H
#define HW1_SALES_H

class PriorityBySale {
public:
    int num_of_sales, typeID, modelID;

    PriorityBySale(){};
    PriorityBySale(int num_of_sales, int typeID, int modelID): num_of_sales(num_of_sales),
            typeID(typeID), modelID(modelID){};
    bool operator>(PriorityBySale p) const;
    bool operator<(PriorityBySale p) const;
    bool operator==(PriorityBySale p) const;
    bool operator!=(PriorityBySale p) const;
};


#endif //HW1_SALES_H
