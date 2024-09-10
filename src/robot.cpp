/*=============================================================================*\
 File: robot.cpp
 Description: Implementations of the methods for Robot class.
\*=============================================================================*/

#include <iostream> 
#include <string>
#include <sstream>
#include <vector>
#include <ctype.h>

#include "robot.hpp"

using namespace std; 

/*=============================================================================*\
 setPlace - Assigns coordinate value for the ToyRobot properties.
\*=============================================================================*/
void Robot::setPlace(vector<string> coordinate, Robot& toy){
    if (!coordinate.empty()) {
        toy.inTable = true;
        toy.x = stoi(coordinate[0]);
        toy.y = stoi(coordinate[1]);
        toy.direction = coordinate[2];
    }
}

/*=============================================================================*\
 moveForward - Changes the location of the ToyRobot depending on current
 coordinate position and direction.
\*=============================================================================*/
void Robot::moveForward(Robot& toy){

    if(!toy.inTable){
            throw invalid_argument("Place ToyRobot in the table first!");
    }

    // Get the Max Position of both TableX and TableY constant array.
    int maxPosX, maxPosY, curX, curY;
    maxPosX = stoi(tableX.back());
    maxPosY = stoi(tableY.back());
    curX = toy.x;
    curY = toy.y;

    if(toy.direction == "NORTH"){
        if(toy.y < maxPosY) toy.y += 1; 
    } else if(toy.direction == "SOUTH"){
        if(toy.y > 0) toy.y -= 1;
    } else if(toy.direction == "EAST"){
        if(toy.x < maxPosX) toy.x += 1;
    } else if(toy.direction == "WEST"){
        if(toy.x > 0) toy.x -= 1;
    }

    // Check if ToyRobot position is unchanged, if yes throw exception.
    if(curX == toy.x && curY == toy.y){
        throw invalid_argument("ToyRobot refuses to move forward from the edge of the table!");
    }
}

/*=============================================================================*\
 faceRight - Changes the direction of the ToyRobot by facing right.
\*=============================================================================*/
void Robot::faceRight(Robot& toy){

    if(!toy.inTable){
        throw invalid_argument("Place ToyRobot in the table first!");
    }

    // Get the Last Direction of the Face constant array.
    string lastDir = face.back();
    auto it = find(face.begin(), face.end(), toy.direction); 
    int index = it - face.begin();

    // If the current Toy Direction is the Last Direction,
    // Then the iteration will restart from front.
    if(toy.direction == lastDir){
        toy.direction = face.front();
    } else {
        toy.direction = face[index+1];
    }
}

/*=============================================================================*\
 faceLeft - Changes the direction of the ToyRobot by facing left.
\*=============================================================================*/
void Robot::faceLeft(Robot& toy){

    if(!toy.inTable){
        throw invalid_argument("Place ToyRobot in the table first!");
    }

    // Get the First Direction of the Face constant array.
    string firstDir = face.front();
    auto it = find(face.begin(), face.end(), toy.direction); 
    int index = it - face.begin();

    // If the current Toy Direction is the First Direction,
    // Then the iteration will restart from back.
    if(toy.direction == firstDir){
        toy.direction = face.back();
    } else {
        toy.direction = face[index-1];
    }
}

/*=============================================================================*\
 getReport - If ToyRobot is currently in the table, this method will print the 
 current coordinate location of the ToyRobot.
\*=============================================================================*/
void Robot::getReport(Robot& toy){

    if(!toy.inTable){
            throw invalid_argument("Place ToyRobot in the table first!");
    } 

    cout << to_string(toy.x) << ", " + to_string(toy.y) << ", " + toy.direction << endl;
}

/*=============================================================================*\
 processComms - Checks command and calls the appropriate Robot functions.
 Will do nothing if the command is invalid.
\*=============================================================================*/
void Robot::processComms(string input, Robot& toy){
    string command;
    command = input.substr(0, input.find(" "));
    
    if (command == "PLACE"){ // Command for placing ToyRobot.
        // Calls the method that checks the validity of the PLACE input.
        vector<string> coordinate = toy.checkValidity(input); 
        toy.setPlace(coordinate,toy);
    } else if(command == "REPORT"){ // Command for reporting the ToyRobot current coordinate.
        toy.getReport(toy); 
    } else if(command == "MOVE"){ // Command for moving ToyRobot forward.
        toy.moveForward(toy);
    } else if(command == "RIGHT"){ // Command for rotating ToyRobot to face rightside.
        toy.faceRight(toy);
    } else if(command == "LEFT"){ // Command for rotating ToyRobot to face leftside.
        toy.faceLeft(toy);
    } else {
        throw invalid_argument("ToyRobot did not recognize the command!"); // Invalid command thow exception.
    }
}

/*=============================================================================*\
 isIn - Checks if the coordinate value is existing in the corresponding 
 constant [Table or Direction] array.
\*=============================================================================*/
template<typename T> bool isIn(T cVal, vector<T> values){
    return find(values.begin(), values.end(), cVal) != values.end();
}

/*=============================================================================*\
 checkValidity - Checks if the PLACE command input is valid for placing, 
 This method will return the coordinate location if valid otherwise it would 
 return empty.
\*=============================================================================*/
vector<string> Robot::checkValidity(string input){
    char checkComma = ',';
    int counter = 0;
    vector<string> empty;

    // Count the number of commas, if the result is not equal to 2 then the
    // input is not valid and would throw exeption and return empty.
    for (int i = 0; i < input.size(); i++){ 
        if (input[i] ==  checkComma){
            ++ counter;
        }
    }

    if(counter != 2){
        throw invalid_argument("ToyRobot did not recognize the coordinate!");
        return empty; 
    }

    string token; 
    vector<string> values; 
    
    // Removes the first 6 character of the input so that the only 
    // remaining characters are the coordinates values.
    input.erase(0, 6);
    stringstream ss(input);

    // Separate each coordinate values and passes it into a vector.
    int coordinateCounter = 0;
    while (getline(ss, token, ',')) {
        values.push_back(token);
        coordinateCounter++;
    }

    // Checks if there are 3 coordinate value pushed in <vector> values.
    // If not then throw exception and return empty.
    if(coordinateCounter != 3){
        throw invalid_argument("ToyRobot did not recognize the coordinate!");
        return empty; 
    }

    // Checks if X value exists in constant Table array, 
    // If not then throw exception and return empty.
    if(!isIn(values[0], tableX)){
        throw invalid_argument("ToyRobot did not recognize the X position!");
        return empty;
    } 

    // Checks if Y value exists in constant Table array,
    // If not then throw exception and return empty.
    if(!isIn(values[1], tableY)){
        throw invalid_argument("ToyRobot did not recognize the Y position!");
        return empty;
    } 

    // Checks if Direction value exists in constant Direction array,
    // If not then throw exception and return empty.
    if(!isIn(values[2], face)){
        throw invalid_argument("ToyRobot did not recognize the Direction!");
        return empty;
    }

    return values;
}