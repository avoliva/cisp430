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

using namespace std;

class Expression;
class TokenList;
class PostFix;
class TokenItem
{
public:
	std::string token;
	std::string type;
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
	// int get_token_count() { return this->token_count; }
	// TokenItem get_token_item(int index) { return this->token_array[index]; }
	void set_token_count(int token_count) { this->token_count = token_count; }
	// void set_token_item(int index, TokenItem item) { this->token_array[index] = item; }

};

class PostFix
{
public:
	TokenItem tokenItem;
	int priority(char a)
	{
		int temp;
		if (a == '^')
			temp = 1;
		else if (a == '*' || a == '/')
			temp = 2;
		else if (a == '+' || a == '-')
			temp = 3;
		return temp;
	}

	void transform(std::string infix, stack<char> operator_stack, std::stringstream* output)
	{
		for (unsigned i = 0; i < infix.length(); ++i)
		{
			if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^')
			{
				while (!operator_stack.empty() && priority(operator_stack.top()) <= priority(infix[i]))
				{
					*output << operator_stack.top();
					operator_stack.pop();
				}
				operator_stack.push(infix[i]);
			} else if (infix[i] == '(') {
				operator_stack.push(infix[i]);
			} else if (infix[i] == ')') {
				while (operator_stack.top() != '(')
				{
					*output << operator_stack.top();
					operator_stack.pop();
				}
				operator_stack.pop();
			} else {
				*output << infix[i];
			}
		}

		while (!operator_stack.empty())
		{
			*output << operator_stack.top();
			operator_stack.pop();
		}
	}
};

class Expression
{
public:
	TokenList token_list;
	TokenItem token_item;
	PostFix post_fix;

	Expression()
	{
		this->token_list.set_token_count(0);
	}

	Expression(std::string input)
	{
		this->token_list.set_token_count(0);
		this->token_list.input = input;
	}

	void read()
	{
		int index = 0;
		while (index < (int)this->token_list.input.length())
		{
			std::cout << "what" << std::endl;
			std::cout << "len is " << this->token_list.input[index] << std::endl;
			// bool t = this->token_item.in(this->token_list.input[index], this->token_item.identifier);
			// std::cout << t;
			// break;
			std::cout << "character is " << this->token_list.input[index] << std::endl;
			switch(this->token_item.in(this->token_list.input[index], this->token_item.identifier))
			{
				case true: std::cout << "test" << std::endl; this->processIdentifier(&index, &this->token_list.token_count, this->token_list.token_array); break;
				case false: 
				{
					switch(this->token_item.in(this->token_list.input[index], this->token_item.operators))
					{
						case true: std::cout << "test3" << std::endl; this->processOperator(&index, &this->token_list.token_count, this->token_list.token_array); break;
						case false: std::cout << "test2" << std::endl;  this->processOther(&index, &this->token_list.token_count, this->token_list.token_array); break;
					}
				}
				
			}
			std::cout << "len is " << (int)this->token_list.input.length() << std::endl;
			std::cout << index << std::endl;
		}
	}

	void processIdentifier(int *ptr, int *tokenCount, TokenItem tokenArray[])
	{
		std::string newToken;
		// std::cout << &this->token_list.input[*ptr];
		while (this->token_item.in(this->token_list.input[*ptr], this->token_item.identifier))
		{
			newToken.append(1, this->token_list.input[*ptr]);
			(*ptr)++;
			std::cout << "this string is " << this->token_list.input[*ptr] << std::endl;
			std::cout << "ptr in loop is " << (*ptr) << std::endl;
			std::cout << "new token in loop is " << newToken << std::endl;
		}
		this->token_item.token.append(newToken);
		(*tokenCount)++;
		std::cout << "fuck " << (*tokenCount) << std::endl;
		if (newToken.length() >= 3)
		{
			if ((newToken.substr(3) == "SIN") || (newToken.substr(3) == "COS"))
			{
				tokenArray[*tokenCount].type = "function";
			}
		}
		else
		{
			tokenArray[*tokenCount].type = "identifier";
		}
		std::cout << "end" << std::endl;
		std::cout << "newToken is " << newToken << std::endl;
	}

	void processOperator(int *ptr, int *tokenCount, TokenItem tokenArray[])
	{
		std::string newToken;
		int startPos = *ptr;
		while (this->token_item.in(this->token_list.input[startPos], this->token_item.operators))
		{
			newToken.append(1, this->token_list.input[startPos]);
			std::cout << "startPos in loop is BEFORE " << startPos << std::endl;
			startPos++;
			(*ptr)++;
			std::cout << "startPos in loop is " << startPos << std::endl;
			// exit(-1);

		}
		this->token_item.token.append(newToken);
		(*tokenCount)++;
		if (startPos != *ptr){
			tokenArray[*tokenCount].type = "badToken";
			std::cout << "take this fucking bad token" << std::endl;
		}
		else
			tokenArray[*tokenCount].type = "operator";
		std::cout << "newToken is " << newToken << std::endl;
	}

	void processOther(int *ptr, int *tokenCount, TokenItem tokenArray[])
	{
		// std::cout << "LOL";
		std::string newToken;
		while (this->token_item.in(this->token_list.input[*ptr], this->token_item.identifier))
		{
			newToken.append(1, this->token_list.input[*ptr]);
			(*ptr)++;
		}
		tokenArray[*tokenCount].token = newToken;
		std::cout << "FUCKINGE XCEPTION" << std::endl;
		exit(-1);
		(*tokenCount)++;
		// std::cout  << (*tokenCount) << std::endl;
		tokenArray[*tokenCount].type = "badToken";
		std::cout << "newToken is " << newToken << std::endl;
	}
};


int main()
{
	std::string infix;

	// Postfix p;
    cout << "Enter an arithmetic expression: " << endl;
    getline(cin, infix);
	for(unsigned i=0; i<infix.length(); i++)
     if(infix[i] == ' ') infix.erase(i,1);
    Expression e(infix);
    e.read();
    // std::cout << e.pe.token_item.token << std::endl;

    stack<char> operator_stack;

    std::stringstream output;

    e.post_fix.transform(e.token_item.token, operator_stack, &output);
    cout << output.str() << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return 0;
}