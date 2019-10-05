/****************************************************
**Sarkis Grigorian
**CS 162 - Project 1
**Date: 4/14/19
**NOTE: This project contains the extra credit random
**ant location.
**Description: This is the functions for the antGame.
**It will collect information about board size, ant
**location and number of moves. It will then create
**a board and run the simulation for the user.
****************************************************/


#include <iostream>
#include<stdlib.h>
#include<time.h>
#include<string>
#include "langtonsant.hpp"


using std::cout;
using std::string;
using std::endl;
using std::cin;

antGame::antGame()
{
    cout << endl << "**************************************************************" << endl;
    cout << "This assignment includes the extra credit random generator." << endl;
    cout << "**************************************************************" << endl << endl;
    countMoves = 0;
    menuRepeat = 0;
}


//CITATION: http://www.cplusplus.com/forum/beginner/149229/
void antGame::menu()
{
    int userChoice;

    //if game has been run already, it will ask to repeat or quit game.
    if (menuRepeat > 0)
    {
        countMoves = 0;
        cout << "Would you like to play again?\n";
        cout << "1. Play Again" << endl << "2. Quit" << endl;
    }

    //if game has not been run, it will ask to play game or quit.
    else
    {
    cout << "What would you like to do: \n";
    cout << "1. Start Langton's Ant Simulation" << endl << "2. Quit" << endl;
    }

    cin >> userChoice;


    //verifies user input is an integer & choice of 1 or 2.
    while(cin.fail() || (userChoice < 1 || userChoice > 2))
        {
            cout << "Error. Type '1' to play Langston Ant Simulation or '2' to quit program. \n";
            cin.clear();
            cin.ignore(100, '\n');
            cin >> userChoice;
        }


        //user choice either starts the game, or quits
       switch (userChoice)
        {
        case 1:
            boardInput();
            menuRepeat += 1;
            menu();
            break;
        case 2:
            cout << endl << "Exiting..." << endl;
            exit(0);
            break;
        }
}


//CITATION: https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
//CITATION: https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
void antGame::boardInput()
{
        int random1, r, c, aR, aC, movesNum;

        //collects number of rows from user + input validation
        cout << "How many rows would you like for the board? \n";
        cin >> r;
            while (cin.fail() || (r < 2))
            {
                cout << "Error. Enter an integer greater than or equal to 2 for rows: \n";
                cin.clear();
                cin.ignore(100, '\n');
                cin >> r;
            }

        //collects number of columns from user + input validation
        cout << "How many columns? \n";
        cin >> c;

            while (cin.fail() || (c < 2))
            {
                cout << "Error. Enter an integer greater than or equal to 2 for columns: \n";
                cin.clear();
                cin.ignore(100, '\n');
                cin >> c;

            }

        //asks user if they would like to randomly generate ants location or input a custom location.
        cout << endl << "Pick an option below for the ant's starting location \n";
        cout << "1. Random " << endl << "2. Custom\n" << endl;

        cin >> random1;

        while(cin.fail() || (random1 < 1 || random1 > 2))
            {
            cout << "Error. Type '1' for random or '2' for custom. \n";
            cin.clear();
            cin.ignore(100, '\n');
            cin >> random1;
            }

        //randomly generates coordinates for the ant.
        if (random1 == 1)
        {
            srand(time(0));

            aR = (rand() % r) + 1;
            aC = (rand() % c) + 1;
        }

        //allows user to input custom coordinates.
        else if (random1 == 2)
        {
        cout << "Where would you like to set the ant down? \n";
        cout << "Enter a row from 1 to " << r << endl;
        cin >> aR;

            while (cin.fail() || (aR < 1 || aR > r))
            {
                cout << "Error. Please enter an integer from 1 to " << r << endl;;
                cin.clear();
                cin.ignore(100, '\n');
                cin >> aR;
            }

        cout << "Enter a column from 1 to " << c << endl;
        cin >> aC;

            while (cin.fail() || (aC< 1 || aC > c))
            {
                cout << "Error. Please enter an integer from 1 to " << c << endl;
                cin.clear();
                cin.ignore(100, '\n');
                cin >> aC;
            }
        }

        //asks user to input how many moves they would like the ant to make in the simulation.
        cout << "How many moves? \n";
        cin >> movesNum;

            while (cin.fail() || (movesNum < 1))
            {
                cout << "Error. Please enter an integer greater than 0: \n";
                cin.clear();
                cin.ignore(100, '\n');
                cin >> movesNum;
            }

        //the following sets the ant orientation, number of moves, board size
        //and starts the simulation.
        antOri = 90;
        setMoves(movesNum);
        setAntBoard(r, c);
        setAnt(aR, aC);
        playGame();
    }



    void antGame::setAntBoard(int arrayX, int arrayY)
    {
        boardRow = arrayX;
        boardCol = arrayY;

        cout << endl << "Ant Board Start: \n";


        //dynamically allocates a 2D array
        antArray = new char *[arrayX + 2];
        for(int i = 0; i < (arrayX + 2); ++i)
        {
            antArray[i] = new char [arrayY + 2];
        }


        //creates array values
        for (int x = 0; x < arrayX + 2; x++)
        {
            for (int y = 0; y < arrayY + 2; y++)
            {

                //creates the board boarders/edges

                if (x == 0 || x == arrayX + 1)
                {
                    antArray[x][y] = '-';
                }

                else if (y == 0 || y == (arrayY + 1))
                {
                    if(x != 0 && x != arrayX + 1)
                        {
                            antArray[x][y] = '|';
                        }
                }


                //creates starting board and sets everything to white.

                else
                    antArray[x][y] = ' ';

                cout << antArray[x][y];

            }
            cout << endl;
        }
}


