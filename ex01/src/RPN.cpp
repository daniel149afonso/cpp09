/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:05:59 by daniel            #+#    #+#             */
/*   Updated: 2026/05/06 01:36:04 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

int applyOp(int a, int b, char op) {
    if (input[0] == '+')
                result = a + b;
            else if (input[0] == '-')
                result = a - b;
            else if (input[0] == '*')
                result = a * b;
            else if (input[0] == '/')
            {
                if (b == 0)
                    return std::cerr << "Error\n", 1;
                result = a / b;
            }
}

int rpn(char **argv) {
    std::stringstream ss(argv[1]);
    std::string input;
    std::stack<int> st;
    ss >> input;

    while (ss >> input) {
        if (input.length() == 1 && std::isdigit(input[0])) {
            st.push(input[0] - '0');
        }
        else if (input.length() == 1 &&
        (input[0] == '+' || input[0] == '-' ||
         input[0] == '*' || input[0] == '/')) {
            if (st.size() < 2)
                return std::cerr << "Error\n", 1;
            int result;
            int b = st.top();
            st.pop();

            int a = st.top();
            st.pop();

            
        }
        std::cout << input << std::endl;
    }
    return 0;
}