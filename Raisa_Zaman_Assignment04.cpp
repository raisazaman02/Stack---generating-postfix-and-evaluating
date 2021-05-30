//============================================================
// Assignment- 04
// Name- Raisa Zaman
// Date- 2/04/2020
// Last edited- 10:52 PM
// Title: Stack - generating postfix and evaluating
// Description:
//    This C++ console application uses stacks to go from infix to postfix, and 
// uses values in the postfix equation to evaluate the expression. 
//
//==========================================================

#include <conio.h> // For function getch()
#include <cstdlib>  // For several general-purpose functions
#include <cmath> //calculate power function
#include <fstream>  // For file handling
#include <iomanip>  // For formatted output
#include <iostream>  // For cin, cout, and system
#include <string>  // For string data
#include <stack> // For stack 

using namespace std;

bool Operand(char C)
{
	if (C >= '0' && C <= '9')
	{
		return true;
	}
	if (C >= 'a' && C <= 'z')
	{
		return true;
	}
	if (C >= 'A' && C <= 'Z')
	{
		return true;
	}
	return false;
}

bool Operator(char C)
{
	if (C == '+' || C == '-' || C == '*' || C == '/' || C == '^')
	{
		return true;
	}
	return false;
}

bool OpeningParentheses(char C)
{
	if (C == '(' || C == '{' || C == '[')
	{
		return true;
	}
	return false;
}

bool ClosingParentheses(char C)
{
	if (C == ')' || C == '}' || C == ']')
	{
		return true;
	}
	return false;
}

int RightToLeft(char op)
{
	if (op == '^')
	{
		return true;
	}
	return false;
}

int OperatorPlacement(char op)
{
	int weight = 0;
	switch (op)
	{
	case '+':
	case '-':
		weight = 1;
		break;
	case '*':
	case '/':
		weight = 2;
		break;
	case '^':
		weight = 3;
	}
	return weight;
}

int Precedence(char op1, char op2)
{
	int op1Weight = OperatorPlacement(op1);
	int op2Weight = OperatorPlacement(op2);

	if (op1Weight == op2Weight)
	{
		if (RightToLeft(op1))
			return false;
		else
		{
			return true;
		}
	}
	return op1Weight > op2Weight ? true : false;
}

string InfixPostfix(string expression)
{
	stack<char> stackLetter;
	string postfix = "";
	for (int i = 0; i < expression.length(); i++)
	{

		if (expression[i] == ' ')
		{
			continue;
		}

		else if (Operand(expression[i]))
		{
			postfix += expression[i];
		}

		else if (Operator(expression[i]))
		{
			while (!stackLetter.empty() && !OpeningParentheses(stackLetter.top())
				&& Precedence(stackLetter.top(), expression[i]))
			{
				postfix += stackLetter.top();
				stackLetter.pop();
			}
			stackLetter.push(expression[i]);
		}

		else if (OpeningParentheses(expression[i]))
		{
			stackLetter.push(expression[i]);
		}

		else if (ClosingParentheses(expression[i]))
		{
			while (!stackLetter.empty() && !OpeningParentheses(stackLetter.top()))
			{
				postfix += stackLetter.top();
				stackLetter.pop();
			}
			stackLetter.pop();
		}
	}

	while (!stackLetter.empty())
	{
		postfix += stackLetter.top();
		stackLetter.pop();
	}

	return postfix;
}

int postfixEval(string exp)
{
	stack<int> stackNum;

	for (int i = 0; i < exp.size(); i++)
	{
		if (exp[i] == 'a')
			stackNum.push(1);
		else if (exp[i] == 'b')
			stackNum.push(2);
		else if (exp[i] == 'c')
			stackNum.push(3);
		else if (exp[i] == 'd')
			stackNum.push(10);
		else if (exp[i] == 'e')
			stackNum.push(5);
		else if (exp[i] == 'f')
			stackNum.push(15);
		else if (exp[i] == 'g')
			stackNum.push(6);
		else if (exp[i] == 'h')
			stackNum.push(4);
		else if (exp[i] == 'i')
			stackNum.push(8);
		else if (exp[i] == 'j')
			stackNum.push(7);
		else if (exp[i] == '+')
		{
			int x = stackNum.top();
			stackNum.pop();
			int y = stackNum.top();
			stackNum.pop();
			stackNum.push(y + x);
		}
		else if (exp[i] == '-')
		{
			int x = stackNum.top();
			stackNum.pop();
			int y = stackNum.top();
			stackNum.pop();
			stackNum.push(y - x);
		}
		else if (exp[i] == '*')
		{
			int x = stackNum.top();
			stackNum.pop();
			int y = stackNum.top();
			stackNum.pop();
			stackNum.push(y * x);
		}
		else if (exp[i] == '/')
		{
			int x = stackNum.top();
			stackNum.pop();
			int y = stackNum.top();
			stackNum.pop();
			stackNum.push(y / x);
		}
		else if (exp[i] == '^')
		{
			int x = stackNum.top();
			stackNum.pop();
			int y = stackNum.top();
			stackNum.pop();
			stackNum.push(pow(x, y));
		}
	}
	return stackNum.top();
}


int main()
{
	string expression = "(f+b)-(d-e)*(f+(g-h)/(i-j))+(a+b)^c";
	string postfix = InfixPostfix(expression);
	cout << "Infix to postfix = " << postfix << endl << endl;
	cout << "Postfix expression evaluation = " << postfixEval(postfix) << endl;
}