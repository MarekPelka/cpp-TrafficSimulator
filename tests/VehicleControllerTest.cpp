#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(first_test)
{
  int i = 1;
  BOOST_TEST(i);
  BOOST_TEST(i == 2);
}

BOOST_AUTO_TEST_CASE(second_test)
{
	BOOST_CHECK_EQUAL(false, false);
}