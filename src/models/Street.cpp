#include "Street.h"

Street::Street() {
	vehOnStreet = std::vector<PVehicle>();
	pedOnStreet = std::vector<PPedestrian>();
}

Street::Street(PNode nodeFrom, PNode nodeTo, bool sidewalk) {
	this->nodeFrom = nodeFrom;
	this->nodeTo = nodeTo;
	this->sidewalk = sidewalk;
	this->direction = getPredictedDirection(this->nodeFrom->getPosition(), this->nodeTo->getPosition());
	this->length = abs(getStartEndPositions().first.y - getStartEndPositions().second.y) >
		abs(getStartEndPositions().first.x - getStartEndPositions().second.x) ?
		abs(getStartEndPositions().first.y - getStartEndPositions().second.y) :
		abs(getStartEndPositions().first.x - getStartEndPositions().second.x);
	vehOnStreet = std::vector<PVehicle>();
	pedOnStreet = std::vector<PPedestrian>();
}

Direction Street::getDirection() {
	return this->direction;
}

int Street::getLength() {
	return length;
}

Direction Street::getPredictedDirection(Position start, Position end) {
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

std::vector<PVehicle> * Street::getVehicles() {
	return &vehOnStreet;
}

std::vector<PPedestrian> * Street::getPedestrians() {
	return &pedOnStreet;
}

bool Street::hasSidewalk() {
	return sidewalk;
}

void Street::alterStart(PNode n) {
	nodeFrom = n;
}

void Street::alterEnd(PNode n) {
	nodeTo = n;
}

void Street::addVehicleToStreet(Vehicle v) {
	v.setToClear(false);
	v.setToSwitch(false);
	v.setStreetToSwitch(nullptr);
	vehOnStreet.push_back(std::make_shared<Vehicle>(v));
}

void Street::addPedestrianToStreet(Pedestrian p) {
    p.setToSwitch(false);
    p.setStreetToSwitch(nullptr);
	pedOnStreet.push_back(std::make_shared<Pedestrian>(p));
}

bool Street::updatePositions(int interval) {
	int place = 0;
	for (auto iter = vehOnStreet.begin(); iter != vehOnStreet.end();) {
		if (iter->get()->updatePosition(this, interval, place)) {
			++iter;
			++place;
		} else {
			iter = vehOnStreet.erase(iter);
		}
	}
	auto deleteIterator = vehOnStreet.begin();
	while (deleteIterator != vehOnStreet.end()) {
		if (deleteIterator->get()->getToSwitch()) {
			MovementController::getInstance()->addVehicleToSwitch(*deleteIterator->get());
			deleteIterator = vehOnStreet.erase(deleteIterator);

		} else {
			++deleteIterator;
		}
	}
	//pedestrians
	if (pedOnStreet.size() != 0) {
		for (auto it = pedOnStreet.begin(); it != pedOnStreet.end();) {
			if (it->get()->updatePosition(this, interval, 0)) {
				++it;
			} else {
				it = pedOnStreet.erase(it);
			}
		}
	}
    auto delIter = pedOnStreet.begin();
    while (delIter != pedOnStreet.end()) {
        if (delIter->get()->getToSwitch()) {
            MovementController::getInstance()->addPedestrianToSwitch(*delIter->get());
            delIter = pedOnStreet.erase(delIter);

        }
        else {
            ++delIter;
        }
    }

	return true;
}

bool Street::swichStreet(std::weak_ptr<Street> s, int spaceNeeded) {
	if (auto street = s.lock()) {
		Position streetEnd = this->getStartEndPositions().second;
		if (street->getVehicles()->empty()) {
			return true;
		} else {
			Position carPosition = street->getVehicles()->back()->getPosition();
			int possibleSpace = streetEnd.x == carPosition.x ? abs(streetEnd.y - carPosition.y) : abs(streetEnd.x - carPosition.x);
			if (possibleSpace >= spaceNeeded) {
				return true;
			}
		}
	}
	return false;

}

bool Street::operator==(const Street & v) {
	return this->nodeFrom == v.nodeFrom && this->nodeTo == v.nodeTo;
}

std::pair<PNode, PNode> Street::getNodes() {
	return{nodeFrom, nodeTo};
}

std::pair<Position, Position> Street::getStartEndPositions() {
	return{nodeFrom->getPosition(), nodeTo->getPosition()};
}
