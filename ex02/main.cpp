#include "includes/PmergeMe.hpp"
#include <exception>
#include <fstream>

int main(int ac, char **av)
{

	PmergeMe p;
	if (ac < 2) {
        std::cerr << "Error: No input provided." << std::endl;
        return 1;
    }
	try {
		
		p.fillDeq(ac, av);
		p.fillVec(ac, av);
		p.splitDeq();
		p.splitVec();
		//p.printAllCon();
	} catch (std::exception &e) {
		std::cout<<e.what()<<"\n";
	}
	

    return 0;

}

// 7 8 27 100 11 46 2 53
// 7 8 | 27 100 | 11 46 | 2 53
// 8 7 | 100 27 | 46 11 | 53 2 
// 8 7 | 46 11 | 53 2 | 100 27 MERGE SORT
// vector1 2 7 8 11 27 46 53 100
// vector2 "7" "11" "2" 27
// "1," 3, 5
// "1," 3, 2, 5, 4, 11, 10, 9, 8, 7, 6
// binarysearch
// use-> lower_bound(iterator first, iterator last, const T& value) 