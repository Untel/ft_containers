/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:01:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/04/09 18:35:01 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP 1

# include <iostream>
# include <stdexcept>
# include "utils.hpp"
# include "pair.hpp"
# include "common.hpp"
# include "rbt_node.hpp"
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
			typedef typename ft::binary_tree_iterator< value_type >					iterator; //a bidirectional iterator to value_type	convertible to const_iterator
			typedef typename ft::binary_tree_iterator< const value_type>		const_iterator; //a bidirectional iterator to const value_type	
			typedef typename ft::reverse_iterator< iterator >           						reverse_iterator;
			typedef typename ft::reverse_iterator< const_iterator >     						const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type     				difference_type;
			// typedef typename ft::RBTree<value_type>												tree_type;

			typedef RBTNode<value_type>															node_type;
			typedef RBTNode<const value_type>													const_node_type;
			typedef node_type *																	node_ptr;
			typedef const_node_type *															const_node_ptr;
			
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

			map(const map &cpy) :
				_comp_values(value_compare(cpy._comp_keys)),
				_comp_keys(cpy._comp_keys),
				_allocator(cpy._allocator),
				_size(0)
			{
				_init_sentry();
				insert(cpy.begin(), cpy.end());
			}
			map & operator = ( const map &cpy) {
				clear();
				_delete_node(_sentry);
				_size = 0;
				_allocator = cpy._allocator;
				_comp_keys = cpy._comp_keys;
				_comp_values = value_compare(_comp_keys);
				_init_sentry();
				insert(cpy.begin(), cpy.end());
                return *this;
            }

			~map() {
				clear();
				_delete_node(_sentry);
			}

            iterator begin() {
                return iterator(_sentry->left);
            }
            const_iterator begin() const {
                return const_iterator(reinterpret_cast<const_node_ptr>(_sentry->left));
            }
            iterator end() {
                return iterator(_sentry);
            }
            const_iterator end() const {
                return const_iterator(reinterpret_cast<const_node_ptr>(_sentry));
            }

            reverse_iterator rbegin() {
                return reverse_iterator(end());
            }
            const_reverse_iterator rbegin() const {
                return const_reverse_iterator(end());
            }
            reverse_iterator rend() {
                return reverse_iterator(begin());
            }
            const_reverse_iterator rend() const {
                return const_reverse_iterator(begin());
            }

			// helped from https://www.techiedelight.com/deletion-from-bst/
			void _erase(node_ptr node) {
				if (node == _sentry->left)
					_sentry->left = node->getNext();
				if (node == _sentry->right)
					_sentry->right = node->getPrev();
				if (_size > 1)
					_unlink_node(node);
				else
					_root = _sentry;
				_sentry->parent = _root;
				_delete_node(node);
				_size--;
				#ifdef DEBUG
					print();
					MDBG("NEW ROOT IS " << *_root);
				#endif
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

			void _attach(node_ptr parent, node_ptr node, NodeFinder pos) {
				node->parent = parent;
				switch (pos) {
					case NO_ELEMS:
						_root = node;
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
						//MDBG("Should never happen");
						throw std::exception();
				}
				_size++;
			}

			pair<iterator, bool> _insert(const value_type & val, node_ptr from) {
				pair<node_ptr, NodeFinder> found = _find(val.first, from);
				node_ptr parent = found.first;
				if (found.second == FOUND)
					return ft::make_pair(iterator(parent), false);
				node_ptr node = _new_node(val);
				MDBG("CREATING NODE " << _size << " " << *node);
				_attach(parent, node, found.second);
				_fixViolation(node);
				_root->color = BLACK_NODE;
				return ft::make_pair<iterator, bool>(iterator(node), true);
			}

			pair<iterator, bool> insert(const value_type & val) {
				return (_insert(val, _root));
			}

			template <class InputIterator>
  			void insert(
				InputIterator first,
				InputIterator last
			) {
				while (first != last) {
					insert(*first);
					first++;
				}
			}

			iterator insert (iterator hint, const value_type & val) {
				// Fast insert if pos is begin or rbegin (sentry values)
				node_ptr	base = hint.base();
				if ((base == _sentry->right) && _comp_values(*base->data, val)) {
					return _insert(val, base).first;
				} else if (base == _sentry->left && _comp_values(val, *base->data)) {
					return _insert(val, base).first;
				}
				return _insert(val, _root).first;
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

			iterator lower_bound(const key_type k) {
				iterator it = begin();
				iterator ite = end();
				for (; it != ite; it++)
					if (!(_comp_keys(it->first, k)))
						return (it);
				return (it);
			}

			const_iterator lower_bound(const key_type k) const {
				const_iterator it = begin();
				const_iterator ite = end();
				for (; it != ite; it++)
					if (!(_comp_keys(it->first, k)))
						return (it);
				return (end());
			}

			iterator upper_bound(const key_type &k) {
				iterator it = begin();
				iterator ite = end();
				for (; it != ite; it++)
					if (!(_comp_keys(it->first, k)) && _comp_keys(k, it->first))
						return (it);
				return (it);
			}

			const_iterator upper_bound(const key_type &k) const {
				const_iterator it = begin();
				const_iterator ite = end();
				for (; it != ite; it++)
					if (!(_comp_keys(it->first, k)) && _comp_keys(k, it->first))
						return (it);
				return (end());
			}

			ft::pair<iterator, iterator> equal_range(const key_type &k) {
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

			ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const {
				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

            void swap (map & x) {
				value_compare		tmp_comp_values = _comp_values;
				key_compare			tmp_comp_keys = _comp_keys;
				node_ptr			tmp_sentry = _sentry;
				node_ptr			tmp_root = _root;
				size_type			tmp_size = _size;

				_comp_values = x._comp_values;
				_comp_keys = x._comp_keys;
				_sentry = x._sentry;
				_root = x._root;
				_size = x._size;

				x._comp_values = tmp_comp_values;
				x._comp_keys = tmp_comp_keys;
				x._sentry = tmp_sentry;
				x._root = tmp_root;
				x._size = tmp_size;
            }

			#ifdef DEBUG
				void	print(node_ptr node)
				{
					std::stringstream	buffer;

					if (node != _sentry) {
						_print(node, buffer, true, "");
						std::cout << buffer.str();
					}
				}

				void	print(void) {
					std::cout << "size: " << size() << std::endl;
					std::cout << "sentry: " << *_sentry << std::endl;
					print(_root);
				}

				void _print(node_ptr node, std::stringstream &buffer, bool isTail, std::string prefix)
				{
					if (node->right && node->right->exist())
						this->_print(node->right, buffer, false, std::string(prefix).append(isTail ? "│   " : "    "));
					buffer << prefix << (isTail ? "└── " : "┌── ");
					if (node->color == RED_NODE)
						buffer << "\033[31m";
					buffer << *(node->data) << "\033[0m" << (node->is_leaf() ? "🌱" : "") << std::endl;
					if (node->left && node->left->exist())
						this->_print(node->left, buffer, true, std::string(prefix).append(isTail ? "    " : "│   "));
				}
			#endif

	    private:
			value_compare				_comp_values;
			key_compare					_comp_keys;
            allocator_type              _allocator;
			node_ptr					_sentry;
			node_ptr					_root;
			size_type					_size;


			node_ptr _init_sentry(void) {
				_sentry = new node_type();
				_sentry->data = _allocator.allocate(1);
				_allocator.construct(_sentry->data, value_type(key_type(), mapped_type()));
				_sentry->color = BLACK_NODE;
				_sentry->right = _sentry;
				_sentry->left = _sentry;
				_sentry->parent = _sentry;
				_sentry->sentry = _sentry;
				_root = _sentry;
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

			void _unlink_node(node_ptr node) {
				node_ptr y = node;
				node_ptr x;
				Color origin = node->color;
				if (node->left->nil()) {
					x = node->right;
					_transplant(node, node->right);
				} else if (node->right->nil()) {
					x = node->left;
					_transplant(node, node->left);
				} else {
					y = node->right->min_subtree();
					origin = y->color;
					x = y->right;
					if (y->parent == node) {
						x->parent = y;
					}
					else {
						_transplant(y, y->right);
						y->right = node->right;
						y->right->parent = y;
					}
					_transplant(node, y);
					y->left = node->left;
					y->left->parent = y;
					y->color = node->color;
				}
				if (origin == BLACK_NODE)
					_fixDelete(x);
			}

			void _rotateLeft(node_ptr node) {
				node_ptr right_node = node->right;
			
				node->right = right_node->left;
				if (node->right->exist())
					node->right->parent = node;
				right_node->parent = node->parent;
				if (node->is_root()) {
					_root = right_node;
				}
				else if (node == node->parent->left)
					node->parent->left = right_node;
				else
					node->parent->right = right_node;
				right_node->left = node;
				node->parent = right_node;
			}
			void _rotateRight(node_ptr node) {
				node_ptr left_node = node->left;
			
				node->left = left_node->right;        
				if (node->left != _sentry)
					node->left->parent = node;
				left_node->parent = node->parent;
				if (node == _root)
					_root = left_node;
				else if (node == node->parent->left)
					node->parent->left = left_node;
				else
					node->parent->right = left_node;
				left_node->right = node;
				node->parent = left_node;
			}

			void _fixViolation(node_ptr node) {
				node_ptr parent_node = _sentry;
				node_ptr grand_parent_node = _sentry;

				while (
					(!node->is_root()) &&
					(node->color != BLACK_NODE) &&
					(node->parent->color == RED_NODE)
				) {
					parent_node = node->parent;
					grand_parent_node = node->grand_parent();
					if (parent_node == grand_parent_node->left) {
						node_ptr uncle_pt = grand_parent_node->right;
						if (uncle_pt->exist() && uncle_pt->color == RED_NODE) {
							grand_parent_node->color = RED_NODE;
							parent_node->color = BLACK_NODE;
							uncle_pt->color = BLACK_NODE;
							node = grand_parent_node;
						} else {
							if (node->is_right()) {
								_rotateLeft(parent_node);
								node = parent_node;
								parent_node = node->parent;
							}
							_rotateRight(grand_parent_node);
							std::swap(parent_node->color, grand_parent_node->color);
							node = parent_node;
						}
					} else {
						node_ptr uncle_pt = grand_parent_node->left;
						if (uncle_pt->exist() && (uncle_pt->color == RED_NODE)) {
							grand_parent_node->color = RED_NODE;
							parent_node->color = BLACK_NODE;
							uncle_pt->color = BLACK_NODE;
							node = grand_parent_node;
						} else {
							if (node == parent_node->left) {
								_rotateRight(parent_node);
								node = parent_node;
								parent_node = node->parent;
							}
							_rotateLeft(grand_parent_node);
							std::swap(parent_node->color, grand_parent_node->color);
							node = parent_node;
						}
					}
				}
			}

			void _fixDelete(node_ptr x) {
				while (x != _root && x != _sentry && x->color == BLACK_NODE) {
					if (x == x->parent->left) {
						node_ptr w = x->parent->right;
						if (w->color == RED_NODE) {
							w->color = BLACK_NODE;
							x->parent->color = RED_NODE;
							_rotateLeft(x->parent);
							w = x->parent->right;
						}
						if (w->left->color == BLACK_NODE && w->right->color == BLACK_NODE) {
							w->color = RED_NODE;
							x = x->parent;
						} else {
							if (x->right->color == BLACK_NODE) {
								w->left->color = BLACK_NODE;
								w->color = RED_NODE;
								_rotateRight(w);
								w = x->parent->right;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK_NODE;
							w->right->color = BLACK_NODE;
							_rotateLeft(x->parent);
							x = _root;
						}
					}
					else {
						node_ptr w = x->parent->left;
						if (w->color == RED_NODE) {
							w->color = BLACK_NODE;
							x->parent->color = RED_NODE;
							_rotateRight(x->parent);
							w = x->parent->left;
						}
						if (w->right->color == BLACK_NODE && w->left->color == BLACK_NODE) {
							w->color = RED_NODE;
							x = x->parent;
						} else {
							if (x->left->color == BLACK_NODE) {
								w->right->color = BLACK_NODE;
								w->color = RED_NODE;
								_rotateLeft(w);
								w = x->parent->left;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK_NODE;
							w->left->color = BLACK_NODE;
							_rotateRight(x->parent);
							x = _root;
						}
					}
				}
				x->color = BLACK_NODE;
			}


			void _transplant(node_ptr node, node_ptr with) {
				if (node == _root) {
					_root = with;
				}  else if (node->is_left()) {
					node->parent->left = with;
				} else {
					node->parent->right = with;
				}
				with->parent = node->parent;
			}

			void _delete_node(node_ptr node) {
				_allocator.destroy(node->data);
				_allocator.deallocate(node->data, 1);
				delete node;
			}

			ft::pair<node_ptr, NodeFinder> _find(const key_type & k) const {
				return _find(k, _root);
			}

			ft::pair<node_ptr, NodeFinder> _find(const key_type & k, node_ptr from) const {
				node_ptr next = from;
				node_ptr prev = from;
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

	template <class K, class V, class Cmp, class Alc>
    bool operator == (const ft::map<K,V,Cmp,Alc> & lhs, const ft::map<K,V,Cmp,Alc> & rhs) {
        if (lhs.size() != rhs.size())
            return false;
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    template <class K, class V, class Cmp, class Alc>
    bool operator != (const ft::map<K,V,Cmp,Alc>& lhs, const ft::map<K,V,Cmp,Alc>& rhs) {
        return (!(lhs == rhs));
    }
    template <class K, class V, class Cmp, class Alc>
    bool operator < (const ft::map<K,V,Cmp,Alc>& lhs, const ft::map<K,V,Cmp,Alc>& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template <class K, class V, class Cmp, class Alc>
    bool operator > (const ft::map<K,V,Cmp,Alc>& lhs, const ft::map<K,V,Cmp,Alc>& rhs) {
        return (rhs < lhs);
    }
    template <class K, class V, class Cmp, class Alc>
    bool operator <= (const ft::map<K,V,Cmp,Alc>& lhs, const ft::map<K,V,Cmp,Alc>& rhs) {
        return !(rhs < lhs);
    }
    template <class K, class V, class Cmp, class Alc>
    bool operator >= (const ft::map<K,V,Cmp,Alc>& lhs, const ft::map<K,V,Cmp,Alc>& rhs) {
        return !(lhs < rhs);
    }

    template <class K, class V, class Cmp, class Alc>
    void swap (ft::map<K,V,Cmp,Alc> & x, ft::map<K,V,Cmp,Alc> & y) {
        x.swap(y);
    }
}

#endif // !STACK_HPP