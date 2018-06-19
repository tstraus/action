#include "action.h"
#include "gtest/gtest.h"

#include <iostream>

using namespace std;
using namespace tstraus;

// setup the test fixture
class ActionTests : public testing::Test
{
protected:
    virtual void SetUp()
    {
        x = 0;

        action += [&] {
            x += 1;
        };
    }

    virtual void TearDown()
    {
        action.clear();
    }

    Action<void()> action;

    int x;
};

// make sure the function added in the fixture is called
TEST_F(ActionTests, AddMemberOperator)
{
    action();

    EXPECT_EQ(1, x);
    EXPECT_NE(0, x);
}

// verify multiple functions are called
TEST_F(ActionTests, MutipleFunctions)
{
    action += [&] {
        x += 2;
    };

    action();

    EXPECT_EQ(3, x);
    EXPECT_NE(1, x);
}

// remove a function when provided the id
TEST_F(ActionTests, RemoveMemberOperator)
{
    auto id = action += [&] {
        x += 4;
    };

    action -= id;

    action();

    EXPECT_EQ(1, x);
    EXPECT_NE(5, x);
}

// set the action with only one function
TEST_F(ActionTests, MakeOnlyOperator)
{
    action = [&] {
        x += 4;
    };

    action();

    EXPECT_EQ(4, x);
    EXPECT_NE(1, x);
    EXPECT_NE(5, x);
}

// clear the action
TEST_F(ActionTests, Clear)
{
    action.clear();

    action();

    EXPECT_EQ(0, x);
    EXPECT_NE(1, x);
}

// non fixture tests
// be sure the action gives arguments
TEST(OtherActionTests, StringAction)
{
    string s = "";

    Action<void(string)> action;

    action += [&] (string input) {
        s = input;
    };

    action("asdf");

    EXPECT_EQ("asdf", s);
    EXPECT_NE("", s);
}