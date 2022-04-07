/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_iterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:48:57 by adda-sil          #+#    #+#             */
/*   Updated: 2022/04/07 02:36:36 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARYTREEITERATOR_HPP
# define BINARYTREEITERATOR_HPP 1
# include <iostream>
# include "iterator.hpp"
# include "rbt_node.hpp"

namespace ft
{
    template < class T >
    class binary_tree_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {
        public:
            typedef ptrdiff_t                           	    difference_type;
            typedef T                                   	    value_type;
            typedef value_type *                           	    pointer;
            typedef value_type &                           	    reference;
            typedef const value_type *                          const_pointer;
            typedef const value_type &                          const_reference;
            typedef std::bidirectional_iterator_tag     	    iterator_category;

            typedef RBTNode<value_type>				            node_type;
            typedef RBTNode<const value_type>                   const_node_type;
			typedef node_type *						            node_ptr;
			typedef const_node_type *						    const_node_ptr;
            // Member types
            binary_tree_iterator(void) : _p(NULL) {}
            binary_tree_iterator(const node_ptr x) : _p(x) {}
            binary_tree_iterator(const binary_tree_iterator & cpy) : _p(cpy._p) {}
            binary_tree_iterator & operator = (const binary_tree_iterator & rhs) {
                _p = rhs._p;
                return *this;
            }
            operator binary_tree_iterator<const value_type>(void) const {
                return (binary_tree_iterator<const value_type>(
                    reinterpret_cast<const_node_ptr>(_p)
                ));
            }
            ~binary_tree_iterator(void) {}
       
            binary_tree_iterator & operator ++ (void) {
                if (_p->nil()) {
                    _p = _p->parent->min_subtree();
                } else
                    _p = _p->getNext();
                return (*this);
            }
            binary_tree_iterator operator ++ (int) {
                binary_tree_iterator tmp(*this); operator++(); return tmp;
            }
            binary_tree_iterator & operator -- (void) {
                // Si le courant == end() == la sentry, alors on set automatiquement à _sentry->right qui est le max value
                if (_p->nil()) {
                    _p = _p->parent->max_subtree();
                } else
                    _p = _p->getPrev();
                return (*this);
            }
            binary_tree_iterator operator -- (int) {
                binary_tree_iterator tmp(*this); operator--(); return tmp;
            }
            reference operator * () const {
                return *(this->_p->data);
            }

            pointer operator -> () const { return _p->data; }

            node_ptr base() const { return _p; }
        private:
            node_ptr           _p;
            node_ptr           _root;

    };

    template <typename T>
    bool operator == (
        const ft::binary_tree_iterator<T> & lhs,
        const ft::binary_tree_iterator<T> & rhs
    ) {
        typedef typename ft::binary_tree_iterator<T>::const_node_ptr n;
        return reinterpret_cast<n>(lhs.base()) == reinterpret_cast<n>(rhs.base());
    }

    template<typename T, typename U>
    bool operator == (
        const ft::binary_tree_iterator<T> & lhs,
        const ft::binary_tree_iterator<U> & rhs
    ) {
        typedef typename ft::binary_tree_iterator<T>::const_node_ptr n;
        typedef typename ft::binary_tree_iterator<U>::const_node_ptr m;
        return reinterpret_cast<n>(lhs.base()) == reinterpret_cast<m>(rhs.base());
    }

	template <typename T, typename U>
	bool operator != (
        const ft::binary_tree_iterator<T> & lhs,
        const ft::binary_tree_iterator<U> & rhs
    ) {
		return !(lhs == rhs);
	}

}

#endif