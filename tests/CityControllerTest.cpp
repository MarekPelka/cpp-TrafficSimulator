#define BOOST_TEST_MODULE Tests
#include "../src/models/Node.h"
#include "../src/models/Street.h"
#include "../src/models/Position.h"
#include "../src/viewmodels/CityController.h"
#include "../src/models/Node.cpp"
#include "../src/models/Street.cpp"
#include "../src/models/Position.cpp"
#include "../src/viewmodels/CityController.cpp"
#include "../src/Enums.h"
#include <list>
#include <memory>

#include <boost/test/included/unit_test.hpp>

typedef std::shared_ptr<Node> PNode;
typedef std::shared_ptr<Street> PStreet;

#define private public
#define protected public

BOOST_AUTO_TEST_CASE(Test_isIntervalX) {
	PNode s = std::make_shared<Node>(Position(100, 100));
	PNode e = std::make_shared<Node>(Position(500, 500));
	PStreet street = std::make_shared<Street>(s, e);
	BOOST_CHECK_EQUAL(CityController::isInIntervalX(Position(100, 100), street), true);
	BOOST_CHECK_EQUAL(CityController::isInIntervalX(Position(250, 250), street), true);
	BOOST_CHECK_EQUAL(CityController::isInIntervalX(Position(500, 500), street), true);
	BOOST_CHECK_EQUAL(CityController::isInIntervalX(Position(99, 99), street), false);
	BOOST_CHECK_EQUAL(CityController::isInIntervalX(Position(501, 501), street), false);
}

BOOST_AUTO_TEST_CASE(Test_isIntervalY) {
    PNode s = std::make_shared<Node>(Position(100, 100));
    PNode e = std::make_shared<Node>(Position(500, 500));
    PStreet street = std::make_shared<Street>(s, e);
	BOOST_CHECK_EQUAL(CityController::isInIntervalY(Position(100, 100), street), true);
	BOOST_CHECK_EQUAL(CityController::isInIntervalY(Position(250, 250), street), true);
	BOOST_CHECK_EQUAL(CityController::isInIntervalY(Position(500, 500), street), true);
	BOOST_CHECK_EQUAL(CityController::isInIntervalY(Position(99, 99), street), false);
	BOOST_CHECK_EQUAL(CityController::isInIntervalY(Position(501, 501), street), false);
}

BOOST_AUTO_TEST_CASE(Test_addSingleStreet) {
	CityController *cityC = CityController::getInstance();
	Position p1(100, 100);
	Position p2(500, 100);

	if (!cityC->addStreet(p1, p2)) throw "Error creating street!";

	auto list = cityC->getStreets();
	BOOST_REQUIRE(list.size() == 1);
	BOOST_CHECK(list.front()->getLength() == 400);
	BOOST_CHECK(list.front()->getDirection() == E);
	BOOST_CHECK(list.front()->getStartEndPositions().first == p1);
	BOOST_CHECK(list.front()->getStartEndPositions().second == p2);
    cityC->clearController();
}

BOOST_AUTO_TEST_CASE(Test_addMultiStreet) {
	CityController *cityC = CityController::getInstance();
	Position p1(100, 100);
	Position p2(500, 100);
	Position p3(500, 500);
	Position p4(100, 500);

	cityC->addStreet(p1, p2);
	cityC->addStreet(p2, p3);
	cityC->addStreet(p3, p4);
	cityC->addStreet(p4, p1);

	cityC->addStreet(p2, p1);
	cityC->addStreet(p3, p2);
	cityC->addStreet(p4, p3);
	cityC->addStreet(p1, p4);

	auto list = cityC->getStreets();
	BOOST_REQUIRE(list.size() == 8);
	BOOST_CHECK(cityC->getNodes().size() == 4);
    cityC->clearController();
}

BOOST_AUTO_TEST_CASE(Test_streetCrossing) {
	CityController *cityC = CityController::getInstance();
	//Crossing
	Position pc3(300, 50);
	Position pc4(300, 550);
	cityC->addStreet(pc3, pc4);
	Position pc1(50, 300);
	Position pc2(550, 300);
	cityC->addStreet(pc1, pc2);

	BOOST_REQUIRE(cityC->getStreets().size() == 4);
	BOOST_CHECK(cityC->getNodes().size() == 5);
    cityC->clearController();
}

BOOST_AUTO_TEST_CASE(Test_city) {
	CityController *cityC = CityController::getInstance();
	Position p1(100, 100);
	Position p2(500, 100);
	Position p3(500, 500);
	Position p4(100, 500);

	cityC->addStreet(p1, p2);
	cityC->addStreet(p2, p3);
	cityC->addStreet(p3, p4);
	cityC->addStreet(p4, p1);

	cityC->addStreet(p2, p1);
	cityC->addStreet(p3, p2);
	cityC->addStreet(p4, p3);
	cityC->addStreet(p1, p4);
	//Crossing
	Position pc3(300, 50);
	Position pc4(300, 550);
	cityC->addStreet(pc3, pc4);
	Position pc1(50, 300);
	Position pc2(550, 300);
	cityC->addStreet(pc1, pc2);

	auto list = cityC->getStreets();
	BOOST_REQUIRE(list.size() == 24);
	BOOST_CHECK(cityC->getNodes().size() == 13);
    cityC->clearController();
}

BOOST_AUTO_TEST_CASE(Test_streetOverlap) {
	CityController *cityC = CityController::getInstance();
	Position p1(100, 100);
	Position p2(500, 100);
	Position p3(700, 100);
	if (!cityC->addStreet(p1, p2)) throw "Error creating street!";

	auto list = cityC->getStreets();
	BOOST_REQUIRE(list.size() == 1);
	BOOST_CHECK(cityC->isStreetsOverlap(Position(300, 100), p3));
    cityC->clearController();
}

BOOST_AUTO_TEST_CASE(Test_streetCross) {
	CityController *cityC = CityController::getInstance();
	Position p1(100, 100);
	Position p2(500, 100);

	if (!cityC->addStreet(p1, p2)) throw "Error creating street!";

	auto list = cityC->getStreets();
	BOOST_REQUIRE(list.size() == 1);
	BOOST_CHECK(!cityC->isStreetsCross(Position(300, 50), Position(300, 150)).empty());
    cityC->clearController();
}

BOOST_AUTO_TEST_CASE(Test_BFS) {
    //TODO
	BOOST_CHECK_EQUAL(true, true);
}