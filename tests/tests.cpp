#include "action.h"
#include "gtest/gtest.h"

#include <iostream>

using namespace std;
using namespace tstraus;

int main()
{
    Action<void()> action;

    action += [] { // add a function the the action
        cout << "asdf" << endl;
    };

    auto id = action += [] { // save the id so we can remove it at a later time
        cout << "fdsa" << endl;
    };

    action(); // execute the action

    cout << "---------" << endl;

    action -= id; // remove one of the functions we put in

    action(); // call the remaining functions

    return 0;
}