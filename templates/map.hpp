/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:01:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/23 13:43:53 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP 1

# include <iostream>
# include <stdexcept>
# include "utils.hpp"
# include "pair.hpp"
# include "rbt_node.hpp"
// # include "rbtree.hpp"
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
			// typedef typename ft::RBTree<value_type>												tree_type;
			typedef RBTNode<value_type>				node_type;
			typedef node_type *						node_ptr;

			class value_compare : public std::binary_function<value_type, value_type, bool> {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
				friend class map<key_type, mapped_type, key_compare, allocator_type>;
				protected:
					key_compare comp;
					value_compare (key_compare c) : comp(c) {}  // constructed with map's comparison object
				public:
					typedef bool			result_type;
					typedef value_type 		first_argument_type;
					typedef value_type 		second_argument_type;
					bool operator() (const value_type & x, const value_type & y) const {
						return comp(x.first, y.first);
					}
			};

			explicit map (
				const key_compare & comp = key_compare(),
				const allocator_type& alloc = allocator_type()
			) : _comparator(value_compare(comp)), _allocator(alloc)
			{
				_init_tree();
			}

			// ft::pair<iterator, bool> insert (const value_type &val) {
			void insert (const value_type &val) {
				node_ptr n = _new_node(val);
				// std::cout << RED << "BEFORE INSERT" << _root << " | " << n << RESET << std::endl;
				_root = _insert_node(_root, n);
				// std::cout << RED << "AFTER INSERT" << _root << " | " << n << RESET << std::endl;
				// print();

				_root->fixViolation(_root, n, _sentry);
				// MDBG("Root is " << *_root);
			}

			void print() {
				print_node(_root);
			}
			void print_node(node_ptr node) {
				if (node == _sentry) {
					std::cout << "Nothing";
					return ;
				}
				std::cout << YELLOW << *node;
				std::cout << RED << "left(";
				if (node->left != _sentry) {
					print_node(node->left);
				} else {
					std::cout << "🍂";
				}
				std::cout << ") " << BLUE << "right(";
				if (node->right != _sentry) {
					std::cout << "right: ";
					print_node(node->right);
				} else {
					std::cout << "🍂";
				}
				std::cout << ")" << RESET;
			}

	    private:
			value_compare				_comparator;
            allocator_type              _allocator;
			node_ptr					_root;
			node_ptr					_sentry;

			void _init_tree(void) {
				_sentry = new node_type();
				_sentry->data = new value_type(make_pair(-1, "sentry"));
				_sentry->color = BLACK_NODE;
				std::cout << "Sentry " << *_sentry << std::endl;
				_root = _sentry;
			}

			node_ptr _new_node(const value_type &val) {
				node_ptr node = new node_type();
				node->data = _allocator.allocate(1);
				_allocator.construct(node->data, val);
				node->right = _sentry;
				node->left = _sentry;
				return node;
			}

			node_ptr _insert_node(node_ptr base, node_ptr el) {
				el->parent = base;
				if (base == _sentry) {
					return el;
				}
				MDBG("Inserting el: " << *el << " | " << el << std::endl);
				MDBG("Inserting base: " << base << " | " << *base << std::endl);
				if (_comparator(*(el->data), *(base->data))) {
					MDBG("Inserting left: " << *el << " | " << el);
					base->left = _insert_node(base->left, el);
				} else if (_comparator(*(base->data), *(el->data))) {
					MDBG("Inserting right: " << *el << " | " << el);
					base->right = _insert_node(base->right, el);
				} else {
					MDBG("Inserting unchanged" << *el << " | " << el);
				}
				return base;
			}
	};
}

#endif // !STACK_HPP