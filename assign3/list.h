/*
 * @name Adam Voliva
 * @desc Assign 2 List, Stack and Queue
 * @date March 11th, 2013
 * @class CISP430
 */

#include <iostream>
#include "config.h"
#ifndef LIST_H
#define LIST_H


/* Class Definitions */
template <class T> class List;
template <class T, class Container __DEFAULT_TMPL(List<T>) > class Stack;
template <class T, class Container __DEFAULT_TMPL(List<T>) > class Queue;

/*
 * Class Iterator
 * A helper class that allows you to iterate through your list.
 */
template <class T> class Iterator
{
    // List is a friend of iterator
    friend class List<typename T::value_type>;

    // The node class (Iterator<Node T> >)
    T *node;
    Iterator(T* in) : node(in) {}
public:
    bool has_next();
    typename T::value_type get_next();
    void operator++();
    void operator++(int);
    bool operator!=(Iterator<T> rhs);
    bool operator==(Iterator<T> rhs);
    typename T::value_type operator*();
    Iterator<T> operator+(int index);
};


/*
 * Class Node
 * A helper class that holds the List data.
 */
template <class T> class Node
{
public:
    typedef T value_type;
private:
    friend class List<value_type>;
    friend class Stack<value_type>;
    friend class Queue<value_type>;
    friend class Iterator<Node<value_type> >;
    Node(value_type in) : data(in), next(NULL) {}
    value_type data;
    Node<value_type>* next;
};



/*
 * Class List
 * The actualy list container class.
 */
template <class T> class List
{
    Node<T>* head; // First item in the list

    /* Sorts C++ base types. If you want to sort a custom class you need
     *  to implement the operators used in here
     */
    void qsort(List<T>& list, int left, int right, std::string order);

public:
    typedef T value_type;
    /* Saves some typing */
    typedef Iterator<Node<value_type> > iterator;

    // Overloading the brackets for easy access to the data
    value_type& operator[] (int index);
    value_type operator[] (int index) const;
    List() : head(NULL) {}

    /* Copy constructor */
    List(List<value_type>& list);

    Node<T>* get_head() const;

    /* List desctructor */
    ~List();

    /*
     * @name sort
     * @params std::string order
     * @desc Order should be either "desc" or "asc"
     */
    void sort(std::string order);

    /*
     * @name sort
     * @desc Default sort is ascending.
     */
    void sort();

    /*
     * @name search
     * @param value_type search_key. The key to search for.
     * @desc Returns true when it finds the first instance of the search key
     * @returns true or false
     */
    bool search(value_type search_key);

    /* Returns the size of the list container */
    unsigned size();

    /*
     * @name insert
     * @param1 position - The position to insert at. Not an int.
     * @param2 in - The data to insert into the list.
     * @desc Inserts data into the list.
     */
    void insert(iterator position, const value_type& in);

    // Insert at end
    void push_back(const value_type in);

    // Insert at beginning
    void push_front(const value_type in);

    // Remove from beginning
    value_type pop_front();

    // Remove from end
    value_type pop_back();

    // If the head is NULL it must be empty
    bool empty() const;

    bool empty_next() const;

    iterator begin();

    // The end of the list is always NULL.
    iterator end();

    /*
     * @name remove
     * @param The position of the list to remove from.
     */
    bool remove(iterator position);
};

#endif



    /*
     * @name has_next
     * @desc Checks if there is a value to iterate to.
     * @returns true or false
     */
    template <class T> bool Iterator<T>::has_next() { return this->node != NULL; }

    /*
     * @name get_next
     * @desc An alternative to ++
     * @returns The contents of the next item in the list.
     *     T::value_type is the typename the List holds.
     */
    template <class T> typename T::value_type Iterator<T>::get_next()
    {
        Iterator<T> it = *this;
        ++it;
        return *(it);
    }
    /*
     * Operator overloads (++, !+, ==, * and +)
     */
    template <class T> void Iterator<T>::operator++() { this->node = (this->has_next()) ? this->node->next : this->node; }
    template <class T> void Iterator<T>::operator++(int) { this->node = (this->has_next()) ? this->node->next : this->node; }
    template <class T> bool Iterator<T>::operator!=(Iterator<T> rhs) { return !(this->node == rhs.node); }
    template <class T> bool Iterator<T>::operator==(Iterator<T> rhs) { return this->node == rhs.node; }
    template <class T> typename T::value_type Iterator<T>::operator*() { return this->node->data; }
    /* Allows you to do this->begin() + 2 to get the third item. */
    template <class T> Iterator<T> Iterator<T>::operator+(int index)
    {
        Iterator<T> it = *this;
        for (int i = 0; i < index; ++i)
        {
            if (it.node) ++it; // If the value of it.node is NULL it just returns;
            else break;
        }
        return it;
    }

