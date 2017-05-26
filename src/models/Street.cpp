#include "Street.h"

Street::Street() {
    vehOnStreet = std::vector<Vehicle>();
    pedOnStreet = std::vector<Pedestrian>();
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
    vehOnStreet = std::vector<Vehicle>();
    pedOnStreet = std::vector<Pedestrian>();
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

std::vector<Vehicle> * Street::getVehicles() {
	return &vehOnStreet;
}

std::vector<Pedestrian> * Street::getPedestrians() {
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
	vehOnStreet.push_back(v);
}

void Street::addPedestrianToStreet(Pedestrian p) {
	pedOnStreet.push_back(p);
}

bool Street::updatePositions(int interval) {
	int place = 0;
    if (vehOnStreet.size() != 0) {
        for (auto iter = vehOnStreet.begin(); iter != vehOnStreet.end();) {
            if (iter->updatePosition(this, interval, place)) {
                ++iter;
                ++place;
            }
            else {
                iter = vehOnStreet.erase(iter);
            }
        }
        auto deleteIterator = vehOnStreet.begin();
        while (deleteIterator != vehOnStreet.end()) {
            if (deleteIterator->getToClear()) {
                if (deleteIterator->getToSwitch()) {
                    MovementController::getInstance()->addVehicleToSwitch(*deleteIterator);
                }
                deleteIterator = vehOnStreet.erase(deleteIterator);
            }
            else {
                ++deleteIterator;
            }
        }
    }
	//pedestrians
    if (pedOnStreet.size() != 0) {
        for (auto it = pedOnStreet.begin(); it != pedOnStreet.end();) {
            if (it->updatePosition(interval)) {
                ++it;
            }
            else {
                it = pedOnStreet.erase(it);
            }
        }
    }

	return true;
}

bool Street::swichStreet(std::weak_ptr<Street> s, int spaceNeeded) {
	if (auto street = s.lock()) {
		//if(this == street.get())
			//return false;
		Position streetEnd = this->getStartEndPositions().second;
		if (street->getVehicles()->empty()) {
			return swichS(street);
		} else {
			Position carPosition = street->getVehicles()->back().getPosition();
			int possibleSpace = streetEnd.x == carPosition.x ? abs(streetEnd.y - carPosition.y) : abs(streetEnd.x - carPosition.x);
			if (possibleSpace >= spaceNeeded) {
				return swichS(street);
			}
		}
	}
	return false;

}

bool Street::operator==(const Street & v) {
	return this->nodeFrom == v.nodeFrom && this->nodeTo == v.nodeTo;
}

bool Street::swichS(std::shared_ptr<Street> s) {
	auto vec = this->vehOnStreet;
	if (!vec.empty()) {
		//s->addVehicleToStreet(vec.front());
		//vec.front().getNodes().pop_front();
		//vec.front() = std::move(vec.back());
		//vec.pop_back();
		return true;
	} else {
		return false;
	}
}

std::pair<PNode, PNode> Street::getNodes() {
	return{nodeFrom, nodeTo};
}

std::pair<Position, Position> Street::getStartEndPositions() {
	return{nodeFrom->getPosition(), nodeTo->getPosition()};
}
