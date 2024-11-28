#include "includes/BitcoinExchange.hpp"
#include <exception>
#include <fstream>





int main(int ac, char **av )
{
	if (ac != 3)
		return (std::cout<<"Error: invalid number of arguments.\n", 0);
	
	BitcoinExchange btce;

	try {
		std::ifstream file(av[1]);
		if (!file.is_open())
			return (std::cout<<"Error: couldn't open "<< av[1]<<"\n", 0);
		btce.fillData(file);
		std::ifstream file2(av[2]);
		if (!file2.is_open())
			return (std::cout<<"Error: couldn't open "<< av[2]<<"\n", 0);
		btce.fillOut(file2);
	} catch (std::exception &e) {
		std::cout<<e.what();
	}

	return 0;
}
/*btc data.csv input.txt*/