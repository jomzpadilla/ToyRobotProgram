# ToyRobot

This application is a simulation of a toy robot moving on a square table top, of dimensions 5 units x 5 units. There are no other obstructions on the table surface. The robot is free to roam around the surface of the table, but must be prevented from falling to destruction. Any movement that would result in the robot falling from the table must be prevented, however further valid movement commands must still be allowed.

### Commands

- `PLACE` will put the toy robot on the table in position X,Y and facing NORTH, SOUTH, EAST or WEST.
- `MOVE`  will move the toy robot one unit forward in the direction it is currently facing.
- `LEFT` will rotate the robot towards left without changing the position of then robot.
- `RIGHT` will rotate the robot towards right without changing the position of then robot.
- `REPORT` will announce the X,Y and F of the robot.

## Compiling and Building

Make sure you have `CMake` installed in your system.

### Visual Studio Code
When using VSCode first you need to make sure you have the extensions `C/C++`, `CMake` and `CMake Tools` installed. These extensions should read the CMakeLists.txt files in this project and automatically creates you the necessary build system once you've open this project on your VSCode Explorer. After the build system were created you just need to manually build the project open a new terminal and run the executable file.

### x64 Command line
You can also build this project using a x64 cmd terminal.

```c++

// go to the ToyRobotProgram directory
cd ToyRobotProgram

// build the CMake build system
cmake -S . -B build

// build ToyRobot project
cmake --build build

```
This will automatically creates your executable file and unit testing.

## Running and Testing

```c++

// change into the created build directory
cd build

// run program (ToyRobot.exe)
.\Debug\ToyRobot.exe

// run ctest (ToyRobotTest)
ctest
// or for detailed information
ctest --verbose
// or run the test executable file
.\test\Debug\ToyRobotTest.exe


```
