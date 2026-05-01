/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:44:18 by daafonso          #+#    #+#             */
/*   Updated: 2026/05/01 18:03:02 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

// lire data.csv + remplir la map
int loadDatabase(const std::string& filename, std::map<std::string, double>& map) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open data.csv\n";
        return 0;
    }

    std::string line;

    // skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        size_t pos = line.find(',');
        if (pos == std::string::npos)
            continue;

        std::string date = line.substr(0, pos);
        std::string rate = line.substr(pos + 1);

        std::stringstream ss(rate);
        double nb;
        ss >> nb;

        map[date] = nb;
    }
    return 1;
}

std::string& trim(std::string& str) {
    while (!str.empty() && str[str.size() - 1] == ' ')
    str.erase(str.size() - 1);
    return str;
}

// parser input.txt
int parseInput(const std::string& filename, std::map<std::string, double>& map) {
    (void)map;
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open input file\n";
        return 0;
    }

    std::string line;

    while (std::getline(file, line)) {
        size_t pos = line.find('|');
        if (pos == std::string::npos) {
            continue;
        }

        std::string date = line.substr(0, pos);
        std::string valueStr = line.substr(pos + 1);
        date = trim(date);
        valueStr = trim(valueStr);
        // ⚠️ à améliorer : enlever espaces

        std::stringstream ss(valueStr);
        double value;
        ss >> value;

        // 👉 pour l’instant juste affichage
        std::cout << date << " => " << value << std::endl;
        std::map<std::string, double>::iterator it = map.lower_bound(date);

        if (it != map.end())
            std::cout << "Value found: " << it->second << std::endl;
        else
            std::cout << "Not found" << std::endl;
    }
    return 1;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Error: file is missing.\n";
        return 1;
    }

    std::map<std::string, double> map;

    // ✅ 1. charger data.csv
    if (!loadDatabase("data.csv", map))
        return 1;

    // ✅ 2. parser input (argv[1])
    if (!parseInput(argv[1], map))
        return 1;

    return 0;
}
