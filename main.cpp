#include <iostream>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;
enum {meniu, gaming} gameState;
enum {none, up, down, right_, left_} moves;
enum {faster, slower, doublePoints, extraPoints, decreaseSize} special;
//enum {singlePlayer, versus, highScores, quit} menu;

unsigned int width = 20, height = 32, cursor=12, score=0, scoreH=0, delay=200;

struct
{
    struct
    {
        unsigned int x, y;
    } normal;

    struct
    {
        unsigned int x, y;
        clock_t timer;
        char name[25];
        bool running, dp;
    } special;
} target;

struct
{
    struct
    {
        unsigned int x, y;
    } head;
    struct
    {
        unsigned int length, x, y;
    } body;
} snake;

void startUp()
{
    srand(time(0));
    gameState = meniu;
    moves=none;

    target.special.x = rand()%(width-1) + 1;
    target.special.y = rand()%(height-1) + 1;
    target.special.running = 0;
    strcpy(target.special.name,"none");
    target.normal.x = rand()%(width-1) + 1;
    target.normal.y = rand()%(height-1) + 1;

    snake.head.x = rand()%(width-1) + 1;
    snake.head.y = rand()%(height-1) + 1;
    snake.body.length=0;

    score=0;
    scoreH=0;
}

void muv()
{
    switch(moves)
    {
    case up://up
        snake.head.y--;
        break;

    case left_://left
        snake.head.x--;
        break;

    case right_://right
        snake.head.x++;
        break;

    case down://down
        snake.head.y++;
        break;

    default:

        break;
    }

    if(snake.head.x < 1) snake.head.x = height-1;
    else if(snake.head.x >= height) snake.head.x = 1;

    if(snake.head.y < 1) snake.head.y = width-1;
    else if(snake.head.y >= width) snake.head.y = 1;

    if(snake.head.x == target.normal.x && snake.head.y == target.normal.y)
    {
        if(target.special.dp) score+=20; else score+=10;
        target.normal.x = rand()%(width-1) + 1;
        target.normal.y = rand()%(height-1) + 1;
        snake.body.length++;
    }
    if(snake.head.x == target.special.x && snake.head.y == target.special.y)
    {
        srand(time(0));
        switch(rand()%5 + 1)
        {
        case faster:
            delay=100;
            target.special.running = 1;
            strcpy(target.special.name,"faster");
            target.special.timer = clock();
            break;
        case slower:
            delay=500;
            target.special.running = 1;
            strcpy(target.special.name,"slower");
            target.special.timer = clock();
            break;
        case doublePoints:
            target.special.running = 1;
            target.special.dp = 1;
            strcpy(target.special.name,"double points");
            target.special.timer = clock();
            break;
        case extraPoints:
            target.special.running = 1;
            score+=50;
            strcpy(target.special.name,"extra points");
            target.special.timer = clock();
            break;
        case decreaseSize:
            target.special.running = 1;
            snake.body.length--;
            strcpy(target.special.name,"size decreased");
            target.special.timer = clock();
            break;
        }
    }
    clock_t actualTime = clock();
    clock_t timer = target.special.timer - actualTime;
    if((timer / (double) CLOCKS_PER_SEC) > 10 && target.special.timer != 0)
    {
        target.special.timer=0;
        target.special.dp=0;
        target.special.running=0;
        strcpy(target.special.name,"none");
        delay=200;
        srand(time(0));
        target.special.x = rand()%(width-1) + 1;
        target.special.y = rand()%(height-1) + 1;
    }
}

void keys()
{
    if(kbhit())
    {
        switch(getch())
        {
        case 72: //up
            if(gameState == gaming)
                moves = up;
            else
                cursor--;
            break;

        case 75: //left
            moves = left_;
            break;


        case 77: //right
            moves = right_;
            break;

        case 80: //down
            if(gameState == gaming)
                moves = down;
            else
                cursor++;
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
    srand(time(0));
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
                    else if(target.normal.y == x && target.normal.x == y) cout<<"~";
                    else if(target.special.y == x && target.special.x == y) cout<<"@";
                    else
                        cout<<" ";
                    break;
                }
        }
        cout<<endl;
    }
    if(gameState==gaming) cout<<"Your score: "<<score<<endl<<"Special: "<<target.special.name<<endl<<endl<<"Highest score: "<<scoreH;
}

int main()
{
    startUp();
    while(1)
    {
        print();
        keys();
        muv();
        Sleep(200);
        system("cls");
    }
    return 0;
}