void antGame::setCurrentSpot(int x, int y)
{
        //sets ants current spots board tile color
        if (antArray[x][y] == ' ')
        {
            currentSpotColor = ' ';
        }

        //sets ants current spots board tile color
        else if (antArray[x][y] == '#')
        {
            currentSpotColor = '#';
        }

        //switches ant location so it does not cross edge
        //antArray[x][y] == '|'
        else if (antArray[x][y] == '|')
        {
            if (antOri == 180)
            {
                antOri = 0;
                antCurrentY += 2;

                if (antArray[antCurrentX][antCurrentY] == ' ')
                {
                    currentSpotColor = ' ';
                }

        //sets ants current spots board tile color
                else if (antArray[antCurrentX][antCurrentY] == '#')
                {
                currentSpotColor = '#';
                }

            }

            else if (antOri == 0)
            {
                antOri = 180;
                antCurrentY -= 2;


                if (antArray[antCurrentX][antCurrentY] == ' ')
                {
                    currentSpotColor = ' ';
                }

        //sets ants current spots board tile color
                else if (antArray[antCurrentX][antCurrentY] == '#')
                {
                currentSpotColor = '#';
                }
            }
        }

        //switches ant location so that it does not cross edge
        else if (antArray[x][y] == '-')
        {
            if (antOri == 90)
            {
                antOri = 270;
                antCurrentX += 2;


                if (antArray[antCurrentX][antCurrentY] == ' ')
                {
                    currentSpotColor = ' ';
                }

        //sets ants current spots board tile color
                else if (antArray[antCurrentX][antCurrentY] == '#')
                {
                currentSpotColor = '#';
                }
            }

            else if (antOri == 270)
            {
                antOri = 90;
                antCurrentX -= 2;


                if (antArray[antCurrentX][antCurrentY] == ' ')
                {
                    currentSpotColor = ' ';
                }

        //sets ants current spots board tile color
                else if (antArray[antCurrentX][antCurrentY] == '#')
                {
                currentSpotColor = '#';
                }
            }
        }
}




