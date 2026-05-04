/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:44:01 by daafonso          #+#    #+#             */
/*   Updated: 2026/05/04 12:45:26 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#define INT_MAX 2147483647

int loadDatabase(const std::string& filename, std::map<std::string, double>& map);
std::string trim(std::string str);
bool isValidDate(const std::string& date);
int parseInput(const std::string& filename, std::map<std::string, double>& map);