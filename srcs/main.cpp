/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:00:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/22 17:57:12 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

std::ostream & operator << (std::ostream & o, Awesome const & a){
    o << "Awesome" << " N: " << a.get() << std::endl; 
    for (int i = 0; i < 10; i++)
        o << i << ": " << a._list[i] << ", ";
    o << std::endl;
	return o;
}

int main(void)
{
    test_vector_main();
    return (0);
}