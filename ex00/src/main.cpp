/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:44:18 by daafonso          #+#    #+#             */
/*   Updated: 2026/04/29 13:56:29 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <fstream>
#include <string.h>

int is_correct_format(std::string btcFile)
{
	size_t pos = btcFile.find(".csv");
	if (btcFile[pos + 4] != '\0')
		return (std::cerr << "Error: wrong format should be .csv\n", 0);
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
