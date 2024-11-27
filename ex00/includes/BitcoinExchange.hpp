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
#include "algorithm"

typedef std::map<time_t, float>::iterator iterator;
typedef std::map<time_t, float>::const_iterator const_iterator;
class BitcoinExchange
{
	private:
		std::map<time_t, float> _data;
		std::map<time_t, float> _out;
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
		time_t	ftStot(std::string str);
		float	ftStof(std::string str);
		void 	fillMap(std::ifstream &file);

		time_t	findDate();
		float	calcVal();
		void	printMap();
};

#endif