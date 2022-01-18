/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:09:31 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/18 22:06:39 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef STL //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "vector.hpp"
#endif

#include "tester.hpp"
#include <vector>

void test_vector_main(void)
{
    std::cout << "TEST VECTORS" << std::endl;
    ft::vector<int> v;
	v.push_back(666);
	std::cout << "First " << v[0] << std::endl;


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