/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:44:01 by daafonso          #+#    #+#             */
/*   Updated: 2026/05/11 17:59:43 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <deque>
#include <algorithm>
#include <sys/time.h>

int mergeSort(char **argv, int argc);
template <typename T> void mergeInsertSort(T& c);