//the following function sets the ant on the board
void antGame::setAnt (int userSetX, int userSetY)
{
        antCurrentX = userSetX;
        antCurrentY = userSetY;

        setCurrentSpot(antCurrentX, antCurrentY);

        //sets ant on board.
        antArray[userSetX][userSetY] = '*';


        //prints current board after setting ant down.
        cout << endl << "Ant Placed on Board" << endl;
        printBoard();

}




//sets how many moves the user would like
void antGame::setMoves(int num)
{
        moves = num;
}


void antGame::playGame()
{
        //moves ant based for the amount of moves that the user inputted.
        for (int x = 0; x < moves; x++)
        {
            //the following statements change the ants direction if ant is on a white/' ' tile
            if (currentSpotColor == ' ')
            {
                if (antOri == 90)
                {
                    antOri = 0;
                    antArray[antCurrentX][antCurrentY] = '#';
                    antCurrentY += 1;

                    setCurrentSpot(antCurrentX, antCurrentY);

                    antArray[antCurrentX][antCurrentY] = '*';

                    printBoard();
                }

                else if (antOri == 180)
                {
                    antOri = 90;
                    antArray[antCurrentX][antCurrentY] = '#';
                    antCurrentX -= 1;

                    setCurrentSpot(antCurrentX, antCurrentY);

                    antArray[antCurrentX][antCurrentY] = '*';

                    printBoard();

                }



                else if (antOri == 0)
                {
                    antOri = 270;
                    antArray[antCurrentX][antCurrentY] = '#';
                    antCurrentX += 1;

                    setCurrentSpot(antCurrentX, antCurrentY);

                    antArray[antCurrentX][antCurrentY] = '*';

                    printBoard();
                }



                else if (antOri == 270)
                {
                    antOri = 180;
                    antArray[antCurrentX][antCurrentY] = '#';
                    antCurrentY -= 1;

                    setCurrentSpot(antCurrentX, antCurrentY);

                    antArray[antCurrentX][antCurrentY] = '*';

                    printBoard();

                }
            }


            //the following statements change the ants direction if ant is on a black/# tile
            else if (currentSpotColor == '#')
            {
                if (antOri == 90)
                {
                    antOri = 180;

                    antArray[antCurrentX][antCurrentY] = ' ';
                    antCurrentY -= 1;

                    setCurrentSpot(antCurrentX, antCurrentY);

                    antArray[antCurrentX][antCurrentY] = '*';

                    printBoard();
                }


                else if (antOri == 180)
                {
                    antOri = 270;
                    antArray[antCurrentX][antCurrentY] = ' ';
                    antCurrentX += 1;

                    setCurrentSpot(antCurrentX, antCurrentY);

                    antArray[antCurrentX][antCurrentY] = '*';

                    printBoard();
                }

                else if (antOri == 270)
                {
                    antOri = 0;
                    antArray[antCurrentX][antCurrentY] = ' ';
                    antCurrentY += 1;

                    setCurrentSpot(antCurrentX, antCurrentY);

                    antArray[antCurrentX][antCurrentY] = '*';

                    printBoard();
                }

                else if (antOri == 0)
                {
                    antOri = 90;
                    antArray[antCurrentX][antCurrentY] = ' ';
                    antCurrentX -= 1;

                    setCurrentSpot(antCurrentX, antCurrentY);

                    antArray[antCurrentX][antCurrentY] = '*';

                    printBoard();
                }
            }
        }

    void clearGameArray();
}



//deletes dynamically allocated 2D array
void antGame::clearGameArray()
{
        for (int ge = 0; ge < antRow; ++ge)
        {
            delete [] antArray[ge];
        }

        delete [] antArray;
        antArray = NULL;
}

//prints the current board.
void antGame::printBoard()
{
        countMoves += 1;
        cout << endl << "Move #: " << countMoves - 1 << endl;
        for (int x = 0; x < boardRow + 2; x++)
            {
                for (int y = 0; y < boardCol + 2; y ++)
                {
                    cout << antArray[x][y];
                }
                cout << endl;
            }
}


