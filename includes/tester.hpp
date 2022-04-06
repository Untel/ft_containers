/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:09:35 by adda-sil          #+#    #+#             */
/*   Updated: 2022/04/06 22:13:19 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
# define TESTER_HPP 1

# include <string>
# include <iostream>
# include <queue>
# include "utils.hpp"

# ifdef STL
    #  include <map>
    #  include <stack>
    #  include <vector>
    namespace ft = std;
# else
    #  include "vector.hpp"
    #  include "map.hpp"
    #  include "stack.hpp"
# endif

void        test_vector_main(void);
void        test_map_main(void);

#endif // !TESTER_HPP