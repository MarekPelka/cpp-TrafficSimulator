#include "../src/models/Node.cpp"
#include "../src/models/Street.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(StreetsIn) {
    Node node(Position(100, 100));
    Node nodeW(Position(0, 100));
    Node nodeN(Position(100, 0));
    Node nodeE(Position(200, 100));
    Street street1(std::make_shared<Node>(nodeN), std::make_shared<Node>(node), false);
    Street street2(std::make_shared<Node>(nodeW), std::make_shared<Node>(node), false);
    Street street3(std::make_shared<Node>(nodeE), std::make_shared<Node>(node), false);
    node.addStreetIn(N, std::make_shared<Street>(street1));
    node.addStreetIn(W, std::make_shared<Street>(street2));
    node.addStreetIn(E, std::make_shared<Street>(street3));

    std::map<int, std::weak_ptr<Street>> streets = node.getStreetsIn();
    BOOST_CHECK_EQUAL(streets.size(), 3);
}