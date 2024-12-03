#include "../includes/PmergeMe.hpp"
#include <cctype>
#include <climits>
#include <cstddef>
#include <cstring>
#include <ctime>
#include <fstream>
#include <string>
#include <utility>


void PmergeMe::printAllCon()
{
	std::cout << "Vector:   ";
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		std::cout << _vec[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Vector 2: ";
	for (size_t i = 0; i < _vecPend.size(); ++i)
	{
		std::cout << _vecPend[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "Deque:   ";
	for (size_t i = 0; i < _deq.size(); ++i)
	{
		std::cout << _deq[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Deque 2: ";
	for (size_t i = 0; i < _deqPend.size(); ++i)
	{
		std::cout << _deqPend[i] << " ";
	}
	std::cout << std::endl;
}

PmergeMe::PmergeMe()
{

}

PmergeMe::PmergeMe(const PmergeMe &p)
{
	if (&p != this)
	{
		_deq = p._deq;
		_deqPend = p._deqPend;
		_vec = p._vec;
		_vecPend = p._vecPend;
	}
}

PmergeMe &PmergeMe::operator =(const PmergeMe &p)
{
	if (&p != this)
	{
		_deq = p._deq;
		_deqPend = p._deqPend;
		_vec = p._vec;
		_vecPend = p._vecPend;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{

}

void PmergeMe::isValidInteger(const std::string& str)
{
    std::stringstream ss(str);
	std::string temp;
	
	while (ss >> temp)
	{
        std::stringstream num_stream(temp);
        int num;
        
        num_stream >> num;
        
        if (num_stream.fail() || !num_stream.eof()) {
            throw exc("invalid num");
        }

        if (num < 0) {
            throw exc("num is < 0");
        }
    }
}
