#include "../includes/PmergeMe.hpp"

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


void PmergeMe::splitVec()
{
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
	// if (last != -1)
	// 	_vec.push_back(last);
	while (!vecPairs.empty())
	{
		_vecPend.push_back(vecPairs.front().second);  // Aggiungi il secondo elemento in ordine
    	_vec.push_back(vecPairs.front().first);  // Aggiungi il primo elemento in ordine
    	vecPairs.erase(vecPairs.begin());
	}
	_vec.insert(_vec.begin(), _vecPend.front());
	_vecPend.erase(_vecPend.begin());
	(void)last;
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