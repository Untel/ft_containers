/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:09:31 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/20 20:14:32 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

void test_vector_main(void)
{
    std::cout << "TEST VECTORS" << std::endl;
    ft::vector<Awesome> v;
	v.reserve(1);
	for (int i = 0; i < 10; i++)
		v.push_back(Awesome(i));

	ft::vector<Awesome>::iterator it = v.begin();
	ft::vector<Awesome>::iterator ite = v.end();

	// it =;
	for (; it != ite; it++) {
		std::cout << "Iter " << (*it).get() << std::endl;
	}
	// v.push_back(666);
	// std::cout << "First " << v[0] << std::endl;


    // ft::vector<int> v(10, 9);
	// for (int i = 0;i < 10; i++)
	// 	std::cout << "Iter " << i << " = " << v[i] << std::endl;
	// v.reserve(30);
	// for (int i = 0;i < 10; i++)
	// 	std::cout << "Iter2 " << i << " = " << v[i] << std::endl;
	// v.reserve(31);
	// for (int i = 0;i < 10; i++)
	// 	std::cout << "Iter3 " << i << " = " << v[i] << std::endl;

    // std::cout << "At 2" << v[2] << std::endl;

}