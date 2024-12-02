#include "includes/RPN.hpp"
#include <exception>
#include <fstream>

int main(int ac, char **av)
{
	if (ac != 2)
		return (std::cout<< "Error: wrong number of arguments\n", 0);
	RPN r;
	try {
		r.checkInput(av[1]);
		r.fillStack(av[1]);
		std::cout<< r.getRes()<<"\n";
	} catch (std::exception &e) {
		std::cout<<e.what()<<"\n";
	}

}