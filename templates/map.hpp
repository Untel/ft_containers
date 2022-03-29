/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:01:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/29 22:37:48 by adda-sil         ###   ########.fr       */
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

	enum NodeFinder { NO_ELEMS, IS_LEFT, IS_RIGHT, FOUND };

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
			) :
				_comp_values(value_compare(comp)),
				_comp_keys(comp),
				_allocator(alloc),
				_size(0)
			{
				_init_sentry();
			}

			template <class InputIterator>
  			map(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()
			) :
				_comp_values(value_compare(comp)),
				_comp_keys(comp),
				_allocator(alloc),
				_size(0)
			{
				_init_sentry();
				insert(first, last);
			}

			~map() {
				clear();
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

			// helped from https://www.techiedelight.com/deletion-from-bst/
			void _erase(node_ptr node) {
				if (node == _sentry->left)
					_sentry->left = node->getNext();
				if (node == _sentry->right)
					_sentry->right = node->getPrev();
				if (node->is_leaf()) {
					MDBG("Deleting case 1");
					// case 1
					if (!node->is_root()) {
						if (node->is_left())
							node->parent->left = _sentry;
						else
							node->parent->right = _sentry;
					} else
						_sentry->parent = _sentry;
				} else if (node->has_one_childs()) {
					MDBG("Deleting case 2");
					node_ptr child = node->get_uniq_child();
					if (node->is_root()) {
						_sentry->parent = child;
						child->parent = _sentry;
					} else {
						if (node->is_left()) {
							node->parent->left = child;
						} else if (node->is_right()) {
							node->parent->right = child;
						}
						child->parent = node->parent;
					}
				} else if (node->has_two_childs()) {
					MDBG("Deleting case 2");
					node_ptr next = node->getNext();
					node_ptr next_parent = next->parent;

					if (node != next_parent) {
						next_parent->left = next->right;
						next->right->parent = next_parent;
					} else {
						if (next->right->exist())
							next->right->parent = node;
						node->right = next->right;
					}
					// Vu qu'on switch les data et pas les nodes, attention à la sentinelle
					if (_sentry->right == next)
						_sentry->right = node;
					std::swap(next->data, node->data);
					node = next;
				}
				_delete_node(node);
				_size--;
			}

			size_type erase(const key_type & k) {
				pair<node_ptr, NodeFinder> found = _find(k);

				if (found.second != FOUND)
					return (0);
				_erase(found.first);
				return (1);
			}

			void erase (iterator it) {
				_erase(it.base());
			}

			void erase (iterator first, iterator last) {
				while (first != last)
					erase(first++);
			}

			iterator find (const key_type & k) {
				pair<node_ptr, NodeFinder> found = _find(k);
				if (found.second == FOUND) {
					return (iterator(found.first));
				}
				return (end());
			}
			const_iterator find (const key_type & k) const {
				pair<node_ptr, NodeFinder> found = _find(k);
				if (found.second == FOUND) {
					return (iterator(found.first));
				}
				return (end());
			}

			mapped_type & operator[] (const key_type & k) {
				return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
			}

			void _insert(node_ptr parent, node_ptr node, NodeFinder pos) {
				node->parent = parent;
				switch (pos) {
					case NO_ELEMS:
						_sentry->parent = node;
						node->parent = _sentry;
						_sentry->right = node;
						_sentry->left = node;
						break;
					case IS_RIGHT:
						parent->right = node;
						if (_comp_values(*(_sentry->right->data), *(node->data)))
							_sentry->right = node;
						break;
					case IS_LEFT:
						parent->left = node;
						if (_comp_values(*(node->data), *(_sentry->left->data)))
							_sentry->left = node;
						break;
					case FOUND:
					default:
						MDBG("Should never happen");
						throw std::exception();
				}
				_size++;
			}

			pair<iterator, bool> insert(const value_type & val) {
				if (_size >= max_size())
                    throw std::length_error("Length error");
				pair<node_ptr, NodeFinder> found = _find(val.first);
				node_ptr parent = found.first;
				if (found.second == FOUND)
					return ft::make_pair(iterator(parent), false);
				node_ptr node = _new_node(val);
				_insert(parent, node, found.second);
				// _root->fixViolation(_root, node, _sentry);
				return ft::make_pair<iterator, bool>(iterator(node), true);
			}

			template <class InputIterator>
  			void insert(
				InputIterator first,
                typename enable_if <!is_integral <InputIterator>::value, InputIterator >::type last
			) {
				while (first != last)
					insert(first, *(first++));
			}

			/**
			 * Bon en vrai ça c'est galère. Le but étant de donner une position "indice"
			 * Tout en vérifiant que la position donnée est "valide" (et donc qu'il n'y a pas une meilleur position)
			 * Si c'est begin() ou end() c'est simple, par contre si le hint est au millieu de l'arbre
			 * il faut vérifier sa validité, et donc vérifié qu'il est cohérent à la position indiquée.
			 */
			iterator insert (iterator hint, const value_type & val) {
				// Fast insert if pos is begin or rbegin (sentry values)
				if ((hint == rbegin()) && _comp_values(*(hint), val)) {
					node_ptr node = _new_node(val);
					_insert(hint, node, IS_RIGHT);
					return (iterator(node));
				} else if (hint == begin() && _comp_values(val, *(hint))) {
					node_ptr node = _new_node(val);
					_insert(hint, node, IS_LEFT);
					return (iterator(node));
				}
				return insert(val).first;


				// val = 105
				// hint = 110
				// 105 < 110, so insert left
				if (_comp_values(val, *hint->data)) {
					MDBG("Should insert left");
					// Should insert left but left still occuped, wrong hint
					if (hint->left->exist())
						return insert(val).first; // BAD HINT, return default behavior
					// Get the oldest left ancestor (stop when the ancestor is a right child)
					node_ptr ancestor = hint->oldest_left_ancestor();
					// So, val should be between ancestor and his parent right ?
					if (_comp_values(*ancestor->data, val) &&
						_comp_values(val, *ancestor->parent->data)
					) {
						// GOOD HINT ?
						node_ptr node = _new_node(val);
						_insert(hint, node, IS_LEFT);
						return iterator(node);
					} else {
						return insert(val).first; // BAD HINT ? return default behavior
					}
				} else if (_comp_values(*hint->data, val)) {
					MDBG("Should insert right");
					// Do the same with the other side
					return iterator(hint);
				}
				return iterator(hint); // Same value, return the existing elem
			}

			size_type 			count(const key_type & k) const { return (find(k) != (end())); }
            size_type           size() const { return _size; }
            bool                empty() const { return _size == 0; }
            size_type           max_size() const { return _allocator.max_size(); }
            key_compare         key_comp() const { return _comp_keys; }
            value_compare       value_comp() const { return _comp_values; }
            allocator_type      get_allocator() const { return _allocator; }

			void clear() {
				erase(begin(), end());
			}

			void print() {
				std::cout << "-------------------" << std::endl;
				// std::cout << "First" << *(_sentry->left) << std::endl;
				std::cout << "Sentry" << *_sentry << std::endl;
				// std::cout << "Last" << *(_sentry->right) << std::endl;
				std::cout << "-------------------" << std::endl;
				print_node(_sentry->parent);
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
			node_ptr					_sentry;
			size_type					_size;

			node_ptr _init_sentry(void) {
				_sentry = new node_type();
				_sentry->data = new value_type(make_pair(-1, "sentry"));
				_sentry->color = BLACK_NODE;
				// risque de poser pb
				_sentry->right = _sentry;
				_sentry->left = _sentry;
				_sentry->parent = _sentry;
				_sentry->sentry = _sentry;
				std::cout << "Sentry " << *_sentry << std::endl;
				return _sentry;
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

			pair<node_ptr, NodeFinder> _find(key_type k) {
				node_ptr next = _sentry->parent;
				node_ptr prev = _sentry->parent;
				NodeFinder state = NO_ELEMS;
				while (!next->nil()) {
					prev = next;
					if (_comp_keys(next->data->first, k)) {
						state = IS_RIGHT;
						next = next->right;
					} else if (_comp_keys(k, next->data->first)) {
						state = IS_LEFT;
						next = next->left;
					} else {
						return ft::make_pair<node_ptr, NodeFinder>(next, FOUND);
					}
				}
				return ft::make_pair<node_ptr, NodeFinder>(prev, state);
			}
		};
}

#endif // !STACK_HPP