#include "action.h"
#include "lest.hpp"

using namespace std;
using namespace tstraus;

const lest::test t[] =
{
    // fixture for most tests
    CASE("BasicTests" "[tstraus::Action]")
    {
        SETUP("Set up an Action")
        {
            int x = 0;
            Action<void()> action;

            action += [&] {
                x += 1;
            };

            // make sure the function added in the fixture is called
            SECTION("Add Member Operator")
            {
                action();

                EXPECT(x == 1);
            }

            // verify multiple functions are called
            SECTION("Mutiple Functions")
            {
                action += [&] {
                    x += 2;
                };

                action();

                EXPECT(x == 3);
            }

            // remove a function when provided the id
            SECTION("Remove Member Operator")
            {
                auto id = action += [&] {
                    x += 4;
                };

                action -= id;

                action();

                EXPECT(x == 1);
            }

            // set the action with only one function
            SECTION("Make Only Operator")
            {
                action = [&] {
                    x += 4;
                };

                action();

                EXPECT(x == 4);
            }

            // clear the action
            SECTION("Clear")
            {
                action.clear();

                action();

                EXPECT(x == 0);
            }

            // combine together
            SECTION("Combine")
            {
                Action<void()> a, b;

                a += [&] {
                    x += 1;
                };

                b += [&] {
                    x += 2;
                };

                auto c = a + b;
                c();

                EXPECT(x == 3);
            }
        }
    },

    // be sure that arguments are passed through
    CASE("String Action" "[tstraus::Action]")
    {
        string s = "";

        Action<void(string)> action;

        action += [&](string input) {
            s = input;
        };

        action("asdf");

        EXPECT(s == "asdf");
    }
};

// run with '-p' to see each test
int main(int argc, char** argv)
{
    return lest::run(t, argc, argv);
}
