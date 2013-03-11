#include <iostream>
# ifdef __DEFAULT_TEMPLATES
#   define __DEFAULT_TMPL(_Tp)
# else
#   define __DEFAULT_TMPL(_Tp) = _Tp
# endif


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
	friend class List<class T::value_type>;

	// The node class (Iterator<Node T> >)
	T *node;
	Iterator(T* in) : node(in) {}

public:

	/*
	 * @name has_next
	 * @desc Checks if there is a value to iterate to.
	 * @returns true or false
	 */
	bool has_next() { return this->node != NULL; }

	/*
	 * @name get_next
	 * @desc An alternative to ++ 
	 * @returns The contents of the next item in the list. 
	 *     T::value_type is the typename the List holds.
	 */
	typename T::value_type get_next() 
	{
		Iterator<T> it = *this;
		++it;
		return *(it); 
	}
	/*
	 * Operator overloads (++, !+, ==, * and +)
	 */
	void operator++() { this->node = (this->has_next()) ? this->node->next : this->node; }
	void operator++(int) { this->node = (this->has_next()) ? this->node->next : this->node; }
	bool operator!=(Iterator<T> rhs) { return !(this->node == rhs.node); }
	bool operator==(Iterator<T> rhs) { return this->node == rhs.node; }
	typename T::value_type operator*() { return this->node->data; }
	/* Allows you to do this->begin() + 2 to get the third item. */
	Iterator<T> operator+(int index)
	{
		Iterator<T> it = *this;
		for (int i = 0; i < index; ++i)
		{
			if (it.node) ++it; // If the value of it.node is NULL it just returns;
			else break;
		}
		return it;
	}
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
public:
	typedef T value_type;
	/* Saves some typing */
	typedef Iterator<Node<value_type> > iterator;

	// Overloading the brackets for easy access to the data
	value_type& operator[] (int index)
	{
		iterator position = this->begin() + index;
		return position.node->data;
	}
	value_type operator[] (int index) const
	{
		iterator position = this->begin() + index;
		return position.node->data;
	}

	/* List default constructor */
	List() : head(NULL) {}

	/* Copy constructor */
	List(List<value_type>& list)
	{
		this->head = NULL;

		for (iterator it = list.begin(); it != list.end(); ++it)
			this->push_back(*it);
		// std::cout << "empty = " << this->empty(); // no seg fault;
		// std::cout << "size = " << this->size(); // also causes a seg fault
		// this->push_back("string") // causes a seg fault
	}

	Node<T>* get_head() const { return head; }
	/* List desctructor */
	~List()
	{
		if (!this->empty())
		{
			Node<value_type> *it = this->head;
			while (it != NULL)
			{
				Node<value_type>* tmp = it;
				it = it->next;
				delete tmp;
			}
		}
	}

	/* Sorts C++ base types. If you want to sort a custom class you need
	 * 	to implement the operators used in here
	 */
	void qsort(List<value_type>& list, int left, int right, std::string order)
	{
		value_type tmp;
		value_type pivot = list[(left + right) / 2];
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
	void sort(std::string order)
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
	void sort()
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
	bool search(value_type search_key)
	{
		for (iterator it = this->begin(); it != this->end(); ++it)
		{
			if (*(it) == search_key) 
				return true;
		}
		return false;
	}

	/* Returns the size of the list container */
	unsigned size()
	{
		if (this->empty()) return 0;
		unsigned i = 0;
		for (iterator it = this->begin(); it != this->end(); ++it, ++i);
		return i;
	}

	/* 
	 * @name insert
	 * @param1 position - The position to insert at. Not an int.
	 * @param2 in - The data to insert into the list.
	 * @desc Inserts data into the list.
	 */
	void insert(iterator position, const value_type& in)
	{
		// If inserting at the front, just change the head to a new Node
		if (position == this->head) 
			this->head = new Node<value_type>(in);
		else
		{
			Node<value_type>* node = this->head;
			// iterate to the position of "position".
			for (; node->next != position.node; node = node->next);
			node->next = new Node<value_type>(in);
		}
		// This is here to put back all the old data into it's correct position.
		// I was having way too much with keeping the integrity of the data
		// while inserting into the middle of the list, so I created this little hack.
		for (iterator it = position; it != this->end(); ++it)
		{
			Node<value_type> *node = this->head;
			for (; node->next != NULL; node = node->next);
			node->next = new Node<value_type>(it.node->data);
		}
	}

	// Insert at end
	void push_back(value_type in)
	{
		this->insert(this->end(), in);
	}

	// Insert at beginning
	void push_front(value_type in)
	{
		this->insert(this->begin(), in);
	}

	// Remove from beginning
	value_type pop_front() 
	{ 
		if (this->empty()) return value_type();
		iterator del = this->begin();
		value_type tmp = *del;
		this->remove(del);
		return tmp;	
	}

	// Remove from end
	value_type pop_back()
	{	
		if (this->empty()) return value_type();
		iterator del = this->begin() + (this->size() - 1);
		value_type tmp = *del;
		this->remove(del);
		return tmp;
	}

	// If the head is NULL it must be empty
	bool empty() const { return this->head == NULL; }
	iterator begin() { return iterator(this->head); }
	// The end of the list is always NULL.
	iterator end() { return iterator(NULL); }

	/*
	 * @name remove
	 * @param The position of the list to remove from.
	 */
	bool remove(iterator position)
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
			for (Node<value_type>* it = this->head; it->next; it = it->next)
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

};