/*
 * Class List
 * The actualy list container class.
 */
    // Overloading the brackets for easy access to the data
    template <class T> typename List<T>::value_type& List<T>::operator[] (int index)
    {
        typename List<T>::iterator position = this->begin() + index;
        return position.node->data;
    }
    template <class T> typename List<T>::value_type List<T>::operator[] (int index) const
    {
        typename List<T>::iterator position = this->begin() + index;
        return position.node->data;
    }


    /* Copy constructor */
    template <class T> List<T>::List(List<typename List<T>::value_type>& list)
    {
        this->head = NULL;

        for (typename List<T>::iterator it = list.begin(); it != list.end(); ++it)
            this->push_back(*it);
        // std::cout << "empty = " << this->empty(); // no seg fault;
        // std::cout << "size = " << this->size(); // also causes a seg fault
        // this->push_back("string") // causes a seg fault
    }

    template <class T> Node<T>* List<T>::get_head() const { return head; }
    /* List desctructor */
    template <class T> List<T>::~List()
    {
        if (!this->empty())
        {
            Node<typename List<T>::value_type> *it = this->head;
            while (it != NULL)
            {
                Node<typename List<T>::value_type>* tmp = it;
                it = it->next;
                delete tmp;
            }
        }
    }

    /* Sorts C++ base types. If you want to sort a custom class you need
     *  to implement the operators used in here
     */
    template <class T> void List<T>::qsort(List<typename List<T>::value_type>& list, int left, int right, std::string order)
    {
        typename List<T>::value_type tmp;
        typename List<T>::value_type pivot = list[(left + right) / 2];
        int i = left, j = right;
        int pivotIndex = (left + right / 2);\
        while (i <= j)
        {
            if (order == "asc")
            {
                while (list[i] < pivot) ++i;
                while (list[j] > pivot) --j;
            }
            else if (order == "desc")
            {
                while (list[i] > pivot) ++i;
                while (list[j] < pivot) --j;
            }
            if (i <= j)
            {
                tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
                ++i;
                --j;
            }
            if (left < j)
                this->qsort(list, left, j, order);
            if (i < right)
                this->qsort(list, i, right, order);
        }
    }

    /*
     * @name sort
     * @params std::string order
     * @desc Order should be either "desc" or "asc"
     */
    template <class T> void List<T>::sort(std::string order)
    {
        if (this->size() <= 1)
            return;
        int left = 0;
        int right = this->size() - 1;
        this->qsort(*this, left, right, order);
    }

    /*
     * @name sort
     * @desc Default sort is ascending.
     */
    template <class T> void List<T>::sort()
    {
        if (this->size() <= 1)
            return;
        int left = 0;
        int right = this->size() - 1;
        this->qsort(*this, left, right, "asc");
    }

    /*
     * @name search
     * @param value_type search_key. The key to search for.
     * @desc Returns true when it finds the first instance of the search key
     * @returns true or false
     */
    template <class T> bool List<T>::search(typename List<T>::value_type search_key)
    {
        for (typename List<T>::iterator it = this->begin(); it != this->end(); ++it)
        {
            if (*(it) == search_key)
                return true;
        }
        return false;
    }

    /* Returns the size of the list container */
    template <class T> unsigned List<T>::size()
    {
        if (this->empty()) return 0;
        unsigned i = 0;
        for (typename List<T>::iterator it = this->begin(); it != this->end(); ++it, ++i);
        return i;
    }

    /*
     * @name insert
     * @param1 position - The position to insert at. Not an int.
     * @param2 in - The data to insert into the list.
     * @desc Inserts data into the list.
     */
    template <class T> void List<T>::insert(typename List<T>::iterator position, const typename List<T>::value_type& in)
    {
        // If inserting at the front, just change the head to a new Node
        if (position == this->head)
            this->head = new Node<typename List<T>::value_type>(in);
        else
        {
            Node<typename List<T>::value_type>* node = this->head;
            // iterate to the position of "position".
            for (; node->next != position.node; node = node->next);
            node->next = new Node<typename List<T>::value_type>(in);
        }
        // This is here to put back all the old data into it's correct position.
        // I was having way too much with keeping the integrity of the data
        // while inserting into the middle of the list, so I created this little hack.
        for (typename List<T>::iterator it = position; it != this->end(); ++it)
        {
            Node<typename List<T>::value_type> *node = this->head;
            for (; node->next != NULL; node = node->next);
            node->next = new Node<typename List<T>::value_type>(it.node->data);
        }
    }

    // Insert at end
    template <class T> void List<T>::push_back(typename List<T>::value_type in)
    {
        this->insert(this->end(), in);
    }

    // Insert at beginning
    template <class T> void List<T>::push_front(typename List<T>::value_type in)
    {
        this->insert(this->begin(), in);
    }

    // Remove from beginning
    template <class T> typename List<T>::value_type List<T>::pop_front()
    {
        if (this->empty()) return value_type();
        typename List<T>::iterator del = this->begin();
        typename List<T>::value_type tmp = *del;
        this->remove(del);
        return tmp;
    }

    // Remove from end
    template <class T> typename List<T>::value_type List<T>::pop_back()
    {
        if (this->empty()) return value_type();
        typename List<T>::iterator del = this->begin() + (this->size() - 1);
        typename List<T>::value_type tmp = *del;
        this->remove(del);
        return tmp;
    }

    // If the head is NULL it must be empty
    template <class T> bool List<T>::empty() const { return this->head == NULL; }
    template <class T> bool List<T>::empty_next() const { return this->head->next == NULL; }
    template <class T> typename List<T>::iterator List<T>::begin() { return typename List<T>::iterator(this->head); }
    // The end of the list is always NULL.
    template <class T> typename List<T>::iterator List<T>::end() { return typename List<T>::iterator(NULL); }

    /*
     * @name remove
     * @param The position of the list to remove from.
     */
    template <class T> bool List<T>::remove(typename List<T>::iterator position)
    {
        if (this->empty()) return false;
        // If removing the first node
        if (position.node == this->head)
        {
            // set the first node to the second node
            this->head = this->head->next;
            delete position.node;
            return true;
        }
        else
        {
            for (Node<typename List<T>::value_type>* it = this->head; it->next; it = it->next)
            {
                if (it->next == position.node)
                {
                    it->next = position.node->next;
                    delete position.node;
                    return true;
                }
            }
        }
        return false;
    }


