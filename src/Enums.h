#pragma once
enum Direction { N, E, S, W, NONE};
enum VehicleType {CAR, TRUCK, NOTHING};

const int CAR_LENGTH = 10;
const double CAR_ACCELERATION = 0.5;
const double CAR_SLOWDOWN = 2;

const int TRUCK_LENGTH = 30;
const double TRUCK_ACCELERATION = 0.3;
const double TRUCK_SLOWDOWN = 1;

const int STREET_WIDTH = 12;
//How much car is slimmer then road
const int VECH_OFFSET = 2;

const int FPS = 60;

const int BRAKING_DISTANCE = 50;
const double MAX_SPEED = 0.5; //[px/ms]

const int CLOSEST_NODE = 50;

const int BUILDING_SIZE = 30;

const int CAMERA_SIZE = 10;

const double PROBABILITY_SPAWN = 2;
const double PERCENTAGE_OF_TRUCKS = 0.1;
const double PARKING_SIZE_MULTIPLIER = 2;

const double CAMERA_PRECISION = 10000; //in meters

const int LABEL_HEIGHT = 20;