/*
 * @name Adam Voliva
 * @desc Assign 2 List, Stack and Queue
 * @date March 11th, 2013
 * @class CISP430
 */

#include "config.h"
#ifndef STACK_H
#define STACK_H
template <class T> class Iterator;
template <class T> class Node;


/*
 * Class Iterator
 * A helper class that allows you to iterate through your list.
 */
/*
 * Class Stack
 * This class is an example of a stack.
 * The second template parameter is a class that must contain the following public member functions:
 *      push_front(value_type in)
 *      value_type pop_front()
 *      bool empty()
 *      iterator begin()
 */
template <class T, class Container> class Stack
{
protected:
    Container c;
public:
    typedef T value_type;
    typedef Iterator<Node<value_type> > iterator;
    Stack() : c() {}
    Stack(const Container& obj) : c(obj) {}
    // No need for destructor. The only thing being created is the Container
    //  which should have it's own destructor
    void push(value_type in) { c.push_front(in); }
    value_type pop() { return (c.empty()) ? '$' : c.pop_front(); }
    bool empty() { return c.empty(); }
    bool empty_next() { return c.empty_next(); }
    // should never be full.
    bool is_full() { return false; }
    value_type show_top() { return (c.empty()) ? '$' : *(c.begin());}
};

#endif
