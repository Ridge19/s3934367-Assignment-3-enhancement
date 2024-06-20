#include <iostream>
#include <limits> // Include the <limits> header file

#include <mcpp/mcpp.h>
#include <cstdlib> // Include the <cstdlib> header file
#include <string_view>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"
//maze testing mode 
#include "testmode.h"
// maze generation 
#include "GenerateMaze.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

#define NORMAL_MODE 0
#define TESTING_MODE 1

enum States
{
    ST_Main,      // main state
    ST_GetMaze,   // create maze
    ST_BuildMaze, // build maze in minecraft
    ST_SolveMaze, // solve maze
    ST_Creators,  // show team info
    ST_Exit       // exit
};

TestMode::TestMode()
{
    // constructor
    // Seed the random number generator
    std::srand(std::time(nullptr));
}
/*
* This Function will be use to get the users base point dependent on the mode
* The input is when the user is prompted to navigate to the their basepoint and is to type out
* 'done'.
*/
mcpp::Coordinate getBasePoint(std::string mode, std::string input)
{
    // create a connection to Minecraft
    mcpp::MinecraftConnection mc;
    //This is where the return coordinate will be returned to.
    mcpp::Coordinate rtnCoord;

    //Initialized the Mode to 0. This is where we will take the string mode to convert it to an acceptable form.
    int intMode = 0;

    //checking the taken string
    if (mode == "-testmode")
    {
        intMode = TESTING_MODE;
    }
    else if (mode.empty())
    {
        intMode = NORMAL_MODE;
    }
    else
    {
        //error
        std::cout << "No mode of maze runner has been specified" << std::endl;
        mcpp::Coordinate tempCoord(0, 0, 0);
    }

    //based on the mode, generate the base point. 
    if (intMode == NORMAL_MODE)
    {
        //checking the input and setting the base point
        if (input == "done")
        {
            rtnCoord = mc.getPlayerPosition();
        }
        else
        {
            //if the basepoint is not 'done'
            std::cout << "Error: At this stage the only accepted input is 'done', please try again" << std::endl;
            mcpp::Coordinate tempCoord(0, 0, 0);
            rtnCoord = tempCoord;
        }
    }
    else if (intMode == TESTING_MODE)
    {
        //the basepoint for testing mode will always be 4848, 71, 4369
        mcpp::Coordinate tempCoord(4848, 71, 4369);
        mc.setPlayerPosition(tempCoord);
        rtnCoord = tempCoord;
    }
    else
    {
        //error
        std::cerr << "Invalid mode! Exiting." << std::endl;
        exit(EXIT_FAILURE);
    }

    //returning a Coordinate back in the form of x, y, z .
    return rtnCoord;
}

