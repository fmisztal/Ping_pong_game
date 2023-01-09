#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;



struct position
{
    int x;
    int y;
};

void Instruction();
void Ball(position *ball1, position board1, position platform1, int platsize1, position *momentum1);
void Movement(position *platform1, position board1, int platsize1, char move1);
void Board(position board1, position ball1, position platform1, int platsize);
int SizeSet(int minimum, int maximum);

int main()
{
    position ball, board, platform, momentum;
    int deaths=0, platsize;
    char move;

    momentum.x=1;
    momentum.y=1;

    cout << "Set the size of the board (minimum size: 5x5, maximum size: 30x100)" << endl;
    cout << "Height: ";
    board.y=SizeSet(5, 30);
    cout << "Width: ";
    board.x=SizeSet(5, 100);

    system("cls");

    cout << "Set the size of the platform (maximum size: 1/2 size of the board)" << endl;
    platsize=SizeSet(1, board.x/2);

    ball.y=board.y-1;
    ball.x=(board.x/2)+1;
    platform.x=((board.x-platsize)/2)+1;

    system("cls");

    do{
    Board(board, ball, platform, platsize);

    Instruction();

    cin >> move;
    Movement(&platform, board, platsize, move);

    Ball(&ball, board, platform, platsize, &momentum);

    if(ball.y==board.y)
        deaths++;

    system("cls");

    }while(deaths==0);

    cout << "Oops, you've lost!" << endl << endl;

    return 0;
}

void Instruction()
{
    cout << "Let's play Ball!" << endl;
    cout << "Don't let it fall out!" << endl << endl;
    cout << "Controls:" << endl;
    cout << "q+ENTER - move left" << endl;
    cout << "p+ENTER - move right" << endl;
    cout << "other+ENTER - don't move the platform" << endl << endl;
}

void Movement(position *platform1, position board1, int platsize1, char move1)
{
    switch(move1)
        {
        case 'q':
            if(platform1->x>1)
                platform1->x-=1;
        break;

        case 'p':
            if(platform1->x<(board1.x-platsize1+1))
                platform1->x+=1;
        break;
        }
}

void Ball(position *ball1, position board1, position platform1, int platsize1, position *momentum1)
{
    if(ball1->y==1)
        momentum1->y=1;
    if(ball1->y==board1.y-1 && (ball1->x<=platform1.x+platsize1 && ball1->x>=platform1.x))
        momentum1->y=-1;
    if(ball1->x==board1.x)
        momentum1->x=-1;
    if(ball1->x==1)
        momentum1->x=1;

    ball1->x+=momentum1->x;
    ball1->y+=momentum1->y;
}

void Board(position board1, position ball1, position platform1, int platsize)
{
    for(int i=0; i<=board1.y; i++)
    {
        if(i==0)
        {
            for(int k=0; k<board1.x+2; k++)
                cout << "_";
            cout << endl;
        }
        if(i>0 && i<=board1.y && ball1.y==i)
        {
            cout << "|";
            for(int k=0; k<ball1.x-1; k++)
                cout << " ";
            cout << "o";
            for(int k=0; k<board1.x-ball1.x; k++)
                cout << " ";
            cout << "|" << endl;
        }
        if(i>0 && i<board1.y && ball1.y!=i)
        {
            cout << "|";
            for(int k=0; k<board1.x; k++)
                cout << " ";
            cout << "|" << endl;
        }
        if(i==board1.y)
        {
            cout << "|";
            for(int k=0; k<platform1.x-1; k++)
                cout << " ";
            for(int k=0; k<platsize; k++)
                cout << "I";
            for(int k=0; k<board1.x-(platform1.x+platsize)+1; k++)
                cout << " ";
            cout << "|" << endl;
        }
    }
    cout << endl << endl;
}

int SizeSet(int minimum, int maximum)
{
    int i;
    while(1)
    {
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(20000,'\n');
        }
        cin >> i;
        if(cin.fail())
        {
            cout << "Invalid character entered!" << endl << "Please re-enter the size: ";
            continue;
        }
        if((i<minimum || i>maximum) && minimum!=maximum)
        {
            cout << "This size is out of range!" << endl << "Please re-enter the size: ";
            continue;
        }
        break;
    }
    return i;
}

