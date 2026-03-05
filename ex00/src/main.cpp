/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:44:18 by daafonso          #+#    #+#             */
/*   Updated: 2026/03/05 20:00:15 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

int is_correct_format(std::string btcFile)
{
	// if (!strstr(btcFile.c_str(), ".csv") || )
	// 	return (std::cerr << "Error: correct format is .csv\n", 0);

	const char	*extension = strrchr(btcFile.c_str(), '.');
	if (!extension)
		return (0);
	if (strncmp(".csv", extension, 4))
		return (std::cerr << "Error: wrong format should be .csv.\n", 0);
	return(1);
}

int parsing_file(std::string btcFile)
{
	if (!is_correct_format(btcFile))
		return (0);
	return(1);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (std::cerr << "Error: file is missing.\n", 1);
	std::ifstream file1(argv[1]);
	if (!file1.is_open())
		return (std::cerr << "Error: " << argv[1] << " file does not exist.\n", 1);
	std::string btcFile(argv[1]);
	if (!parsing_file(btcFile))
		return (1);
	file1.close();
	return (0);
}
