/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:01:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/18 17:20:33 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <stdexcept>
# include "utils.hpp"

namespace ft
{
    /**
     * @brief Vector class
     * @see https://en.cppreference.com/w/cpp/container/vector
     * @see https://www.cplusplus.com/reference/vector/vector/.
     * @see https://docs.microsoft.com/fr-fr/cpp/standard-library/vector-class
     * @tparam T 
     * @tparam Allocator 
     */
    template < class T, class Allocator = std::allocator<T> >
    class vector {
        public:
            // Member types
            typedef T                                           value_type;
            typedef Allocator                                   allocator_type;
            typedef std::size_t                                 size_type;
            typedef std::ptrdiff_t                              difference_type;
            typedef typename Allocator::reference               reference;
            typedef typename Allocator::pointer                 pointer;
            typedef typename Allocator::const_reference         const_reference;
            typedef typename Allocator::const_pointer           const_pointer;

            // Member functions
            explicit vector (const allocator_type& alloc = allocator_type()) :
                _size(0), _capacity(0)
            {
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

            // Data access
            reference at(size_type position) {
                if (!(position < this->size()))
                    throw std::out_of_range("out of range");
                return this->c[position];
            }
            const_reference at(size_type position) const {
                if (!(position < this->size()))
                    throw std::out_of_range("out of range");
                return this->c[position];
            }

            reference front() {
                return this->c[0];
            };
            const_reference front() const {
                return this->c[0];
            }

            // Size
            size_type size() const {
                return this->_size;
            }
            size_type max_size() const {
                return this->_capacity;
            }
            size_type capacity() const {
                return this->_capacity;
            }
            /**
             * @brief 
             * Increase the capacity of the vector to a value that's greater or equal to new_cap. If new_cap is greater than the current capacity(), new storage is allocated, otherwise the function does nothing.
             * reserve() does not change the size of the vector.
             * If new_cap is greater than capacity(), all iterators, including the past-the-end iterator, and all references to the elements are invalidated. Otherwise, no iterators or references are invalidated.
             * @param new_cap 
             */
            void reserve( size_type new_cap ) {
                (void)new_cap;
            }

        protected:
            T c[10];
        
        private:
            int         _size;
            int         _capacity;

    };
}

#endif // !VECTOR_HPP