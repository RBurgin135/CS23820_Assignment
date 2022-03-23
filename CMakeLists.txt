cmake_minimum_required(VERSION 3.20)
project(Richard_Burgin_CS23820_Assignment C)

set(CMAKE_C_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(ERP_Richard_Burgin_CS23820_Assignment
        erp.c
        erp_functions.c
        erp_functions.h
        file_management.c
        file_management.h
        competitor.c
        competitor.h
        utility.c
        utility.h
        track.c
        track.h)
add_executable(CDP_Richard_Burgin_CS23820_Assignment
        cdp.c
        cdp_functions.c
        cdp_functions.h
        file_management.c
        file_management.h
        competitor.c
        competitor.h
        utility.c
        utility.h
        track.c
        track.h)
