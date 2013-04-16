// Adam Voliva
// CISP430
// Postfix evaluator (assign 3)
// unfinished, horribly written code that still works

#include <iostream>
#include <sstream>
#include <set>
#include <cmath>
#include <cstdlib>
#include "list.h"
#include "stack.h"
#include <limits>
#include <iterator>
#include <vector>
#include <map>
#include <exception>
#define PI 3.1415926535897932384626433832795
using namespace std;

#define A "5"
#define B "10"
#define C "-1"
#define D "2"

// TODO....
class SymbolTable
{
public:
    std::string convert(std::string input)
    {
        unsigned result;
        do {
            result = input.find("A");
            if (result != std::string::npos)
            {
                unsigned i = result;
                const char * test = input.c_str();
                std::string sine;
                for (; test[i] != ' '; ++i){
                    if (!isdigit(test[i]) || test[i] != '.') sine += test[i]; 
                }
                try {
                    input = input.substr(0, result) + A + input.substr(i);
                } catch (...)
                {
                    input = input.substr(0, result) + A;
                }
                
            }
            result = input.find("B");
            if (result != std::string::npos)
            {
                unsigned i = result;
                const char * test = input.c_str();
                std::string sine;
                for (; test[i] != ' '; ++i){
                    if (!isdigit(test[i]) || test[i] != '.') sine += test[i]; 
                }
                try {
                    input = input.substr(0, result) + B + input.substr(i);
                } catch (...)
                {
                    input = input.substr(0, result) + B;
                }
                
            }
            result = input.find("C");
            if (result != std::string::npos)
            {
                unsigned i = result;
                const char * test = input.c_str();
                std::string sine;
                for (; test[i] != ' '; ++i){
                    if (!isdigit(test[i]) || test[i] != '.') sine += test[i]; 
                }
                try {
                    input = input.substr(0, result) + C + input.substr(i);
                } catch (...)
                {
                    input = input.substr(0, result) + C;
                }
                
            }
            result = input.find("D");
            if (result != std::string::npos)
            { 
                unsigned i = result;
                const char * test = input.c_str();
                std::string sine;
                for (; test[i] != ' '; ++i){
                    if (!isdigit(test[i]) || test[i] != '.') sine += test[i]; 
                }
                try {
                    input = input.substr(0, result) + D + input.substr(i);
                } catch (...)
                {
                    input = input.substr(0, result) + D;
                }
                
            }
        } while (result != std::string::npos);

        return input;
    }

};

class InfixToPostfix
{
    public:
        InfixToPostfix() {}

        std::string exec( std::string infix )
        {
            if( infix.length() == 0 )
            {
                return "Error";
            } else {

                Stack<char> stack;

                int pop_value, pinfix, pstack;
                char temp_top;

                std::string postfix;

                for( std::string::iterator it = infix.begin(); it < infix.end(); it++ )
                {
                    if( *it != '(' && *it != ')' && *it != '+' && *it != '-' && *it != '*' && *it != '/' )
                    {   

                        postfix += *it;
                    } else if( *it == '(' ) {
                      // stack.push(' ');
                        stack.push( *it );
                    } else if( *it == ')' ) {
                        while(( pop_value = stack.pop() ) != '(' )
                        {   
                            postfix += " ";
                            postfix += pop_value;
                        }
                    } else {
                        if (isdigit(*(it+1))) {
                            postfix+=*it;
                            continue;
                        }
                        pinfix = this->priority_operator( *it );
                        temp_top = stack.show_top();
                        pstack = this->priority_operator( temp_top );

                        if( pinfix > pstack )
                        {

                            stack.push( *it );
                        } else {
                            while( pstack >= pinfix )
                            {
                                if( temp_top == '$' )
                                    break;

                                pop_value = stack.pop();
                                temp_top = stack.show_top();
                                postfix += " ";
                                postfix += pop_value;
                                pstack = this->priority_operator( temp_top );
                            }
                            stack.push( *it );
                        }
                    }
                }
                postfix += " ";
                while(( pop_value = stack.pop() ) != '$' ) {
                    postfix += " ";
                    postfix += pop_value;
                }

                return postfix;
            }
        }

    private:
        int priority_operator( char ch )
        {
            switch( ch )
            {
                case '*': case '/': return 4;
                case '+': case '-': return 3;
                default : return 0;
            }
        }

};

