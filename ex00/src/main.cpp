/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:44:18 by daafonso          #+#    #+#             */
/*   Updated: 2026/05/04 12:43:13 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Error: file is missing.\n";
        return 1;
    }

    std::map<std::string, double> map;

    if (!loadDatabase("data.csv", map))
        return 1;

    if (!parseInput(argv[1], map))
        return 1;

    return 0;
}
