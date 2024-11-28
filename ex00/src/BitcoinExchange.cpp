#include "../includes/BitcoinExchange.hpp"
#include <climits>
#include <ctime>
#include <fstream>
#include <string>

void printData(const std::map<myTime, float>& data) {
    for (std::map<myTime, float>::const_iterator it = data.begin(); it != data.end(); ++it) {
        it->first.print(); // Stampa la chiave (myTime)
        std::cout << " | " << it->second << std::endl; // Stampa il valore (float)
    }
}

std::string to_string(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

float myStof(std::string str)
{
    std::stringstream ss(str);

    float num;
    ss >> num;
    return num;
}

int ftStoi(std::string str) {

    std::stringstream ss(str);
    int num;
    ss >> num;
    return num;
}

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


myTime	BitcoinExchange::ftStot(std::string str)
{
	myTime res;

	res.year = ftStoi(str.substr(0, 4));
	res.month = ftStoi(str.substr(6, 2));
	res.day = ftStoi(str.substr(8, 2));
	return res;
}

float	BitcoinExchange::ftStof(std::string str)
{
	
	std::string temp = str.substr(11);
	float res = myStof(temp);
	return res;
}


void BitcoinExchange::fillData(std::ifstream &file)
{
	std::string str;
	std::string first;

	std::getline(file, first);
	if (first != "date,exchange_rate")
		BitcoinExchange::exc("worng first line\n");
	while (std::getline(file, str))
	{
		_data[ftStot(str)] = ftStof(str);
	}
}

bool isLeapYear(int year)
{
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        return true;
    }
    return false;
}

int BitcoinExchange::dateToDays(myTime date)
{
    int totalDays = 0;
	int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (int y = 1900; y < date.year; ++y) {
        totalDays += isLeapYear(y) ? 366 : 365;
    }
    for (int m = 0; m < date.month - 1; ++m)
	{
        totalDays += daysInMonth[m];
        if (m == 1 && isLeapYear(date.year))
            totalDays += 1;
    }
    totalDays += date.day;
    return totalDays;
}


std::string	BitcoinExchange::findDate(myTime input)
{
	long int conv = dateToDays(input);
	int diff;
	int temp = INT_MAX;
	myTime ret;
	for (std::map<myTime, float>::iterator it = _data.begin(); it != _data.end(); ++it)
	{
		
		diff = std::abs(conv - dateToDays(it->first));
		if (temp > diff)
		{
			temp = diff;
			ret = it->first;
		}
	}
	_date.day = ret.day;
	_date.month = ret.month;
	_date.year = ret.year;
	return (to_string(ret.year) + "-" + to_string(ret.month) + "-" + to_string(ret.day));
}

int	BitcoinExchange::validDate(myTime date)
{
	int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (date.year > 2024 || date.year <= 1900)
		return 0;
	if (date.month > 12 || date.month <= 0)
		return 0;
	int maxDays = daysInMonth[date.month];
	if (date.day > maxDays || date.day <= 0)
		return 0;
	return 1;
}

int BitcoinExchange::validVal(std::string str, std::string lineToAdd)
{
	if (str.length() <= 14)
		return 0;
	if (str[12] == '-')
	{
		lineToAdd = "Error: not a positive number.\n";
		return  0;
	}
	std::string temp = str.substr(12);
	for (size_t i = 0; i < temp.length(); i++)
	{
		if (!isdigit(temp[i]))
		{
			lineToAdd  = "Error: invalid value\n";
			return 0;
		}
	}
	float res = myStof(temp);
	if (res >= FLT_MAX)
	{
		lineToAdd = "Error: too large a number.\n";
		return 0;
	}
	return 1;
}

void	BitcoinExchange::validStr(std::string str)
{

	myTime date;
	std::string lineToAdd;
	date = ftStot(str);
	if (!validDate(date))
		lineToAdd = "Error: bad input => date";
	else
	{
		lineToAdd = findDate(date);
		lineToAdd+= " => ";
		if (validVal(str, lineToAdd))
		{
			std::string temp = str.substr(12);
			_val = _data[_date] * myStof(temp);
			lineToAdd += to_string(_val);
		}
	}
	_out += lineToAdd + '\n';
}

void BitcoinExchange::fillOut(std::ifstream &file)
{
	std::string line;
	std::string first;

	printData(_data);
	std::getline(file, first);
	if (first != "date | value\n")
		BitcoinExchange::exc("Wrong first line: date | value!");
	while (std::getline(file, line))
	{
		validStr(line);
	}
	std::cout<<_out;
}
