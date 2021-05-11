

#ifndef HW1_CARMODEL_H
#define HW1_CARMODEL_H


class carModel {
public:
    int typeID, modelID;
    int grade, complains, sales;
    bool zeroed;

    carModel(int typeID, int modelID): typeID(typeID), modelID(modelID),
        grade(0), complains(0), sales(0){};
    bool operator<(const carModel& carModel) const;
    bool operator>(const carModel& carModel) const;
    bool operator==(const carModel& carModel) const;
    bool operator!=(const carModel& carModel) const;

    void saleModel();
    void complainModel(int t);
};




#endif //HW1_CARMODEL_H
