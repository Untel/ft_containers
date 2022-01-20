/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:01:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/20 20:29:59 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <stdexcept>
# include "utils.hpp"
# include "array_iterator.hpp"
# include "iterator.hpp"

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
            typedef T                                               value_type;
            typedef Allocator                                       allocator_type;
            typedef std::size_t                                     size_type;
            typedef std::ptrdiff_t                                  difference_type;
            typedef typename Allocator::reference                   reference;
            typedef typename Allocator::pointer                     pointer;
            typedef typename Allocator::const_reference             const_reference;
            typedef typename Allocator::const_pointer               const_pointer;
            typedef typename ft::array_iterator<const value_type>   const_iterator;
            typedef typename ft::array_iterator<value_type>         iterator;

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
            ) : _size(0), _capacity(0), _allocator(alloc) {
                VDBG("Parametric Constructor: - N > " << n);
                VDBG("Size: " << _size);
                this->reserve(n);
                for (size_type i = 0; i < n; i++)
                    this->_allocator.construct(&this->_c[i], val);
                this->_size = n;
                VDBG("End construct");
            }
            vector(const vector & x) {
                VDBG("Copy Constructor");
                this->clear();
                *this = x;
            };
            // template <class InputIterator>
            // vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
            ~vector(void) {
                VDBG("Destructor");
                this->_clean();
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
                    this->reserve(this->_capacity * 2);
                }
                this->at(this->_size++) = val;
            }

            iterator insert (iterator position, const value_type& val) {
                difference_type idx = (position - this->begin()); //maybe fail if not ref
                
                return iterator(this->_c[idx]);
            }
            void insert (iterator position, size_type n, const value_type& val);
            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last);

            // getters
            allocator_type      get_allocator() const { return this->_allocator; }
            reference           operator[] (size_type position) { return this->at(position); }
            const_reference     operator[] (size_type position) const { return this->at(position); }
            T *                 data() { return this->_c; }
            const T *           data() const { return this->_c; }
            reference           front() { return *this->_c; }
            const_reference     front() const { return *this->_c; }
            reference           back() { return this->_c[this->_size]; }
            const_reference     back() const { return this->_c[this->_size]; }
            size_type           size() const { return this->_size; }
            size_type           max_size() const { return this->_allocator.max_size(); }
            size_type           capacity() const { return this->_capacity; }
            
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
                    size_type s = this->_size;
                    VDBG("Reallocating " << new_cap);
                    pointer tmp = this->_allocator.allocate(new_cap + 1);
                    for (size_type i = 0; i < this->_size; i++)
                        this->_allocator.construct(tmp + i, this->_c[i]);
                    this->_clean();
                    this->_c = tmp;
                    this->_size = s;
                    this->_capacity = new_cap;
                }
            }

            void clear(void) {
                if (this->_size) {
                    VDBG("Clearing actual container");
                    for (size_type i = 0; i < this->_size; i++) {
                        this->_allocator.destroy(this->_c + i);
                    }
                }
                this->_size = 0;
            }

            iterator begin() {
                VDBG("Begin iterator" << this->_c[0].get() );
                return iterator(this->_c);
            }
            const_iterator begin() const {
                return iterator(this->_c);
            }
            iterator end() {
                VDBG("End iterator");
                return iterator(this->_c + this->_size);
            }
            const_iterator end() const {
                return iterator(this->_c + this->_size);
            }

        private:
            size_type                   _size;
            size_type                   _capacity;
            allocator_type              _allocator;
            T *                         _c;

            void _clean(void) {
                this->clear();
                if (this->_capacity)
                    this->_allocator.deallocate(this->_c, this->_capacity + 1);
                this->_capacity = 0;
            }
    };
}

#endif // !VECTOR_HPP