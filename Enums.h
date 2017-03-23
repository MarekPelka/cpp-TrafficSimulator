#pragma once
enum Direction { N, E, W, S, NONE};
enum vehicleType {CAR, TRUCK, NOTHING};

const float CAR_LENGTH = 20;
const float CAR_ACCELERATION = 0.5;
const float CAR_SLOWDOWN = 2;

const float TRUCK_LENGTH = 60;
const float TRUCK_ACCELERATION = 2;
const float TRUCK_SLOWDOWN = 3;

const int STREET_WIDTH = 10;

const int FPS = 60;
