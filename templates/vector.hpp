/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:01:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/18 22:09:42 by adda-sil         ###   ########.fr       */
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
                _size(0), _capacity(0), _allocator(alloc)
            {
                VDBG("Default Constructor");
                (void) alloc;
            };
            explicit vector (
                size_type n,
                const value_type & val = value_type(),
                const allocator_type & alloc = allocator_type()
            ) : _size(n), _capacity(n), _allocator(alloc) {
                VDBG("Parametric Constructor: " << val << " - N > " << n);
                VDBG("Size: " << _size);
                VDBG("Capacity: " << _capacity);
                this->_c = this->_allocator.allocate(n);
                for (size_type i = 0; i < n; i++)
                    this->_allocator.construct(this->_c + i, val);
            }
            vector(const vector & x) {
                VDBG("Copy Constructor");
                *this = x;
            };
            // template <class InputIterator>
            // vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
            ~vector(void) {
                VDBG("Destructor");
                for (size_type i = 0; i < this->_size; i++)
                    this->_allocator.destroy(this->_c + i);
                this->_allocator.deallocate(this->_c, this->_capacity);
            };

            // Data access
            reference at(size_type position) {
                VDBG("At position " << position);
                if (!(position < this->size()))
                    throw std::out_of_range("out of range");
                return this->_c[position];
            }
            const_reference at(size_type position) const {
                VDBG("const At position " << position);
                if (!(position < this->size()))
                    throw std::out_of_range("out of range");
                return this->_c[position];
            }

            void push_back (const value_type& val) {
                if (this->_size == this->_capacity) {
                    VDBG("Max size reached");
                    this->reserve(this->_capacity * 2 || 1);
                }
                this->at(this->_size++) = val;
            }

            reference operator[] (size_type position) {
                return this->at(position);
            }
            const_reference operator[] (size_type position) const {
                return this->at(position);
            }

            reference front() {
                return *this->_c;
            };
            const_reference front() const {
                return *this->_c;
            }

            reference back() {
                return this->_c[this->_size];
            }
            const_reference back() const {
                return this->_c[this->_size];
            }

            allocator_type get_allocator() const {
                return this->_allocator;
            }

            // Size
            size_type size() const {
                return this->_size;
            }
            size_type max_size() const {
                return this->_allocator.max_size();
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
            void reserve(size_type new_cap) {
                if (new_cap > this->max_size()) {
                    throw std::length_error("Length error");
                } else if (new_cap > this->_capacity) {
                    VDBG("Reallocating " << new_cap);
                    T *tmp = this->_allocator.allocate(new_cap);
                    // Askip il faudra reconstruct + destroy pcq Maia l'a dit cf. Constructor
                    for (size_type i = 0; i < this->_size; i++)
                        tmp[i] = this->_c[i];
                    if (this->_capacity)
                        this->_allocator.deallocate(this->_c, this->_capacity);
                    this->_c = tmp;
                    this->_capacity = new_cap;
                }
            }

        private:
            size_type                   _size;
            size_type                   _capacity;
            allocator_type              _allocator;
            T *                         _c;

            void    _upCapacity(size_type count) {
                size_type target = this->_size + count;
                if (target > this->_capacity) {
                    if (target > this->max_size()) {
                        throw std::exception();
                    }
                }
            }
    };
}

#endif // !VECTOR_HPP