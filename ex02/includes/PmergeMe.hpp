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
#include <deque>
#include <ctime>
#include <bits/types/timer_t.h>

class PmergeMe
{
	private:

		clock_t _vecStart;
		clock_t _vecEnd;
		clock_t _deqStart;
		clock_t _deqEnd;

		std::vector<int> _vec;
		std::vector<int> _vecPend;
		std::deque<int> _deq;
		std::deque<int> _deqPend;
		int _prev1;
		int _prev2;
		int _currId;
		std::vector<int> _jacob;
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &p);
		PmergeMe &operator =(const PmergeMe &p);
		~PmergeMe();

		void fillVec(int ac, char **av);
		void fillDeq(int ac, char **av);

		void splitVec();
		void splitDeq();


		void mergeVec(std::vector<std::pair<int, int> > &vecPairs, int left, int mid, int right);
		void mergeDeq(std::deque<std::pair<int, int> > &deqPairs, int left, int mid, int right);

		void mergePairsVec(std::vector<std::pair<int, int> > &vecPairs, int left, int right);
		void mergePairsDeq(std::deque<std::pair<int, int> > &deqPairs, int left, int right);

		void vecBinarySearch(int val);
		void deqBinarySearch(int val);

		void vecJacobPush(int last);
		void deqJacobPush(int last);

		void calculateJacobs();
		void printAllCon();
		void checkNum();

		void printDeq(std::deque<int> toprint);

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