#ifndef HW1_EXECPTION_H
#define HW1_EXECPTION_H

#include <exception>


class Exception : public std::exception {
public:
    const char* what() const noexcept;
};
class TreeEmpty : public Exception {
public:
    const char* what() const noexcept;
};
class KeyAlreadyExist : public Exception {
public:
    const char* what() const noexcept;
};
class KeyNotExist : public Exception {
public:
    const char* what() const noexcept;
};




#endif //HW1_EXECPTION_H
