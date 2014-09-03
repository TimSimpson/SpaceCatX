#define BOOST_TEST_MODULE bad_test_suite

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(bad_test) {
    const void * memory = ::operator new(1024);
}
