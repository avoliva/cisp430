#ifndef List_H
#define List_H

#include <exception>
#include <iostream>

using namespace std;

const unsigned DEFAULT_SIZE = 0;

template <class T>
class List
{
    public:
        List();
        List(const List &initialiser);
        ~List(){delete_array();};
        unsigned size() const;
        void insert(const T &element);
        T* begin() const;
        T* end() const;
        T* remove(T* posPtr);
        void clear();
        void resize(unsigned allocateSize);
        unsigned get_alloc_size() const;
        unsigned get_count() const { return this->count; }
        void set_count(unsigned count) { this->count = count; }
        void set_alloc_size(unsigned allocated_size) { this->allocted_size = allocated_size; }
        void set_data(T* data) { this->data = data; }

        const T &operator[](int i) const;
        T &operator[](int i);
        List<T>& operator=(List rhs);

    private:
        T* init(unsigned allocateSize, unsigned fromArraySize, const T* fromArrayPtr);
        void delete_array();
        void copy(List &rhs);
        void swap(T &one,T &two);

        unsigned count;
        unsigned allocted_size;
        T *data;
};

template <class T>
List<T>::List()
{

    data = init(DEFAULT_SIZE, 0, NULL);
    allocted_size = DEFAULT_SIZE;
    count = 0;
}

template <class T>
List<T>::List(const List &initialiser)
{
    data = init(initialiser.get_alloc_size(), initialiser.size(), &(initialiser[0]));
    allocted_size = initialiser.get_alloc_size();
    count = initialiser.size();
}

template <class T>
unsigned List<T>::size() const
{
    return count;
}

template <class T>
void List<T>::insert(const T &element)
{
    if (allocted_size == count)
        resize((unsigned)((count * 1.5) + 1));
    data[count] = element;
    count++;
}

template <class T>
T* List<T>::begin() const
{
    return data;
}

template <class T>
T* List<T>::end() const
{
    return data + count;
}

template <class T>
T* List<T>::remove(T* posPtr)
{
    while(posPtr != end())
    {
        *posPtr = *(posPtr + 1);
        posPtr++;
    }
    count--;

    return posPtr;
}

template <class T>
void List<T>::clear()
{
    delete_array();
    allocted_size = 0;
    count = 0;
}

template <class T>
void List<T>::resize(unsigned allocateSize)
{
    T *newArray = init(allocateSize, count, data);
    delete[] data;
    data = newArray;
    allocted_size = allocateSize;
}

template <class T>
unsigned List<T>::get_alloc_size() const
{
    return allocted_size;
}

template <class T>
const T &List<T>::operator[](int i) const
{
    return *(data + i);
}

template <class T>
T &List<T>::operator[](int i)
{
    return *(data + i);
}

template <class T>
List<T>& List<T>::operator=(List rhs)
{
    copy(rhs);
    return *this;
}

template <class T>
T* List<T>::init(unsigned allocateSize, unsigned fromArraySize, const T* fromPtr)
{
    T* resultArray = new T[allocateSize];;
    if(fromPtr)
    {
        const T* tmpFromPtr = fromPtr;
        T* tmpToPtr = resultArray;
        for(unsigned i = 0; i < fromArraySize; i++)
        {
            try
            {
                *(tmpToPtr++) = *(tmpFromPtr++);
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

template <class T>
void List<T>::delete_array()
{
    delete[] data;
    data = NULL;
}

template <class T>
void List<T>::copy(List &rhs)
{
    swap(data,rhs.data);
    swap(count, rhs.count);
    swap(allocted_size, rhs.allocted_size);
}

template<class T>
void List<T>::swap(T &one,T &two)

{
    T temp=one;
    one=two;
    two=temp;
}

template <class T> class Stack: public List<T>
{
    public:
        Stack()
        {
            this->set_data(this->init(DEFAULT_SIZE, 0, NULL));
        }
        void push(const T &element)
        {
            this->insert(element);
        }
        T* pop()
        {
            T ret_val = this->end();
            this->remove(ret_val);
            return ret_val;
        }
        bool is_empty() { return this->get_count() == 0; }
        

    private:
        T* init(unsigned allocateSize, unsigned fromArraySize, const T* fromPtr)
        {
            T* resultArray = new T[allocateSize];;
            if(fromPtr)
            {
                const T* tmpFromPtr = fromPtr;
                T* tmpToPtr = resultArray;
                for(unsigned i = 0; i < fromArraySize; i++)
                {
                    try
                    {
                        *(tmpToPtr++) = *(tmpFromPtr++);
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
        // T* data;
        // int count;
        // int allocated_size;
};

int main()
{
    List<int> list;
    Stack<int> stack;
    int *s = list.begin();
    std::cout << " s is " << s << std::endl;
    list.insert(6);
    list.insert(5);
    list.insert(1);
    list.insert(3);
    std::cout << " list[2] is " << list.size() << std::endl;
    list.remove(&list[2]);
    std::cout << " list[2] is " << list.size() << std::endl;


}

#endif