//
// Created by Michael Malul on 11/05/2021.
//

#ifndef HW1_SALES_H
#define HW1_SALES_H


class PriorityBySale {
public:
    int num_of_sales, typeID, modelID;
    bool operator>(PriorityBySale p) const;
    bool operator<(PriorityBySale p) const;
    bool operator==(PriorityBySale p) const;
    bool operator!=(PriorityBySale p) const;
};


#endif //HW1_SALES_H
