/*
 * @name Adam Voliva
 * @desc Assign 2 List, Stack and Queue
 * @date March 11th, 2013
 * @class CISP430
 */

#include "list.h"
#include "queue.h"
#include "stack.h"

int main()
{
    List<std::string> list;
    std::cout << "empty is " << list.empty() << std::endl;
    // // list.push_back("shit");
    // // list.push_back("fuck");
    // list.push_back("crap");
    // list.push_back("lol");
    // list.push_back("what");
    // list.push_front("screw");
    // std::cout << "pop back is " << list.pop_back() << std::endl;
    // list.remove(list.begin());
    // List<std::string>::iterator iters = list.begin();
    // // std::cout << " get next is " << iters.get_next() << std::endl;
    // // iters++;
    // list.push_back(*iters);

    // std::cout << "size is " << list.size() << std::endl;
    // // list.sort("asc");
    // for (List<std::string>::iterator iter = list.begin();
    //      iter != list.end(); ++iter)
    // {
    //     std::cout << (*iter) << std::endl;
    // }
    // List<std::string> list2 = list;
    // for (List<std::string>::iterator iter = list2.begin();
    //      iter != list2.end(); ++iter)
    // {
    //     std::cout << (*iter) << std::endl;
    // }
    // std::cout << list.search("shit") << std::endl;

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
