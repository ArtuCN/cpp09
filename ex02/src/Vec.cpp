#include "../includes/PmergeMe.hpp"

void PmergeMe::fillVec(int ac, char **av)
{
	for (int i = 1; i < ac; i++){
        std::string arg = av[i];
		isValidInteger(arg);
        std::stringstream ss(arg);
        int number;
        while (ss >> number)
            _vec.push_back(number);
	}
}

void PmergeMe::vecBinarySearch(int val)
{

	int left = 0; 
	int right = _vec.size();
	int pos = -1; 

	while (left < right) {
		int mid = left + (right - left) / 2;

		if (_vec[mid] < val)
		{
			left = mid + 1;
		} else 
		{
			right = mid;
		}
	}
	pos = left;
	_vec.insert(_vec.begin() + pos, val);
}

void PmergeMe::splitVec()
{
	_vecStart = clock();
	std::vector<std::pair<int, int> > vecPairs;
	int last = -1;
	vecPairs.clear();
	if (_vec.size()%2 != 0)
	{
		last = _vec.back();
		_vec.pop_back();
	}
	while(!_vec.empty())
	{
		int first = _vec.back();
		_vec.pop_back();
		int second = _vec.back();
		_vec.pop_back();
		if (first < second)
			vecPairs.push_back(std::make_pair(second,first));
		else
			vecPairs.push_back(std::make_pair(first,second));
	}
	mergePairsVec(vecPairs, 0, vecPairs.size()-1);
	while (!vecPairs.empty())
	{
		_vecPend.push_back(vecPairs.front().second);
    	_vec.push_back(vecPairs.front().first);
    	vecPairs.erase(vecPairs.begin());
	}
	vecJacobPush(last);
}

void PmergeMe::vecJacobPush(int last)
{
	int i = 0;
	while(i < (int)_jacob.size())
	{
		int toPush = _jacob[i] - 1;
		int nextID = (i + 1 < (int)_jacob.size()) ? _jacob[i + 1] - 1 : (int)_vecPend.size();
		while (toPush < nextID && toPush < (int)_vecPend.size())
		{
			if (toPush < 0 || toPush >= (int)_vecPend.size())
            	break;
			vecBinarySearch(_vecPend[toPush]);
			toPush++;
		}
		i++;
	}
	if (last != -1)
	{
		vecBinarySearch(last);
	}
	_vecEnd = clock();
	std::cout << "Time to process a range of " << _vec.size()<<  " elements with std::vector time: "<< (double)(_vecEnd - _vecStart) / CLOCKS_PER_SEC << "\n";
}

void PmergeMe::mergeVec(std::vector<std::pair<int, int> > &vecPairs, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

	std::vector<std::pair<int, int> > L(n1), R(n2);
	for (int i = 0; i < n1; i++)
		L[i] = vecPairs[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = vecPairs[mid + 1 + j];
	int i = 0, j = 0;
    int k = left;
	while (i < n1 && j < n2)
	{
		if (L[i].first <= R[j].first)
		{
			vecPairs[k] = L[i];
			i++;
		}
		else
		{
			vecPairs[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
        vecPairs[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        vecPairs[k] = R[j];
        j++;
        k++;
    }
}

void PmergeMe::mergePairsVec(std::vector<std::pair<int, int> > &vecPairs, int left, int right)
{
	if (left >= right)
		return;
	int mid = left + (right - left) / 2;
	mergePairsVec(vecPairs, left, mid);
	mergePairsVec(vecPairs, mid + 1, right);
	mergeVec(vecPairs, left, mid, right);
}