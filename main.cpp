#include <iostream>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;
enum {meniu, gaming} gameState;
//enum {singlePlayer, versus, highScores, quit} menu;

unsigned int width = 20, height = 32, cursor=12, score=0, scoreH=0;

struct{
    struct{
        unsigned int x, y;
    }normal;

    struct{
        unsigned int x, y;
    }special;
}target;

struct{
    struct{
        unsigned int x, y;
    }head;
    struct{
        unsigned int length, x, y;
    }body;
}snake;

void startUp()
{
    srand(time(0));
    gameState = meniu;

    target.special.x = rand()%(width-1) + 1;
    target.special.y = rand()%(height-1) + 1;
    target.normal.x = rand()%(width-1) + 1;
    target.normal.y = rand()%(height-1) + 1;

    snake.head.x = rand()%(width-1) + 1;
    snake.head.y = rand()%(height-1) + 1;
    snake.body.length=0;

    score=0;
    scoreH=0;
}

void muv(unsigned int m)
{
    switch(m)
    {
    case 72://up
        if(snake.head.y <= 1)
            snake.head.y = height-1;
        else
            snake.head.y--;
        break;

    case 80://dn
        if(snake.head.y >= height-1)
            snake.head.y = 1;
        else
            snake.head.y++;
        break;

    case 77:
        if(snake.head.x >= width-1)
            snake.head.x = 1;
        else
            snake.head.x++;
        break;

    case 75:
        if(snake.head.x <= 1)
            snake.head.x = width-1;
        else
            snake.head.x--;
        break;
    }
}

void keyboard()
{
    if(kbhit())
    {
        switch(getch())
        {
            case 72: //up
                if(gameState == gaming)
                    muv(72);
                else
                    cursor--;
                break;

            case 80: //down
                if(gameState == gaming)
                    muv(80);
                else
                    cursor++;
                break;

            case 77: //right
                muv(77);
                break;

            case 75: //left
                muv(75);
                break;

            case 13:
                if(gameState == meniu)
                    switch(cursor)
                    {
                    case 12: //single
                        gameState=gaming;
                        break;
                    case 13: //versus
                        gameState=gaming;
                        break;
                    case 14: //highscore
                        break;
                    case 15: //quit
                        break;

                    }

        }
    }
}

void print()
{
    for(int x=0; x<=width; x++)
    {
        for(int y=0; y<=height; y++)
        {
            if((x == 0 || x == width) && (y >= 0 || y <= height)) cout<<"-";
            else if((x > 0 || x < width) && (y == 0 || y == height)) cout<<"|";
            else
                switch(gameState)
                {
                case meniu:
                    if( x == 10 && y == 15)
                    {
                        cout<<"MENU";
                        y=y+strlen("MENU") - 1;
                    }
                    else if( x == 12 && y == 13)
                    {
                        cout<<"play solo";
                        y=y+strlen("play solo") - 1;
                    }
                    else if( x == 13 && y == 12)
                    {
                        cout<<"play versus";
                        y=y+strlen("play versus") - 1;
                    }
                    else if( x == 14 && y == 12)
                    {
                        cout<<"high scores";
                        y=y+strlen("high scores") - 1;
                    }
                    else if( x == 15 && y == 15)
                    {
                        cout<<"quit";
                        y=y+strlen("quit") - 1;
                    }
                    else if( x == cursor && y == 10)
                    {
                        cout<<">";
                        y=y+strlen(">") - 1;
                    }
                    else cout<<" ";
                    break;
                case gaming:
                    if(snake.head.y == x && snake.head.x == y) cout<<"O";
                    else
                    if(target.normal.y == x && target.normal.x == y) cout<<"~";
                    else
                    if(target.special.y == x && target.special.x == y) cout<<"@";
                    else
                        cout<<" ";
                    break;
                }
        }
        cout<<endl;
    }
}

int main()
{
    startUp();
    while(1)
    {
        print();
        keyboard();
        Sleep(200);
        system("cls");
    }
    return 0;
}
