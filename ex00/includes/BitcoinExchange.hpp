#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <exception>
#include <iostream>
#include <ctime>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <list>
#include <limits>
#include "algorithm"
#include <sstream>
#include <iomanip> 
#include <cmath>
#include <cmath>   // Per std::round
#include <cstdlib> // Per std::strtod
#include <cstring> // Per std::strcpy

typedef std::map<time_t, double>::iterator iterator;
typedef std::map<time_t, double>::const_iterator const_iterator;


struct myTime
{
	int year;
	int month;
	int day;
	bool operator==(const myTime& other) const {
		return year == other.year && month == other.month && day == other.day;
	}
	bool operator<(const myTime& other) const {
		if (year != other.year) return year < other.year;
		if (month != other.month) return month < other.month;
		return day < other.day;
	}
	void print() const {
		std::cout << year << "-" 
				<< (month < 10 ? "0" : "") << month << "-" 
				<< (day < 10 ? "0" : "") << day;
	}
};

class BitcoinExchange
{
	private:
		std::map<myTime, double> _data;
		std::string _out;
		myTime _date;
		double _val;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &btce);
		BitcoinExchange &operator=(const BitcoinExchange &btce);
		~BitcoinExchange();

		class exc: public std::exception
		{
			private:
				std::string _s;
			public:
				exc(std::string s): _s(s) {};
				~exc() throw() {};
				const char* what() const throw()
				{
					return _s.c_str();
				};
		};
		int		validVal(std::string str, std::string &lineToAdd);
		int		validDate(myTime date);
		int		dateToDays(myTime date);
		void	validStr(std::string str);
		myTime	ftStot(std::string str);
		double	ftStof(std::string str);
		void 	fillData(std::ifstream &file);
		void	fillOut(std::ifstream &file);
		std::string	findDate(myTime input);
		double	calcVal();
		void	printMap();
};

#endif