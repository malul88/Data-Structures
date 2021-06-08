#ifndef HW2_SALESKEY_H
#define HW2_SALESKEY_H

class PriorityBySale {
public:
    int num_of_sales, typeID;

    PriorityBySale(){};
    PriorityBySale(int num_of_sales, int typeID): num_of_sales(num_of_sales),
                                                               typeID(typeID){};
    bool operator>(PriorityBySale p) const;
    bool operator<(PriorityBySale p) const;
    bool operator==(PriorityBySale p) const;
    bool operator!=(PriorityBySale p) const;
};

#endif //HW2_SALESKEY_H
