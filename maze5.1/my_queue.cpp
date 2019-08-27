#include "my_queue.h"
using namespace std;

point::point (int _x, int _y)
{
    x = _x;
    y = _y;
}

node::node(int _x, int _y)
{
    p.x = _x;
    p.y = _y;
    next = NULL;
}

my_queue::my_queue()
{
    head = new node(0, 0);
    last = head;
}

bool my_queue::push(const point &a)
{
    try
    {
        last -> next = new node(a.x, a.y);
        last = last -> next;
    }
    catch(const bad_alloc &e)
    {
        cout << "Run out of computer memory" << endl;
        return false;
    }
    return true;
}

bool my_queue::empty()
{
    if(head ->next == NULL)
        return true;
    else return false;
}

bool my_queue::pop()
{
    if(!empty())
    {
        node *temp = head -> next;
        head -> next = temp -> next;
        if(head -> next == NULL)
        {
            last = head;
        }
        delete temp;
        return true;
    }
    else return false;
}

point my_queue::front()
{
    if(!empty())
        return head->next->p;
    else return point (0, 0);
}

