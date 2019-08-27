#ifndef MY_STACK_H_INCLUDED
#define MY_STACK_H_INCLUDED
#include "my_queue.h"

class mystack
{
    point *Arr;
    int tp;
    int maxsize;

public:
    mystack();
    bool push(const point& a);
    bool empty();
    bool pop();
    point top();
};

#endif // MY_STACK_H_INCLUDED
