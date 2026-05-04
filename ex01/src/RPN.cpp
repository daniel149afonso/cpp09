/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:05:59 by daniel            #+#    #+#             */
/*   Updated: 2026/05/04 14:25:11 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

int applyOp(int a, int b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') {
        if (b == 0) throw std::runtime_error("Error");
        return a / b;
    }
    throw std::runtime_error("Error");
}

int rpn(char **argv) {
    std::stack<int> st;
    std::stringstream ss(argv[1]);
    std::string token;

    while (ss >> token) {
        // number
        if (token.length() == 1 && std::isdigit(token[0])) {
            st.push(token[0] - '0');
        }
        // operator
        else if (token.length() == 1 &&
                (token[0] == '+' || token[0] == '-' ||
                 token[0] == '*' || token[0] == '/')) {

            if (st.size() < 2) {
                std::cerr << "Error\n";
                return 0;
            }

            int b = st.top(); st.pop();
            int a = st.top(); st.pop();

            try {
                int result = applyOp(a, b, token[0]);
                st.push(result);
            } catch (...) {
                std::cerr << "Error\n";
                return 0;
            }
        }
        else {
            std::cerr << "Error\n";
            return 0;
        }
    }

    if (st.size() != 1) {
        std::cerr << "Error\n";
        return 0;
    }

    std::cout << st.top() << std::endl;
    return 1;
}