#include "../src/models/Vehicle.cpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(checkslowdown) {

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

BOOST_AUTO_TEST_CASE(color) {

}

BOOST_AUTO_TEST_CASE(switchingstreets) {

}

BOOST_AUTO_TEST_CASE(calculatespeed) {

}

BOOST_AUTO_TEST_CASE(updateposition) {

}