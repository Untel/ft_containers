/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:23:38 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/23 13:44:15 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

void test_init_map() {
	std::cout << "INIT MAP" << std::endl;

	ft::map<int, std::string> m;
    m.insert(ft::make_pair(3, "hihi"));
    m.insert(ft::make_pair(1, "lol"));
    // m.insert(ft::make_pair(1, "truc"));
    m.insert(ft::make_pair(2, "ahah"));
    m.insert(ft::make_pair(4, "uh?"));
    // m.insert(ft::make_pair(2, "rewrite"));
    // m.insert(ft::make_pair(2, "rerewrite"));
	// m[1] = "yolo";
	m.print();
	// m.print();
	std::cout << "\n";
}

void test_map_main(void) {
	#ifdef STL
		std::cout << "IS STL" << std::endl;
	#else
		std::cout << "IS FT" << std::endl;
	#endif

	test_init_map();
}
