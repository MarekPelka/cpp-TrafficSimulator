#include "../src/models/Camera.cpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(angle) {
    Camera camera(Position(50, 50), 0, N);
    camera.setAngle(120);
    Camera camera2(Position(0, 50), 0, N);
    camera2.setAngle(120);
    BOOST_CHECK_EQUAL(camera.getAngle(), camera2.getAngle());
}

BOOST_AUTO_TEST_CASE(direction) {
    Camera camera(Position(50, 50), 60, NONE);
    camera.setDirection(N);
    Camera camera2(Position(0, 50), 120, NONE);
    camera2.setDirection(N);
    BOOST_REQUIRE(camera.getDirection() != NONE);
    BOOST_REQUIRE(camera2.getDirection() != NONE);
    BOOST_CHECK_EQUAL(camera.getDirection(), camera2.getDirection());
}


BOOST_AUTO_TEST_CASE(observation) {
    MovementController *moveC = MovementController::getInstance();
    CameraController *camC = CameraController::getInstance();
    CityController *cityC = CityController::getInstance();

    //test city
    Position p1(0, 0);
    Position p2(500, 0);
    Position p3(500, 500);
    Position p4(0, 500);

    cityC->addStreet(p1, p2);
    cityC->addStreet(p2, p3);
    cityC->addStreet(p3, p4);

    cityC->addStreet(p2, p1);
    cityC->addStreet(p3, p2);
    cityC->addStreet(p4, p3);
    std::list<PNode> nodes = cityC->getNodes();
    if (!nodes.empty()) {
        for (int i = 0; i < 10; i++) {
            Vehicle car(CAR, nodes);
            MovementController::getInstance()->addVehicle(car);
        }
    }

    Building building(Position(15, 15));
    camC->addBuilding(building);
    Position pos1(50, 50);
    Position pos2(0, 50);
    Camera camera(pos1, 120, N);
    Camera camera2(pos2, 60, N);
    camC->addCamera(camera);
    camC->addCamera(camera2);
    camera.updateObservation();
    camera2.updateObservation();
    BOOST_CHECK_EQUAL(camera.getView().size(), 0);
    BOOST_CHECK_EQUAL(camera2.getView().size(), 10);
    camC->deleteBuilding(building);

    camera.clearObservation();
    camera2.clearObservation();
    camera.updateObservation();
    camera2.updateObservation();
    BOOST_CHECK_EQUAL(camera.getView().size(), 10);
    BOOST_CHECK_EQUAL(camera2.getView().size(), 10);
    moveC->clearController();
    camC->clearController();
    cityC->clearController();
}

BOOST_AUTO_TEST_CASE(getDistanceBetweenPoints) {
    Position pos1(0, 0);
    Position pos2(3, 4);
    Camera camera(pos1, 120, N);
    double distance = camera.getDistanceBetweenPoints(pos1, pos2);
    BOOST_TEST_MESSAGE("Distance to power: " << distance);
    BOOST_REQUIRE_EQUAL(distance, 25);
}

BOOST_AUTO_TEST_CASE(getAngleBetweenPoints) {
    Position pos1(50, 50);
    Position pos2(0, 0);
    Camera camera(pos1, 120, N);
    double angle = camera.getAngleBetweenPoints(pos1, pos2);
    BOOST_TEST_MESSAGE("Angle in degrees: " << angle);
    BOOST_CHECK_EQUAL(angle, (double)-135);
}

BOOST_AUTO_TEST_CASE(checkIfInZone) {
    Position pos1(50, 50);
    Position posOut(0, 50);
    Position posOut2(100, 100);
    Position posIn(0, 0);
    Position posIn2(50, 0);
    Camera camera(pos1, 120, N);
    BOOST_CHECK_EQUAL(camera.checkIfInZone(camera.getAngleBetweenPoints(pos1, posOut)), false);
    BOOST_CHECK_EQUAL(camera.checkIfInZone(camera.getAngleBetweenPoints(pos1, posOut2)), false);
    BOOST_CHECK(camera.checkIfInZone(camera.getAngleBetweenPoints(pos1, posIn)));
    BOOST_CHECK(camera.checkIfInZone(camera.getAngleBetweenPoints(pos1, posIn2)));
}