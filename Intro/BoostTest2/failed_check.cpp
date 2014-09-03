#define BOOST_TEST_MODULE bad_test_suite

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(bad_test) {
    int answer = 1;
    
    BOOST_CHECK_EQUAL(4, answer);

    BOOST_CHECK_EQUAL(8, answer);

    BOOST_CHECK_EQUAL(12, answer);
}
