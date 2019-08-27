#ifndef MY_QUEUE_H_INCLUDED
#define MY_QUEUE_H_INCLUDED
#include <iostream>
using namespace std;

struct point
{
    int x, y;
    point (int _x = 0, int _y = 0);
};
struct node
{
    point p;
    node *next;
    node(int _x = 0, int _y = 0);
};
class my_queue
{
    node *head;
    node *last;
public:
    my_queue();
    bool push(const point &a);
    bool empty();
    bool pop();
    point front();
};


#endif // MY_QUEUE_H_INCLUDED
