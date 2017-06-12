#include "Pedestrian.h"
#include "../viewmodels/CityController.h"

Pedestrian::Pedestrian(std::list<PNode> nods) {
    int offset = FULL_STREET_WIDTH - PED_OFFSET;
    Position temp = nods.front()->getPosition();
    nods.pop_front();
    for (auto n : nods) {
        nodes.push_back(*n);
    }
    orientation = predictDirection(temp, nodes.front().getPosition());
    if (orientation == N) {
        position = Position(temp.x + offset, temp.y - offset);
    }
    else if (orientation == S) {
        position = Position(temp.x - offset, temp.y + offset);
    }
    else if (orientation == E) {
        position = Position(temp.x + offset, temp.y + offset);
    }
    else if (orientation == W) {
        position = Position(temp.x - offset, temp.y - offset);
    }
    else {
        position = temp;
    }
}

void Pedestrian::move(Street * const s, int time, int place) {
	if (place < 0 || s == nullptr)
		return;
    int offset = FULL_STREET_WIDTH - PED_OFFSET;
    if (nodes.size() != 0) {
        isMoving = true;
        Position nextNode;
        auto next = nodes.front().getPosition();
        orientation = predictDirection(position, next);
        if (nodes.size() > 1) {
            nodes.pop_front();
            auto nextnext = nodes.front().getPosition();
            nodes.push_front(next);

            if (orientation == N) {
                if (predictDirection(next, nextnext) == W) {
                    nextNode = Position(next.x + offset, next.y - offset);
                }
                else
                    nextNode = Position(next.x + offset, next.y + offset);
            }
            else if (orientation == S) {
                if (predictDirection(next, nextnext) == E) {
                    nextNode = Position(next.x - offset, next.y + offset);
                }
                else
                    nextNode = Position(next.x - offset, next.y - offset);
            }
            else if (orientation == E) {
                if (predictDirection(next, nextnext) == N) {
                    nextNode = Position(next.x + offset, next.y + offset);
                }
                else
                    nextNode = Position(next.x - offset, next.y + offset);
            }
            else if (orientation == W) {
                if (predictDirection(next, nextnext) == S) {
                    nextNode = Position(next.x - offset, next.y - offset);
                }
                else
                    nextNode = Position(next.x + offset, next.y - offset);
            }
        }
        else {
            if (orientation == N) {
                nextNode = Position(nodes.front().getPosition().x + offset, nodes.front().getPosition().y + offset);
            }
            else if (orientation == S) {
                nextNode = Position(nodes.front().getPosition().x - offset, nodes.front().getPosition().y - offset);
            }
            else if (orientation == E) {
                nextNode = Position(nodes.front().getPosition().x - offset, nodes.front().getPosition().y + offset);
            }
            else if (orientation == W) {
                nextNode = Position(nodes.front().getPosition().x + offset, nodes.front().getPosition().y - offset);
            }
        }
        int step = static_cast<int> (PEDESTRIAN_SPEED * time);

        if (position.x != nextNode.x || position.y != nextNode.y) {
            if (position.x < nextNode.x) {
                orientation = E;
                if (step + position.x >= nextNode.x) {
                    step = nextNode.x;
                }
                else {
                    step += position.x;
                }
                position = Position(step, position.y);
            }
            else if (position.x > nextNode.x) {
                orientation = W;
                if (position.x - step <= nextNode.x) {
                    step = nextNode.x;
                }
                else {
                    step = position.x - step;
                }
                position = Position(step, position.y);
            }
            else if (position.y < nextNode.y) {
                orientation = S;
                if (step + position.y >= nextNode.y) {
                    step = nextNode.y;
                }
                else {
                    step += position.y;
                }
                position = Position(position.x, step);
            }
            else if (position.y > nextNode.y) {
                orientation = N;
                if (position.y - step <= nextNode.y) {
                    step = nextNode.y;
                }
                else {
                    step = position.y - step;
                }
                position = Position(position.x, step);
            }
        }
        else {
            if (nodes.size() > 1) {
                nodes.pop_front();
                auto nextnext = nodes.front();
                //nodes.push_front(next);
                Direction nextDirection = predictDirection(next, nextnext.getPosition());
                std::weak_ptr<Street> nextStreet = nextnext.getStreetsIn().at(nextDirection);
                this->toSwitch = true;
                this->setStreetToSwitch(nextStreet.lock());
            }
            else {
                nodes.pop_front();
            }
        }
    }
    else {
        isMoving = false;
    }
}

bool Pedestrian::getToSwitch() {
    return toSwitch;
}

void Pedestrian::setToSwitch(bool t) {
    toSwitch = t;
}

std::shared_ptr<Street> Pedestrian::getStreetToSwitch() {
    return streetToSwitch;
}

void Pedestrian::setStreetToSwitch(std::shared_ptr<Street> t) {
    streetToSwitch = t;
}

Position Pedestrian::getPosition() {
    return position;
}

Direction Pedestrian::getOrientation() {
    return orientation;
}

std::list<Node> Pedestrian::getNodes() {
    return nodes;
}

bool Pedestrian::updatePosition(Street * const s, int time, int place) {
    if (isMoving == false && nodes.size() == 0) {
        //pedestrian to delete
        return false;
    }
    else {
        //vehicle still moving
        move(s, time, place);
        return true;
    }
}

bool Pedestrian::operator==(const Pedestrian & p) {
    return position == p.position;
}


Direction Pedestrian::predictDirection(Position start, Position end) {
    double angleRad = atan2(end.y - start.y, end.x - start.x);
    angleRad *= 2 * right_angle / M_PI;

    if (-(right_angle/2) <= angleRad && angleRad < right_angle/2) {
        return E;
    }
    else if (right_angle/2 <= angleRad && angleRad < 135) {
        return S;
    }
    else if ((1.5 * right_angle <= angleRad && angleRad <= 2 * right_angle) || (-(2 * right_angle) < angleRad && angleRad < -(1.5 * right_angle))) {
        return W;
    }
    else if (-(1.5 * right_angle) <= angleRad && angleRad < -(right_angle/2)) {
        return N;
    }
    return NONE;
}