class Functions
{
public:
    std::string clean(std::string postfix)
    {
        unsigned result;
        do {
            result = postfix.find("SIN");
            if (result != std::string::npos)
            {
                unsigned i = result;
                const char * test = postfix.c_str();
                std::string sine;
                for (; test[i] != ' '; ++i){
                    if (isdigit(test[i]) || test[i] == '.') sine += test[i]; 
                }
                postfix = postfix.substr(0, result) + this->sine(atof(sine.c_str())) + postfix.substr(i);
            }
            result = postfix.find("COS");
            if (result != std::string::npos)
            {
                unsigned i = result;
                const char * test = postfix.c_str();
                std::string cosine;
                for (; test[i] != ' '; ++i){
                    if (isdigit(test[i]) || test[i] == '.') cosine += test[i];       
                }
                postfix = postfix.substr(0, result) + this->cosine(atof(cosine.c_str())) + postfix.substr(i);
            }
            result = postfix.find("SQRT");
            if (result != std::string::npos)
            {
                unsigned i = result;
                const char * test = postfix.c_str();
                std::string sqroot;
                for (; test[i] != ' '; ++i){
                    if (isdigit(test[i]) || test[i] == '.') sqroot += test[i];
                }
                postfix = postfix.substr(0, result) + this->sqroot(atof(sqroot.c_str())) + postfix.substr(i);
            }
            result = postfix.find("ABS");
            if (result != std::string::npos)
            {
                unsigned i = result;
                const char * test = postfix.c_str();
                std::string absolute;
                for (; test[i] != ' '; ++i){
                    if (isdigit(test[i]) || test[i] == '.') absolute += test[i];
                }
                postfix = postfix.substr(0, result) + this->absolute(atof(absolute.c_str())) + postfix.substr(i);
            }
        } while (result != std::string::npos);

        return postfix;

    }
private:
    std::string sine(float n){ 
        n = sin(n*PI/180);
        std::ostringstream ss;
        ss << n;
        return (ss.str()); 
    }
    std::string cosine(float n){
        n = cos(n*PI/180);
        std::ostringstream ss;
        ss << n;
        return (ss.str());
    }
    std::string sqroot(float n){
        n = sqrt(n);
        std::ostringstream ss;
        ss << n;
        return (ss.str());
    }

    std::string absolute(float n){
        n = abs(n);
        std::ostringstream ss;
        ss << n;
        return (ss.str());
    }
};


class Evaluator : public Stack<float> {
public:   
    void add(){
        if (this->empty()) 
           return;
        
        this->push(this->pop() + this->pop()); 
    }

    void subtract(){
        if (this->empty()) 
           return;
           
        this->push((this->pop() - this->pop())*-1);
    }

    void multiply(){
        if (this->empty()) 
           return;
           
        this->push(this->pop()*this->pop()); 
    }

    void divide(){
        if (this->empty()) 
           return;
           
        this->push(1./(float(this->pop())/this->pop())); 
    }
};



bool is_num(std::string input){
    for (unsigned i = 0; i < input.length(); i++){
        if (!(isdigit(input[i])) && input[i] != '.' && input[i] != '-') 
            return false;
    }
    return true;
}


class TokenItem
{
public:
    std::string type;
    std::string token;
    std::set<char> identifier;
    std::set<char> operators;
    std::set<std::string> function;
    bool in(char c, std::set<char> table)
    {
        std::set<char>::iterator it;
        it = table.find(c);
        if (it == table.end()) return false;
        else return true;
    }
    bool in(std::string s, std::set<std::string> table)
    {
        std::set<std::string>::iterator it;
        it = table.find(s);
        if (it == table.end()) return false;
        else return true;
    }
    TokenItem()
    {
        for (int i = 48; i < 58; ++i)
            identifier.insert(char(i));
        for (int i = 65; i <=90; ++i)
            identifier.insert(char(i));
        for (int i = 97; i <=122; ++i)
            identifier.insert(char(i));
        identifier.insert(' ');
        identifier.insert('.');
        operators.insert('+');
        operators.insert('-');
        operators.insert('*');
        operators.insert('/');
        operators.insert(')');
        operators.insert('(');
        function.insert("SIN");
        function.insert("COS");
    }
};

class TokenList
{
// private:
public:
    int token_count;
    TokenItem token_array[100];
    std::string input;
    int get_token_count() { return this->token_count; }
    TokenItem get_token_item(int index) { return this->token_array[index]; }
    void set_token_count(int token_count) { this->token_count = token_count; }
    void set_token_item(int index, TokenItem item) { this->token_array[index] = item; }

};



