/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:01:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/21 20:45:37 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <stdexcept>
# include "utils.hpp"
# include "array_iterator.hpp"
# include "iterator.hpp"
# include "iVector.hpp"

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
            typedef T                                                           value_type;
            typedef Allocator                                                   allocator_type;
            typedef typename Allocator::reference                               reference;
            typedef typename Allocator::pointer                                 pointer;
            typedef typename Allocator::const_reference                         const_reference;
            typedef typename Allocator::const_pointer                           const_pointer;
            typedef typename ft::array_iterator<const value_type>               const_iterator;
            typedef typename ft::array_iterator<value_type>                     iterator;
            typedef typename ft::reverse_iterator< const_iterator >             const_reverse_iterator;
            typedef typename ft::reverse_iterator< iterator >                   reverse_iterator;
            typedef typename ft::iterator_traits<iterator>::difference_type     difference_type;
            typedef std::size_t                                                 size_type;

            // Member functions
            explicit vector (const allocator_type& alloc = allocator_type()) :
                _size(0), _capacity(0), _allocator(alloc)
            {
                VDBG("Default Constructor");
                this->_c = this->_allocator.allocate(1);
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
                    this->_allocator.construct(this->_c + i, val);
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
            void push_back (const value_type & val) {
                if (this->_size == this->_capacity) {
                    VDBG("Max size reached");
                    this->reserve(this->_capacity * 2);
                }
                // this->c + this->_size++ = value_type(val);
                this->_allocator.construct(this->_c + this->_size++, val);
            }

            void pop_back() {
                VDBG("Poping back");
                this->erase(this->end() - 1);
            }

            // iterator insert (iterator position, const value_type& val) {
            //     size_type idx = (position - this->begin()); //maybe fail if not ref
                
            //     if (this->_size == this->_capacity) {
            //         this->reserve(this->_capacity * 2);
            //     }
            //     for (size_t i = idx; i < idx + _size; i++)
            //         this->_c[i + _size] = this->_c[i];


            //     return iterator(this->_c + idx);
            // }
            void insert (iterator position, size_type n, const value_type& val);

            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last) {
                difference_type dist = std::distance(first, last);
                difference_type at = std::distance(this->begin(), position);
                // difference_type fe = this->end() - at;
                // (void)fe;
                difference_type still_constructed = this->end() - position;
                difference_type to_construct = dist - still_constructed;
                if (this->_size + dist > this->_capacity) {
                    VDBG("Should upgrade container size");
                } else {
                    VDBG("Have enough container size");
                    for (difference_type i = 0; i < to_construct; i++) {
                        difference_type fromIdx = at + still_constructed + i;
                        difference_type targetIdx = still_constructed + i;
                        VDBG("To construct: " << (*(first + targetIdx)).str << " at idx " << fromIdx);
                        this->_allocator.construct(this->_c + fromIdx, *(first + targetIdx));
                    }
                    for (difference_type i = 0; i < still_constructed; i++) {
                        difference_type idx = at + i + dist;
                        VDBG("Still constructed copy: " << (*(position + i)).str << " at idx " << idx);
                        this->_allocator.construct(this->_c + idx, *(position + i));
                    }
                    for (difference_type i = 0; i < still_constructed; i++) {
                        VDBG("Still constructed assignation: " << (*(position + i)).str << " at idx " << at + i);
                        *(this->_c + at + i) = *(first + i);
                    }
                }

                this->_size += dist;
            }

            // void _buildHole(iterator position, difference_type width) {
            //     iterator b = this->begin();
            //     iterator e = this->end();

            //     for (size_type s = this->_size; s < this->_size + width; s++) {
                    
            //     }
            // }

            iterator erase (iterator position) {
                if (position < this->end())
                    this->erase(position, position + 1);
            }
            iterator erase (iterator first, iterator last) {
                iterator e          = this->end();
                // Nombre d'el a remove
                size_type n         = last - first;
                VDBG("Erasing " << n << " elements");

                // Iterer entre iterator last et iterator end(), car on déplace ce qu'il y a après last a l'endroit mémoire qu'on erase
                // Cf. problème de memset dans libft (gauche a droite et pas droite a gauche)
                iterator it = first;
                for (; it != e - n; it++) {
                    // VDBG("Erasing " << (it - n)->get() << " with " << it->get() );
                    *(it - n) = *(it); // assigner de n elements vers la gauche
                }
                it = e - n;
                // détruire les n éléments en partant du iterator end()
                // on ne détruit pas les éléments qu'on a érase, mais ceux a la fin du ctn, qui on été réassigné a la boucle précédente
                for (; it != e; it++)
                    this->_allocator.destroy(&(*it));
                this->_size -= n;
                return first;
            }

            // will probably just call insert ??
            void resize (size_type n, value_type val = value_type()) {
                if (n < this->_size) {
                    VDBG("Resizing: deletion");
                    this->erase(this->begin() + n, this->end());
                } else if (n > this->_size) {
                    VDBG("Resizing: addition");
                    // do insert
                }
            }

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
            bool                empty() const { return this->_size == 0; }
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
                VDBG("Clearing actual container");
                this->erase(this->begin(), this->end());
            }

            void swap (vector & x) {
                size_type   tmp_s   = this->_size;
                size_type   tmp_c   = this->_capacity;
                pointer     tmp_p   = this->_c;

                this->_size         = x._size;
                this->_capacity     = x._capacity;
                this->_c            = x._c;

                x._size             = tmp_s;
                x._capacity         = tmp_c;
                x._c                = tmp_p;
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
            pointer                     _c;

            void _clean(void) {
                this->clear();
                this->_allocator.deallocate(this->_c, this->_capacity + 1);
                this->_capacity = 0;
            }
    };

    template <class T, class Alloc>
    void swap (vector<T, Alloc> & x, vector<T, Alloc> & y) {
        x.swap(y);
    }
}
#endif // !VECTOR_HPP