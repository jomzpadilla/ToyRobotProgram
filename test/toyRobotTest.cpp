#include <gtest/gtest.h>
#include "../src/robot.hpp"
#include <vector>

TEST(ToyRobotTestUnit, testPLACE){
    Robot toy;
    vector<string> input = {"PLACE 0,0,NORTH"};
    for(auto command : input){
        toy.processComms(command, toy);
    }
    
    EXPECT_TRUE(toy.inTable);
    EXPECT_EQ(toy.x, 0);
    EXPECT_EQ(toy.y, 0);
    EXPECT_EQ(toy.direction, "NORTH");
}

TEST(ToyRobotTestUnit, testMOVE){
    Robot toy;
    vector<string> input = {"PLACE 0,0,NORTH","MOVE"};
    for(auto command : input){
        toy.processComms(command, toy);
    }
    
    EXPECT_TRUE(toy.inTable);
    EXPECT_EQ(toy.x, 0);
    EXPECT_EQ(toy.y, 1);
    EXPECT_EQ(toy.direction, "NORTH");
}

TEST(ToyRobotTestUnit, testRIGHT){
    Robot toy;
    vector<string> input = {"PLACE 0,0,NORTH","RIGHT"};
    for(auto command : input){
        toy.processComms(command, toy);
    }
    
    EXPECT_TRUE(toy.inTable);
    EXPECT_EQ(toy.x, 0);
    EXPECT_EQ(toy.y, 0);
    EXPECT_EQ(toy.direction, "EAST");
}

TEST(ToyRobotTestUnit, testLEFT){
    Robot toy;
    vector<string> input = {"PLACE 0,0,NORTH","LEFT"};
    for(auto command : input){
        toy.processComms(command, toy);
    }
    
    EXPECT_TRUE(toy.inTable);
    EXPECT_EQ(toy.x, 0);
    EXPECT_EQ(toy.y, 0);
    EXPECT_EQ(toy.direction, "WEST");
}

TEST(ToyRobotTestUnit, testREPORT){
    Robot toy;
    vector<string> input = {"PLACE 0,0,NORTH","REPORT"};
    for(auto command : input){
        toy.processComms(command, toy);
    }
    
    EXPECT_TRUE(toy.inTable);
    EXPECT_EQ(toy.x, 0);
    EXPECT_EQ(toy.y, 0);
    EXPECT_EQ(toy.direction, "NORTH");
}

TEST(ToyRobotTestIntegration, testExample1){
    Robot toy;
    vector<string> input = {"PLACE 0,0,NORTH","MOVE","REPORT"};
    for(auto command : input){
        toy.processComms(command, toy);
    }
    
    EXPECT_TRUE(toy.inTable);
    EXPECT_EQ(toy.x, 0);
    EXPECT_EQ(toy.y, 1);
    EXPECT_EQ(toy.direction, "NORTH");
}

TEST(ToyRobotTestIntegration, testExample2){
    Robot toy;
    vector<string> input = {"PLACE 0,0,NORTH","LEFT","REPORT"};
    for(auto command : input){
        toy.processComms(command, toy);
    }
    
    EXPECT_TRUE(toy.inTable);
    EXPECT_EQ(toy.x, 0);
    EXPECT_EQ(toy.y, 0);
    EXPECT_EQ(toy.direction, "WEST");
}

TEST(ToyRobotTestIntegration, testExample3){
    Robot toy;
    vector<string> input = {"PLACE 1,2,EAST","MOVE","MOVE","LEFT","MOVE","REPORT"};
    for(auto command : input){
        toy.processComms(command, toy);
    }
    
    EXPECT_TRUE(toy.inTable);
    EXPECT_EQ(toy.x, 3);
    EXPECT_EQ(toy.y, 3);
    EXPECT_EQ(toy.direction, "NORTH");
}

