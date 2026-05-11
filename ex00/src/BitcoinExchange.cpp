/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:44:14 by daafonso          #+#    #+#             */
/*   Updated: 2026/05/11 17:32:19 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

int loadDatabase(const std::string& filename, std::map<std::string, double>& map) {

	// open the file
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		std::cerr << "Error: could not open data.csv\n";
		return 0;
	}

	std::string line;

	// check empty file
	if (!std::getline(file, line)) {
		std::cerr << "Error: empty data.csv\n";
		return 0;
	}

	// check headers
	if (line != "date,exchange_rate") {
		std::cerr << "Error: bad data.csv header\n";
		return 0;
	}

	while (std::getline(file, line)) {
		if (line.empty())
			continue;

		// check data.csv
		size_t pos = line.find(',');
		if (pos == std::string::npos || pos == 0 || pos == line.size() - 1) {
			std::cerr << "Error: bad data.csv line => " << line << std::endl;
			return 0;
		}

		// trim date and rate
		std::string date = trim(line.substr(0, pos));
		std::string rate = trim(line.substr(pos + 1));

		if (!isValidDate(date)) {
			std::cerr << "Error: bad data.csv date => " << line << std::endl;
			return 0;
		}

		std::stringstream ss(rate);
		double nb;
		char extra;

		if (!(ss >> nb) || (ss >> extra)) {
			std::cerr << "Error: bad data.csv rate => " << line << std::endl;
			return 0;
		}
		map[date] = nb;
	}

	if (map.empty()) {
		std::cerr << "Error: data.csv has no data\n";
		return 0;
	}
	return 1;
}

std::string trim(std::string str) {
	size_t start = 0;
	while (start < str.size() && str[start] == ' ')
		start++;

	size_t end = str.size();
	while (end > start && str[end - 1] == ' ')
		end--;

	return str.substr(start, end - start);
}

bool isLeapYear(int year) {
	return ((year % 4 == 0 && year % 100 != 0)
		|| (year % 400 == 0));
}

bool isValidDate(const std::string& date) {

	// format YYYY-MM-DD
	if (date.length() != 10)
		return false;

	if (date[4] != '-' || date[7] != '-')
		return false;

	for (int i = 0; i < 10; i++) {

		if (i == 4 || i == 7)
			continue;

		if (!std::isdigit(date[i]))
			return false;
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	// month
	if (month < 1 || month > 12)
		return false;

	// days in month
	int daysInMonth[] =
	{
		31, // jan
		28, // feb
		31,
		30,
		31,
		30,
		31,
		31,
		30,
		31,
		30,
		31
	};

	// leap year
	if (month == 2 && isLeapYear(year))
		daysInMonth[1] = 29;

	// day check
	if (day < 1 || day > daysInMonth[month - 1])
		return false;

	return true;
}

int parseInput(const std::string& filename, std::map<std::string, double>& map) {
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		std::cerr << "Error: could not open input file\n";
		return 0;
	}

	std::string line;

	while (std::getline(file, line)) {
		if (line.empty())
			continue;

		if (line[0] == '#')
			continue;

		if (line == "date | value")
			continue;

		size_t pos = line.find(" | ");
		if (pos == std::string::npos) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = trim(line.substr(0, pos));
		std::string valueStr = trim(line.substr(pos + 3));

		// validate date
		if (!isValidDate(date)) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::stringstream ss(valueStr);
		double value;
		char extra;

		if (!(ss >> value) || (ss >> extra)) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		if (value < 0) {
			std::cerr << "Error: not a positive number.\n";
			continue;
		}
		if (value > 1000) {
			std::cerr << "Error: too large a number.\n";
			continue;
		}
		std::map<std::string, double>::iterator it = map.lower_bound(date);

		if (it == map.end()) {
			it--;
		}
		else if (it->first != date) {
			if (it == map.begin()) {
				std::cerr << "Error: no earlier date.\n";
				continue;
			}
			it--;
		}

		double result = value * it->second;
		std::cout << date << " => " << value << " = " << result << std::endl;
	}
	return 1;
}
