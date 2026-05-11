/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:44:01 by daafonso          #+#    #+#             */
/*   Updated: 2026/05/11 17:10:10 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>

int loadDatabase(const std::string& filename, std::map<std::string, double>& map);
std::string trim(std::string str);
bool isValidDate(const std::string& date);
int parseInput(const std::string& filename, std::map<std::string, double>& map);
