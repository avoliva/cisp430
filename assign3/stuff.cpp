// coercion - forced data type conversion
// 	promotion - gain zeroes for precision
// 	demotion - loss accuracy (decimal part is truncated)

// IntVar = Realresult; // demotion via coercion: C++(Ok),Java(error)
// RealVar = Integerresult; // promotion-gain zeroes.


// OperatorToken ----------> Token
// 	"An operator token IS A kind of Token"
// 	 "An operand token IS A kind of Token"
// OperandToken ---------->  Token
// Expression ----- 1 : m -----  Token
// Parser
// ParseTable: converts an "infix" expression into its
// 		    "postfix" equivalent
// 	Parser ----- 1: 1 ------ ParseTable
// SymbolTable -----------> Hashtable
// EvaluatorClass
// 	postFix ----> Evaluator ----> rhsResult
// 	Evaluator "is an instance of a" STACK

// S1 "is an instance of a" Stack
// S2"is an instance of a" Stack
// ==============================
// 	infix: A+B*C
// 	postfix: ABC*+
// 	prefix +A*BC

#include "list.h"
#include "stack.h"
#include "queue.h"
#include <map>


//#include "stack.h"

// const float A = 0.0;
// const float B = 0.0;
// const float C = 0.0;
// const float D = 0.0;

/*
List
Stack
Queue
HashTable
Expression
Token
*/

/*
An expression is just a collection of tokens.
C = SIN(A) + (C-D) * 3 // The following has 12 tokens
*/


/*
OperatorToken -> Token
    "An operator token IS a kind of token"
    "An operand token IS a kind of token"
OperandToken -> Token
Expression -- 1 : m -- Table

Parser
ParseTable converts an "infix" expressiont into its "postfix" equilvalent 

SymbolTable -> HashTable
Evaluator -> 
    postfix -> Evaluator -> rhsResult
    Evaluator is an instance of a stack

S1 -> is an instance of a stack
S2 -> is an instance of a stack
=================
    infix: A + B * C
    postfix: ABC*+
    prefix: +A*BC
*/
// int main()
// {
//     std::string expression;
//     std::getline(std::cin, expression);
    

    
//     return 0;
// }

typedef int value_type

value_type GetValue(char value)
{
	switch (value)
	{
		case 'A': break;
		case 'B': break;
		case 'C': break;
		case 'D': break;
	}
}


class Coercion

class IntVar;

class RealVar;

class OperatorToken;

class OperandToken;

class Expression;

class Parser;

class ParseTable;

class SymbolTable;

class EvaulatorClass;




/*
Input Expression Tokenizer(in String80, out TokenList)
TokenList
	tokenCount : integer
	tokenArray : array of tokenItem
TokenItem
	Token : string
	Type : {Identifier,operator,function,badToken}
	Identifer ::= {'A'..'Z','a'..'z','0'..'9','_'}
	operator ::= {'+','-','*','/','(',')'}
	function ::= {"Sin","Cos"}
		input: String max length 80 bytes
set tokenCount to zero
set tokenArray index to zero
set ptr to zero
while ptr < String80.length
	switch String80[ptr] in {Identifier}
		case TRUE: processIdentifier
		case FALSE: switch String80[ptr] in {operator}
		{
			case TRUE: processOperator
			case FALSE: processOther
		} // operator
	} // operand
end while
processIdentifier(out ptr,out tokenCount,out TokenArray)
	string newToken = null
	while string80[ptr] in {identifier} do
	{
		append string80[ptr] to newToken
		ptr++
	}
	tokenArray[tokenCount].token = newToken
	tokenCount++
	if isValidToken(newToken)
	begin
		if substring(newToken,3) = "sin" or "cos"
		tokenArray[tokenCount].type = function
	else
		tokenArray[tokenCount].type = Identifier
	end
	else
		tokenArray[tokenCount].type = badToken
end // processIdentifier

processOperator(out ptr,out tokenCount,out TokenArray)
	string newToken = null
	int startPos = ptr
	while string80[startPos] in {operator}
	{
		append string80[startPos] to newToken
		startPos++
	}
	tokenArray[tokenCount].token = newToken
	tokenCount++
	if startPos != ptr
		tokenArray[tokenCount].type = badToken
	else
		tokenArray[tokenCount].type = operator
end // processOperator

processOther(out ptr,out tokenCount,out TokenArray)
	string newToken = null
	while string80[ptr] in {identifier} do
	{
		append string80[ptr] to newToken
		ptr++
	}
	tokenArray[tokenCount].token = newToken
	tokenCount++
	tokenArray[tokenCount].type = badToken
end // processOther

*/