/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:01:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/07 16:22:15 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP 1

# include <iostream>
# include <stdexcept>

namespace ft {

	template <
		class Key,                                     // map::key_type
		class T,                                       // map::mapped_type
		class Compare = less<Key>,                     // map::key_compare
		class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
	>
	class map {
        public:

	    private:
	};
}

#endif // !STACK_HPP