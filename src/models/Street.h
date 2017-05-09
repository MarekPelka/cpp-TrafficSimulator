#pragma once
#include "Position.h"
#include "Node.h"
#include "../Enums.h"
#include <utility>
#include <memory>

typedef std::shared_ptr<Node> PNode;

class Street {
public:
    Street();
    Street(PNode nodeFrom, PNode nodeTo, bool sidewalk = false);
    std::pair <PNode, PNode> getNodes();
    std::pair <Position, Position> getStartEndPositions();
    Direction getDirection();
    int getLength();
    static Direction getPredictedDirection(Position start, Position end);

    bool hasSidewalk();
    void alterStart(PNode n);
    void alterEnd(PNode n);
private:
    Direction direction;
    PNode nodeFrom;
    PNode nodeTo;
    bool sidewalk;
    int length;
};
