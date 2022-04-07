/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:09:31 by adda-sil          #+#    #+#             */
/*   Updated: 2022/04/06 23:53:00 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include <list>
#include <deque>

template <class T, class Ctn >
void test_push(int m = 10) {
	std::cout << "PUSHHHH" << std::endl;

	ft::stack<T, Ctn> test2;
    for (int i = 0; i < m; i++) {
        test2.push(T());
    }
	while (!test2.empty()) {
		std::cout << test2.top() << std::endl;
		test2.pop();
	}
}

void	massive_tests_stack()
{
    std::cout << std::endl << "MASSIVE TESTS" << std::endl;
    ft::stack<std::string> test2;
    for (int i = 0; i < 50000; i++) {
        test2.push(toString(i).append(" yo"));
    }
	while (!test2.empty()) {
		std::string str = test2.top();
		std::cout << str << std::endl;
		test2.pop();
	}
}

void test_stack_main(void) {
	test_push<int, ft::vector<int> >();
	test_push<double, std::list<double> >();
	test_push<std::string, std::deque<std::string> >();
    #ifdef RUN_PERF
	    massive_tests_stack();
    #endif
}
