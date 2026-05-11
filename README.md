# CPP Module 09

*This project has been created as part of the 42 curriculum by <daniel149afonso>.*

---

# Description

This project is part of the C++ Module 09 of the 42 curriculum and focuses on STL containers, algorithms, parsing, recursion, and performance comparison in C++98.

The module is divided into three exercises:

## ex00 — Bitcoin Exchange

This program reads a database containing historical Bitcoin exchange rates and evaluates values from an input file.

Main concepts:
- file parsing
- date handling
- associative containers (`std::map`)
- searching with `lower_bound`
- error handling

---

## ex01 — Reverse Polish Notation (RPN)

This program evaluates mathematical expressions written in Reverse Polish Notation.

Main concepts:
- stack-based evaluation
- token parsing
- arithmetic operations
- STL stack container usage
- error management

Example:

```bash
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
```

Output:

```text
42
```

---

## ex02 — PmergeMe

This program sorts a sequence of positive integers using a merge-insert inspired sorting algorithm based on the Ford–Johnson algorithm.

Main concepts:
- recursive algorithms
- STL containers
- merge-insert sorting
- binary insertion using `lower_bound`
- performance comparison between `std::vector` and `std::deque`

The execution time of each container is displayed in microseconds.

---

# Instructions

## Compilation

Each exercise contains its own `Makefile`.

Compile:

```bash
make
```

Clean object files:

```bash
make clean
```

Remove binaries:

```bash
make fclean
```

Recompile everything:

```bash
make re
```

---

# Usage

## ex00

```bash
./btc input.txt
```

Example:

```bash
./btc input.txt
```

---

## ex01

```bash
./RPN "8 9 * 9 -"
```

---

## ex02

```bash
./PmergeMe 3 5 9 7 4
```

Example output:

```text
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::vector : 5 us
Time to process a range of 5 elements with std::deque : 8 us
```

---

# Technical Choices

## ex00

- `std::map` was used to store Bitcoin exchange rates.
- `lower_bound` was used to retrieve the closest previous date efficiently.

## ex01

- `std::stack` was used to evaluate Reverse Polish expressions.
- Expressions are parsed token by token using `std::stringstream`.

## ex02

- `std::vector` and `std::deque` were both implemented and benchmarked.
- A merge-insert inspired recursive sorting algorithm was implemented.
- `std::lower_bound` was used for binary insertion.

---

# Resources

## Documentation

- https://cplusplus.com
- https://en.cppreference.com

## References

- Donald Knuth — *The Art of Computer Programming, Volume 3*
- Ford–Johnson Merge-Insertion Sort
- STL container documentation

---

# AI Usage

AI tools were used during the development of this project for:
- understanding STL containers and iterators
- debugging parsing and template issues
- understanding `lower_bound`
- explaining merge-insert sorting concepts
- improving code readability and project structure

All code was reviewed, adapted, and integrated manually.