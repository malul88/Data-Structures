#ifndef HW2_TYPEKEY_H
#define HW2_TYPEKEY_H

class PriorityByType {
public:
    int num_of_sales, typeID;

    PriorityByType(){};
    PriorityByType(int num_of_sales, int typeID): num_of_sales(num_of_sales),
                                                  typeID(typeID){};
    bool operator>(PriorityByType &p) const;
    bool operator<(PriorityByType &p) const;
    bool operator==(PriorityByType &p) const;
    bool operator!=(PriorityByType &p) const;
};


#endif //HW2_TYPEKEY_H
