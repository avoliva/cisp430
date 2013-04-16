/*

  Simple RPN Parser written by Jiin.

*/

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Stack
{
    private:
        char *s;
        int count;


    public:
        int empty()
        {
            return (( count != 0 ) ? 1 : 0);
        }
        Stack()
        {
            s = NULL;
            count = 0;
        }

        ~Stack()
        {
            if( s != NULL )
                free(s);
        }

        char pop()
        {
            return (( this->empty() != 0 ) ? s[count--] : '$' );
        }

        char top()
        {
            return (( this->empty() != 0 ) ? s[count] : '$' );
        }

        void push( char value )
        {
            s = ( char *)realloc( s, sizeof(char) * (count + 1) );
            s[++count] = value;
        }

        int size()
        {
            return count;
        }
};

class RPN
{
    public:
        RPN() {}

        string exec( string infix )
        {
            if( infix.length() == 0 )
            {
                return "Error";
            } else {

                Stack stack;

                int pop_value, pinfix, pstack;
                char temp_top;

                string postfix;

                for( string::iterator it = infix.begin(); it < infix.end(); it++ )
                {
                    if( *it != '(' && *it != ')' && *it != '+' && *it != '-' && *it != '*' && *it != '/' )
                    {
                        postfix += *it;
                    } else if( *it == '(' ) {
                      stack.push(' ');
                        stack.push( *it );
                    } else if( *it == ')' ) {
                        while(( pop_value = stack.pop() ) != '(' )
                        {
                            postfix += pop_value;
                        }
                    } else {
                        pinfix = this->priority_operator( *it );
                        temp_top = stack.top();
                        pstack = this->priority_operator( temp_top );

                        if( pinfix > pstack )
                        {
                            stack.push(' ');
                            stack.push( *it );
                        } else {
                            while( pstack >= pinfix )
                            {
                                if( temp_top == '$' )
                                    break;

                                pop_value = stack.pop();
                                temp_top = stack.top();

                                postfix += pop_value;
                                pstack = this->priority_operator( temp_top );
                            }
                            stack.push( *it );
                        }
                    }
                }
                while(( pop_value = stack.pop() ) != '$' )
                    postfix += (pop_value + ' ');

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

#include <iostream>

int main( void ) 
{
        RPN parser;
        cout << "Parsed Expression: " << parser.exec("C = 32323.2323 + (5-4) * 3") << endl;
        return 0;
}