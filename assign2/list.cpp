/*
 * @author Adam Voliva
 * @name Assignment 2 - Containers
 * @date March 3, 2013
 * @lang C++
 */

#ifndef LIST_H
#define LIST_H

#include <exception>
#include <stdexcept>
#include <iostream>
#include <cstdio>

using namespace std;

const unsigned DEFAULT_SIZE = 0;


// List container
template <class T> class List
{
    public:
        // Conctructors and desctroctors
        List();
        List(const List &initialiser);
        ~List(){delete_container();};

        // Manipulators
        T* begin() const;
        T* end() /*const*/;
        T* remove(T* pos_ptr);
        void insert(const T &element);
        void delete_container();
        bool is_empty() { return this->get_count() == 0; }
        void clear();
        void resize(unsigned allocated_size);

        // Accessors
        unsigned size() const;
        unsigned get_alloc_size() const;
        unsigned get_count() const { return this->count; }
        void set_count(unsigned count) { this->count = count; }
        void set_alloc_size(unsigned allocated_size) { this->allocated_size = allocated_size; }
        void set_data(T* data) { this->data = data; }
        T* get_data() const { return this->data; }

        // Overloaded ops
        const T &operator[](int i) const;
        T &operator[](int i);
        List<T>& operator=(List rhs);

    private:
        // private constructor
        T* init(unsigned allocated_size, unsigned array_size, const T* copy_ptr);

        // copy and swap
        void copy(List &rhs);
        void swap(T &one,T &two);

        // private data members
        unsigned count;
        unsigned allocated_size;
        T *data;
};

/*
 * Default Contructor
 * Allocates a container object with a default size
 */
template <class T> List<T>::List()
{

    this->data = this->init(DEFAULT_SIZE, 0, NULL);
    this->allocated_size = DEFAULT_SIZE;
    this->count = 0;
}

/*
 * Copy Constructor
 */
template <class T> List<T>::List(const List &initialiser)
{
    this->data = this->init(initialiser.get_alloc_size(), initialiser.size(), &(initialiser[0]));
    this->allocated_size = initialiser.get_alloc_size();
    this->count = initialiser.size();
}

/*
 * Grabs the size of the container
 */
template <class T> unsigned List<T>::size() const
{
    return this->count;
}

/*
 * Inserts data into the container 
 */
template <class T> void List<T>::insert(const T &element)
{
    if (this->allocated_size == this->count)
        this->resize((unsigned)((this->count * 1.5) + 1));
    this->data[count] = element;
    this->count++;
}

/*
 * Grabs the first element
 */
template <class T> T* List<T>::begin() const
{
    return this->data;
}

/*
 * Grabs the last element
 * Throws an exception if there is no data.
 */
template <class T> T* List<T>::end() /*const*/
{   try 
    {
        if (this->is_empty())
            throw std::out_of_range("Out Of Range Error.");
    }
    catch (std::exception &e) {
        std::cerr << "exception caught: "  << '\n';
        std::terminate();
    }
    return this->data + this->size() - 1;
}

/*
 * Removes an element and handles the gap in the data
 */
template <class T> T* List<T>::remove(T* pos_ptr)
{
    
    while(pos_ptr != this->end())
    {
        *pos_ptr = *(pos_ptr + 1);
        pos_ptr++;
    }
    this->count--;

    return pos_ptr;
}

/*
 * Resets the container 
 */
template <class T> void List<T>::clear()
{
    this->delete_container();
    this->allocated_size = 0;
    this->count = 0;
}


/* 
 * Resizes the container
 */
template <class T> void List<T>::resize(unsigned allocated_size)
{
    T *new_data = this->init(allocated_size, count, data);
    delete[] this->data;
    this->data = new_data;
    this->allocated_size = allocated_size;
}

/* 
 * Grabs the allocated size of the container 
 */
template <class T> unsigned List<T>::get_alloc_size() const
{
    return this->allocated_size;
}


/* 
 * Overload for the [] operator
 * This allows you to read the container like list[5]
 * Throws an exception of the index is out of range
 */
template <class T> const T &List<T>::operator[](int i) const
{   
    try 
    {
        if (this->is_empty() || i >= this->size())
            throw std::out_of_range("Out Of Range Error.");
        // return *(data + i);
    }
    catch (std::exception &e) {
        std::cerr << "exception caught: "  << '\n';
        std::terminate();
    }
    return *(this->data + i);
}

/* 
 * Overload for the [] operator
 * This allows you to read the container like list[5]
 * Throws an exception of the index is out of range
 */
