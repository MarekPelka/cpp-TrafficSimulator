#include "../src/models/Pedestrian.cpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(switchingStreets) {
    PNode start = std::make_shared<Node>(Position(0, 0));
    PNode middle = std::make_shared<Node>(Position(0, 50));
    PNode end = std::make_shared<Node>(Position(0, 100));
    Street street1(start, middle, false);
    Street street2(middle, end, false);
    std::list<PNode> nodes = { start ,middle, end };
    Pedestrian bob(nodes);
    bob.setToSwitch(true);
    bob.setStreetToSwitch(std::make_shared<Street>(street2));
    BOOST_CHECK_EQUAL(bob.getToSwitch(), true);
}

BOOST_AUTO_TEST_CASE(updatePosition) {
    PNode start = std::make_shared<Node>(Position(0, 0));
    PNode end = std::make_shared<Node>(Position(0, 100));
    Street street1(start, end, false);
    std::list<PNode> nodes = { start ,end};
    Pedestrian john(nodes);
    Position oldPos = john.getPosition();
    int interval = 500;
    john.move(&street1, interval, 0);
    Position newPos = john.getPosition();
    BOOST_CHECK_EQUAL(oldPos.x, newPos.x);
    BOOST_CHECK_EQUAL(oldPos.y, newPos.y-(PEDESTRIAN_SPEED*interval));
}