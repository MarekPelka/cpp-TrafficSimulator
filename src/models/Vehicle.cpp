#include "Vehicle.h"
#include "../viewmodels/MovementController.h"

Vehicle::Vehicle(VehicleType typ, std::list<Node> nods) {
	type = typ;
	if (type == CAR) {
		length = CAR_LENGTH;
		acceleration = CAR_ACCELERATION;
		slowdown = CAR_SLOWDOWN;
	} else if (type == TRUCK) {
		length = TRUCK_LENGTH;
		acceleration = TRUCK_ACCELERATION;
		slowdown = TRUCK_SLOWDOWN;
	}
	position = nods.front().getPosition();
	nods.pop_front();
	nodes = nods;
	orientation = N;
	speed = 0;
}

Vehicle::Vehicle(VehicleType typ, std::list<PNode> nods) {
	type = typ;
	if (type == CAR) {
		length = CAR_LENGTH;
		acceleration = CAR_ACCELERATION;
		slowdown = CAR_SLOWDOWN;
	} else if (type == TRUCK) {
		length = TRUCK_LENGTH;
		acceleration = TRUCK_ACCELERATION;
		slowdown = TRUCK_SLOWDOWN;
	}
	position = nods.front()->getPosition();
	nods.pop_front();
	for (auto n : nods)
		nodes.push_back(*n);
	orientation = getPredictedDirection(position, nodes.front().getPosition());
	speed = 0;
}

void Vehicle::move(Street * const s, int time, int place) {
	if (nodes.size() != 0) {
		isMoving = true;
		if (place == 0) { //first  vehicle
			/*if (place != 0)
				throw "First and not first element";*/
			int brakingDistance = static_cast <int> (pow(speed, 2) / 2 / CAR_SLOWDOWN);
			int roadTT = nodes.front().getPosition().x == position.x ? abs(nodes.front().getPosition().y - position.y) : abs(nodes.front().getPosition().x - position.x);
			if (roadTT < DRIVE_UP) {
				//arrive to crossroad an should stay
			} else if (roadTT - brakingDistance < DRIVE_UP) {
				//SLOW DOWN
				speed -= slowdown * time / 1000;
			} else if (!checkMaxSpeed()) {
				//ACCELERATE
				speed += acceleration * time / 1000;
			} else {
				//TOP SPEED
				speed = MAX_SPEED;
			}
			//calculating shift
		} else { //Not first vehicle
			Vehicle vehInFront = *s->getVehicles()->at(place - 1);
			int distanceFromVehInFront = static_cast <int> (this->speed / 2 + 1);
			int brakingOffset = DRIVE_UP;

			int p = 0;
			for (auto vh : *s->getVehicles()) {
				brakingOffset += CAR_SPACING;
				if (p == place)
					break;
				if (vh->getType() == CAR) {
					brakingOffset += CAR_LENGTH;
				} else {
					brakingOffset += TRUCK_LENGTH;
				}
				++p;
				brakingOffset += CAR_SPACING;
			}

			int brakingDistance = static_cast <int> (pow(speed, 2) / (2 * CAR_SLOWDOWN));
			int roadTT = nodes.front().getPosition().x == position.x ? abs(nodes.front().getPosition().y - position.y) : abs(nodes.front().getPosition().x - position.x);
			int carInFrontRoadTT = nodes.front().getPosition().x == vehInFront.getPosition().x ? abs(nodes.front().getPosition().y - vehInFront.getPosition().y) : abs(nodes.front().getPosition().x - vehInFront.getPosition().x);
			if (roadTT <= brakingOffset) {
				//arrive to car before him and sholud stay
				speed = 0;
			} else if (roadTT - brakingDistance <= brakingOffset) {
				//slowdown before another object
				speed -= slowdown * time / 1000;
			} else if (carInFrontRoadTT + distanceFromVehInFront + DRIVE_OFFSET < roadTT) {
				//THIS too FAR
				calculateSpeed(1, time, vehInFront);
				//speed += acceleration * time / 1000;
			} else if (carInFrontRoadTT + distanceFromVehInFront - DRIVE_OFFSET > roadTT) {
				//THIS TOO CLOSE
				calculateSpeed(-1, time, vehInFront);
			} else {
				//Everything is ok
				//speed = MAX_SPEED;
				calculateSpeed(0, time, vehInFront);
			}
			if (speed < 0)
				speed = 0;
		}
		Position step = nodes.front().getPosition();
		int temp = static_cast <int> (speed*time);
		if (position.x != step.x || position.y != step.y) {
			if (position.x < step.x) {
				orientation = E;
				if (temp + position.x > step.x) {
					temp = step.x;
				} else {
					temp += position.x;
				}
				position = Position(temp, position.y);
			} else if (position.x > step.x) {
				orientation = W;
				if (position.x - temp < step.x) {
					temp = step.x;
				} else {
					temp = position.x - temp;
				}
				position = Position(temp, position.y);
			} else if (position.y < step.y) {
				orientation = S;
				if (temp + position.y > step.y) {
					temp = step.y;
				} else {
					temp += position.y;
				}
				position = Position(position.x, temp);
			} else if (position.y > step.y) {
				orientation = N;
				if (position.y - temp < step.y) {
					temp = step.y;
				} else {
					temp = position.y - temp;
				}
				position = Position(position.x, temp);
			}
		} else {
			if (nodes.size() > 1) {
				Node nextNode = *std::next(nodes.begin(), 1);
				Direction nextDirection = getPredictedDirection(nodes.front().getPosition(), nextNode.getPosition());

				std::weak_ptr<Street> nextStreet = nextNode.getStreetsIn().at(nextDirection);
				if (s->swichStreet(nextStreet, this->length + CAR_SPACING)) {
					nodes.pop_front();
					auto myIter = std::next(s->getVehicles()->begin(), place);
					if (myIter != s->getVehicles()->end()) {
						this->toSwitch = true;
						this->setStreetToSwitch(nextStreet.lock());
					} 
				}
			} else {
				nodes.pop_front();
			}
		}
	} else {
		isMoving = false;
	}
}

