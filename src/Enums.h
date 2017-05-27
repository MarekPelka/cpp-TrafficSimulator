/**
* set of enums and constant variables used in whole project
* \author Michal Krzeminski
* \author Marek Pelka
*/

#ifndef ENUMS_H
#define ENUMS_H

///enum orientation on screen using geographic directions
enum Direction { N, E, S, W, NONE};
//enum vehicle type car or truck
enum VehicleType {CAR, TRUCK, NOTHING};

///car properties
const int CAR_LENGTH = 10;
const double CAR_ACCELERATION = 0.5;
const double CAR_SLOWDOWN = 2;

///truck properties
const int TRUCK_LENGTH = 30;
const double TRUCK_ACCELERATION = 0.3;
const double TRUCK_SLOWDOWN = 1;

///fixed width of street object
const int STREET_WIDTH = 12;
///fixed width of sidewalk
const int SIDEWALK_WIDTH = 6;
///width of complete street with sidewalk
const int FULL_STREET_WIDTH = STREET_WIDTH + SIDEWALK_WIDTH;

///fixed pedestrian speed
const double PEDESTRIAN_SPEED = 0.1;

///How much car is slimmer then road
const int VECH_OFFSET = 2;
///How much pedestrian is slimmer then sidewalk
const int PED_OFFSET = 3;

///fixed size of pedestrian object
const int PEDESTRIAN_SIZE = 4;

///frames per second
const int FPS = 60;

///distance when car start to slowdown
const int BRAKING_DISTANCE = 50;
const double MAX_SPEED = 0.5; //[px/ms]

///area where to serach for node
const int CLOSEST_NODE = 50;

///fixed size of building object 
const int BUILDING_SIZE = 30;

///fixed size of camera object
const int CAMERA_SIZE = 10;

///variables for random spawning vehicles
const double PROBABILITY_SPAWN = 4;
const double PERCENTAGE_OF_TRUCKS = 0.1;
const double PARKING_SIZE_MULTIPLIER = 2;

//distance where there is 100% chance of observation success to teh square i.e 4900 -> 70px
const double CAMERA_PRECISION = 4900;

///fixed size of label with current user input 
const int LABEL_HEIGHT = 20;

/// distance between first car and intersection
const int DRIVE_UP = 3;
/// distance between cars
const int CAR_SPACING = 3;
/// accuracy of traling cars
const int DRIVE_OFFSET = 0;
#endif