#include "../src/models/Building.cpp"
#include "../src/models/Camera.cpp"
#include "../src/models/Vehicle.cpp"
#include "../src/viewmodels/CameraController.cpp"
#include "../src/viewmodels/VehicleController.cpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(addCamAndBuild)
{
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

BOOST_AUTO_TEST_CASE(deleteCamAndBuild)
{
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

BOOST_AUTO_TEST_CASE(getDistanceBetweenPoints) {
    Position pos1(0,0);
    Position pos2(3,4);
    Camera camera(pos1, 120, N);
    double distance = camera.getDistanceBetweenPoints(pos1,pos2);
    BOOST_TEST_MESSAGE("Distance to power: " << distance);
    BOOST_REQUIRE(distance == 25);
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
    BOOST_CHECK_EQUAL(camera.checkIfInZone(camera.getAngleBetweenPoints(pos1, posIn)), true);
    BOOST_CHECK_EQUAL(camera.checkIfInZone(camera.getAngleBetweenPoints(pos1, posIn2)), true);
}

BOOST_AUTO_TEST_CASE(updateObservation) {
    VehicleController *vehC = VehicleController::getInstance();
    CameraController *camC = CameraController::getInstance();
    CityController *cityC = CityController::getInstance();

    //test city
    Position p1(0,0);
    Position p2(500, 0);
    Position p3(500, 500);
    Position p4(0, 500);

    cityC->addStreet(p1, p2);
    cityC->addStreet(p2, p3);
    cityC->addStreet(p3, p4);

    cityC->addStreet(p2, p1);
    cityC->addStreet(p3, p2);
    cityC->addStreet(p4, p3);
    std::list<PNode> nodes =cityC->getNodes();
    if (!nodes.empty()) {
        for (int i = 0; i < 10; i++) {
            Vehicle car(CAR, nodes);
            VehicleController::getInstance()->addVehicle(car);
        }
    }

    Building building(Position(15,15));
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
    vehC->clearController();
    camC->clearController();
    cityC->clearController();
}