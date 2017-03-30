#include "stdafx.h"
#include "../TrafficSimulator/Node.h"
#include "../TrafficSimulator/Street.h"
#include "../TrafficSimulator/Position.h"
#include "../TrafficSimulator/CityController.h"
#include "../TrafficSimulator/Node.cpp"
#include "../TrafficSimulator/Street.cpp"
#include "../TrafficSimulator/Position.cpp"
#include "../TrafficSimulator/CityController.cpp"
#include "../TrafficSimulator/Enums.h"
#include <list>

#include <boost/test/unit_test.hpp>

/*
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
*/

#define private public
#define protected public

BOOST_AUTO_TEST_CASE(Test_isIntervalX) {
	// TODO: Your test code here
	Node s(Position(100, 100));
	Node e(Position(500, 500));
	Street street(&s, &e);
	BOOST_CHECK_EQUAL(CityController::isInIntervalX(Position(100, 100), &street), true);
	BOOST_CHECK_EQUAL(CityController::isInIntervalX(Position(250, 250), &street), true);
	BOOST_CHECK_EQUAL(CityController::isInIntervalX(Position(500, 500), &street), true);
	BOOST_CHECK_EQUAL(CityController::isInIntervalX(Position(99, 99), &street), false);
	BOOST_CHECK_EQUAL(CityController::isInIntervalX(Position(501, 501), &street), false);
}

BOOST_AUTO_TEST_CASE(Test_isIntervalY) {
	// TODO: Your test code here
	Node s(Position(100, 100));
	Node e(Position(500, 500));
	Street street(&s, &e);
	BOOST_CHECK_EQUAL(CityController::isInIntervalY(Position(100, 100), &street), true);
	BOOST_CHECK_EQUAL(CityController::isInIntervalY(Position(250, 250), &street), true);
	BOOST_CHECK_EQUAL(CityController::isInIntervalY(Position(500, 500), &street), true);
	BOOST_CHECK_EQUAL(CityController::isInIntervalY(Position(99, 99), &street), false);
	BOOST_CHECK_EQUAL(CityController::isInIntervalY(Position(501, 501), &street), false);
}

BOOST_AUTO_TEST_CASE(Test_addStreet) {
	// TODO: Your test code here
	CityController *cityC = CityController::getInstance();
	Position p1(100, 100);
	Position p2(500, 100);

	/*if (add(2, 2) != 4)
		BOOST_ERROR("Ouch...");*/
	//if (!cityC->addStreet(p1, p2)) throw "Error creating street!";

	auto list = cityC->getStreets();
	BOOST_REQUIRE(list.size() == 1);
	BOOST_CHECK(list.front()->getLength() == 400);
	BOOST_CHECK(list.front()->getDirection() == E);
	BOOST_CHECK(list.front()->getStartEndPositions().first == p1);
	BOOST_CHECK(list.front()->getStartEndPositions().second == p2);
}
