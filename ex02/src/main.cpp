/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 13:16:08 by daniel            #+#    #+#             */
/*   Updated: 2026/05/07 13:18:04 by daniel           ###   ########.fr       */
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