int main(int argc, char **argv)
{

    mcpp::MinecraftConnection mc; // create a connection to Minecraft

    // mc.getPlayerPosition();

    // Agent *agent;

    void printStartText();
    void printMainMenu();
    void printGenerateMazeMenu();
    void printSolveMazeMenu();
    void printTeamInfo();

    void printExitMessage();

    bool mode = NORMAL_MODE;

    std::string input;

    // int size_Z = 0, size_X = 0;

    if (argc > 1 && string(argv[1]) == "-testmode")
    {
        mode = TESTING_MODE;
        std::cout << "Testing mode" << endl;
        mc.postToChat("Testing mode enabled - you are in testing mode");
        mc.setPlayerPosition(mcpp::Coordinate(4848, 71, 4369));
        mc.postToChat("player position set to (4848, 71, 4369)");

        //TESTING MODE IMPLEMENTATION
        int rows, columns;
        std::cout << "Enter the number of rows: ";
        std::cin >> rows;
        std::cout << "Enter the number of columns: ";
        std::cin >> columns;

        if (rows < 3 || columns < 3) {
            std::cout << "Maze dimensions must be at least 3x3." << std::endl;
            return 1;
        }

        TestMode testing;
        testing.GenerateMazeTest(rows, columns);

    }
    else if (argc > 1 && string(argv[1]) != "-testmode")
    {
        mc.postToChat("error! invalid flag!");
        mc.postToChat("please use -testing flag to enable testing mode");
        return EXIT_SUCCESS;
    }
    else
    {
        mc.postToChat("Welcome to MazeRunner!");
        mc.postToChat("normal mode"); 
    }

    cout << "mode selected: " << mode << endl;
    States curState = ST_Main;

    printMainMenu();



    // State machine for menu
    while (curState != ST_Exit)
    {
    
        // command seen in demo video 
        mc.doCommand("time set day"); 

        // command added cause no one likes rain
        mc.doCommand("weather clear");

        // Do something
        int MainMenuChoice;

        while (!(cin >> MainMenuChoice)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input, must be an integer. Please try again";
            printMainMenu();
        }

        if (MainMenuChoice == 1) // create a maze
        {
            // generate maze menu
            curState = ST_GetMaze;
            printGenerateMazeMenu();
            int GenerateMazeChoice;
            cin >> GenerateMazeChoice;

            if (GenerateMazeChoice == 1)
            {   
                // TODO: read maze from terminal

                if (input == "done"){
                    getBasePoint(argv[1], input);
                }else{
                    std::cout << "Error: The only accepted inout in this section is 'done', please try again" << std::endl;
                }

                //TO DO:
                //When getting the size of the perfect maze please place the length and width into the defined size_X and size_Z
            }
            else if (GenerateMazeChoice == 2)
            {
                std::string status;
                cout << "in minecraft, navigate to where you need the maze\n to be built in Minecraft and type - done in terminal" << endl;
                cin >> status;
                if (status == "done") {
                    // User input is "done"
                    // Perform the desired action
                    mcpp::Coordinate basePoint = mc.getPlayerPosition();
                    unsigned int xlen, zlen;
                    cout << "Enter the length and width of maze: " << endl;
                    cin >> xlen >> zlen;
                    cout << "maze generated successfully" << endl;
            
                    // Declare or define the 'checkMaze' function before using it
                    GenerateMaze myMaze;

                    myMaze.checkMaze(xlen, zlen);

                    if (xlen < 3 || zlen < 3) {
                        mc.postToChat("maze generation failed! cannot be smaller than 3");
                    } else if (myMaze.checkMaze(xlen, zlen)) {
                        cout << "**Printing Maze**" << endl;

                        // testing - output to terminal
                        basePoint = mcpp::Coordinate(mc.getPlayerPosition());
                        std::cout << "BasePoint: " << basePoint << std::endl; 

                        myMaze.PrintMaze(xlen, zlen);
                        // 0, x-length, 0, z-length 
                        // where xlen and zlen are inputted by the user 

                        printMainMenu();
                    }
                } else {
                    // User input is not "done"
                    // Handle the case accordingly
                    cout << "command not recognised" << endl;
                    printGenerateMazeMenu();
                }
                
            }
            else if (GenerateMazeChoice == 3)
            {
                // back
                cout << "going back to main menu!" << endl;
                printMainMenu();
            }
            else
            {
                cout << "Invalid MainMenuChoice! number must be between 1 and 3!" << endl;
                printGenerateMazeMenu();
            }
        }
        else if (MainMenuChoice == 2)
        {
            // solve maze
            curState = ST_BuildMaze;
            printGenerateMazeMenu();
            curState = ST_Main;
        }
        else if (MainMenuChoice == 3)
        {
            // team info
            curState = ST_SolveMaze;
            printGenerateMazeMenu();
        }
        else if (MainMenuChoice == 4)
        {
            curState = ST_Creators;
            printTeamInfo();
        }
        else if (MainMenuChoice == 5)
        {
            curState = ST_Exit;
            printExitMassage();
        }
        else
        {
            cout << "Invalid MainMenuChoice! number must be between 1 and 5!" << endl;
            printMainMenu();
        }
    }

    return EXIT_SUCCESS;
}
