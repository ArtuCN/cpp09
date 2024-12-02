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
    std::cout << "Vector: ";
    for (size_t i = 0; i < _vec.size(); ++i)
    {
        std::cout << _vec[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Vector 2: ";
    for (size_t i = 0; i < _vec2.size(); ++i)
    {
        std::cout << _vec2[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Vector of Pairs: ";
    for (size_t i = 0; i < _vecPairs.size(); ++i)
    {
        std::cout << "(" << _vecPairs[i].first << ", " << _vecPairs[i].second << ") ";
    }
    std::cout << std::endl;

    std::cout << "Deque: ";
    for (size_t i = 0; i < _deq.size(); ++i)
    {
        std::cout << _deq[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Deque 2: ";
    for (size_t i = 0; i < _deq2.size(); ++i)
    {
        std::cout << _deq2[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Deque of Pairs: ";
    for (size_t i = 0; i < _deqPairs.size(); ++i)
    {
        std::cout << "(" << _deqPairs[i].first << ", " << _deqPairs[i].second << ") ";
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
		_deq2 = p._deq2;
		_vec = p._vec;
		_vec2 = p._vec2;
	}
}

PmergeMe &PmergeMe::operator =(const PmergeMe &p)
{
	if (&p != this)
	{
		_deq = p._deq;
		_deq2 = p._deq2;
		_vec = p._vec;
		_vec2 = p._vec2;
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

void PmergeMe::fillDeq(int ac, char **av)
{
	for (int i = 1; i < ac; i++) {
        std::string arg = av[i];
		isValidInteger(arg);
        std::stringstream ss(arg);
        int number;
        while (ss >> number)
		{
            _deq.push_back(number);
        }
    }
}

void PmergeMe::fillVec(int ac, char **av)
{
	for (int i = 1; i < ac; i++)
	{
        std::string arg = av[i];
		isValidInteger(arg);
        std::stringstream ss(arg);
        int number;
        while (ss >> number)
		{
            _vec.push_back(number);
        }
	}
}

void PmergeMe::swapVec(int pos1, int pos2)
{
	int temp = _vec[pos1];

	_vec[pos1] = _vec[pos2];
	_vec[pos2] = temp;
}

void PmergeMe::swapDeq(int pos1, int pos2)
{
	int temp = _deq[pos1];

	_deq[pos1] = _deq[pos2];
	_deq[pos2] = temp;
}

void PmergeMe::splitVec()
{
	_vecPairs.clear();
	for (size_t i = 0; i < _vec.size(); i+= 2)
	{
		if (i >= _vec.size())
			break ;
		if (_vec[i] < _vec[i + 1])
			swapVec(i, i + 1);
		int first = _vec[i];
		int second = _vec[i + 1];
		_vecPairs.push_back(std::make_pair(first,second));
	}
}

void PmergeMe::splitDeq()
{	
	_deqPairs.clear();
	for (size_t i = 0; i < _deq.size(); i+= 2)
	{
		if (i >= _deq.size())
			break ;
		if (_deq[i] < _deq[i + 1])
			swapDeq(i, i + 1);
		int first = _deq[i];
		int second = _deq[i + 1];
		_vecPairs.push_back(std::make_pair(first,second));
	}
}

void PmergeMe::mergePairsVec()
{

}

void PmergeMe::mergePairsDeq()
{

}

