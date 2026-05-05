/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:44:01 by daafonso          #+#    #+#             */
/*   Updated: 2026/05/05 22:23:49 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <deque>

class PmergeMe {
public:
    static void sortVector(std::vector<int>& v);
    static void sortDeque(std::deque<int>& d);
};