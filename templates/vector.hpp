/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:01:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/18 16:46:11 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "utils.hpp"

namespace ft
{
    /**
     * @brief Vector class
     * @see https://en.cppreference.com/w/cpp/container/vector
     * @see https://www.cplusplus.com/reference/vector/vector/
     * @tparam T 
     * @tparam Allocator 
     */
    template < class T, class Allocator = std::allocator<T> >
    class vector {
        public:
            /**
             * Member types
             * @see 
             */
            typedef T                                           value_type;
            typedef Allocator                                   allocator_type;
            typedef std::size_t                                 size_type;
            typedef std::ptrdiff_t                              difference_type;
            typedef typename Allocator::reference               reference;
            typedef typename Allocator::pointer                 pointer;
            typedef typename Allocator::const_reference         const_reference;
            typedef typename Allocator::const_pointer           const_pointer;

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



        protected:
            T * c;
    };
}

#endif // !VECTOR_HPP