/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:23:38 by adda-sil          #+#    #+#             */
/*   Updated: 2022/04/06 22:04:25 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include <list>

template <class key, class value>
void    print_map( ft::map<key, value> &test)
{
    size_t i = 0;
    typename  ft::map<key, value>::const_iterator        beg = test.begin();
    typename  ft::map<key, value>::const_iterator        end = test.end();
    typename  ft::map<key, value>::const_reverse_iterator        rbeg = test.rbegin();
    typename  ft::map<key, value>::const_reverse_iterator        rend = test.rend();
    std::cout << "size : " << test.size() << std::endl;
    for (typename  ft::map<key, value>::const_iterator it = beg; it != end; it++)
    {
        std::cout << "\"" << it->first << "\" : " << it->second;
        if (i % 5 == 4 || i == test.size() - 1)
            std::cout << std::endl;
        else
            std::cout << " - ";
        i++;
    }
    for (typename  ft::map<key, value>::const_reverse_iterator it = rbeg; it != rend; it++)
    {
        std::cout << "\"" << it->first << "\" : " << it->second;
        if (i % 5 == 4 || i == test.size() - 1)
            std::cout << std::endl;
        else
            std::cout << " - ";
        i++;
    }
}

void test_iterators() {
	ft::map<int, std::string> m;
    // m.insert(ft::make_pair(3, "lol"));
    // m.insert(ft::make_pair(2, "lol"));
    // m.insert(ft::make_pair(1, "lol"));
    m.insert(ft::make_pair(5, "lol"));
    m.insert(ft::make_pair(4, "lol"));
    m.insert(ft::make_pair(6, "lol"));
	
    // m.insert(ft::make_pair(12, "lol"));

	MAP_PRINT(m);
	m.erase(5);
	MAP_PRINT(m);


	ft::map<int, std::string>::iterator it = m.begin();
	ft::map<int, std::string>::iterator ite = m.end();
	for (; it != ite; it++) {
		std::cout << "Iter " << it->second << std::endl;
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
	MAP_PRINT(m);
	// MAP_PRINT(m);
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
	MAP_PRINT(m);
    m.insert(m.find(110), ft::make_pair(105, ""));
	MAP_PRINT(m);

    m.insert(m.find(105), ft::make_pair(102, ""));
	MAP_PRINT(m);
	m.insert(m.begin(), ft::make_pair(9, ""));
	m.insert(m.begin(), ft::make_pair(8, ""));
	m.insert(m.begin(), ft::make_pair(7, ""));
	m.insert(m.begin(), ft::make_pair(6, ""));
	m.insert(m.begin(), ft::make_pair(5, ""));
	m.insert(m.begin(), ft::make_pair(4, ""));
	m.insert(m.begin(), ft::make_pair(3, ""));
	m.insert(m.begin(), ft::make_pair(2, ""));
	m.insert(m.begin(), ft::make_pair(1, ""));
	MAP_PRINT(m);

    m.insert(m.find(90), ft::make_pair(99, ""));
	MAP_PRINT(m);

	// m.erase(110);
	std::cout << "\n";
}

void const_pair() {
	ft::pair<int, std::string> f = ft::make_pair<int, std::string>(1, "yo");
	const ft::pair<int, std::string> s = ft::make_pair<int, std::string>(2, "yo");

	f = s;
	const ft::pair<int, std::string> y(f);
}

template <class K, class V>
void insert_test(K a, V b, V c) {
	typedef typename ft::map<K, V>::iterator iter;
	typedef typename ft::pair<iter, bool> inserter;
	ft::map<K, V>	m;

	inserter ins;
	iter it;

	ins = m.insert(ft::make_pair<K, V>(a, b));
	it = ins.first;
	std::cout << "Inserted " << ins.second << " :: " << it->first << " value: " << it->second << std::endl;

	ins = m.insert(ft::make_pair<K, V>(a, c));
	it = ins.first;
	std::cout << "Reinsert " << ins.second << " :: " << it->first << " value: " << it->second << std::endl;
}

void                            massive_tests()
{
    std::cout << std::endl << "MASSIVE TESTS" << std::endl;
    ft::map<int, std::string> *test2 = new ft::map<int, std::string>();
    std::string str;
    for (int i = 0; i < 50000; i++)
    {
        test2->insert(ft::make_pair<int, std::string>(i, toString(i)));
    }
    print_map<int, std::string>(*test2);
    for (int i = 49999; i >= 0; i--)
        std::cout << (*test2)[i] << std::endl;
    for (int i = 0; i < 50000; i++)
        std::cout << (*test2)[i] << std::endl;
    delete test2;
}

void test_map_main(void) {

	// test_iterators();

	// insert_range<int, char>(20);
	// insert_test<int, std::string>(1, "yolo", "re");
	// const_pair();
	// mescande_example();
	// test_init_map();
	// test_iterators();
	massive_tests();
}
