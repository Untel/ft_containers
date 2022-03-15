/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:00:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/14 16:12:31 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

std::ostream & operator << (std::ostream & o, Awesome const & a){
    o << "Awesome" << " N: " << a.get() << std::endl; 
	return o;
}

int main(void)
{
    // test_vector_main();
    test_map_main();
    return (0);
}