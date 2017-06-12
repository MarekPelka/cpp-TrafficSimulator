#include "../src/models/Vehicle.cpp"

#include <boost/test/unit_test.hpp>

#define private public

BOOST_AUTO_TEST_CASE(checkslowdown) {
    Position pos2(70, 0);
    Position pos3(100, 0);
    PNode start = std::make_shared<Node>(pos2);
    PNode end = std::make_shared<Node>(pos3);
    std::list<PNode> nodes = { start ,end };
    Vehicle veh(CAR, nodes);
    BOOST_CHECK(veh.checkSlowdown(veh.getPosition()));
}

BOOST_AUTO_TEST_CASE(checkmaxspeed) {
    Position pos1(100, 100);
    Position pos2(0, 100);
    PNode start = std::make_shared<Node>(pos1);
    PNode end = std::make_shared<Node>(pos2);
    std::list<PNode> nodes = { start ,end };
    Vehicle veh(CAR, nodes);
    BOOST_CHECK_EQUAL(veh.checkMaxSpeed(), false);
}

BOOST_AUTO_TEST_CASE(switchingstreets) {
    Position pos1(100, 100);
    Position pos2(0, 100);
    PNode start = std::make_shared<Node>(pos1);
    PNode end = std::make_shared<Node>(pos2);
    std::list<PNode> nodes = { start ,end };
    Vehicle veh(CAR, nodes);
    Street street(std::make_shared<Node>(pos1), std::make_shared<Node>(pos2), false);
    veh.setStreetToSwitch(std::make_shared<Street>(street));
    auto street2 = veh.getStreetToSwitch();
    BOOST_CHECK(*street2.get() == street);
}