/* 
 * Class Stack
 * This class is an example of a stack.
 * The second template parameter is a class that must contain the following public member functions:
 * 		push_front(value_type in)
 *		value_type pop_front()
 *		bool empty()
 *		iterator begin()
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
	// 	which should have it's own destructor
	void push(value_type in) { c.push_front(in); }
	value_type pop() { return c.pop_front(); }
	bool empty() { return c.empty(); }
	// should never be full.
	bool is_full() { return false; }
	value_type show_top() { return *(c.begin());}
};

/* 
 * Class Queue
 * This class is an example of a FIFO queue.
 * The second template parameter is a class that must contain the following public member functions:
 * 		push_back(value_type in)
 *		value_type pop_front()
 *		bool empty()
 *		void sort(std::string order)
 *		bool search(value_type search_key)
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
	// 	which should have it's own destructor
	void enqueue(value_type in) { c.push_back(in); }
	value_type dequeue() { return c.pop_front(); }
	bool empty() { return c.empty(); }
	// should never be full.
	bool is_full() { return false; }
	void sort(std::string order) { c.sort(order); }
	void sort() { c.sort(); }
	bool search(value_type search_key) { return c.search(search_key); }
};

int main() 
{
	List<std::string> list;
	std::cout << "empty is " << list.empty() << std::endl;
	// list.push_back("shit");
	// list.push_back("fuck");
	list.push_back("crap");
	list.push_back("lol");
	list.push_back("what");
	list.push_front("screw");
	std::cout << "pop back is " << list.pop_back() << std::endl;
	list.remove(list.begin());
	List<std::string>::iterator iters = list.begin();
	// std::cout << " get next is " << iters.get_next() << std::endl;
	// iters++;
	list.push_back(*iters);

	std::cout << "size is " << list.size() << std::endl;
	// list.sort("asc");
	for (List<std::string>::iterator iter = list.begin();
	     iter != list.end(); ++iter)
	{	
		std::cout << (*iter) << std::endl;
	}
	List<std::string> list2 = list;
	for (List<std::string>::iterator iter = list2.begin();
	     iter != list2.end(); ++iter)
	{	
		std::cout << (*iter) << std::endl;
	}
	std::cout << list.search("shit") << std::endl;

	Stack<int> stack;
	stack.push(5);
	stack.push(4);
	stack.pop();
	std::cout << "stack top is " << stack.show_top() << std::endl;

	Queue<std::string> queue;
	queue.enqueue("hahahaha");
	queue.dequeue();
	queue.dequeue();
	std::cout << queue.empty() << std::endl;
	std::cin.ignore();
}