/*Jason Shao ICS4U November 20, 2011
Stack and RPN Class Implementations
*/

#include <iostream>
#include <cmath>
#include "list.h"
#include "stack.h"
/* Jason Shao               ICS4U                   November 20th, 2011
Stack Class and RPN Class */

#ifndef RPN_1
#define RPN_1


class RPN : public Stack<float> {
      public:
             //display method
             void DisplayStack(); //outputs all values in the current stack
             
             //modifiers
             void add();          //pushes in sum of top 2 values
             void subtract();     //pushes in difference of top 2 values
             void multiply();     //pushes in product of top 2 values
             void divide();       //pushes in quotient of top 2 values
             void factorial();    //pushes in the factorial value of the top value
             void sine();         //pushes in the sin value of the top value
             void cosine();       //pushes in the cos value of the top value
             void tangent();      //pushes in the tan value of the top value
             void log();          //pushes in the logarithm of the top value
};

#endif


using namespace std;

#define PI 3.1415926535897932384626433832795


void RPN::add(){
    if (this->empty()) //Error-checks for at least two nodes
       return;
    
    this->push(this->pop() + this->pop()); //sum of top 2 values
}

void RPN::subtract(){
    if (this->empty()) //Error-checks for at least two nodes
       return;
       
    this->push((this->pop() - this->pop())*-1); //difference of top 2 values
}

void RPN::multiply(){
    if (this->empty()) //Error-checks for at least two nodes
       return;
       
    this->push(this->pop()*this->pop()); //product of top 2 values
}

void RPN::divide(){
    if (this->empty()) //Error-checks for at least two nodes
       return;
       
    this->push(1./(float(this->pop())/this->pop())); //quotient of top 2 values
}

void RPN::factorial(){
    if (this->empty()) //Error-checks for at least one node
       return;
       
    float temp = 1;
    
    for (int i = this->pop(); i>0; i--) //convert the number into a integer
        temp*=i; //multiply until factorial is done
    this->push(temp); //factorial value
}

void RPN::sine(){
     if (this->empty()) //Error-checks for at least one node
       return;
       
     this->push(sin(this->pop()*PI/180)); //convert to degrees and then push sine value
}
void RPN::cosine(){
     if (this->empty()) //Error-checks for at least one node
       return;
       
     this->push(cos(this->pop()*PI/180)); //convert to degrees and then push cosine value
}
void RPN::tangent(){
     if (this->empty()) //Error-checks for at least one node
       return;
       
     this->push(tan(this->pop()*PI/180)); //convert to degrees and then push tangent value
}
void RPN::log(){
     if (this->empty()) //Error-checks for at least one node
       return;
       
     this->push(log10(this->pop())); //convert to degrees and then push log value
}




/*Jason Shao                    ICS4U                       November 20, 2011
This program declares a calculator using the RPN class which inherits the Stack class. It stores
numbers that are user-inputted into a dynamic linked list. It can perform operations of addition/subtraction/
multiplication/division. It then displays the up-to-date values within the calculator memory.
Error checking for invalid inputs is done and such inputs are ignored. 
*/

#include <iostream>
#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include <limits>
#include <string>
#include <set>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <cctype>
// #include "stdafx.h"
#include <string>
#include <cmath>
#include <string>
// #include <windows.h>
// #include "RPN_1.h"
// #include "RPN_1.cpp"

using namespace std;

bool isNum(string input); //Determines whether the input is valid (numeric)

int main(){
    //Declaration and Initializations
    RPN Calc;
    string Input = "";
    
    //Calculator continues to read inputs until the user inputs 'q' to quit.
    while (Input.compare("q")){
          //Instructions and Input
          // cout << "          Please input number, operation (+ - * /), trig (sin/cos/tan)," <<endl <<endl 
          //      << "                   log (base 10), factorial(!), clear, quit(q): " << endl << endl
          //      << "                                       ";
          cin >> Input;
          
          //Process: Perform appropriate operations: 
          //add; subtract; multiply; divide; trig; log; clear screen; store number
          if (Input == "+")
             Calc.add();
          else if (Input == "-")
             Calc.subtract();
          else if (Input == "*")
             Calc.multiply();
          else if (Input == "/")
             Calc.divide();
          else if (Input == "!")
             Calc.factorial();
          else if (Input == "SIN")
             Calc.sine();
          else if (Input == "COS")
             Calc.cosine();
          else if (Input == "SQRT")
             Calc.tangent();
          else if (Input == "ABS")
             Calc.log();
          else if (Input == "clear"){
               while(!(Calc.empty())) //Deletes all inputs in memory until the list of numbers is empty
                    Calc.pop();
          }
          else if (Input == "q") break;
          else if (isNum(Input) && Input != "q") {
             Calc.push(atof(Input.c_str())); //Pushes the float value of number into the stack
             std::cout << " top is " << Calc.show_top() << std::endl;
           }
          else {              
             if (Input!="q"){ //Any other input except for 'q' is an invalid input at this point
                cout << "                                INVALID INPUT!!!!";
                // Sleep(1000);
             }
          }
             
          // system("cls"); //clear screen
          
          //Output: Unless the stack is empty, Output all the current values in the stack
             
    }   
          std::cout << "result is ";
          do {
             std::cout << << Calc.pop();
          } while (!Calc.empty());
          std::cout << std::endl;
    return 0;
}

//Error checks the string input to make sure the user is attempting to input a number
bool isNum(string input){
    for (int i = 0; i < input.length(); i++){
        if (!(isdigit(input[i])) && input[i] != '.' && input[i] != '-') //if the digit is a number, decimal, or negative sign.
             return 0;
    }
    return 1; //all digits are numbers or decimal/negative
}