class Validator
{
public:
    TokenList token_list;
    TokenItem token_item;

    Validator()
    {
        this->token_list.set_token_count(0);
    }

    Validator(std::string input)
    {
        this->token_list.set_token_count(0);
        this->token_list.input = input;
    }

    void validate()
    {
        int index = 0;
        while (index < (int)this->token_list.input.length())
        {
            switch(this->token_item.in(this->token_list.input[index], this->token_item.identifier))
            {
                case true: this->processIdentifier(&index, &this->token_list.token_count, this->token_list.token_array); break;
                case false: 
                {
                    switch(this->token_item.in(this->token_list.input[index], this->token_item.operators))
                    {
                        case true: this->processOperator(&index, &this->token_list.token_count, this->token_list.token_array); break;
                        case false: this->processOther(&index, &this->token_list.token_count, this->token_list.token_array); break;
                    }
                }
                
            }
        }
    }
private:
    void processIdentifier(int *ptr, int *tokenCount, TokenItem tokenArray[])
    {
        std::string newToken;
        while (this->token_item.in(this->token_list.input[*ptr], this->token_item.identifier))
        {
            newToken.append(1, this->token_list.input[*ptr]);
            (*ptr)++;
        }
        this->token_item.token.append(newToken);
        (*tokenCount)++;
        if (newToken.length() >= 3)
        {
            if ((newToken.substr(0, 3) == "SIN") || (newToken.substr(3) == "COS"))
            {
                tokenArray[*tokenCount].type = "function";
            }
        }
        else
        {
            tokenArray[*tokenCount].type = "identifier";
        }
    }

    void processOperator(int *ptr, int *tokenCount, TokenItem tokenArray[])
    {
        std::string newToken;
        int startPos = *ptr;
        while (this->token_item.in(this->token_list.input[startPos], this->token_item.operators))
        {
            newToken.append(1, this->token_list.input[startPos]);
            startPos++;
            (*ptr)++;
        }
        this->token_item.token.append(newToken);
        (*tokenCount)++;
        if (startPos != *ptr){
            tokenArray[*tokenCount].type = "badToken";
        }
        else
            tokenArray[*tokenCount].type = "operator";
    }

    void processOther(int *ptr, int *tokenCount, TokenItem tokenArray[])
    {
        std::string newToken;
        while (this->token_item.in(this->token_list.input[*ptr], this->token_item.identifier))
        {
            newToken.append(1, this->token_list.input[*ptr]);
            (*ptr)++;
        }
        tokenArray[*tokenCount].token = newToken;
        exit(-1);
        (*tokenCount)++;
        tokenArray[*tokenCount].type = "badToken";
    }
};


std::vector<std::string> split(std::string const &input) { 
    std::stringstream buffer(input);
    std::vector<std::string> ret;

    std::copy(std::istream_iterator<std::string>(buffer), 
              std::istream_iterator<std::string>(),
              std::back_inserter(ret));
    return ret;
}

int main()
{
    std::string infix;
    InfixToPostfix parser;
    char first;
    Evaluator eval;
    Functions funcs;
    std::cout << "Please input the equation. Press q afterwards to get the result INCLUDE SPACES AFTER EVERY CHARACTER: " << std::endl << std::endl;
    std::getline(std::cin, infix);
    unsigned eq = infix.find("=");
    if (eq != std::string::npos)
    {
        first = infix[0];
        infix = infix.substr(eq+1);
    }
    Validator v(infix);
    v.validate();
    SymbolTable c;
    infix = c.convert(infix);
    std::string postfix = parser.exec(infix);
    postfix = funcs.clean(postfix);

    std::vector<std::string> s = split(postfix);

    for (std::vector<std::string>::iterator it = s.begin(); it != s.end(); ++it)
    {
        if (*it == "+")
            eval.add();
        else if (*it == "-")
            eval.subtract();
        else if (*it == "*")
            eval.multiply();
        else if (*it == "/")
            eval.divide();
        else if (is_num(*it) && *it != "q")
            eval.push(atof((*it).c_str())); 
       else             
            cout << "Invalid input" << std::endl;
    }
    
          
      std::cout << first << " = ";
      do {
         std::cout << eval.pop();
      } while (!eval.empty());
      std::cout << std::endl;
   

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return 0;
}