#include<iostream>
#include<string.h>
#include "my_queue.h"
#include <stack>
#include <windows.h>
#include <time.h>

using namespace std;
#define MAXSIZE 15728
extern int dir[4][2];
class Matrix
{
    //queue<point> lu;
    int high[MAXSIZE];
    int parent[MAXSIZE];
    int height, wid;
    void Initialize();
    int findSet(int x);  
    void unionSet(int root1, int root2);
    int findPos(int x,int y,int wid);

public:
    int getheight();
    bool book[100][100];
    my_queue lu;
    char Maze [100][100];
    Matrix(int t=0);

    void initMaze(int, int );
    int getwid();
    void makeMaze();
};

