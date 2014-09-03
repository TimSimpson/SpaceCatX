#define BOOST_TEST_MODULE CatFakeItTests

#include <boost/test/unit_test.hpp>
#include "GroundControl.hpp"
#include <fakeit.hpp>

struct FakeItClientBase {
    virtual void MoveX(int v) = 0;
    virtual void MoveY(int v) = 0;
    virtual bool Crashed() = 0;
    virtual void Refresh() = 0;
    virtual std::string Status() = 0;
    virtual int X() = 0;
    virtual int Y() = 0;
};

BOOST_AUTO_TEST_CASE(AssertNotCrashed_passes_2) {
    using namespace fakeit;
    Mock<FakeItClientBase> mock;
    When(Method(mock, Refresh)).Return();
    When(Method(mock, Crashed)).Return(false);
    FakeItClientBase & m = mock.get();
    Cat<decltype(m)> cat(m);
    cat.AssertNotCrashed();
}
