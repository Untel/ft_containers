/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:09:31 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/21 00:04:55 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

// void thetest(void) {
// 	    std::cout << "TEST VECTORS" << std::endl;
//     ft::vector<Awesome> v;
// 	v.reserve(30);
// 	for (int i = 0; i < 10; i++)
// 		v.push_back(i);

// 	ft::vector<Awesome>::iterator it = v.begin();
// 	ft::vector<Awesome>::iterator ite = v.end();

// 	std::cout << ">>>>>>>>>>>> Inserting " << std::endl;
// 	ft::vector<Awesome>::iterator lit = v.insert(it + 4, Awesome(666));
// 	std::cout << ">>>>>>>>>>>> Inserted " << (*lit).get() << std::endl;
// 	(void)lit;
// 	(void)it;

// 	ft::vector<Awesome>::iterator nit = v.begin();
// 	ite = v.end();

// 	// it =;
// 	for (; nit != ite; nit++) {
// 		std::cout << "Iter " << (*nit).str << std::endl;
// 	}
// }

// void yolo_test(void) {
// 	std::cout << "TEST VECTORS" << std::endl;
//     ft::vector<Awesome> v;
// 	v.reserve(30);
// 	for (int i = 0; i < 10; i++)
// 		v.push_back(i);

// 	ft::vector<Awesome>::iterator it = v.begin();
// 	ft::vector<Awesome>::iterator ite = v.end();

// 	std::cout << ">>>>>>>>>>>> Inserting " << std::endl;
// 	v.insert(it + 2, 4, Awesome(666));
// 	std::cout << ">>>>>>>>>>>> Inserted " << std::endl;
// 	// (void)lit;
// 	(void)it;

// 	ft::vector<Awesome>::iterator nit = v.begin();
// 	ite = v.end();

// 	std::cout << "Size " << v.size() << std::endl;
// 	for (; nit != ite; nit++) {
// 		std::cout << "Iter " << (*nit).str << " From " << (*nit)._n << std::endl;
// 	}
// }


void test_vector_main(void) {
	std::cout << "TEST VECTORS" << std::endl;
    ft::vector<Awesome> v;
	v.reserve(30);
	for (int i = 0; i < 10; i++)
		v.push_back(i);

	ft::vector<Awesome>::iterator it = v.begin();
	ft::vector<Awesome>::iterator ite = v.end();

	std::cout << ">>>>>>>>>>>> Inserting " << std::endl;
	ft::vector<Awesome>::iterator four = v.erase(it + 2, it + 4);
	std::cout << ">>>>>>>>>>>> Inserted " << std::endl;
	std::cout << ">>>>>>>>>>>> Should be it + 4 " << (*four).get() << std::endl;
	// (void)lit;
	(void)it;

	ft::vector<Awesome>::iterator nit = v.begin();
	ite = v.end();

	std::cout << "Size " << v.size() << std::endl;
	for (; nit != ite; nit++) {
		std::cout << "Iter " << (*nit).str << " From " << (*nit)._n << std::endl;
	}
}
