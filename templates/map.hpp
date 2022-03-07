/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:01:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/07 18:02:01 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP 1

# include <iostream>
# include <stdexcept>
# include "pair.hpp"
# include "rbtree.hpp"

namespace ft {

	template <
		class Key,                                     // map::key_type
		class T,                                       // map::mapped_type
		class Compare = std::less<Key>,                     // map::key_compare
		class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
	>
	class map {
        public:
			typedef key															key_type; //The first template parameter (Key)	
			typedef T															mapped_type; //The second template parameter (T)	
			typedef typename ft::pair<const key_type, mapped_type>				value_type;
			typedef typename Compare											key_compare;//The third template parameter (Compare)	defaults to: less<key_type>
			typedef typename Alloc												allocator_type; //The fourth template parameter (Alloc)	defaults to: allocator<value_type>
			typedef typename allocator_type::reference							reference; //for the default allocator: value_type&
			typedef typename allocator_type::const_reference					const_reference; //for the default allocator: const value_type&
			typedef typename allocator_type::pointer							pointer; //for the default allocator: value_type*
			typedef typename allocator_type::const_pointer						const_pointer; //for the default allocator: const value_type*
			typedef typename allocator_type::size_type                          size_type;
			typedef typename ft::binary_tree_iterator<value_type>				iterator; //a bidirectional iterator to value_type	convertible to const_iterator
			typedef typename ft::binary_tree_iterator<const value_type>			const_iterator; //a bidirectional iterator to const value_type	
			typedef typename ft::reverse_iterator< iterator >           		reverse_iterator;
			typedef typename ft::reverse_iterator< const_iterator >     		const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type     difference_type;

			class value_compare {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			}

			pair<iterator, bool> insert (const value_type &val) {
				value_type *allocated = _allocator.allocate(1);
				_allocator.construct(allocated, val);
				return (_rbt.insert(allocated));
			}

	    private:
			RBTree _rbt;
	};
}

#endif // !STACK_HPP