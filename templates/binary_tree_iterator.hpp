/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_iterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:48:57 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/08 14:58:57 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARYTREEITERATOR_HPP
# define BINARYTREEITERATOR_HPP 1
# include <iostream>
# include "iterator.hpp"

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
            // binary_tree_iterator(const_pointer x) : _p(x) {}
            // binary_tree_iterator(const_iterator & cpy) : _p(cpy._p) {}
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
  
            // bool operator == (const binary_tree_iterator & rhs) const { return this->_p == rhs._p; }
            // bool operator != (const binary_tree_iterator & rhs) const { return this->_p != rhs._p; }
            // bool operator >= (const binary_tree_iterator & rhs) const { return this->_p >= rhs._p; }
            // bool operator <= (const binary_tree_iterator & rhs) const { return this->_p <= rhs._p; }
            // bool operator < (const binary_tree_iterator & rhs) const { return this->_p < rhs._p; }
            // bool operator > (const binary_tree_iterator & rhs) const { return this->_p > rhs._p; }
       
            binary_tree_iterator & operator ++ (void) { ++(this->_p); return *this; }
            binary_tree_iterator operator ++ (int) { binary_tree_iterator tmp(*this); operator++(); return tmp; }
            binary_tree_iterator & operator -- (void) { --(this->_p); return *this; }
            binary_tree_iterator operator -- (int) { binary_tree_iterator tmp(*this); operator--(); return tmp; }
            binary_tree_iterator & operator += (difference_type dt) { this->_p += dt; return *this; }
            binary_tree_iterator & operator -= (difference_type dt) { this->_p -= dt; return *this; }
            // contains: *a++ *a-- *a = T
            reference operator * () { return *(this->_p); }
            pointer operator -> () { return this->_p; }
		    reference operator [] (difference_type at) const {
				IDBG("op[" << at << "] = " << _p[at]);
                return (_p[at]); 
            }
			binary_tree_iterator operator + (difference_type n) const { IDBG("this + n"); return this->_p + n; }
			binary_tree_iterator operator - (difference_type n) const { return this->_p - n; }
			difference_type operator - (binary_tree_iterator rhs) const { return this->_p - rhs._p; }

            pointer base(void) const { return _p; }

        private:
            pointer     _p;
    };

    template<typename T>
    ft::binary_tree_iterator<T> operator + (
        typename ft::binary_tree_iterator<T>::difference_type lhs,
        typename ft::binary_tree_iterator<T> & rhs
    ) {
        IDBG("T + n");
        return (&(*rhs) + lhs);
    }

    template<typename T>
    ft::binary_tree_iterator<T> operator - (
        typename ft::binary_tree_iterator<T>::difference_type lhs,
        typename ft::binary_tree_iterator<T> & rhs
    ) {
        return (&(*rhs) - lhs);
    }

    // template<typename T>
    // typename ft::binary_tree_iterator<T>::difference_type operator - (
    //     typename ft::binary_tree_iterator<T> & lhs,
    //     typename ft::binary_tree_iterator<T> & rhs
    // ) {
    //     IDBG("T - T");
    //     return (lhs.base() - rhs.base());
    // }

    template<typename T, typename U>
    typename ft::binary_tree_iterator<T>::difference_type operator - (
        const ft::binary_tree_iterator<T> & lhs,
        const ft::binary_tree_iterator<U> & rhs
    ) {
        IDBG("T - U");
        return (&(lhs[0]) - &(rhs[0]));
    }

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
	// template <typename T, typename U>
	// bool operator == (const ft::binary_tree_iterator<T> & lhs, const ft::binary_tree_iterator<U> & rhs) {
	// 	return &(lhs[0]) == &(rhs[0]);
	// }

	template <typename T, typename U>
	bool operator != (
        const ft::binary_tree_iterator<T> & lhs,
        const ft::binary_tree_iterator<U> & rhs
    ) {
		return !(lhs == rhs);
	}
	template <typename T, typename U>
	bool operator < (const ft::binary_tree_iterator<T> & lhs, const ft::binary_tree_iterator<U> & rhs) {
		return !(lhs >= rhs);
	}
	template <typename T, typename U>
	bool operator > (const ft::binary_tree_iterator<T> & lhs, const ft::binary_tree_iterator<U> & rhs) {
		return !(lhs <= rhs);
	}
	template <typename T, typename U>
	bool operator <= (const ft::binary_tree_iterator<T> & lhs, const ft::binary_tree_iterator<U> & rhs) {
		return &(lhs[0]) <= &(rhs[0]);
	}
	template <typename T, typename U>
	bool operator >= (const ft::binary_tree_iterator<T> & lhs, const ft::binary_tree_iterator<U> & rhs) {
		return &(lhs[0]) >= &(rhs[0]);
	}

}

#endif