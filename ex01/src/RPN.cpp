/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:05:59 by daniel            #+#    #+#             */
/*   Updated: 2026/05/06 15:34:04 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

// check operator
int applyOp(int a, int b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') {
        if (b == 0) throw std::runtime_error("Error"); //divid by 0
        return a / b;
    }
    throw std::runtime_error("Error");
}

int rpn(char **argv) {
    std::stringstream ss(argv[1]);
    std::string input;
    std::stack<int> st;

    while (ss >> input) {
        if (input.length() == 1 && std::isdigit(input[0])) { // cas number
            st.push(input[0] - '0'); // char -> int conversion
        }
        else if (input.length() == 1 && //cas operator
        (input[0] == '+' || input[0] == '-' ||
         input[0] == '*' || input[0] == '/')) {
            if (st.size() < 2)
                return std::cerr << "Error\n", 1;
            int op = input[0];
            int b = st.top();
            st.pop();

            int a = st.top();
            st.pop();
            try {
                int result = applyOp(a, b, op);
                st.push(result);
            }
            catch(const std::exception& e) {
                return std::cerr << e.what() << '\n', 1;
            }
        }
        else // invalid token
            return std::cerr << "Error\n", 1;
    }
    if (st.size() != 1)
        return std::cerr << "Error\n", 1;
    std::cout << st.top() << std::endl;
    return 0;
}