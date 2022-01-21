/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:48:57 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/21 00:18:45 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>     // std::cout
#include "iterator.hpp"     // std::iterator, std::random_access_iterator_tag
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
            typedef std::random_access_iterator_tag     	iterator_category;
            // Member types
            array_iterator(void) : _p(value_type()) {}
            array_iterator(pointer x) : _p(x) {}
            array_iterator(const array_iterator & cpy) : _p(cpy._p) {}
            array_iterator & operator = (const array_iterator & rhs) {
                if (this != &rhs) {
                    this->_p = rhs._p;
                }
                return *this;
            }
            // maybe return void *a = t
            // array_iterator & operator = (reference val) { *this->_p = val; return *this; }
            ~array_iterator(void) {}
            
            bool operator == (const array_iterator & rhs) const { return this->_p == rhs._p; }
            bool operator != (const array_iterator & rhs) const { return this->_p != rhs._p; }
            bool operator >= (const array_iterator & rhs) const { return this->_p >= rhs._p; }
            bool operator <= (const array_iterator & rhs) const { return this->_p <= rhs._p; }
            bool operator < (const array_iterator & rhs) const { return this->_p < rhs._p; }
            bool operator > (const array_iterator & rhs) const { return this->_p > rhs._p; }
            
            array_iterator & operator ++ (void) { ++(this->_p); return *this; }
            array_iterator operator ++ (int) { array_iterator tmp(*this); operator++(); return tmp; }
            array_iterator & operator -- (void) { --(this->_p); return *this; }
            array_iterator operator -- (int) { array_iterator tmp(*this); operator--(); return tmp; }
            array_iterator & operator += (difference_type dt) { this->_p += dt; return *this; }
            array_iterator & operator -= (difference_type dt) { this->_p -= dt; return *this; }
            // contains: *a++ *a-- *a = T
            reference operator * () { return *(this->_p); }
            pointer operator -> () { return this->_p; }
			array_iterator operator + (difference_type n) const { return this->_p + n; }
			array_iterator operator - (difference_type n) const { return this->_p - n; }
			difference_type operator - (array_iterator rhs) const { return this->_p - rhs._p; }

        private:
            pointer     _p;
    };
}