template <class T> T &List<T>::operator[](int i)
{
    try 
    {
        if (this->is_empty() || i >= this->size())
            throw std::out_of_range("Out Of Range Error.");
        // return *(data + i);
    }
    catch (std::exception &e) {
        std::cerr << "exception caught: "  << '\n';
        std::terminate();
    }
    return *(this->data + i);
}

/*
 * Overloads the assignment operator
 */
template <class T> List<T>& List<T>::operator=(List rhs)
{
    copy(rhs);
    return *this;
}


/* 
 * Container initialization
 */
template <class T> T* List<T>::init(unsigned allocated_size, unsigned array_size, const T* copy_ptr)
{
    T* resultArray = new T[allocated_size];;
    if(copy_ptr)
    {
        const T* tmp_copy_ptr = copy_ptr;
        T* tmp_to_ptr = resultArray;
        for(unsigned i = 0; i < array_size; i++)
        {
            try
            {
                *(tmp_to_ptr++) = *(tmp_copy_ptr++);
            }
            catch(...)
            {
                delete[] resultArray;
                resultArray = NULL;
                throw;
            }
        }
    }

    return resultArray;
}


/* 
 * Deletes the container and sets it to null
 */
template <class T> void List<T>::delete_container()
{
    delete[] this->data;
    this->data = NULL;
}

/*
 * Helps the copy constructor
 */
template <class T> void List<T>::copy(List &rhs)
{
    swap(this->data,rhs.data);
    swap(this->count, rhs.count);
    swap(this->allocated_size, rhs.allocated_size);
}


/* 
 * Data swapping
 */
template<class T> void List<T>::swap(T &one,T &two)
{
    T temp=one;
    one=two;
    two=temp;
}



/*
 * Stack class which inherits the list
 */
template <class T> class Stack: public List<T>
{
    public:
        Stack()
        {
            this->data = this->init(DEFAULT_SIZE, 0, NULL);
        }

        /* 
         * Adds data to the 'top' of the stack
         */
        void push(const T &element)
        {
            this->insert(element);
        }

        /*
         * Removes and returns the top of the stack
         */
        T* pop()
        {
            T* ret_val = this->end();
            this->remove(this->end());
            return ret_val;
        }

        /* 
         * Returns the top of the stack 
         */
        T* show_top()
        {
            return this->end();
        }


    private:
        /*
         * Container initialization
         */
        T* init(unsigned allocated_size, unsigned array_size, const T* copy_ptr)
        {
            T* resultArray = new T[allocated_size];;
            if(copy_ptr)
            {
                const T* tmp_copy_ptr = copy_ptr;
                T* tmp_to_ptr = resultArray;
                for(unsigned i = 0; i < array_size; i++)
                {
                    try
                    {
                        *(tmp_to_ptr++) = *(tmp_copy_ptr++);
                    }
                    catch(...)
                    {
                        delete[] resultArray;
                        resultArray = NULL;
                        throw;
                    }
                }
            }

            return resultArray;
        }
        T* data;
};

int main()
{
    List<int> list;
    Stack<int> stack;
    // std::cout << "stack size is " << stack.size() << std::endl;
    // int *s = list.begin();
    // std::cout << " s is " << s << std::endl;
    list.insert(6);
    list.insert(6);
    // list.remove(list.end());
    std::cout << " list[0] is " << list[1] << std::endl;
    // list.insert(5);
    // // list.remove(list.begin());
    // std::cout << " list[0] is " << list[0] << std::endl;
    stack.push(5);
    stack.push(22);
    stack.push(55);
    stack.push(1);
    // // stack.push(3);
    // // stack.push(3);
    std::cout << "stack[0] is " << *stack.end() << std::endl;
    //     // std::cout << "stack end is " << stack.end() << std::endl;
    stack.pop();
    std::cout << "stack[0] is " << *stack.end() << std::endl;

        stack.pop();
    std::cout << "stack[0] is " << *stack.end() << std::endl;

    //     stack.pop();
    // std::cout << "stack[0] is " << *stack.end() << std::endl;

            stack.pop();
    std::cout << "stack[0] is " << *stack.show_top() << std::endl;

    // std::cout << "list end is " << list.end() << std::endl;

            // std::cout << "stack size is " << stack[0] << std::endl;
    // list.insert(3);
    // std::cout << " list[2] is " << list.size() << std::endl;
    // list.remove(&list[2]);
    // std::cout << " list[2] is " << list.size() << std::endl;


}

#endif