/*=============================================================================*\
 File: robot.cpp

 Description: Definition of the properties and methods for Robot class.
              Definition of global constants.
\*=============================================================================*/

#if !defined (ROBOT_HPP)
#define ROBOT_HPP

using namespace std;
#include <vector>

// Global constable for Table and Direction array.
const vector<string> tableX = {"0","1","2","3","4"};
const vector<string> tableY = {"0","1","2","3","4"}; 
const vector<string> face = {"NORTH","EAST","SOUTH","WEST"};

class Robot {
    public:
        int x,y;
        string direction;
        bool inTable = false;
        void setPlace(vector<string> coordinate, Robot& toy);
        void moveForward(Robot& toy);
        void faceRight(Robot& toy);
        void faceLeft(Robot& toy);
        void getReport(Robot& toy);
        void processComms(string input, Robot& toy);
        vector<string> checkValidity(string input);
};

#endif