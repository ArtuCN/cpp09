#include "../includes/BitcoinExchange.hpp"
#include <fstream>
#include <string>

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &btce)
{
	if (this != &btce)
	{
		*this = btce;
	}
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &btce)
{
	_out = btce._out;
	_data = btce._data;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{

}



void BitcoinExchange::fillMap(std::ifstream &file)
{
	std::string str;

	while (std::getline(file, str))
	{
		
	}
}

