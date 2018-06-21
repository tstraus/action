#include "action.h"
#include "lest.hpp"

#include <iostream>

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
				EXPECT_NOT(x == 0);
            }

			// verify multiple functions are called
            SECTION("Mutiple Functions")
            {
                action += [&] {
                    x += 2;
                };

                action();

                EXPECT(x == 3);
				EXPECT_NOT(x == 1);
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
				EXPECT_NOT(x == 5);
			}

			// set the action with only one function
			SECTION("Make Only Operator")
			{
				action = [&] {
					x += 4;
				};

				action();

				EXPECT(x == 4);
				EXPECT_NOT(x == 1);
				EXPECT_NOT(x == 5);
			}

			// clear the action
			SECTION("Clear")
			{
				action.clear();

				action();

				EXPECT(x == 0);
				EXPECT_NOT(x == 1);
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
		EXPECT_NOT(s == "");
	}
};

// run with '-p' to see each test
int main(int argc, char** argv)
{
	return lest::run(t, argc, argv);
}
