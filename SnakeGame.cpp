#include <iostream>
#include "Queue.h"
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define SIZE 20

using namespace std;

struct PositionHolder{
	int row;
	int col;
};

class Snake{
private:
    char gameField[SIZE][SIZE];
    PositionHolder snakeHead;
    Queue<PositionHolder> bodyQueue;
    int snakeSize;
    int counter;
    int nextSizeUp;
    int score;
    void display();
public:
    Snake();
    void gameLoop();
};

Snake :: Snake(){
    snakeHead.row = 5;
    snakeHead.col = 5;
    snakeSize = 1;
    score = snakeSize;
    srand(time(0));
    nextSizeUp = rand() % 5 + 1;
    counter = 0;
    for (int row = 0; row < SIZE; row++)
        for (int col = 0; col < SIZE; col++)
            if ( row == 5 && col == 5)
                gameField[row][col] = -78;
            else
                gameField[row][col] = -80;
}

void Snake :: gameLoop(){
    display();
    char action;
    PositionHolder destination;
    bool gameOver = false;

    action = getch();
    switch(action){
        case 'w':
            destination.row = snakeHead.row - 1;
            destination.col = snakeHead.col;
            if (destination.row < 0 || gameField[destination.row][destination.col] == -78)
                gameOver = true;
            break;
        case 'a':
            destination.row = snakeHead.row;
            destination.col = snakeHead.col - 1;
            if (destination.col < 0 || gameField[destination.row][destination.col] == -78)
                gameOver = true;
            break;
        case 's':
            destination.row = snakeHead.row + 1;
            destination.col = snakeHead.col;
            if (destination.row > SIZE - 1 || gameField[destination.row][destination.col] == -78)
                gameOver = true;
            break;
        case 'd':
            destination.row = snakeHead.row;
            destination.col = snakeHead.col + 1;
            if (destination.col > SIZE - 1 || gameField[destination.row][destination.col] == -78)
                gameOver = true;
            break;
    }
    if (!gameOver)
    {
        bodyQueue.add(snakeHead);
        if (bodyQueue.size() >= snakeSize)
        {
            PositionHolder oldHead = bodyQueue.remove();
            gameField[oldHead.row][oldHead.col] = -80;
        }

        snakeHead = destination;
        gameField[snakeHead.row][snakeHead.col] = -78;

        counter++;
        if (counter == nextSizeUp)
        {
            counter = 0;
            snakeSize++;
            nextSizeUp = rand() % 5 + 1;
            score = snakeSize;
        }
        system("cls");
        gameLoop();
    }
    else
    {
        cout << "Game Over\n" << "your score : " << score <<endl;
        //To not close the command prompt directly if the user keeps playing.
        cout << "Press enter to quit\n";

        cin.ignore();
    }
}

void Snake :: display(){
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
            cout << gameField[row][col];
        cout << endl;
    }
}
int main(void)
{
    Snake obj;
    obj.gameLoop();
    return 0;
}
