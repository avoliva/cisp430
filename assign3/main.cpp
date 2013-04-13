/*
 * @name Adam Voliva
 * @desc Assign 2 List, Stack and Queue
 * @date March 11th, 2013
 * @class CISP430
 */
#include <fstream>
#include "list.h"
#include "queue.h"
#include "stack.h"

int main()
{
    // Testing List
    List<std::string> list;
    std::cout << "Is the list empty? = " << list.empty() << std::endl;
    std::string line;
    std::ifstream myfile ("datain.dat");
    if (myfile.is_open())
    {
        while ( myfile.good() )
        {
            getline (myfile,line);
            list.push_back(line);
        }
        myfile.close();
    }
    list.sort();
    std::ofstream outfile("output.txt");
    outfile << "List in ascending output (strings): " << std::endl << std::endl;
    if (outfile.is_open())
    {
        for (List<std::string>::iterator it = list.begin(); it != list.end(); ++it)
            outfile << *it << std::endl;
    }

    list.sort("desc");
    std::ofstream desc_outfile("output2.txt");
    desc_outfile << "List in descending output (strings): " << std::endl << std::endl;
    if (desc_outfile.is_open())
    {
        for (List<std::string>::iterator it = list.begin(); it != list.end(); ++it)
            desc_outfile << *it << std::endl;
    }

    
    std::cout << "pop back is " << list.pop_back() << std::endl;
    list.remove(list.begin() + 2);
    List<std::string>::iterator iters = list.begin();
    std::cout << " get next is " << iters.get_next() << std::endl;
    list.push_back(*iters);

    std::cout << "size is " << list.size() << std::endl;
    List<std::string> list2 = list;
    for (List<std::string>::iterator iter = list2.begin();
         iter != list2.end(); ++iter)
    {
        std::cout << (*iter) << std::endl;
    }
    std::cout << "search result " << list.search("5") << std::endl;
    std::cout << "get_head() " << list.get_head() << std::endl;
    List<std::string>::iterator it = list.begin() + 1;
    std::cout << "has_next() " << it.has_next() << std::endl;

    // Stack testing
    Stack<std::string> stack;
    std::cout << "stack.empty() (should be 1) " << stack.empty() << std::endl;
    std::ifstream my_stack_file ("datain.dat");
    if (my_stack_file.is_open())
    {
        while ( my_stack_file.good() )
        {
            getline (my_stack_file,line);
            stack.push(line);
        }
        my_stack_file.close();
    }
    stack.pop();
    std::cout << "stack top is " << stack.show_top() << std::endl;
    std::cout << "stack.empty() " << stack.empty() << std::endl;
    std::cout << "stack.is_full() " << stack.is_full() << std::endl;

    std::ofstream stack_out("stack_output.txt");
    stack_out << "Popping stack output ( minus 1): " << std::endl << std::endl;
    while (!stack.empty())
        stack_out << stack.pop() << std::endl;

    // Testing Queue
    Queue<std::string> queue;
    std::cout << "queue.empty() (should be 1) " << queue.empty() << std::endl;
    std::ifstream my_queue_file ("datain.dat");
    if (my_queue_file.is_open())
    {
        while ( my_queue_file.good() )
        {
            getline (my_queue_file,line);
            queue.enqueue(line);
        }
        my_queue_file.close();
    }
    std::cout << "searching queue for '5': " << queue.search("5") << std::endl;
    std::cout << "queue.empty() (should be 0) " << queue.empty() << std::endl;
    std::ofstream queue_out("queue_output.txt");
    queue.sort();
    queue_out << "Dequeue queue output sorted ascending: " << std::endl << std::endl;
    while (!queue.empty())
        queue_out << queue.dequeue() << std::endl;
    if (my_queue_file.is_open())
    {
        while ( my_queue_file.good() )
        {
            getline (my_queue_file,line);
            queue.enqueue(line);
        }
        my_queue_file.close();
    }
    std::ofstream queue_out_desc("queue_output_Desc.txt");
    queue.sort("desc");;
    queue_out_desc << "Dequeue queue output sorted descending: " << std::endl << std::endl;
    while (!queue.empty())
        queue_out_desc << queue.dequeue() << std::endl;

    std::cout << "queue.is_full(): " << stack.is_full() << std::endl;

    std::cin.ignore();
}
