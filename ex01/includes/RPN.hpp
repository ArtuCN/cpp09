#ifndef RPN_HPP
#define RPN_HPP

#include <exception>
#include <iostream>
#include <ctime>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <list>
#include <limits>
#include "algorithm"
#include <sstream>
#include <iomanip> 
#include <cmath>
#include <cmath>   // Per std::round
#include <cstdlib> // Per std::strtod
#include <cstring> // Per std::strcpy
#include <stack>

class RPN
{
	private:
		std::stack<int> _n;
		std::stack<char> _op;
		int _counter;
		double _res;
	public:
		RPN();
		RPN(const RPN &r);
		RPN &operator=(const RPN &r);
		~RPN();

		void checkInput(std::string av);
		void fillStack(std::string av);
		double performOperation(char op, double a, double b);

		double getRes();
		class exc: public std::exception
		{
			private:
				std::string _str;
			public:
				exc(std::string s): _str(s) {}; 
				~exc() throw() {};
				const char* what() const throw()
				{
					return _str.c_str();
				};
		};

};

#endif