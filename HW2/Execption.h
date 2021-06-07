#ifndef HW1_EXECPTION_H
#define HW1_EXECPTION_H

#include <exception>


class Exception : public std::exception {
};
class TreeEmpty : public Exception {
};
class KeyAlreadyExist : public Exception {
};
class KeyNotExist : public Exception {
};
class AllocationError : public Exception {
};
class NotEnoughCars : public Exception {
};




#endif //HW1_EXECPTION_H
