#include "../includes/PmergeMe.hpp"

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

void PmergeMe::splitDeq()
{	
	std::deque<std::pair<int, int> > deqPairs;
	deqPairs.clear();
	int last = -1;
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
	_deqPend.pop_front();
	// if (last != -1)
	// 	_deq.push_front(last);
	(void)last;
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
			deqPairs[k].first = L[i].first;
			deqPairs[k].second = L[i].second;
			i++;
		}
		else
		{
			deqPairs[k].first = R[j].first;
			deqPairs[k].second = R[j].second;
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

// 8 6 | 3 5 | 4 1 | 7 10
// 8 6 | 3 5 |
//
void PmergeMe::mergePairsDeq(std::deque<std::pair<int, int> > &deqPairs, int left, int right)
{
	if (left >= right)
		return;
	int mid = left + (right - left) / 2;
	mergePairsDeq(deqPairs, left, mid);
	mergePairsDeq(deqPairs, mid + 1, right);
	mergeDeq(deqPairs, left, mid, right);
}
