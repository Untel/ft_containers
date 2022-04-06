/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:48:57 by adda-sil          #+#    #+#             */
/*   Updated: 2022/04/06 22:16:19 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAYITERATOR_HPP
# define ARRAYITERATOR_HPP 1
# include <iostream>
# include "iterator.hpp"

namespace ft
{
    template < class T >
    class array_iterator : public std::iterator<std::random_access_iterator_tag, T>
    {
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

            array_iterator(void) : _p(NULL) {}
            array_iterator(pointer x) : _p(x) {}
            array_iterator(const array_iterator & cpy) : _p(cpy._p) {}
            array_iterator & operator = (const array_iterator & rhs) {
                _p = rhs._p;
                return *this;
            }
            operator array_iterator<const value_type>() const {
                return (array_iterator<const value_type>(this->_p));
            }

            ~array_iterator(void) {}
       
            array_iterator & operator ++ (void) { ++(this->_p); return *this; }
            array_iterator operator ++ (int) { array_iterator tmp(*this); operator++(); return tmp; }
            array_iterator & operator -- (void) { --(this->_p); return *this; }
            array_iterator operator -- (int) { array_iterator tmp(*this); operator--(); return tmp; }
            array_iterator & operator += (difference_type dt) { this->_p += dt; return *this; }
            array_iterator & operator -= (difference_type dt) { this->_p -= dt; return *this; }
            reference operator * () { return *(this->_p); }
            pointer operator -> () { return this->_p; }
		    reference operator [] (difference_type at) const {
                return (_p[at]); 
            }
			array_iterator operator + (difference_type n) const { IDBG("this + n"); return this->_p + n; }
			array_iterator operator - (difference_type n) const { return this->_p - n; }
			difference_type operator - (array_iterator rhs) const { return this->_p - rhs._p; }

        private:
            pointer     _p;
    };

    template<typename T>
    ft::array_iterator<T> operator + (
        typename ft::array_iterator<T>::difference_type lhs,
        typename ft::array_iterator<T> & rhs
    ) {
        return (&(*rhs) + lhs);
    }

    template<typename T>
    ft::array_iterator<T> operator - (
        typename ft::array_iterator<T>::difference_type lhs,
        typename ft::array_iterator<T> & rhs
    ) {
        return (&(*rhs) - lhs);
    }

    template<typename T, typename U>
    typename ft::array_iterator<T>::difference_type operator - (
        const ft::array_iterator<T> & lhs,
        const ft::array_iterator<U> & rhs
    ) {
        return (&(lhs[0]) - &(rhs[0]));
    }

    template <typename T>
    bool operator == (
        const ft::array_iterator<T> & lhs,
        const ft::array_iterator<T> & rhs
    ) {
        return (&(lhs[0]) == &(rhs[0]));
    }

    template<typename T, typename U>
    bool operator == (
        const ft::array_iterator<T> & lhs,
        const ft::array_iterator<U> & rhs
    ) {
        return (&(lhs[0]) == &(rhs[0]));
    }

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
		return &(lhs[0]) <= &(rhs[0]);
	}
	template <typename T, typename U>
	bool operator >= (const ft::array_iterator<T> & lhs, const ft::array_iterator<U> & rhs) {
		return &(lhs[0]) >= &(rhs[0]);
	}

}

#endif