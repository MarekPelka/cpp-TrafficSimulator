#include "../src/models/Street.cpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(getStartEndPos) {
    Position pos1(100, 100);
    Position pos2(0, 100);
    Street street(std::make_shared<Node>(pos1), std::make_shared<Node>(pos2), false);
    std::pair<Position,Position> map = street.getStartEndPositions();
    BOOST_CHECK_EQUAL(map.first.x, pos1.x);
    BOOST_CHECK_EQUAL(map.first.y, pos1.y);
    BOOST_CHECK_EQUAL(map.second.x, pos2.x);
    BOOST_CHECK_EQUAL(map.second.y, pos2.y);
}

BOOST_AUTO_TEST_CASE(getPredictedDir) {
    Position pos(100, 100);
    Position posW(0, 100);
    Position posE(200, 100);
    Position posN(100, 0);
    Position posS(100, 200);
    BOOST_CHECK_EQUAL(Street::getPredictedDirection(pos, posW), W);
    BOOST_CHECK_EQUAL(Street::getPredictedDirection(pos, posE), E);
    BOOST_CHECK_EQUAL(Street::getPredictedDirection(pos, posN), N);
    BOOST_CHECK_EQUAL(Street::getPredictedDirection(pos, posS), S);
}

BOOST_AUTO_TEST_CASE(addobjecttostreet) {
    Position pos1(100, 100);
    Position pos2(0, 100);
    PNode start = std::make_shared<Node>(pos1);
    PNode end = std::make_shared<Node>(pos2);
    Street street1(start, end, false);
    std::list<PNode> nodes = { start ,end };
    Street street(std::make_shared<Node>(pos1), std::make_shared<Node>(pos2), false);
    Vehicle veh(CAR, nodes);
    Vehicle veh2(CAR, nodes);
    Pedestrian ped(nodes);
    street.addVehicleToStreet(veh);
    street.addVehicleToStreet(veh2);
    street.addPedestrianToStreet(ped);
    BOOST_CHECK_EQUAL(street.getVehicles()->size(), 2);
    BOOST_CHECK_EQUAL(street.getPedestrians()->size(), 1);
}