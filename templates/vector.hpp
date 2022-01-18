/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:01:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/18 15:54:36 by adda-sil         ###   ########.fr       */
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
            typedef T           value_type;
            typedef Alloc       allocator_type;
            typedef size_t      size_type;

            explicit vector (const allocator_type& alloc = allocator_type()) {
                VDBG("Default Constructor");
                (void) alloc;
            };
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
            vector(const vector & x) {
                VDBG("Copy Constructor");
                *this = x;
            };
            //template <class InputIterator>
            //vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
            ~vector(void) { VDBG("Destructor"); };

        private:

        protected:
    };
}

#endif // !VECTOR_HPP