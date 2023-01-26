cmake_minimum_required(VERSION 3.24)
project(INSA_2022_classification_algorithm)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(INSA_2022_classification_algorithm
        algorithm.hpp
        algorithm.cpp
        algorithm1.hpp
        algorithm1.cpp
        data.cpp
        data.hpp
        main.cpp
        utils.cpp
        utils.hpp
        compareAlgo.cpp
        compareAlgo.hpp
        algorithm2.cpp
        algorithm2.hpp
        )
