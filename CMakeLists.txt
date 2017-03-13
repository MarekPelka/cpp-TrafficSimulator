cmake_minimum_required(VERSION 3.7)
project(cpp_TrafficSimulator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        TrafficSimulator/Models/Camera.cpp
        TrafficSimulator/Models/Camera.h
        TrafficSimulator/Models/Enums.h
        TrafficSimulator/Models/MovingObject.h
        TrafficSimulator/Models/Pedestrian.cpp
        TrafficSimulator/Models/Pedestrian.h
        TrafficSimulator/Models/Position.cpp
        TrafficSimulator/Models/Position.h
        TrafficSimulator/Models/Vehicle.cpp
        TrafficSimulator/Models/Vehicle.h)

add_executable(cpp_TrafficSimulator ${SOURCE_FILES})