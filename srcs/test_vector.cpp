/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:09:31 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/31 18:16:51 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

// void thetest(void) {
// 	    std::cout << "TEST VECTORS" << std::endl;
//     ft::vector<double> v;
// 	v.reserve(30);
// 	for (int i = 0; i < 10; i++)
// 		v.push_back(i);

// 	ft::vector<double>::iterator it = v.begin();
// 	ft::vector<double>::iterator ite = v.end();

// 	std::cout << ">>>>>>>>>>>> Inserting " << std::endl;
// 	ft::vector<double>::iterator lit = v.insert(it + 4, double(666));
// 	std::cout << ">>>>>>>>>>>> Inserted " << (*lit).get() << std::endl;
// 	(void)lit;
// 	(void)it;

// 	ft::vector<double>::iterator nit = v.begin();
// 	ite = v.end();

// 	// it =;
// 	for (; nit != ite; nit++) {
// 		std::cout << "Iter " << (*nit).str << std::endl;
// 	}
// }

// void yolo_test(void) {
// 	std::cout << "TEST VECTORS" << std::endl;
//     ft::vector<double> v;
// 	v.reserve(30);
// 	for (int i = 0; i < 10; i++)
// 		v.push_back(i);

// 	ft::vector<double>::iterator it = v.begin();
// 	ft::vector<double>::iterator ite = v.end();

// 	std::cout << ">>>>>>>>>>>> Inserting " << std::endl;
// 	v.insert(it + 2, 4, double(666));
// 	std::cout << ">>>>>>>>>>>> Inserted " << std::endl;
// 	// (void)lit;
// 	(void)it;

// 	ft::vector<double>::iterator nit = v.begin();
// 	ite = v.end();

// 	std::cout << "Size " << v.size() << std::endl;
// 	for (; nit != ite; nit++) {
// 		std::cout << "Iter " << (*nit) << std::endl;
// 	}
// }


void insert_inside_range(void) {
	std::cout << "TEST INSIDE RANGE VECTORS" << std::endl;
    ft::vector<double> v;
	v.reserve(30);
	for (int i = 0; i < 10; i++)
		v.push_back(i);

	ft::vector<double>::iterator it = v.begin();
	ft::vector<double>::iterator ite = v.end();
	std::cout << ">>>>>>>>>>>> Prepare range ite " << std::endl;
    ft::vector<double> x;
	x.reserve(30);
	for (int i = 70; i < 74; i++)
		x.push_back(i);
	std::cout << ">>>>>>>>>>>> Inserting " << std::endl;
	v.insert(it + 2, x.begin(), x.end());
	std::cout << ">>>>>>>>>>>> Inserted " << std::endl;
	// (void)lit;
	(void)it;

	ft::vector<double>::iterator nit = v.begin();
	ite = v.end();

	std::cout << "Size " << v.size() << std::endl;
	for (; nit != ite; nit++) {
		std::cout << "Iter " << (*nit) << std::endl;
	}
}

void insert_outside_range(void) {
	std::cout << "TEST OUTSIDE VECTORS" << std::endl;
    ft::vector<double> v;
	v.reserve(30);
	for (int i = 0; i < 10; i++)
		v.push_back(i);

	ft::vector<double>::iterator it = v.begin();
	ft::vector<double>::iterator ite = v.end();
	std::cout << ">>>>>>>>>>>> Prepare range ite " << std::endl;
    ft::vector<double> x;
	x.reserve(30);
	for (int i = 70; i < 74; i++)
		x.push_back(i);
	std::cout << ">>>>>>>>>>>> Inserting " << std::endl;
	v.insert(ite - 2, x.begin(), x.end());
	std::cout << ">>>>>>>>>>>> Inserted " << std::endl;
	// (void)lit;
	(void)it;

	ft::vector<double>::iterator nit = v.begin();
	ite = v.end();

	std::cout << "Size " << v.size() << std::endl;
	for (; nit != ite; nit++) {
		std::cout << "Iter " << (*nit) << std::endl;
	}
}

