#include "../includes/PmergeMe.hpp"

void PmergeMe::fillDeq(int ac, char **av)
{
	for (int i = 1; i < ac; i++) {
        std::string arg = av[i];
		isValidInteger(arg);
        std::stringstream ss(arg);
        int number;
        while (ss >> number)
            _deq.push_back(number);
    }
	if (_deq.size() == 1)
		throw exc("Only one element.");
	bool ordered = true;
	for (size_t i = 0; i < _deq.size(); i++)
	{
		int t = _deq[i];
		if (std::count(_deq.begin(), _deq.end(), t) > 1)
			throw exc("Error: duplicate element.");
		if (i + 1 < _deq.size())
		{
			if (_deq[i] < _deq[i + 1])
				ordered = false;
		} 
	}
	if (ordered == true)
		throw exc("Already ordered!");

}

void PmergeMe::deqBinarySearch(int val)
{
	int left = 0; 
	int right = _deq.size();
	int pos = -1; 

	while (left < right) {
		int mid = left + (right - left) / 2;

		if (_deq[mid] < val)
		{
			left = mid + 1;
		} else 
		{
			right = mid;
		}
	}
	pos = left;
	_deq.insert(_deq.begin() + pos, val);
}

void PmergeMe::splitDeq()
{
	_deqStart = clock();
	std::deque<std::pair<int, int> > deqPairs;
	int last = -1;
	deqPairs.clear();
	if (_deq.size()%2 != 0)
	{
		last = _deq.back();
		_deq.pop_back();
	}
	while(!_deq.empty())
	{
		int first = _deq.back();
		_deq.pop_back();
		int second = _deq.back();
		_deq.pop_back();
		if (first < second)
			deqPairs.push_back(std::make_pair(second,first));
		else
			deqPairs.push_back(std::make_pair(first,second));
	}
	mergePairsDeq(deqPairs, 0, deqPairs.size() - 1);
	while (!deqPairs.empty())
	{
		_deqPend.push_back(deqPairs.front().second);
		_deq.push_back(deqPairs.front().first);
		deqPairs.pop_front();
	}
	_deq.push_front(_deqPend.front());
	_deqPend[0] = -1;
	deqJacobPush(last);
}

void PmergeMe::deqJacobPush(int last)
{
	unsigned id = 3;
	unsigned int limit = 0;
	unsigned int nlimit;
	if (_deqPend.size() <= id)
	{
		if (_deqPend[1])
			deqBinarySearch(_deqPend[1]);
	}
	else
	{
		while (id <= _deqPend.size())
		{
			unsigned id2 = (id < _jacob.size()) ? _jacob[id] - 1 : _deqPend.size() - 1;
			while (id2 >= _deqPend.size())
				id2--;
			nlimit = id2;
			while (id2 > limit)
			{
				if (_deqPend[id2] == -1)
					break;
				deqBinarySearch(_deqPend[id2]);
				_deqPend[id2] = -1;
				id2--;
			}
			limit = nlimit;
			id++;
		}
	}
	if (last != -1)
	{
		deqBinarySearch(last);
	}
	_deqEnd = clock();
	std::cout << "Deque time:   "<<(double)(_deqEnd - _deqStart) / CLOCKS_PER_SEC << "\n";
}

void PmergeMe::mergeDeq(std::deque<std::pair<int, int> > &deqPairs, int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;

	std::deque<std::pair<int, int> > L(n1), R(n2);
	for (int i = 0; i < n1; i++)
		L[i] = deqPairs[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = deqPairs[mid + 1 + j];
	int i = 0, j = 0;
	int k = left;
	while (i < n1 && j < n2)
	{
		if (L[i].first <= R[j].first)
		{
			deqPairs[k] = L[i];
			i++;
		}
		else
		{
			deqPairs[k] = R[j];
			j++;	
		}
		k++;
	}
	while (i < n1) {
		deqPairs[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		deqPairs[k] = R[j];
		j++;
		k++;
	}
}

void PmergeMe::mergePairsDeq(std::deque<std::pair<int, int> > &deqPairs, int left, int right)
{
	if (left >= right)
		return;
	int mid = left + (right - left) / 2;
	mergePairsDeq(deqPairs, left, mid);
	mergePairsDeq(deqPairs, mid + 1, right);
	mergeDeq(deqPairs, left, mid, right);
}
