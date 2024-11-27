#include "includes/BitcoinExchange.hpp"





int main(int ac, char **av )
{
	if (ac != 3)
		return (std::cout<<"Error: invalid number of arguments.\n", 0);
	
	BitcoinExchange btce;

	try {
		std::ifstream file(av[1]);
		if (!file.is_open())
			return (std::cout<<"Error: couldn't open "<< av[1]<<"\n", 0);
		btce.fillMap(file);
	} catch () {
	
	}

	return 0;
}
/*btc data.csv input.txt*/