/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:01:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/28 21:55:56 by adda-sil         ###   ########.fr       */
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

			typedef RBTNode<value_type>															node_type;
			typedef node_type *																	node_ptr;
			
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
			) : _comp_values(value_compare(comp)), _comp_keys(comp), _allocator(alloc)
			{
				_init_tree();
			}

			~map() {
				erase(begin(), end());
				//to delete;
				delete _sentry->data;
				delete _sentry;
			}

			iterator begin() {
				return iterator(_sentry->left);
			}
			iterator end() {
				return iterator(_sentry);
			}
			iterator rbegin() {
				return iterator(_sentry->right);
			}
			iterator rend() {
				return iterator(_sentry);
			}

			// ft::pair<iterator, bool> insert (const value_type &val) {
			// pair<iterator, bool> insert (const value_type &val) {
			// 	node_ptr n = _new_node(val);
			// 	std::cout << RED << "BEFORE INSERT" << _root << " | " << n << RESET << std::endl;
			// 	node_ptr still_exist = NULL;
			// 	_root = _insert_node(_root, n, &still_exist);
			// 	std::cout << RED << "AFTER INSERT" << _root << " | " << n << RESET << std::endl;
			// 	// print();

			// 	if (still_exist) {
			// 		std::cout << "Still exist ? " << *still_exist << " root is " << *_root << std::endl;
			// 		return ft::make_pair<iterator, bool>(iterator(still_exist), false);
			// 	} else {
			// 		if (_sentry->left == _sentry || _comp_values(*(n->data), *(_sentry->left->data)))
			// 			_sentry->left = n;
			// 		else if (_sentry->right == _sentry || _comp_values(*(_sentry->left->data), *(n->data)))
			// 			_sentry->right = n;
			// 		_sentry->parent = _root;
			// 		// _root->fixViolation(_root, n, _sentry);
			// 		return ft::make_pair<iterator, bool>(iterator(n), true);
			// 	}
			// 	// MDBG("Root is " << *_root);
			// }

			// helped from https://www.techiedelight.com/deletion-from-bst/
			size_type erase(const key_type & k) {
				pair<node_ptr, bool> found = _find(k);

				if (!found.second)
					return (0);
				node_ptr d = found.first;
				_erase(d);
				return (1);
			}
			
			void _erase(node_ptr d) {
				_prepare_sentry_kill(d);
				MDBG("Deleting case");
				if (d->is_leaf()) {
					MDBG("Deleting case 1");
					// case 1
					if (!d->is_root()) {
						if (d->is_left()) {
							d->parent->left = _sentry;
						} else {
							d->parent->right = _sentry;
						}
					} else {
						_root = _sentry;
					}
				} else if (d->has_one_childs()) {
					MDBG("Deleting case 2");
					node_ptr child = d->get_uniq_child();
					if (d->is_root()) {
						_root = child;
						child->parent = _sentry;
						_sentry->parent = child;
					} else {
						if (d->is_left()) {
							d->parent->left = child;
						} else if (d->is_right()) {
							d->parent->right = child;
						}
						child->parent = d->parent;
					}
				} else if (d->has_two_childs()) {
					MDBG("Third case delete");
					node_ptr next = d->getNext();
					node_ptr next_parent = next->parent;

					MDBG("Third case next " << *next);
					MDBG("Third case next_parent " << *next_parent);
					// 1
					if (d != next_parent) {
						MDBG("UUUH? " << *next << " AND " << *next->right);
						next_parent->left = next->right;
						next->right->parent = next_parent;
					} else {
						MDBG("YOOO " << *next << " AND " << *next->right);
						if (next->right->exist())
							next->right->parent = d;
						d->right = next->right;
					}
					// 2
					MDBG("A " << *d);
					MDBG("B " << *next);
					// Vu qu'on switch les data et pas les nodes, attention à la sentinelle
					if (_sentry->right == next)
						_sentry->right = d;
					std::swap(next->data, d->data);
					MDBG("C " << *d);
					MDBG("D " << *next);
					d = next;
				}
				_delete_node(d);
			}

			void erase (iterator it) {
				_erase(it.base());
			}

			void erase (iterator first, iterator last) {
				while (first != last)
					erase(first++);
			}

			pair<iterator, bool> insert(const value_type &val) {
				pair<node_ptr, bool> found = _find(val.first);
				node_ptr parent = found.first;
				MDBG("Found" << found.second << " | " << *parent);
				if (found.second) {
					return ft::make_pair(iterator(parent), false);
				} else {
					node_ptr node = _new_node(val);
					if (_root == _sentry) {
						_root = node;
						node->parent = _sentry;
						_sentry->right = node;
						_sentry->left = node;
						_sentry->parent = node;
					} else {
						node->parent = parent;
						MDBG("Inserting " << *node);
						if (_comp_values(*(parent->data), val)) {
							parent->right = node;
						} else {
							parent->left = node;
						}
						if (_comp_values(*(_sentry->right->data), val)) {
							_sentry->right = node;
						} else if (_comp_values(val, *(_sentry->left->data))) {
							_sentry->left = node;
						}
						// _root->fixViolation(_root, node, _sentry);
					}
					return ft::make_pair<iterator, bool>(iterator(node), true);
				}
			}

			void print() {
				std::cout << "-------------------" << std::endl;
				// std::cout << "First" << *(_sentry->left) << std::endl;
				std::cout << "Sentry" << *_sentry << std::endl;
				// std::cout << "Last" << *(_sentry->right) << std::endl;
				std::cout << "-------------------" << std::endl;
				print_node(_root);
			}

			void print_node(node_ptr node, int level = 0) {
				std::cout << "PRINNNNT --- \n";
				if (node == _sentry) {
					std::cout << "Nothing";
					return ;
				}
				std::cout << "Lvl " << level << YELLOW;
				std::cout << " Node: " << *node;
				std::cout << RED << "left(";
				if (node->left != _sentry) {
					print_node(node->left, level += 1);
				} else {
					std::cout << "🍂";
				}
				std::cout << ") " << BLUE << "right(";
				if (node->right != _sentry) {
					std::cout << "right: ";
					print_node(node->right, level += 1);
				} else {
					std::cout << "🍂";
				}
				std::cout << ")" << RESET;
			}

	    private:
			value_compare				_comp_values;
			key_compare					_comp_keys;
            allocator_type              _allocator;
			node_ptr					_root;
			node_ptr					_sentry;

			void _init_tree(void) {
				_sentry = new node_type();
				_sentry->data = new value_type(make_pair(-1, "sentry"));
				_sentry->color = BLACK_NODE;
				// risque de poser pb
				_sentry->right = _sentry;
				_sentry->left = _sentry;
				_sentry->parent = _sentry;
				_sentry->sentry = _sentry;
				std::cout << "Sentry " << *_sentry << std::endl;
				_root = _sentry;
			}

			node_ptr _new_node(const value_type &val) {
				node_ptr node = new node_type();
				node->data = _allocator.allocate(1);
				_allocator.construct(node->data, val);
				node->right = _sentry;
				node->left = _sentry;
				node->sentry = _sentry;
				return node;
			}

			void _delete_node(node_ptr node) {
				std::cout << "deleting " << *node << std::endl; 
				_allocator.destroy(node->data);
				_allocator.deallocate(node->data, 1);
				delete node;
			}

			void _prepare_sentry_kill(node_ptr node) {
				if (node == _sentry->left) {
					node_ptr n = node->getNext();
					MDBG("Sentry left reset to " << *n);
					_sentry->left = n;
				}
				if (node == _sentry->right) {
					node_ptr n = node->getPrev();
					MDBG("Sentry right reset to " << *n);
					_sentry->right = n;
				}
				// _sentry->parent = _root;
			}

			pair<node_ptr, bool> _find(key_type k) {
				node_ptr next = _root;
				node_ptr prev = _root;

				MDBG("Start");
				while (!next->nil()) {
					prev = next;
					MDBG("Slt" << *next);
					if (_comp_keys(next->data->first, k)) {
						next = next->right;
					} else if (_comp_keys(k, next->data->first)) {
						next = next->left;
					} else {
						return ft::make_pair<node_ptr, bool>(next, true);
					}
				}
				return ft::make_pair<node_ptr, bool>(prev, false);
			}

			node_ptr _insert_node(node_ptr base, node_ptr el, node_ptr *still_exist) {
				MDBG("Inserting " << *still_exist << std::endl);
				el->parent = base;
				if (base == _sentry) {
					return el;
				}
				MDBG("Inserting el: " << *el << " | " << el << std::endl);
				MDBG("Inserting base: " << base << " | " << *base << std::endl);
				if (_comp_values(*(el->data), *(base->data))) {
					MDBG("Inserting left: " << *el << " | " << el);
					base->left = _insert_node(base->left, el, still_exist);
				} else if (_comp_values(*(base->data), *(el->data))) {
					MDBG("Inserting right: " << *el << " | " << el);
					base->right = _insert_node(base->right, el, still_exist);
				} else {
					MDBG("Inserting unchanged" << *el << " | " << el);
					*still_exist = base;
				}
				return base;
			}
	};
}

#endif // !STACK_HPP