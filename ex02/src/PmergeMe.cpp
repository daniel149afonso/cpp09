/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:44:14 by daafonso          #+#    #+#             */
/*   Updated: 2026/05/12 17:57:09 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

// ── display ──────────────────────────────────────────────────────────────────

static void printContainer(const std::vector<int>& c, const std::string& msg) {
    std::cout << msg;
    for (size_t i = 0; i < c.size(); i++)
        std::cout << c[i] << " ";
    std::cout << std::endl;
}

static void display_time(struct timeval start, struct timeval end,
                         size_t n, const std::string& name) {
    double us = (end.tv_sec - start.tv_sec) * 1000000.0
              + (end.tv_usec - start.tv_usec);
    std::cout << "Time to process a range of " << n
              << " elements with std::" << name << " : "
              << us << " us" << std::endl;
}

// ── Jacobsthal insertion order ────────────────────────────────────────────────
// small[0] is inserted first (it is < every big element).
// This returns the 0-indexed positions in small[1..k-1] to insert next,
// in the order that minimises binary-search comparisons (Ford-Johnson).
// Groups are derived from the Jacobsthal sequence J(n) = J(n-1) + 2*J(n-2).
// Within each group [J(n-1)+1 .. J(n)] the elements are inserted in reverse.

static std::vector<size_t> buildInsertOrder(size_t k) {
    std::vector<size_t> order;
    if (k <= 1) return order;

    size_t ja = 1, jb = 3; // J(2)=1, J(3)=3
    while (ja < k) {
        size_t hi = (jb - 1 < k - 1) ? jb - 1 : k - 1;
        // insert from hi down to ja (exclusive), i.e. indices hi, hi-1, ..., ja
        for (size_t i = hi + 1; i-- > ja; )
            order.push_back(i);
        size_t next = jb + 2 * ja;
        ja = jb;
        jb = next;
    }
    return order;
}

// ── Ford-Johnson for std::vector<int> ────────────────────────────────────────

static void mergeInsertSortVector(std::vector<int>& c) {

    if (c.size() <= 1)
        return;

    // STEP 1 : make pairs ex:  8|3, 1|5, 9|2
    // pair = (small, big) ex:  3|8, 1|5, 2|9

    std::vector<std::pair<int, int> > pairs;

    for (size_t i = 0; i + 1 < c.size(); i += 2) {

        int a = c[i];
        int b = c[i + 1];

        if (a > b)
            std::swap(a, b);

        // (small, big)
        pairs.push_back(std::make_pair(a, b));
    }

    // odd element
    bool hasOdd = c.size() % 2;
    int odd = 0;

    if (hasOdd)
        odd = c.back();

    // STEP 2 : sort big elements ex: 5, 8, 9
    std::vector<int> bigElems;

    for (size_t i = 0; i < pairs.size(); i++)
        bigElems.push_back(pairs[i].second);

    mergeInsertSortVector(bigElems);

    // STEP 3 : rebuild sorted pairs based on big ex: 1|5, 3|8, 2|9
    std::vector<std::pair<int, int> > sortedPairs;
    std::vector<int> used(pairs.size(), 0);

    for (size_t i = 0; i < bigElems.size(); i++) {
        
        for (size_t j = 0; j < pairs.size(); j++) {

            if (!used[j] && pairs[j].second == bigElems[i]) {
                sortedPairs.push_back(pairs[j]);
                used[j] = 1;
                break;
            }
        }
    }

    // ---------- STEP 4 : MAIN CHAIN ----------
    c.clear();

    std::vector<int> small;

    for (size_t i = 0; i < sortedPairs.size(); i++) {

        // bigs -> main chain
        c.push_back(sortedPairs[i].second);

        // smalls -> small
        small.push_back(sortedPairs[i].first);
    }

    // ---------- STEP 5 : INSERT FIRST small ----------
    if (!small.empty())
        c.insert(c.begin(), small[0]);

    // ---------- STEP 6 : JACOBSTHAL INSERTION ----------
    std::vector<size_t> order = buildInsertOrder(small.size());

    for (size_t idx = 0; idx < order.size(); idx++) {

        size_t i = order[idx];

        // safety check
        if (i >= small.size() || i >= sortedPairs.size())
            continue;

        // small[i] < sortedPairs[i].second
        std::vector<int>::iterator upper =
            std::upper_bound(c.begin(), c.end(),
                            sortedPairs[i].second);

        std::vector<int>::iterator pos =
            std::lower_bound(c.begin(), upper,
                            small[i]);

        c.insert(pos, small[i]);
    }

    // ---------- STEP 7 : INSERT ODD ----------
    if (hasOdd) {

        std::vector<int>::iterator pos =
            std::lower_bound(c.begin(), c.end(), odd);

        c.insert(pos, odd);
    }
}

// ── Ford-Johnson for std::deque<int> ─────────────────────────────────────────

static void mergeInsertSortDeque(std::deque<int>& c) {
    if (c.size() <= 1)
        return;

    std::vector<std::pair<int,int> > pairs;
    for (size_t i = 0; i + 1 < c.size(); i += 2) {
        int a = c[i], b = c[i + 1];
        if (a > b) std::swap(a, b);
        pairs.push_back(std::make_pair(b, a));
    }
    bool hasOdd = c.size() % 2;
    int  odd    = hasOdd ? c.back() : 0;

    std::deque<int> bigElems;
    for (size_t i = 0; i < pairs.size(); i++)
        bigElems.push_back(pairs[i].first);
    mergeInsertSortDeque(bigElems);

    std::vector<std::pair<int,int> > sortedPairs;
    std::vector<int> used(pairs.size(), 0);
    for (size_t i = 0; i < bigElems.size(); i++) {
        for (size_t j = 0; j < pairs.size(); j++) {
            if (!used[j] && pairs[j].first == bigElems[i]) {
                sortedPairs.push_back(pairs[j]);
                used[j] = 1;
                break;
            }
        }
    }

    c.clear();
    std::vector<int> small;
    for (size_t i = 0; i < sortedPairs.size(); i++) {
        c.push_back(sortedPairs[i].first);
        small.push_back(sortedPairs[i].second);
    }

    c.insert(c.begin(), small[0]);

    std::vector<size_t> order = buildInsertOrder(small.size());
    for (size_t idx = 0; idx < order.size(); idx++) {
        size_t i = order[idx];
        std::deque<int>::iterator upper =
            std::upper_bound(c.begin(), c.end(), sortedPairs[i].first);
        std::deque<int>::iterator pos =
            std::lower_bound(c.begin(), upper, small[i]);
        c.insert(pos, small[i]);
    }

    if (hasOdd) {
        std::deque<int>::iterator pos = std::lower_bound(c.begin(), c.end(), odd);
        c.insert(pos, odd);
    }
}

// ── entry point ───────────────────────────────────────────────────────────────

int mergeSort(char **argv, int argc) {
    std::vector<int> v;
    std::deque<int>  d;

    for (int i = 1; i < argc; i++) {
        std::string str(argv[i]);
        if (str.empty())
            return std::cerr << "Error\n", 0;
        for (size_t j = 0; j < str.size(); j++) {
            if (!std::isdigit(str[j]))
                return std::cerr << "Error\n", 0;
        }
        long nb = std::atol(argv[i]);
        if (nb <= 0 || nb > 2147483647)
            return std::cerr << "Error\n", 0;
        v.push_back(static_cast<int>(nb));
        d.push_back(static_cast<int>(nb));
    }

    printContainer(v, "Before: ");

    struct timeval sv, ev, sd, ed;

    gettimeofday(&sv, NULL);
    mergeInsertSortVector(v);
    gettimeofday(&ev, NULL);

    gettimeofday(&sd, NULL);
    mergeInsertSortDeque(d);
    gettimeofday(&ed, NULL);

    printContainer(v, "After:  ");
    display_time(sv, ev, v.size(), "vector");
    display_time(sd, ed, d.size(), "deque");

    return 1;
}
