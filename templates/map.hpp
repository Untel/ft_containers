/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:01:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/14 16:27:26 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP 1

# include <iostream>
# include <stdexcept>
# include "utils.hpp"
# include "pair.hpp"
# include "rbtree.hpp"
# include "binary_tree_iterator.hpp"

namespace ft {
	template <
		class Key,                                     											// map::key_type
		class T,                                       											// map::mapped_type
		class Compare = std::less<Key>,                     									// map::key_compare
		class Allocator = std::allocator<ft::pair<const Key,T> >    							// map::allocator_type
	>
	class map {
        public:
			typedef Key																			key_type; //The first template parameter (Key)	
			typedef T																			mapped_type; //The second template parameter (T)	
			typedef Compare																		key_compare;//The third template parameter (Compare)	defaults to: less<key_type>
			typedef Allocator																	allocator_type; //The fourth template parameter (Alloc)	defaults to: allocator<value_type>
			typedef typename ft::pair<const key_type, mapped_type>								value_type;
			typedef typename allocator_type::reference											reference; //for the default allocator: value_type&
			typedef typename allocator_type::const_reference									const_reference; //for the default allocator: const value_type&
			typedef typename allocator_type::pointer											pointer; //for the default allocator: value_type*
			typedef typename allocator_type::const_pointer										const_pointer; //for the default allocator: const value_type*
			typedef typename allocator_type::size_type                          				size_type;
			typedef typename ft::binary_tree_iterator< value_type >::iterator					iterator; //a bidirectional iterator to value_type	convertible to const_iterator
			typedef typename ft::binary_tree_iterator<const value_type>::const_iterator			const_iterator; //a bidirectional iterator to const value_type	
			typedef typename ft::reverse_iterator< iterator >           						reverse_iterator;
			typedef typename ft::reverse_iterator< const_iterator >     						const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type     				difference_type;

			typedef typename ft::RBTree<value_type>												tree_type;
			typedef typename ft::RBTree<value_type>::value_type									node_type;
			typedef typename ft::RBTree<value_type>::pointer									node_ptr;

			class value_compare : public std::binary_function<value_type, value_type, bool> {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
				friend class map<key_type, mapped_type, key_compare, allocator_type>;
				protected:
					key_compare comp;
					value_compare (key_compare c) : comp(c) {}  // constructed with map's comparison object
				public:
					typedef bool			result_type;
					typedef value_type 		first_argument_type;
					typedef value_type 		second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const {
						return comp(x.first, y.first);
					}
			};

			explicit map (
				const key_compare & comp = key_compare(),
				const allocator_type& alloc = allocator_type()
			) : _comp(comp), _allocator(alloc), _rbt()
			{}

			// ft::pair<iterator, bool> insert (const value_type &val) {
			void insert (const value_type &val) {
				node_ptr node = new node_type();
				node->data = _allocator.allocate(1);
				_allocator.construct(node->data, val);
				_rbt.insert(node);
			}

			// wrap into debug delete before prod
            void inorder() { _rbt.inorder(); }
            void levelOrder() { _rbt.levelOrder(); }

	    private:
			key_compare					_comp;
            allocator_type              _allocator;
			tree_type					_rbt;
	};
}

#endif // !STACK_HPP