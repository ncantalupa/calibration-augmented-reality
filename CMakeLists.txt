cmake_minimum_required(VERSION 3.10)
project(project4)

set(CMAKE_CXX_STANDARD 17)

add_executable(calibration-AR
        #vidDisplay.cpp
        imgProc.cpp
        csv_util/csv_util.cpp
        csv_util/csv_util.h
        harrisCorners.cpp
)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(calibration-AR ${OpenCV_LIBS})