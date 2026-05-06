/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:44:01 by daafonso          #+#    #+#             */
/*   Updated: 2026/05/06 18:09:08 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <sstream>

class PmergeMe {
public:
    static void sortVector(std::vector<int>& v);
    static void sortDeque(std::deque<int>& d);
};

int mergeSort(char **argv, int argc);
