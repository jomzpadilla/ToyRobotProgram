/*=============================================================================*\
 File: toyRobot.cpp
 Description: contains the main method responsible for reading inputs and 
 distinguishing which command should be called based on it.
\*=============================================================================*/

using namespace std;
#include <iostream>
#include <sstream>

#include "robot.hpp"

int main() 
{ 
    cout << "------------------ToyRobot------------------" << endl; 
    cout << "|Use the following commands:               |" << endl; 
    cout << "|PLACE: Place ToyRobot in given coordinate.|" << endl; 
    cout << "|MOVE: Moves ToyRobot one unit forward.    |" << endl; 
    cout << "|LEFT: Rotates ToyRobot towards left.      |" << endl; 
    cout << "|RIGHT: Rotates ToyRobot towards right.    |" << endl; 
    cout << "|REPORT: Prints ToyRobot current location. |" << endl; 
    cout << "--------------------------------------------" << endl;

    string str; 
    Robot toy;

    while (getline(cin, str)){
        try {
            if(str == "EXIT"){ // Command for exiting the program.
                break;
            } else { // Proceeds on distinguishing which command should be called.
                toy.processComms(str, toy);
            }
        } catch (invalid_argument& err) {
            cerr << err.what() << endl;
        }
    }
    return 0;
}

