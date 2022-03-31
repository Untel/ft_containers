/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:23:38 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/30 20:30:51 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include <list>

void test_iterators() {
	ft::map<int, std::string> m;
    // m.insert(ft::make_pair(3, "lol"));
    // m.insert(ft::make_pair(2, "lol"));
    // m.insert(ft::make_pair(1, "lol"));
    m.insert(ft::make_pair(5, "lol"));
    m.insert(ft::make_pair(4, "lol"));
    m.insert(ft::make_pair(6, "lol"));
    // m.insert(ft::make_pair(12, "lol"));

	m.print();
	m.erase(5);
	m.print();


	ft::map<int, std::string>::iterator it = m.begin();
	ft::map<int, std::string>::iterator ite = m.end();

	std::cout << "YOOO\n\n\n";
	std::cout << "Lol" << *it << std::endl;
	std::cout << "aj" << *ite << std::endl;
	for (; it != ite; it++) {
		std::cout << "Iter " << *it << std::endl;
	}
}

void test_init_map() {
	std::cout << "INIT MAP" << std::endl;

	ft::map<int, std::string> m;
    m.insert(ft::make_pair(9438, ""));
    m.insert(ft::make_pair(5412, ""));
    m.insert(ft::make_pair(2029, ""));
    m.insert(ft::make_pair(3356, ""));
    m.insert(ft::make_pair(5547, ""));
    m.insert(ft::make_pair(8199, ""));
    m.insert(ft::make_pair(1070, ""));
    m.insert(ft::make_pair(147, ""));
    m.insert(m.find(5547), ft::make_pair(6063, ""));
	// m[1] = "yolo";
	m.print();
	// m.print();
	std::cout << "\n";
}

void mescande_example() {
	std::cout << "INIT MAP" << std::endl;

	ft::map<int, std::string> m;
    m.insert(ft::make_pair(10, ""));
    m.insert(ft::make_pair(30, ""));
    m.insert(ft::make_pair(40, ""));
    m.insert(ft::make_pair(50, ""));
    m.insert(ft::make_pair(60, ""));
    m.insert(ft::make_pair(70, ""));
    m.insert(ft::make_pair(80, ""));
    m.insert(ft::make_pair(90, ""));
    m.insert(ft::make_pair(100, ""));
    m.insert(ft::make_pair(110, ""));
    m.insert(ft::make_pair(130, ""));
    m.insert(ft::make_pair(140, ""));
    m.insert(ft::make_pair(120, ""));

	m[10] = "yolo";
	m.print();
    m.insert(m.find(110), ft::make_pair(105, ""));
	m.print();

    m.insert(m.find(105), ft::make_pair(102, ""));
	m.print();
	m.insert(m.begin(), ft::make_pair(9, ""));
	m.insert(m.begin(), ft::make_pair(8, ""));
	m.insert(m.begin(), ft::make_pair(7, ""));
	m.insert(m.begin(), ft::make_pair(6, ""));
	m.insert(m.begin(), ft::make_pair(5, ""));
	m.insert(m.begin(), ft::make_pair(4, ""));
	m.insert(m.begin(), ft::make_pair(3, ""));
	m.insert(m.begin(), ft::make_pair(2, ""));
	m.insert(m.begin(), ft::make_pair(1, ""));
	m.print();

    m.insert(m.find(90), ft::make_pair(99, ""));
	m.print();
	std::cout << "\n";
}

void const_pair() {
	ft::pair<int, std::string> f = ft::make_pair<int, std::string>(1, "yo");
	const ft::pair<int, std::string> s = ft::make_pair<int, std::string>(2, "yo");

	f = s;
	const ft::pair<int, std::string> y(f);
}

template <class K, class V>
void insert_range(int size) {
	std::list<ft::pair<K, V> > lst;

	for (int i = 1; i < size + 1; i++)
		lst.push_back(ft::pair<K, V>(K(i), V(i * 3)));
	
	ft::map<K, V> m;
	m.insert((lst.begin(), lst.end()));
	ft::map<K, V>::iterator it = m.begin();
	ft::map<K, V>::iterator ite = m.end();
	for (; it != ite; it++)
		std::cout << "R " << it->first << " | " << it->second << std::endl;
}

void test_map_main(void) {
	#ifdef STL
		std::cout << "IS STL" << std::endl;
	#else
		std::cout << "IS FT" << std::endl;
	#endif

	insert_range<int, char>(20);
	// const_pair();
	// mescande_example();
	// test_init_map();
	// test_iterators();
}
