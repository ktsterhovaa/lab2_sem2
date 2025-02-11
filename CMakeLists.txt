cmake_minimum_required(VERSION 3.27)
project(lab2)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab2
        Sequence.h
        MutableArraySequence.h
        ListSequence.h
        LinkedList.h
        DynamicArray.h
        IndexOutOfRange.hpp
        ImmutableArraySequence.h
        main.cpp
        mainFunctions.h

)
add_subdirectory(Google_tests)