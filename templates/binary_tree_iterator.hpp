/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_iterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:48:57 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/18 19:05:05 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARYTREEITERATOR_HPP
# define BINARYTREEITERATOR_HPP 1
# include <iostream>
# include "iterator.hpp"
# include "rbt_node.hpp"

namespace ft
{
    /**
     * @brief 
     * @see https://cplusplus.com/reference/iterator/RandomAccessIterator/
     * @todo For mutable iterators (non-constant iterators): Can be dereferenced as an lvalue (if in a dereferenceable state).
     */
    template < class T >
    class binary_tree_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {
        // typedef typename
        public:
            typedef ptrdiff_t                           	    difference_type;
            typedef T                                   	    value_type;
            typedef value_type *                           	    pointer;
            typedef value_type &                           	    reference;
            typedef const value_type *                          const_pointer;
            typedef const value_type &                          const_reference;
            typedef std::bidirectional_iterator_tag     	    iterator_category;
            typedef binary_tree_iterator<value_type>     	    iterator;
            typedef binary_tree_iterator<const value_type>     	const_iterator;
            // Member types
            binary_tree_iterator(void) : _p(NULL) {}
            binary_tree_iterator(pointer x) : _p(x) {}
            binary_tree_iterator(const binary_tree_iterator & cpy) : _p(cpy._p) {}
            binary_tree_iterator & operator = (const binary_tree_iterator & rhs) {
                _p = rhs._p;
                return *this;
            }
            operator binary_tree_iterator<const value_type>() const {
                return (binary_tree_iterator<const value_type>(this->_p));
            }
            // maybe return void *a = t
            // binary_tree_iterator & operator = (reference val) { *this->_p = val; return *this; }
            ~binary_tree_iterator(void) {}
       
            // binary_tree_iterator & operator ++ (void) {
            //     // return binary_tree_iterator();
            // }
            binary_tree_iterator operator ++ (int) { binary_tree_iterator tmp(*this); operator++(); return tmp; }
            binary_tree_iterator & operator -- (void) { --(this->_p); return *this; }
            binary_tree_iterator operator -- (int) { binary_tree_iterator tmp(*this); operator--(); return tmp; }
            reference operator * () { return *(this->_p); }
            pointer operator -> () { return this->_p; }

        private:
            RBTNode<T> *     _p;

    };

    template <typename T>
    bool operator == (
        const ft::binary_tree_iterator<T> & lhs,
        const ft::binary_tree_iterator<T> & rhs
    ) {
        IDBG("T == T");
        return (&(lhs[0]) == &(rhs[0]));
    }

    template<typename T, typename U>
    bool operator == (
        const ft::binary_tree_iterator<T> & lhs,
        const ft::binary_tree_iterator<U> & rhs
    ) {
        IDBG("T == U");
        return (&(lhs[0]) == &(rhs[0]));
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