bool Vehicle::checkSlowdown(Position step) {
	if (nodes.size() == 1) {
		switch (orientation) {
			case N:
			{
				if (position.y - BRAKING_DISTANCE < step.y) {
					return true;
				}
				break;
			}
			case S:
			{
				if (position.y + BRAKING_DISTANCE > step.y) {
					return true;
				}
				break;
			}
			case E:
			{
				if (position.x + BRAKING_DISTANCE > step.x) {
					return true;
				}
				break;
			}
			case W:
			{
				if (position.x - BRAKING_DISTANCE < step.x) {
					return true;
				}
				break;
			}
			case NONE:
			{
				//Do nothing
				break;
			}
		}
	}
	return false;
}

bool Vehicle::checkMaxSpeed() {
	if (speed >= MAX_SPEED)
		return true;
	else
		return false;
}

bool Vehicle::operator==(const Vehicle & v) {
	return type == v.type && speed == v.speed && orientation == v.orientation && position == v.position;
}

bool Vehicle::getToSwitch() {
	return toSwitch;
}

void Vehicle::setToSwitch(bool t) {
	toSwitch = t;
}

double Vehicle::getSpeed() {
	return speed;
}

std::shared_ptr<Street> Vehicle::getStreetToSwitch() {
	return streetToSwitch;
}

void Vehicle::setStreetToSwitch(std::shared_ptr<Street> t) {
	streetToSwitch = t;
}

Position Vehicle::getPosition() {
	return position;
}

void Vehicle::setPosition(Position& pos) {
    position = pos;
}

VehicleType Vehicle::getType() {
	return type;
}

std::list<Node> Vehicle::getNodes() {
	return nodes;
}

bool Vehicle::updatePosition(Street * const s, int time, int place) {
	if (isMoving == false && nodes.size() == 0) {
		//vehicle to delete
		return false;
	} else {
		//vehicle still moving
		move(s, time, place);
		return true;
	}
}

Direction Vehicle::getOrientation() {
	return orientation;
}

Direction Vehicle::getPredictedDirection(Position start, Position end) {
	if (start.x == end.x) {
		if (start.y > end.y) {
			return N;
		} else {
			return S;
		}
	} else if (start.y == end.y) {
		if (start.x > end.x) {
			return W;
		} else {
			return E;
		}
	}
	return NONE;
}

void Vehicle::calculateSpeed(int d, int time, Vehicle inFront) {

	//speed -= slowdown * time / 1000;
	//speed += acceleration * time / 1000;

	if (d > 0) {
		if (this->speed > inFront.speed) {
			//nt;
		} else if (this->speed < inFront.speed) {
			speed += acceleration * time / 1000;
		} else {
			speed += acceleration * time / 1000;
		}
	} else if (d == 0) {
		if (this->speed > inFront.speed) {
			speed -= slowdown * time / 1000;
		} else if (this->speed < inFront.speed) {
			speed += acceleration * time / 1000;
		} else {
			//nt
		}
	} else if (d < 0) {
		if (this->speed > inFront.speed) {
			speed -= slowdown * time / 1000;
		} else if (this->speed < inFront.speed) {
			//nt
		} else {
			//nt
		}
	}
}