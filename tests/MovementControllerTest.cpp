#include "../src/viewmodels/MovementController.cpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(addVehaddPed) {
    MovementController *moveC = MovementController::getInstance();
    Position pos1(0, 0);
    Position pos2(100, 0);
    PNode start = std::make_shared<Node>(pos1);
    PNode end = std::make_shared<Node>(pos2);
    std::list<PNode> nodes = { start ,end };
    Vehicle veh(CAR, nodes);
    Pedestrian bob(nodes);

    BOOST_CHECK_THROW(moveC->addVehicle(veh), std::out_of_range);
    BOOST_CHECK_THROW(moveC->addPedestrian(bob), std::out_of_range);

    moveC->clearController();
}

BOOST_AUTO_TEST_CASE(addVehaddPedtoSwitch) {
    MovementController *moveC = MovementController::getInstance();
    Position pos1(0, 0);
    Position pos2(100, 0);
    PNode start = std::make_shared<Node>(pos1);
    PNode end = std::make_shared<Node>(pos2);
    std::list<PNode> nodes = { start ,end };
    Vehicle veh(CAR, nodes);
    Pedestrian bob(nodes);

    moveC->addVehicleToSwitch(veh);
    moveC->addPedestrianToSwitch(bob);
    BOOST_REQUIRE(moveC->getVehiclesToSwitch()->size() == 1);
    BOOST_REQUIRE(moveC->getPedestriansToSwitch()->size() == 1);
    moveC->clearController();
}