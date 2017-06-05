#include "../src/models/Building.cpp"
#include "../src/models/SqlConnector.cpp"
#include "../src/viewmodels/CameraController.cpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(addCamAndBuild) {
    CameraController *camC = CameraController::getInstance();
    Camera camera(Position(100,100), 60, E);
    Camera camera2(Position(200, 200), 30, W);
    camC->addCamera(camera);
    camC->addCamera(camera2);
    BOOST_REQUIRE(camC->getCameras().size() == 2);
    Building building(Position(0, 0));
    Building building2(Position(1000, 1000));
    camC->addBuilding(building);
    camC->addBuilding(building2);
    BOOST_REQUIRE(camC->getBuildings().size() == 2);
    camC->clearController();
}

BOOST_AUTO_TEST_CASE(deleteCamAndBuild) {
    CameraController *camC = CameraController::getInstance();
    Camera camera(Position(100, 100), 60, E);
    Camera camera2(Position(200, 200), 30, W);
    camC->addCamera(camera);
    camC->addCamera(camera2);
    camC->deleteCamera(camera);
    BOOST_REQUIRE(camC->getCameras().size() == 1);
    Building building(Position(0, 0));
    Building building2(Position(1000, 1000));
    camC->addBuilding(building);
    camC->addBuilding(building2);
    camC->deleteBuilding(building2);
    BOOST_REQUIRE(camC->getBuildings().size() == 1);
    camC->clearController();
}

BOOST_AUTO_TEST_CASE(IfBuilding) {
    CameraController *camC = CameraController::getInstance();
    Building building(Position(15, 15));
    CameraController::getInstance()->addBuilding(building);
    Position pos(0, 0);
    Position posFalse(50, 50);
    Position posTrue(0, 50);
    BOOST_CHECK_EQUAL(camC->checkIfBuilding(pos,posTrue), true);
    BOOST_CHECK_EQUAL(camC->checkIfBuilding(pos, posFalse), false);
}

BOOST_AUTO_TEST_CASE(lineintersections) {
    CameraController *camC = CameraController::getInstance();
    Position p1(50, 0);
    Position p2(50, 100);
    Position q1(0, 50);
    Position q2(100, 50);
    Position r1(0, 0);
    Position r2(0, 100);
    BOOST_CHECK_EQUAL(camC->LineIntersectsLine(p1, p2, q1, q2), true);
    BOOST_CHECK_EQUAL(camC->LineIntersectsLine(p1, p2, r1, r2), false);
}