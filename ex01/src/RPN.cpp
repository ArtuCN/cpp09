#include "../includes/RPN.hpp"
#include <cctype>
#include <climits>
#include <cstddef>
#include <cstring>
#include <ctime>
#include <fstream>
#include <string>


RPN::RPN()
{

}

RPN::RPN(const RPN &r)
{
	if (&r != this)
	{
		this->_counter = r._counter;
		this->_n = r._n;
		this->_op = r._op;
		this->_res = r._res;
	}
}

RPN &RPN::operator=(const RPN &r)
{
	if (&r != this)
	{
		this->_counter = r._counter;
		this->_n = r._n;
		this->_op = r._op;
		this->_res = r._res;
	}
	return *this;
}
RPN::~RPN()
{

}

void RPN::checkInput(std::string av)
{
	int num = 0;
	int op = 0;

	for (size_t i = 0; i < av.size(); i++)
	{
		if (std::isspace(av[i]))
			;
		else if (std::isdigit(av[i]))
		{
			while (av[i] && std::isdigit(av[i]))
				i++;
			num++;
		}
		else if (av[i] == '+' || av[i] == '-' || av[i] == '*' || av[i] == '/')
			op++;
		else
		 	throw exc("Error: not valid character");
	}
	if (op + 1 == num)
		return ;
	else
	 	throw exc("Error: different number of valid character");
}



double RPN::performOperation(char op, double a, double b)
{
	switch (op) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			if (b != 0) {
				return a / b;
			} else {
				throw  exc("Error: division by 0!");
				return 0;
			}
	}
	return 0;
}

void RPN::fillStack(std::string av)
{
	int num;
	for (size_t i = 0; i < av.size(); i++)
	{
		num = 0;
		if (std::isspace(av[i]))
			continue ;
		else if (std::isdigit(av[i]))
		{
			num = av[i] - 48;
			while (av[++i] && std::isdigit(av[i]))
			{
				num = (num * 10) + ((av[i] - 48));
			}
			if (num >= 10)
				throw exc(("Error: num >= 10!"));
			_n.push(num);
		}
		else if (av[i] == '+' || av[i] == '-' || av[i] == '*' || av[i] == '/')
			_op.push(av[i]);
		if (_n.size() >= 2 && _op.size() >= 1)
		{
			num = _n.top();
			_n.pop();
			_res = performOperation(_op.top(), _n.top(), num);
			_n.pop();
			_op.pop();
			_n.push(_res);
		}
	}
}

double RPN::getRes()
{
	return this->_res;
}