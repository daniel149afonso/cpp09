/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:44:14 by daafonso          #+#    #+#             */
/*   Updated: 2026/05/11 14:47:37 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

// print container
template <typename T>
static void printContainer(T& c, const std::string& msg) {
    std::cout << msg;

    for (typename T::iterator it = c.begin(); it != c.end(); ++it)
        std::cout << *it << " ";

    std::cout << std::endl;
}

// display time
template <typename T>
static void display_time(clock_t start, clock_t end,
                        T& c, const std::string& name) {

    double time =
        (double)(end - start) / CLOCKS_PER_SEC * 1000000;

    std::cout << "Time to process a range of "
        << c.size()
        << " elements with std::" << name
        << " : "
        << time << " us" << std::endl;
}

// Jacob algorithm
template <typename T> void mergeInsertSort(T& c) {

    // already sorted
    if (c.size() <= 1)
        return;

    T big;
    T small;

    // make pairs
    for (size_t i = 0; i + 1 < c.size(); i += 2) {

        int a = c[i];
        int b = c[i + 1];

        if (a > b)
            std::swap(a, b);

        small.push_back(a);
        big.push_back(b);
    }

    // if the number of elements is impair
    bool hasOdd = c.size() % 2;
    int odd;

    if (hasOdd)
        odd = c.back();

    // recursive sort
    mergeInsertSort(big);

    // main chain
    c = big;

    // insert small
    for (size_t i = 0; i < small.size(); i++) {

        typename T::iterator pos =
            std::lower_bound(c.begin(), c.end(), small[i]);

        c.insert(pos, small[i]);
    }

    // insert odd
    if (hasOdd) {

        typename T::iterator pos =
            std::lower_bound(c.begin(), c.end(), odd);

        c.insert(pos, odd);
    }
}

int mergeSort(char **argv, int argc) {

    std::vector<int> v;
    std::deque<int> d;

    // parsing
    for (int i = 1; i < argc; i++) {

        std::string str(argv[i]);

        if (str.empty())
            return std::cerr << "Error\n", 0;

        // check digits
        for (size_t j = 0; j < str.size(); j++) {
            if (!std::isdigit(str[j]))
                return std::cerr << "Error\n", 0;
        }

        long nb = std::atol(argv[i]);

        if (nb < 0 || nb > 2147483647)
            return std::cerr << "Error\n", 0;

        v.push_back(static_cast<int>(nb));
        d.push_back(static_cast<int>(nb));
    }

    // Sort Vector
    printContainer(v, "Before: ");
    clock_t start_vector = clock();
    mergeInsertSort(v);
    clock_t end_vector = clock();

    // Sort Deque
    clock_t start_deque = clock();
    mergeInsertSort(d);
    clock_t end_deque = clock();

    // Print Container
    printContainer(v, "After: ");

    // Display Time
    display_time(start_vector, end_vector, v, "vector");
    display_time(start_deque, end_deque, d, "deque");

    return 1;
}