TEST(ToyRobotTestNegative, testInvalidInput){
    Robot toy;
    vector<string> input = {"HELLOWORLD","foobar","12345","1.1","-1"," ","-",""};
    for(auto command : input){
        EXPECT_THROW(toy.processComms(command, toy), invalid_argument);
    }
}

TEST(ToyRobotTestNegative, testInvalidCoordinate){
    Robot toy;
    vector<string> input = {"PLACE INVALID","PLACE 12345","PLACE ,,,","PLACE hello,world","-1","PLACE 0 0 NORTH","PLACE 0-0-NORTH"};
    for(auto command : input){
        EXPECT_THROW(toy.processComms(command, toy), invalid_argument);
    }
}

TEST(ToyRobotTestNegative, testInvalidXPosition){
    Robot toy;
    vector<string> input = {"PLACE INVALID,0,NORTH","PLACE 11,0,NORTH","PLACE -1,0,NORTH","PLACE 1.1,0,NORTH","PLACE ,0,NORTH"};
    for(auto command : input){
        EXPECT_THROW(toy.processComms(command, toy), invalid_argument);
    }
}

TEST(ToyRobotTestNegative, testInvalidYPosition){
    Robot toy;
    vector<string> input = {"PLACE 0,INVALID,NORTH","PLACE 0,11,NORTH","PLACE 0,-1,NORTH","PLACE 0,1.1,NORTH","PLACE 0,,NORTH"};
    for(auto command : input){
        EXPECT_THROW(toy.processComms(command, toy), invalid_argument);
    }
}

TEST(ToyRobotTestNegative, testInvalidFacePosition){
    Robot toy;
    vector<string> input = {"PLACE 0,0,INVALID","PLACE 0,0,NORTHNORTH","PLACE 0,0,NORT","PLACE 0,0,0","PLACE 0,0,"};
    for(auto command : input){
        EXPECT_THROW(toy.processComms(command, toy), invalid_argument);
    }
}   

TEST(ToyRobotTestNegative, testCommandBeforePlace){
    Robot toy;
    vector<string> input = {"REPORT","MOVE","RIGHT","LEFT"};
    for(auto command : input){
        EXPECT_THROW(toy.processComms(command, toy), invalid_argument);
    }
}

TEST(ToyRobotTestNegative, testMoveWhileOnEdgeNorth){
    Robot toy;
    toy.processComms("PLACE 0,4,NORTH", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);

    toy.processComms("PLACE 1,4,NORTH", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);

    toy.processComms("PLACE 2,4,NORTH", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);

    toy.processComms("PLACE 3,4,NORTH", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);

    toy.processComms("PLACE 4,4,NORTH", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);
}

TEST(ToyRobotTestNegative, testMoveWhileOnEdgeEAST){
    Robot toy;

    toy.processComms("PLACE 4,0,EAST", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);
    
    toy.processComms("PLACE 4,1,EAST", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);

    toy.processComms("PLACE 4,2,EAST", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);

    toy.processComms("PLACE 4,3,EAST", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);

    toy.processComms("PLACE 4,4,EAST", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);
}

TEST(ToyRobotTestNegative, testMoveWhileOnEdgeSOUTH){
    Robot toy;

    toy.processComms("PLACE 0,0,SOUTH", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);
    
    toy.processComms("PLACE 1,0,SOUTH", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);

    toy.processComms("PLACE 2,0,SOUTH", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);

    toy.processComms("PLACE 3,0,SOUTH", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);

    toy.processComms("PLACE 4,0,SOUTH", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);
}

TEST(ToyRobotTestNegative, testMoveWhileOnEdgeWEST){
    Robot toy;

    toy.processComms("PLACE 0,0,WEST", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);
    
    toy.processComms("PLACE 0,1,WEST", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);

    toy.processComms("PLACE 0,2,WEST", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);

    toy.processComms("PLACE 0,3,WEST", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);

    toy.processComms("PLACE 0,4,WEST", toy);
    EXPECT_THROW(toy.processComms("MOVE", toy), invalid_argument);
}


