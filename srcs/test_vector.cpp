/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:09:31 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/04 07:12:01 by adda-sil         ###   ########.fr       */
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

void test_erase() {
	std::cout << "ERASE" << std::endl;

	ft::vector<int> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = i;


	std::cout << "Size " << vct.size() << std::endl;
	ft::vector<int>::iterator it = vct.begin();
	ft::vector<int>::iterator ite = vct.end();
	for (; it != ite; it++) {
		std::cout << "Pre " << *it << std::endl;
	}

	std::cout << "Iter " << *(vct.erase(vct.begin())) << std::endl;

	it = vct.begin();
	ite = vct.end();
	std::cout << "Size " << vct.size() << std::endl;
	for (; it != ite; it++) {
		std::cout << "Post " << *it << std::endl;
	}
}

void plus_iterator() {
	std::cout << "Iterator" << std::endl;
	ft::vector<int> vct(10);
	vct[1] = 66;

	ft::vector<int>::iterator it = vct.begin();
	ft::vector<int>::iterator it2;

	std::cout << "It + 1" << std::endl;
	it2 = it + 1;
	std::cout << "Ret is " << *it2 << std::endl;

	std::cout << "1 + it" << std::endl;
	it2 = it + 1;

	std::cout << "Ret is " << *it2 << std::endl;
}


void comp() {
  ft::vector<int> foo (3,100);   // three ints with a value of 100
  ft::vector<int> bar (2,200);   // two ints with a value of 200

  if (foo==bar) std::cout << "foo and bar are equal\n";
//   if (foo!=bar) std::cout << "foo and bar are not equal\n";
//   if (foo< bar) std::cout << "foo is less than bar\n";
//   if (foo> bar) std::cout << "foo is greater than bar\n";
//   if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
//   if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}

void revite() {
	const int size = 5;
	ft::vector<int> vct(size);
	ft::vector<int>::reverse_iterator it = vct.rbegin();
	ft::vector<int>::const_reverse_iterator ite = vct.rbegin();


	for (int i = 0; i < size; ++i) {
		it[i] = (size - i) * 5;
		std::cout << "Insert at " << i << " value "
			<< it[i] << " should be " << (size - i) * 5 << std::endl;
	}

	ft::vector<int>::iterator nit = vct.begin();
	ft::vector<int>::iterator nite = vct.end();
	for (; nit != nite; nit++)
		std::cout << "By normal iterator is " << *nit << " " << std::endl;
	for (int i = 0; i < size; ++i) {
		std::cout << "Index " << vct[i] << " " << std::endl;
	}
	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
}

void test_vector_main(void) {
	#ifdef STL
		std::cout << "IS STL" << std::endl;
	#else
		std::cout << "IS FT" << std::endl;
	#endif
	// test_push_back();
	// test_push_list();
	// test_erase();
	// plus_iterator();
	// comp();
	revite();
}
