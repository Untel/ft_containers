/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:09:35 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/19 16:44:19 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
# define TESTER_HPP

# include <string>
# include <iostream>
# include "awesome.hpp"

# ifdef STL
    #  include <map>
    #  include <stack>
    #  include <vector>
    namespace ft = std;
# else
    #  include "vector.hpp"
# endif

void        test_vector_main(void);

#endif // !TESTER_HPP