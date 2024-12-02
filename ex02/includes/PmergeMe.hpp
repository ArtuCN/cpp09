#ifndef PMERGEME_HPP
#define PMERGEME_HPP

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

class PmergeMe
{
	private:

		std::vector<std::pair<int, int> > _vecPairs;
		std::deque<std::pair<int, int> > _deqPairs;

		std::vector<int> _vec;
		std::vector<int> _vec2;
		std::deque<int> _deq;
		std::deque<int> _deq2;
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &p);
		PmergeMe &operator =(const PmergeMe &p);
		~PmergeMe();

		void fillVec(int ac, char **av);
		void fillDeq(int ac, char **av);

		void swapVec(int pos1, int pos2);
		void swapDeq(int pos1, int pos2);

		void splitVec();
		void splitDeq();

		void mergePairsVec();
		void mergePairsDeq();
		void printAllCon();
		void checkNum();
		void isValidInteger(const std::string& str);
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