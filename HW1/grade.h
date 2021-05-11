
#ifndef HW1_GRADE_H
#define HW1_GRADE_H


class PriorityByGrade {
public:
    int grade, typeID, modelID;

    bool operator<(PriorityByGrade p) const;
    bool operator>(PriorityByGrade p) const;
    bool operator==(PriorityByGrade p) const;
    bool operator!=(PriorityByGrade p) const;
};





#endif //HW1_GRADE_H
