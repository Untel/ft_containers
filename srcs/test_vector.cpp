/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:09:31 by adda-sil          #+#    #+#             */
/*   Updated: 2022/02/18 18:03:03 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

void test_push_back() {
	std::cout << "ENABLE IF" << std::endl;

	ft::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	v.insert(v.begin() + 1, 3, 10);

	ft::vector<int>::iterator it = v.begin();
	ft::vector<int>::iterator ite = v.end();
		for (; it != ite; it++) {
		std::cout << "Iter " << *it << std::endl;
	}
}

void test_push_list() {
	std::cout << "RANGE" << std::endl;

	ft::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	ft::vector<int> w;
	w.push_back(4);
	w.push_back(5);
	w.push_back(6);

	v.insert(v.begin() + 1, w.begin(), w.end());

	ft::vector<int>::iterator it = v.begin();
	ft::vector<int>::iterator ite = v.end();
		for (; it != ite; it++) {
		std::cout << "Iter " << *it << std::endl;
	}
}


void test_constructor() {
	std::cout << "RANGE" << std::endl;

	ft::vector<int> v(10);

	ft::vector<int> w;
	w.push_back(4);
	w.push_back(5);
	w.push_back(6);

	v.insert(v.begin() + 1, w.begin(), w.end());

	ft::vector<int>::iterator it = v.begin();
	ft::vector<int>::iterator ite = v.end();
		for (; it != ite; it++) {
		std::cout << "Iter " << *it << std::endl;
	}
}


void test_vector_main(void) {
	#ifdef STL
		std::cout << "IS STL" << std::endl;
	#else
		std::cout << "IS FT" << std::endl;
	#endif
	test_push_back();
	test_push_list();
}
