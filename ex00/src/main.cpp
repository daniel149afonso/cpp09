/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:44:18 by daafonso          #+#    #+#             */
/*   Updated: 2026/04/30 17:31:27 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

int is_correct_format(const std::string& file) {
    if (file.length() < 4 || file.substr(file.length() - 4) != ".csv") {
        std::cerr << "Error: wrong format should be .csv\n";
        return 0;
    }
    return 1;
}

int getTheLines(const std::string& filename) {
    std::ifstream file(filename.c_str());
	std::map<std::string, double> m;
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file\n";
        return 0;
    }

    std::string line;
    while (std::getline(file, line)) {
		size_t pos = line.find(",");
		std::string date = line.substr(0, pos);
		std::string rate = line.substr(pos + 1);

        std::stringstream ss(rate);
        double nb;
        
        ss >> nb;
		m[date] = nb;

        std::cout << m[date] << std::endl;
    }
    return 1;
}

int parsing_file(const std::string& btcFile) {
	
    return getTheLines(btcFile);
}

int main(int argc, char **argv) {
    if (argc != 2)
        return (std::cerr << "Error: file is missing.\n", 1);

    std::string fileName(argv[1]);

    if (!is_correct_format(fileName))
        return 1;

    if (!parsing_file(fileName))
        return 1;

    return 0;
}
