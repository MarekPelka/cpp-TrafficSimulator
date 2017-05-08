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
    Camera camera(pos1, 60, E);
    double distance = camera.getDistanceBetweenPoints(pos1,pos2);
    BOOST_TEST_MESSAGE("Distance to power: " << distance);
    BOOST_REQUIRE(distance == 25);
}

BOOST_AUTO_TEST_CASE(getAngleBetweenPoints) {
    Position pos1(0, 0);
    Position pos2(100, 100);
    Camera camera(pos1, 60, E);
    double angle = camera.getAngleBetweenPoints(pos1, pos2);
    BOOST_TEST_MESSAGE("Angle in degrees: " << angle);
    BOOST_CHECK_EQUAL(angle, (double)45);
}

BOOST_AUTO_TEST_CASE(checkIfInZone) {
    Position pos1(0, 0);
    Position posOut(100, 100);
    Position posOut2(-100, 0);
    Position posIn(100, 0);
    Position posIn2(100, 20);
    Camera camera(pos1, 60, E);
    BOOST_CHECK_EQUAL(camera.checkIfInZone(camera.getAngleBetweenPoints(pos1, posOut)), false);
    BOOST_CHECK_EQUAL(camera.checkIfInZone(camera.getAngleBetweenPoints(pos1, posOut2)), false);
    BOOST_CHECK_EQUAL(camera.checkIfInZone(camera.getAngleBetweenPoints(pos1, posIn)), true);
    BOOST_CHECK_EQUAL(camera.checkIfInZone(camera.getAngleBetweenPoints(pos1, posIn2)), true);
}

BOOST_AUTO_TEST_CASE(updateObservation) {
    VehicleController *vehC = VehicleController::getInstance();
    CameraController *camC = CameraController::getInstance();

    Vehicle vehIn(CAR,Position(100,0));
    Vehicle vehIn2(TRUCK, Position(100, 50));
    Vehicle vehOut(CAR, Position(100, 100));
    vehC->addVehicle(vehIn);//correct
    vehC->addVehicle(vehIn2);//shadowed by building
    vehC->addVehicle(vehOut);//not in zone
    Building building(Position(50,50));
    Building building2(Position(200, 500));
    camC->addBuilding(building);
    camC->addBuilding(building2);
    Position pos1(0, 0);
    Camera camera(pos1, 60, E);
    camC->addCamera(camera);
    camera.updateObservation();
    BOOST_CHECK_EQUAL(camera.getView().size(), 1);
    camC->deleteBuilding(building);
    camC->deleteBuilding(building2);
    camera.clearObservation();
    camera.updateObservation();
    BOOST_CHECK_EQUAL(camera.getView().size(), 2);
    vehC->clearController();
    camC->clearController();
}