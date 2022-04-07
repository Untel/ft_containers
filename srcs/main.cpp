/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:00:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/04/07 00:09:31 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "tester.hpp"

int main(int ac, char **av)
{
    if (ac == 1) {
        test_vector_main();
        test_stack_main();
        test_map_main();
        return (0);
    }

    for (int i = 1; av[i] != NULL; i++) {
        std::string str(av[i]);
        std::cout << "******************************************" << std::endl;
        std::cout << "******************************************" << std::endl;
        std::cout << "     TESTING " << str << std::endl;
        std::cout << "******************************************" << std::endl;
        std::cout << "******************************************" << std::endl;
        if (str == "stack")
            test_stack_main();
        if (str == "vector")
            test_vector_main();
        if (str == "map")
            test_map_main();
    }
    return (0);
}