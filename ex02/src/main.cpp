/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daafonso <daafonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:44:18 by daafonso          #+#    #+#             */
/*   Updated: 2026/05/11 17:24:13 by daafonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

int main(int argc, char **argv) {
	if (argc < 2)
		return std::cerr << "Error\n", 1;

	if (!mergeSort(argv, argc))
		return 1;
	return 0;
}
