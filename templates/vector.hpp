/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:01:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/18 16:05:48 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "utils.hpp"

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector {
        public:
            explicit vector (const allocator_type& alloc = allocator_type()) {
                VDBG("Default Constructor");
                (void) alloc;
            };
            explicit vector (
                size_type n,
                const value_type & val = value_type(),
                const allocator_type & alloc = allocator_type()
            );
            vector(const vector & x) {
                VDBG("Copy Constructor");
                *this = x;
            };
            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
            ~vector(void) { VDBG("Destructor"); };

        private:
            typedef T                   value_type;
            typedef value_type &        reference;
            typedef value_type *        pointer;
            typedef Alloc               allocator_type;
            typedef size_t              size_type;

        protected:
            T * c;
    };
}

#endif // !VECTOR_HPP