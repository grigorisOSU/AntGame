/****************************************************
**Sarkis Grigorian
**CS 162 - Project 1
**Date: 4/14/19
**NOTE: This project contains the extra credit random
**ant location.
**Description: This is the header file for the
**langston ant simulation.
****************************************************/


#ifndef LANGTONSANT_HPP
#define LANGTONSANT_HPP

class antGame
{

private:
    //board initial rows and columns from user input
    int boardRow,
        boardCol,
        antOri,
        antRow,
        antCol,
        moves,
        antCurrentX,
        antCurrentY,
        random1,
        menuRepeat,
        countMoves;


    char **antArray,
         currentSpotColor;


public:
    antGame();
    void menu();
    void boardInput();
    void setAntBoard(int, int);
    void setCurrentSpot(int x, int y);
    void setAnt (int, int);
    void setMoves(int num);
    void printBoard();
    void playGame();
    void clearGameArray();
};

#endif // LANGTONS_ANT
