#define BOOST_TEST_MODULE CatTests

#include <boost/test/unit_test.hpp>
#include "GroundControl.hpp"
#define GTEST_LINKED_AS_SHARED_LIBRARY 1
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::AtLeast;


struct FakeClientBase {
    void MoveX(int v) {
    }
    void MoveY(int v) {
    }

    bool Crashed() {
        return false;
    }

    std::string Status() {
        return "";
    }

    int X() {
        return 0;
    }

    int Y() {
        return 0;
    }
};

struct FakeItClientBase {
    virtual void MoveX(int v) = 0;
    virtual void MoveY(int v) = 0;
    virtual bool Crashed() = 0;
    virtual void Refresh() = 0;
    virtual std::string Status() = 0;
    virtual int X() = 0;
    virtual int Y() = 0;
};


struct MockClient : public FakeItClientBase {
    MOCK_METHOD1(MoveX, void(int v));
    MOCK_METHOD1(MoveY, void(int v));
    MOCK_METHOD0(Crashed, bool());
    MOCK_METHOD0(Refresh, void());
    MOCK_METHOD0(Status, std::string());
    MOCK_METHOD0(X, int());
    MOCK_METHOD0(Y, int());
};

BOOST_AUTO_TEST_CASE(AssertNotCrashed_passes) {
    MockClient client;
    EXPECT_CALL(client, Refresh())
        .Times(AtLeast(1));

    Cat<decltype(client)> cat(client);
    //cat.AssertNotCrashed();
}

BOOST_AUTO_TEST_CASE(AssertNotCrashed_fails) {
    struct FakeClient : public FakeClientBase {
        bool Crashed() {
            return true;
        }
    } fake;
    Cat<decltype(fake)> cat(fake);
    try {
        cat.AssertNotCrashed();
    } catch(std::exception e) {
        BOOST_REQUIRE_EQUAL(e.what(), "Crashed!");
    }
}

BOOST_AUTO_TEST_CASE(MoveX) {
    struct FakeClient : public FakeClientBase {
        int x;

        bool Crashed() {
            return true;
        }
        int X() {
            return  x;
        }
    } fake;
    Cat<decltype(fake)> cat(fake);
    try {
        cat.AssertNotCrashed();
    } catch(std::exception e) {
        BOOST_REQUIRE_EQUAL(e.what(), "Crashed!");
    }


}