void not_enough_capacity(void) {
	std::cout << "TEST NOT ENOUGH CAPACITY VECTORS" << std::endl;
    ft::vector<double> v;
	v.reserve(5);
	for (int i = 0; i < 10; i++)
		v.push_back(i);

	ft::vector<double>::iterator it = v.begin();
	ft::vector<double>::iterator ite = v.end();
	std::cout << ">>>>>>>>>>>> Prepare range ite " << std::endl;
    ft::vector<double> x;
	x.reserve(30);
	for (int i = 70; i < 74; i++)
		x.push_back(i);
	std::cout << ">>>>>>>>>>>> Inserting " << std::endl;
	v.insert(ite - 2, x.begin(), x.end());
	std::cout << ">>>>>>>>>>>> Inserted " << std::endl;
	// (void)lit;
	(void)it;

	ft::vector<double>::iterator nit = v.begin();
	ite = v.end();

	std::cout << "Size " << v.size() << std::endl;
	for (; nit != ite; nit++) {
		std::cout << "Iter " << (*nit) << std::endl;
	}
}


void add_more_than_size(void) {
	std::cout << "TEST NOT ENOUGH CAPACITY VECTORS" << std::endl;
    ft::vector<double> v;
	v.reserve(5);
	for (int i = 0; i < 10; i++)
		v.push_back(i);

	ft::vector<double>::iterator it = v.begin();
	ft::vector<double>::iterator ite = v.end();
	std::cout << ">>>>>>>>>>>> Prepare range ite " << std::endl;
    ft::vector<double> x;
	x.reserve(30);
	for (int i = 70; i < 74; i++)
		x.push_back(i);
	std::cout << ">>>>>>>>>>>> Inserting " << std::endl;
	v.insert(ite - 2, x.begin(), x.end());
	std::cout << ">>>>>>>>>>>> Inserted " << std::endl;
	// (void)lit;
	(void)it;

	ft::vector<double>::iterator nit = v.begin();
	ite = v.end();

	std::cout << "Size " << v.size() << std::endl;
	for (; nit != ite; nit++) {
		std::cout << "Iter " << (*nit) << std::endl;
	}
}

void add_big_size(void) {
	std::cout << "TEST ADD BIG SIZE VECTORS" << std::endl;
    ft::vector<double> v;
	// v.reserve(30);
	ft::vector<double>::iterator it = v.begin();
	ft::vector<double>::iterator ite = v.end();
	std::cout << ">>>>>>>>>>>> Prepare range ite " << std::endl;
    ft::vector<double> x;
	x.reserve(30);
	for (int i = 70; i < 74; i++)
		x.push_back(i);
	std::cout << ">>>>>>>>>>>> Inserting MAX_SIZE=" << v.capacity() << std::endl;
	v.insert(it, x.begin(), x.end());
	std::cout << ">>>>>>>>>>>> Inserted MAX_SIZE=" << v.capacity() << std::endl;
	// (void)lit;
	(void)it;

	ft::vector<double>::iterator nit = v.begin();
	ite = v.end();

	std::cout << "Size " << v.size() << std::endl;
	for (; nit != ite; nit++) {
		std::cout << "Iter " << (*nit) << std::endl;
	}
}

void add_n_elems(void) {
	std::cout << "TEST ADD N ELEMS" << std::endl;
    ft::vector<double> v;
	ft::vector<double>::iterator it = v.begin();
	ft::vector<double>::iterator ite = v.end();
	(void)it;
	(void)ite;
	for (int i = 10; i < 3; i++)
		v.push_back(i);
	std::cout << ">>>>>>>>>>>> Inserting MAX_SIZE=" << v.capacity() << std::endl;
	v.insert(it, 5, double(3));
	std::cout << ">>>>>>>>>>>> Inserted MAX_SIZE=" << v.capacity() << std::endl;

	ft::vector<double>::iterator nit = v.begin();
	ite = v.end();

	std::cout << "Size " << v.size() << std::endl;
	for (; nit != ite; nit++) {
		std::cout << "Iter " << (*nit) << std::endl;
	}
}

void test_push_back() {
	
}

void test_vector_main(void) {
	#ifdef STL
		std::cout << "IS STL" << std::endl;
	#else
		std::cout << "IS FT" << std::endl;
	#endif
	insert_inside_range();
	std::cout << std::endl << std::endl << std::endl;
	insert_outside_range();
	std::cout << std::endl << std::endl << std::endl;
	add_more_than_size();
	std::cout << std::endl << std::endl << std::endl;
	add_big_size();
	// std::cout << std::endl << std::endl << std::endl;
	// add_n_elems();
	// push_back();
}
