#include "my_stack.h"

mystack::mystack()
{
    tp = -1;
    maxsize = 3 * 100;
    Arr = new point[maxsize];
}

point mystack::top()
{
    return Arr[tp];
}
bool mystack::push(const point& a)
{
    tp++;
    if(tp > maxsize)
    {
        try
        {
            point *Arrt = new point(maxsize * 2);
            for(int i = 0; i < maxsize; i++)
            {
                Arrt[i] = Arr[i];
            }
            point *t = Arr;
            Arr = Arrt;

            delete []t;
            maxsize *= 2;
        }
        catch(const bad_alloc &e)
        {
            cout << "Run out of computer memory" << endl;
            return false;
        }
    }
    point *t = new point(a.x, a.y);
    Arr[tp] = *t;
    return true;
}


bool mystack::empty()
{
    return tp == -1;
}


bool mystack::pop()
{
    if(!empty())
    {
        tp--;
        return true;
    }
    else return false;
}
