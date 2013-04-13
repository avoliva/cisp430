/*
 * @name Adam Voliva
 * @desc Assign 2 List, Stack and Queue
 * @date March 11th, 2013
 * @class CISP430
 */

#include <iostream>
#include "config.h"
#ifndef QUEUE_H
#define QUEUE_H
template <class T> class Iterator;
template <class T> class Node;
/*
 * Class Queue
 * This class is an example of a FIFO queue.
 * The second template parameter is a class that must contain the following public member functions:
 *      push_back(value_type in)
 *      value_type pop_front()
 *      bool empty()
 *      void sort(std::string order)
 *      bool search(value_type search_key)
 */
template <class T, class Container> class Queue
{
protected:
    Container c;
public:
    typedef T value_type;
    typedef Iterator<Node<value_type> > iterator;
    Queue() : c() {}
    Queue(const Container& obj) : c(obj) {}
    // No need for destructor. The only thing being created is the Container
    //  which should have it's own destructor
    void enqueue(value_type in) { c.push_back(in); }
    value_type dequeue() { return c.pop_front(); }
    bool empty() { return c.empty(); }
    // should never be full.
    bool is_full() { return false; }
    void sort(std::string order) { c.sort(order); }
    void sort() { c.sort(); }
    bool search(value_type search_key) { return c.search(search_key); }
};

#endif
