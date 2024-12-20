#include "../includes/BitcoinExchange.hpp"
#include <cctype>
#include <climits>
#include <cstring>
#include <ctime>
#include <fstream>
#include <string>

void printData(const std::map<myTime, double>& data) {
    for (std::map<myTime, double>::const_iterator it = data.begin(); it != data.end(); ++it) {
        it->first.print(); // Stampa la chiave (myTime)
        std::cout << " | " << it->second << std::endl; // Stampa il valore (double)
    }
}

std::string to_string(int value, int date) {
    std::stringstream ss;
    ss << value;
	if (date && value < 10)
    	return ("0" + (ss.str()));
	else
	 	return ss.str();
}

double myStof(std::string str)
{
	char c[str.length()];
	std::strcpy(c, str.c_str());	
	double num;
    num = std::strtod(c, NULL);
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
	res.month = ftStoi(str.substr(5, 2));
	res.day = ftStoi(str.substr(8, 2));
	return res;
}

double	BitcoinExchange::ftStof(std::string str)
{
	
	std::string temp = str.substr(11);
	double res = myStof(temp);
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
		{
			daysInMonth[1] = 29;
            totalDays += 1;
		}
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
	for (std::map<myTime, double>::iterator it = _data.begin(); it != _data.end(); ++it)
	{
		if (dateToDays(it->first) <= conv)
		{
			diff = conv - dateToDays(it->first);
			if (temp > diff)
			{
				temp = diff;
				ret = it->first;
			}
		}
	}
	_date.day = ret.day;
	_date.month = ret.month;
	_date.year = ret.year;
	// std::cout<<"moth "<<_date.month<<"\n";
	return (to_string(ret.year, 0) + "-" + to_string(ret.month, 1) + "-" + to_string(ret.day, 1));
}

int	BitcoinExchange::validDate(myTime date)
{
	int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (date.year > 2024 || date.year <= 1900)
		return 0;
	if (isLeapYear(date.year))
		daysInMonth[1] = 29;
	if (date.month > 12 || date.month <= 0)
		return 0;
	int maxDays = daysInMonth[date.month - 1];
	if (date.day > maxDays || date.day <= 0)
		return 0;
	return 1;
}

int BitcoinExchange::validVal(std::string str, std::string &lineToAdd)
{
	if (str.length() < 14)
		return 0;
	if (str[13] == '-')
	{
		lineToAdd = "Error: not a positive number.";
		return  0;
	}
	std::string temp = str.substr(12);
	for (size_t i = 0; i < temp.length(); i++)
	{
		if (!isdigit(temp[i]) && temp[i] != '.' && !temp[i])
		{
			lineToAdd  = "Error: invalid value";
			return 0;
		}
	}
	double res = myStof(temp);
	if (res > 1000)
	{
		lineToAdd = "Error: too large a number.";
		return 0;
	}
	return 1;
}

bool	checkLine(std::string str)
{
	if (str.length() < 4 || !std::isdigit(str[0]) || !std::isdigit(str[1])
		|| !std::isdigit(str[2]) || !std::isdigit( str[3]))
		return false;
	if (str.length() < 7 || str[4] != '-'
		|| !std::isdigit(str[5]) || !std::isdigit(str[6]))
		return false;
	if (str.length() < 10 || str[7] != '-'
		|| !std::isdigit(str[8]) || !std::isdigit(str[9]))
		return false;
	
	return true;
}

bool isAllDigits(const std::string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (!std::isdigit(str[i]) && !std::isspace(str[i]) && (str[i] != '.' && !std::isdigit(str[i + 1]) ))
            return false;
    }
    return true;
}

void	BitcoinExchange::validStr(std::string str)
{
	_val = -1;
	myTime date;
	std::string lineToAdd;
	if (!checkLine(str))
	{
		std::cout<<"Error: wrong line\n";
		return;
	}
	date = ftStot(str);
	if (!validDate(date))
		lineToAdd = "Error: bad input => " + to_string(date.year, 0)
			+ "-" + to_string(date.month, 1)
			+ "-" + to_string(date.day, 1);
	else if (str.substr(10, 3) != " | ")
		lineToAdd ="Error: no ' | '";
	else if (!isAllDigits(str.substr(13)))
		lineToAdd = "Error: wrong number " + str.substr(13);
	else
	{
		lineToAdd = findDate(date);
		if (validVal(str, lineToAdd))
		{
			lineToAdd = to_string(date.year, 0) + "-" + to_string(date.month, 1) + "-" + to_string(date.day, 1);
			lineToAdd += " => ";
			std::string temp = str.substr(12);
			_val = _data[_date] * myStof(temp);
			lineToAdd += (str.substr(13) + " = ");
		}
	}
	if (_val != -1)
		std::cout<< lineToAdd << _val << "\n";
	else
		std::cout<< lineToAdd << "\n";
}

void BitcoinExchange::fillOut(std::ifstream &file)
{
	std::string line;

	// printData(_data);
	while (std::getline(file, line))
	{
		validStr(line);
	}
	// std::cout<<_out;
}
