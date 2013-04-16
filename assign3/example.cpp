#include <iostream>
#include <sstream>
#include <stack>
#include <limits>
#include <string>
#include "stdafx.h"
#include <string>
#include <stdio.h>
#include <math.h>
using namespace std;

int priority(char a) {
    int temp;
    if (a == '^')
        temp = 1;
    else  if (a == '*' || a == '/')
        temp = 2;
    else  if (a == '+' || a == '-')
        temp = 3;
    return temp;
}

int main() {
    string infix;
    cout << "Enter an arithmetic expression: " << endl;
    getline(cin, infix);

    stack<char> operator_stack;

    stringstream output;

    for (unsigned i = 0; i < infix.length(); i++) {
        if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^') {
            while (!operator_stack.empty() && priority(operator_stack.top()) <= priority(infix[i])) {
                output << operator_stack.top();
                operator_stack.pop();
            }
            operator_stack.push(infix[i]);
        } else if (infix[i] == '(') {
            operator_stack.push(infix[i]);
        } else if (infix[i] == ')') {
            while (operator_stack.top() != '(') {
                output << operator_stack.top();
                operator_stack.pop();
            }
            operator_stack.pop();
        } else {
            output << infix[i];
        }
    }

    while (!operator_stack.empty()) {
        output << operator_stack.top();
        operator_stack.pop();
    }

    cout << output.str() << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return 0;
}



// more examples
// main
#include<iostream>
#include"convert.h"
#include<cstring>

using namespace std;

int main()
{
        stack op;
        stack post;
        stack res;
        char infex[SIZE];
        cout<<"Please Enter Infex Formula :";
        cin.get(infex,SIZE);
        char OpValue;
        char ch;
        int lenght;
        lenght=strlen(infex);
        for(int i=0;i<lenght;i++)
        {
                if(infex[i]=='+'||infex[i]=='-'||infex[i]=='*'||infex[i]=='/'||infex[i]=='('||infex[i]==')')
                {
                        if(infex[i]=='*'||infex[i]=='/'||infex[i]=='(')
                                op.push(infex[i]);
                        else if(infex[i]=='+'||infex[i]=='-')
                        {
                                if(op.topnum=='*'||op.topnum=='/')
                                {
                                        op.pop(ch);
                                        OpValue=ch;
                                        while(ch!='('&& !op.isempty())
                                        {
                                                post.push(ch);
                                                op.pop(ch);

                                        }
                                        op.push(infex[i]);
                                }
                                else
                                        op.push(infex[i]);
                                }
                        else if(infex[i]==')')
                        {
                                op.pop(ch);
                                OpValue=ch;
                                while(OpValue!='(')
                                {
                                        post.push(OpValue);
                                        op.pop(ch);
                                        OpValue=ch;
                                }

                        }


                        }
                else
                        post.push(infex[i]);

                }
        while(!op.isempty())
        {
                op.pop(ch);
                OpValue=ch;
                post.push(OpValue);     
        }

        post.print();
        cout<<endl;

        cout<<"RESULT OF INFIX : ";
        res.result(post);

system("pause");
return 0;
}



/// possibly very simple method.....
while( cin>>input ) //while there is more input
if( isalnum(input) ) //if input is an operand (A-Za-Z0-9) you may want to implement it
cout << input; //print input 



// another one
#ifndef H_infixToPostfix
#define H_infixToPostfix

#include <string>
#include <stack>

using namespace std;

class infixToPostfix
{
public:
    void convertToPostfix();
    bool precedence(char opr1, char opr2);
    void storeInfix(string s);
    void showInfix();
    void showPostfix();
    infixToPostfix(); //Default constructor

private:
    string  ifx; //infix string
    string  pfx; //postfix string

};
//definition of Class Constructor
inline infixToPostfix::infixToPostfix()
{
    ifx = "";
    pfx = "";
}

//definition for precedence function
bool infixToPostfix::precedence(char opr1, char opr2)
{
    int val1, val2;

    if(opr1 == '+' || opr1 == '-')
        val1 = 1;
    if(opr1 == '/' || opr1 == '*')
        val1 = 2;
    if(opr2 == '+' || opr2 == '-')
        val2 = 1;
    if(opr2 == '*' || opr2 == '/')
        val2 = 2;
    return (val1 >= val2);
}

//Definition of storeInfix function
void infixToPostfix::storeInfix(string s)
{
    ifx = s;
}

//Definition of showInfix function
void infixToPostfix::showInfix()
{
    cout << ifx << endl;
}

//Definition of showPostfix function
void infixToPostfix::showPostfix()
{
    cout << pfx << endl;
}

//Definition of converToPostfix function
void infixToPostfix::convertToPostfix()
{
    string expression = "6+5";
    string::size_type i;
    int intValue;
    float x, y;
    float answer;
    stack<float> numStack;

    char op = 0; // remember the operation symbol
    for(i = 0; i < expression.length(); i++)
    {
        //if the current character is a digit, convert it to an int and push in into the stack
        if(isdigit(expression[i]))
        {
            intValue = (expression[i] - '0'); // no need for a stringstream, really
            if(numStack.empty())
                numStack.push(intValue);
            else
            {
                x = intValue;
                y = numStack.top();
                if(op == '+')
                    {answer = y + x;}
                else if(op == '-')
                    {answer = y - x;}
                else if(op == '/')
                    {answer = y / x;}
                else if(op == '*')
                    {answer = y * x;}
                else if(op == '^')
                    {answer = pow(y, x);}
                else
                    break;
                numStack.push(answer);
            }
        }
        else // if(IsValidOp(expression[i]))
            op = expression[i];
        // else
            //  break;
    }
    if(i == expression.length())
    {
        if(numStack.empty())
            cout << "No result" << endl;
        else //print solution
            cout << numStack.top() << endl;
    }
    else
        cout << "Error at position " << i << endl;
    

    system("PAUSE");
    return 0;
}


#endif 




// postfix evaluator

// http://www.dreamincode.net/forums/topic/204754-c-postfix-evaluation/

// http://www.cplusplus.com/forum/general/56869/

// tokenizer

// http://cboard.cprogramming.com/c-programming/112925-tokenizing-expression-strtok-other-alternatives.html

// tokenizer example on d2l (in stuff.cpp)


// Dixon example on board

// switch s2.show_top(c)
//     case '=': swtich(new Token(inputExpr.getNext()))
//     case '+': case '_': 


// // q1 should contain the postfix


// sample application (E Evaulator)
//     Enter Expr: A = 10
//     Enter Expr: B = SIN(A)
//     Enter Expr: C = A+B 


// Token 
//     "1073" -> ASCII -> Binary (atoi) (atof) (atol) (atoll)
//     "18.268" -> ASCII -> Binary (atoi) (atof) (atol) (atoll)
