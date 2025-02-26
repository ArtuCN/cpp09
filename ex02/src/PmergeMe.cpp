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
	if (_vec.size() <= 4)
	{
		for (size_t i = 0; i < _vec.size(); ++i)
		{
			std::cout << _vec[i] << " ";
		}
	}
	else
		std::cout<< _vec[0] << " " << _vec[1] << " ... " << _vec[_vec.size() - 2] << " " <<_vec[_vec.size() - 1];
	std::cout << std::endl;
	std::cout << "Deque:   ";
	if (_deq.size() <= 4)
	{
		for (size_t i = 0; i < _deq.size(); ++i)
		{
			std::cout << _deq[i] << " ";
		}
	}
	else
		std::cout<< _deq[0] << " " << _deq[1] << " ... " << _deq[_deq.size() - 2] << " " <<_deq[_vec.size() - 1];
	std::cout << std::endl;
}

PmergeMe::PmergeMe()
{
	_currId = 1;
	_prev1 = 1;
	_prev2 = 0;
}

PmergeMe::PmergeMe(const PmergeMe &p)
{
	if (&p != this)
	{
		_deq = p._deq;
		_deqPend = p._deqPend;
		_vec = p._vec;
		_vecPend = p._vecPend;
		_jacob = p._jacob;
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
		_jacob = p._jacob;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{

}

void PmergeMe::calculateJacobs() {
    int size = _deqPend.size();

    _jacob.clear();
    _jacob.push_back(0);
    if (size == 0) return;

    _jacob.push_back(1);
    for (int i = 2; i <= size; ++i) {
        int curr = _jacob[i - 1] + 2 * _jacob[i - 2];
        _jacob.push_back(curr);
    }
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
            throw exc("Error: invalid num");
        }

        if (num < 0) {
            throw exc("Error: num is < 0");
        }
    }
}
