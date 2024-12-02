#include "includes/BitcoinExchange.hpp"
#include <exception>
#include <fstream>


bool isValidCSV(const std::string &filename, size_t expectedColumns)
{

	std::ifstream file(filename.c_str());
    if (!file.is_open())
		return false;

    std::string line;
    size_t columnCount = 0;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
		columnCount++;
		if (line.length() < 12 || line.length() > 19)
			return false;
    }
	if (columnCount != expectedColumns) {
		return false; // Numero di colonne errato
	}
    return true;
}



int main(int ac, char **av )
{
	if (ac != 2)
		return (std::cout<<"Error: invalid number of arguments.\n", 0);
	
	BitcoinExchange btce;

	try {
		std::ifstream file("data.csv");
		if (!file.is_open())
			return (std::cout<<"Error: couldn't open data.csv\n", 0);
		if (!isValidCSV("data.csv", 1613))
			return (std::cout<<"Error: wrong file data.csv\n", 0);
		btce.fillData(file);
		std::ifstream file2(av[1]);
		if (!file2.is_open())
			return (std::cout<<"Error: couldn't open "<< av[1]<<"\n", 0);
		btce.fillOut(file2);
	} catch (std::exception &e) {
		std::cout<<e.what();
	}

	return 1;
}
/*btc data.csv input.txt*/