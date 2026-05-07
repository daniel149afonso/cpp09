/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:44:14 by daafonso          #+#    #+#             */
/*   Updated: 2026/05/07 14:29:52 by daniel           ###   ########.fr       */
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

// ---------- VECTOR ----------
void PmergeMe::sortVector(std::vector<int>& v) {

    if (v.size() <= 1)
        return;

    std::vector<int> big;
    std::vector<int> small;

    // ---------- MAKE PAIRS ----------
    for (size_t i = 0; i + 1 < v.size(); i += 2) {

        int a = v[i];
        int b = v[i + 1];

        if (a > b)
            std::swap(a, b);

        small.push_back(a);
        big.push_back(b);
    }

    // odd element
    bool hasOdd = v.size() % 2;
    int odd;

    if (hasOdd)
        odd = v.back();

    // ---------- RECURSIVE SORT ----------
    sortVector(big);

    // ---------- MAIN CHAIN ----------
    v = big;

    // ---------- INSERT SMALL ----------
    for (size_t i = 0; i < small.size(); i++) {

        std::vector<int>::iterator pos =
            std::lower_bound(v.begin(), v.end(), small[i]);

        v.insert(pos, small[i]);
    }

    // ---------- INSERT ODD ----------
    if (hasOdd) {

        std::vector<int>::iterator pos =
            std::lower_bound(v.begin(), v.end(), odd);

        v.insert(pos, odd);
    }
}

// ---------- DEQUE ----------
void PmergeMe::sortDeque(std::deque<int>& d) {

    if (d.size() <= 1)
        return;

    std::deque<int> big;
    std::deque<int> small;

    for (size_t i = 0; i + 1 < d.size(); i += 2) {

        int a = d[i];
        int b = d[i + 1];

        if (a > b)
            std::swap(a, b);

        small.push_back(a);
        big.push_back(b);
    }

    bool hasOdd = d.size() % 2;
    int odd;

    if (hasOdd)
        odd = d.back();

    sortDeque(big);

    d = big;

    for (size_t i = 0; i < small.size(); i++) {

        std::deque<int>::iterator pos =
            std::lower_bound(d.begin(), d.end(), small[i]);

        d.insert(pos, small[i]);
    }

    if (hasOdd) {

        std::deque<int>::iterator pos =
            std::lower_bound(d.begin(), d.end(), odd);

        d.insert(pos, odd);
    }
}

int mergeSort(char **argv, int argc) {

    std::vector<int> v;
    std::deque<int> d;

    // parsing
    for (int i = 1; i < argc; i++) {

        std::string str(argv[i]);

        if (str.empty())
            return std::cerr << "Error\n", 1;

        // check digits
        for (size_t j = 0; j < str.size(); j++) {
            if (!std::isdigit(str[j]))
                return std::cerr << "Error\n", 1;
        }

        long nb = std::atol(argv[i]);

        if (nb < 0 || nb > 2147483647)
            return std::cerr << "Error\n", 1;

        v.push_back(static_cast<int>(nb));
        d.push_back(static_cast<int>(nb));
    }

    // Sort Vector
    printContainer(v, "Before: ");
    clock_t start_vector = clock();
    PmergeMe::sortVector(v);
    clock_t end_vector = clock();

    // Sort Deque
    clock_t start_deque = clock();
    PmergeMe::sortDeque(d);
    clock_t end_deque = clock();

    // Print Container
    printContainer(v, "After: ");

    // Display Time
    display_time(start_vector, end_vector, v, "vector");
    display_time(start_deque, end_deque, d, "deque");

    return 1;
}
