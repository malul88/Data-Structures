cmake_minimum_required(VERSION 3.19)
project(HW1)

set(CMAKE_CXX_STANDARD 14)

add_executable(HW1 AVLTree.h carModel.h carModel.cpp library.h car_type.cpp DS.cpp DS.h Execption.cpp
        Execption.h library.cpp grade.cpp grade.h sales.cpp sales.h main1.cpp)
