/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:48:57 by adda-sil          #+#    #+#             */
/*   Updated: 2022/02/25 07:10:04 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAYITERATOR_HPP
# define ARRAYITERATOR_HPP 1
# include <iostream>     // std::cout
# include "iterator.hpp"     // std::iterator, std::random_access_iterator_tag

namespace ft
{
    /**
     * @brief 
     * @see https://cplusplus.com/reference/iterator/RandomAccessIterator/
     * @todo For mutable iterators (non-constant iterators): Can be dereferenced as an lvalue (if in a dereferenceable state).
     */
    template < class T >
    class array_iterator : public std::iterator<std::random_access_iterator_tag, T>
    {
        // typedef typename
        public:
            typedef ptrdiff_t                           	difference_type;
            typedef T                                   	value_type;
            typedef value_type *                           	pointer;
            typedef value_type &                           	reference;
            typedef const value_type *                      const_pointer;
            typedef const value_type &                      const_reference;
            typedef std::random_access_iterator_tag     	iterator_category;
            typedef array_iterator<value_type>     	        iterator;
            typedef array_iterator<const value_type>     	const_iterator;
            // Member types
            array_iterator(void) : _p(NULL) {}
            array_iterator(pointer x) : _p(x) {}
            // array_iterator(const_pointer x) : _p(x) {}
            // array_iterator(const_iterator & cpy) : _p(cpy._p) {}
            array_iterator(const array_iterator & cpy) : _p(cpy._p) {}
            array_iterator & operator = (const array_iterator & rhs) {
                if (this != &rhs) {
                    _p = rhs._p;
                }
                return *this;
            }
            operator array_iterator<const value_type>() const {
                return (array_iterator<const value_type>(this->_p));
            }
            // maybe return void *a = t
            // array_iterator & operator = (reference val) { *this->_p = val; return *this; }
            ~array_iterator(void) {}
  
            // bool operator == (const array_iterator & rhs) const { return this->_p == rhs._p; }
            // bool operator != (const array_iterator & rhs) const { return this->_p != rhs._p; }
            // bool operator >= (const array_iterator & rhs) const { return this->_p >= rhs._p; }
            // bool operator <= (const array_iterator & rhs) const { return this->_p <= rhs._p; }
            // bool operator < (const array_iterator & rhs) const { return this->_p < rhs._p; }
            // bool operator > (const array_iterator & rhs) const { return this->_p > rhs._p; }
       
            array_iterator & operator ++ (void) { ++(this->_p); return *this; }
            array_iterator operator ++ (int) { array_iterator tmp(*this); operator++(); return tmp; }
            array_iterator & operator -- (void) { --(this->_p); return *this; }
            array_iterator operator -- (int) { array_iterator tmp(*this); operator--(); return tmp; }
            array_iterator & operator += (difference_type dt) { this->_p += dt; return *this; }
            array_iterator & operator -= (difference_type dt) { this->_p -= dt; return *this; }
            // contains: *a++ *a-- *a = T
            reference operator * () { return *(this->_p); }
            pointer operator -> () { return this->_p; }
		    reference operator[](difference_type at) const { return (_p[at]); }
			array_iterator operator + (difference_type n) const { IDBG("this + n"); return this->_p + n; }
			array_iterator operator - (difference_type n) const { return this->_p - n; }
			difference_type operator - (array_iterator rhs) const { return this->_p - rhs._p; }

            pointer base(void) const { return _p; }

        private:
            pointer     _p;
    };

    template<typename T>
    ft::array_iterator<T> operator + (
        typename ft::array_iterator<T>::difference_type lhs,
        typename ft::array_iterator<T> & rhs
    ) {
        IDBG("T + n");
        return (&(*rhs) + lhs);
    }

    template<typename T>
    ft::array_iterator<T> operator - (
        typename ft::array_iterator<T>::difference_type lhs,
        typename ft::array_iterator<T> & rhs
    ) {
        return (&(*rhs) - lhs);
    }

    template <typename T>
    bool operator == (
        const ft::array_iterator<T> & lhs,
        const ft::array_iterator<T> & rhs
    ) {
        IDBG("T == T");
        return (lhs.base() == rhs.base());
    }

    template<typename T, typename U>
    bool operator == (
        const ft::array_iterator<T> & lhs,
        const ft::array_iterator<U> & rhs
    ) {
        IDBG("T == U");
        return (lhs.base() == rhs.base());
    }
	// template <typename T, typename U>
	// bool operator == (const ft::array_iterator<T> & lhs, const ft::array_iterator<U> & rhs) {
	// 	return lhs.base() == rhs.base();
	// }

	template <typename T, typename U>
	bool operator != (
        const ft::array_iterator<T> & lhs,
        const ft::array_iterator<U> & rhs
    ) {
		return !(lhs == rhs);
	}
	template <typename T, typename U>
	bool operator < (const ft::array_iterator<T> & lhs, const ft::array_iterator<U> & rhs) {
		return !(lhs >= rhs);
	}
	template <typename T, typename U>
	bool operator > (const ft::array_iterator<T> & lhs, const ft::array_iterator<U> & rhs) {
		return !(lhs <= rhs);
	}
	template <typename T, typename U>
	bool operator <= (const ft::array_iterator<T> & lhs, const ft::array_iterator<U> & rhs) {
		return lhs.base() <= rhs.base();
	}
	template <typename T, typename U>
	bool operator >= (const ft::array_iterator<T> & lhs, const ft::array_iterator<U> & rhs) {
		return lhs.base() >= rhs.base();
	}

}

#endif