#include <iostream>
#include <string>
#include <vector>

template <class T> class List
{
public:
	List()
    {
        this->data = init(0, 0, NULL);
        this->allocated_size = 0;
        this->element_count = 0;
        // std::cout << "end ss= " << *this->end() << std::endl;
    }
    List(unsigned size)
    {
        try {
            bool test = this->init(size);
            if (!test) throw 0;
        }
        catch (int) {
            std::cout << "Error in initializing list." << std::endl;
        }
        
    }
    T* init(unsigned size, unsigned from_size, const T* from_ptr)
    {

        T* result_array = new T[allocated_size];
        if (from_ptr)
        {
            const T* tmp_from_ptr = from_ptr;
            T* tmp_to_ptr = result_array;
            for (unsigned i = 0; i < from_size; ++i)
            {
                try
                {
                    *(tmp_to_ptr++) = *(tmp_from_ptr++);
                }
                catch(...)
                {
                    delete[] result_array;
                    result_array = NULL;
                    throw;
                }
            }
        }

    }
	// void Insert(T data);
    void insert(T data)
    {
        if (this->allocated_size == this->element_count)
        {
            this->resize((unsigned)((this->element_count * 1.5) + 1));
            // this->resize((unsigned)(this->element_count));
        }
        this->data[this->element_count] = data;
        this->element_count++;

    }
	// void Insert(T data, int index);
    // void Insert(T data, int index)
    // {
    //     this->data[index] = data;
    // }
    // template <class T>
    const T &operator[](int i) const
    {
        return *(this->data + i);
    }

    // template <class T>
    T &operator[](int i)
    {
        return *(this->data + i);
    }
	T *remove(T* pos_ptr)
    {
        while(pos_ptr != this->end())
        {
            *pos_ptr = *(pos_ptr + 1);
            pos_ptr++;
        }
        element_count--;
        return pos_ptr;
    }
	bool Search(int dataKey) const;
	void Sort(std::string order);
	T *begin()
    {
        return this->data;
    }
    T *end()
    {
        return this->data + list_size;
    }
	T GetNext();
	bool HasNext() const;
    unsigned size() const { return this->list_size; }
    void resize(unsigned size)
    {
        T *new_data = this->init(size, this->element_count, this->data);
        delete[] this->data;
        this->data = new_data;
        this->allocated_size = size;
    }

private:
     T *data;
     // T *begin;
     // T *end;
     unsigned list_size;
     unsigned allocated_size;
     unsigned element_count;


};

template <class T> class Stack
{
private:
    List<T> list;
public:
	Stack();
    void Push(T data);
    T Pop();
    bool isEmpty();
    bool isFull();
    T ShowTop() const;
};

template <class T> class Queue
{
private:
    List<T> list;
public:
    Queue();
    void Enqueue(T data);
    T Dequeue();
    bool isEmpty();
    bool isFull();
    void Sort();
    void Sort(std::string order);
    bool Search(int dataKey) const;

};


int main() {

    List<int> list;
    int s = 2;
    list.insert(6);
    list.insert(6);
    list.insert(6);
    list.insert(5);
    list.remove(&list[2]);
    // std::cout << list[0] << std::endl;
    // std::cout << list[1] << std::endl;
    // std::cout << list[2] << std::endl;
    // std::cout << list[3] << std::endl;



    return 0;
}

/*
Intermediate types
	Arrays
	Records
		Array-Records

Primitive
	Integer
	Floating


Class Interface
	Constructors
		Method Overloads
	Accessors
	Manipulator(s)
	Desctructor?

*/

/*

OO Reuse Hierarchy
    Class
    Method Overloads (Same name, different signature)
    Object Oriented Desisgn Patterns 
        Containment (has a relation)
        Inheritance (is a relation)
    Method override (same name, same signature)
    Templates (changing data types - data morhpism)
        Programmer Defined Types Require Template Extensions
        Sometimes called parametized types.
    any time you go over this, you will increase complexity in your problem, and increase resuability.
    Abstract Classses
        If a class has at least one abstract member, then it is abstract.
        You can't instance a abstract class because it has a 'hole'
        You can't make an object from one, because it is not complete.
        The hole must be filled in at run-time.
    Generic Classes
        A class is generic if it's services are insensitive to the kind of data to be operated on.
        The top level of reusability
        Pattern reuse required extension, you gotta write some code.

Assign to will start at "level 4".
Going to have a parent-child relationship between List, Stack and Queue.

Assign 2 Class Model
    List
        Stack
        Queue

    A list is basically a stack, vis-versa

    A stack is a Last In First Out (LIFO) list.

    A queue is a First In First Out (FIFO) list.

    The list is a container class.

    What is a list item?
        A data value that gets packages inside a construct known as a list entry.
        A list entry fullly encapsulates a list item.
        And then the balance of the list entry is for overhead, and that overhead is hidden

    Iheritance model is a relation between a base class.
        A relationship between a parent and a child.
        A child inherits the benefits of a parent (code, data, or both).
        A parent represents the general concepts of it's intended use.

    A container does not change the item, it just holds the data itself.

    A container should contain at a minimum these abilities:
        Init()
        Insert()
        Delete()
        Search()
        Sort()
        Interator()


PDF Explanation:
    
    The list shall be implemented with an underlying data structure, which is a LInked list
        Singluar linked
            Next
        Doubly linked
            Prev
            Next
        Circular linked
            The last item points to the first item and vic-versa



*/
