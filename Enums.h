#pragma once
enum Direction { N, E, S, W, NONE};
enum vehicleType {CAR, TRUCK, NOTHING};

const float CAR_LENGTH = 20;
const float CAR_ACCELERATION = 0.5;
const float CAR_SLOWDOWN = 2;

const float TRUCK_LENGTH = 60;
const float TRUCK_ACCELERATION = 0.3;
const float TRUCK_SLOWDOWN = 1;

const int STREET_WIDTH = 10;

const int FPS = 60;

const int BRAKING_DISTANCE = 50;
const float MAX_SPEED = 0.5; //[px/ms]
