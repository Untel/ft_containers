/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:48:57 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/19 20:56:20 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>     // std::cout
#include "iterator.hpp"     // std::iterator, std::random_access_iterator_tag
namespace ft
{
    template < class T >
    class array_iterator : public std::iterator<std::random_access_iterator_tag, T>
    {
        public:
            // Member types

            array_iterator(T * x) : p(x) {}
            array_iterator(const array_iterator & mit) : p(mit.p) {}
            bool operator == (const array_iterator & rhs) const { return p == rhs.p; }
            bool operator != (const array_iterator & rhs) const { return p != rhs.p; }
            bool operator >= (const array_iterator & rhs) const { return p >= rhs.p; }
            bool operator <= (const array_iterator & rhs) const { return p <= rhs.p; }
            bool operator < (const array_iterator & rhs) const { return p < rhs.p; }
            bool operator > (const array_iterator & rhs) const { return p > rhs.p; }
            
            array_iterator & operator ++ (void) { ++p;return *this; }
            array_iterator operator ++ (int) { array_iterator tmp(*this); operator++(); return tmp; }
            array_iterator & operator += (difference_type dt) { p += dt; return p; }
            array_iterator & operator -= (difference_type dt) { p -= dt; return p; }
            T & operator * () { return *p; }
        private:
            T * p;
    };
}