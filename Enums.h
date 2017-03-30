#pragma once
enum Direction { N, E, S, W, NONE};
enum vehicleType {CAR, TRUCK, NOTHING};

const float CAR_LENGTH = 10;
const float CAR_ACCELERATION = 0.5;
const float CAR_SLOWDOWN = 2;

const float TRUCK_LENGTH = 30;
const float TRUCK_ACCELERATION = 0.3;
const float TRUCK_SLOWDOWN = 1;

const int STREET_WIDTH = 12;
//How much car is slimmer then road
const int VECH_OFFSET = 2;

const int FPS = 60;

const int BRAKING_DISTANCE = 50;
const float MAX_SPEED = 0.5; //[px/ms]

const int CLOSEST_NODE = 20;

const int BUILDING_SIZE = 30;

const int CAMERA_SIZE = 10;