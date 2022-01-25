/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:01:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/25 17:15:46 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP 1

# include <iostream>
# include <stdexcept>
# include "utils.hpp"
# include "array_iterator.hpp"
# include "iterator.hpp"
# include "iVector.hpp"

#define __VECTOR_INSERT(__RESOLVER, __RESOLVER2) \
    size_type required_cap = _size + n_to_insert; \
    size_type at = std::distance(begin(), position); \
    iterator it_end = end(); \
    bool is_collapsing = (position + n_to_insert) > it_end; \
    size_type collapse_at = is_collapsing ? (it_end - position) : 0; \
    size_type remaining_to_insert = is_collapsing ? n_to_insert - collapse_at : 0; \
    VDBG("INSERTING at: " << at << " length: " << n_to_insert << " actual_size: " << _size); \
    if (required_cap > _capacity) { \
        size_type s = _size; \
        size_type next_capacity = (required_cap > (_capacity * 2) \
            ? required_cap \
            : _capacity * 2 \
        ); \
        VDBG("NOT ENOUGH CAP cap" << _capacity << " required" << required_cap  << " next" << next_capacity); \
        pointer tmp = _allocator.allocate(next_capacity + 1); \
        VDBG("Copying length " << at); \
        VDBG("Next capacity " << next_capacity); \
        for (size_type i = 0; i < at; i++) {\
            VDBG("Copying " << _c[i]); \
            _allocator.construct(tmp + i, _c[i]); \
        } \
        VDBG("Constructing length" << n_to_insert); \
        for (size_type i = 0; i < n_to_insert; i++) { \
            VDBG("Constructing " << __RESOLVER); \
            _allocator.construct(tmp + at + i, __RESOLVER); \
        } \
        VDBG("Collapsing length" << remaining_to_insert); \
        for (size_type i = 0; i < remaining_to_insert; i++) { \
            VDBG("Collapsing " << *(_c + s - remaining_to_insert + i)); \
            _allocator.construct(tmp + at + n_to_insert + i, *(_c + s - remaining_to_insert + i)); \
        } \
        _clean(); \
        _c = tmp; \
        _size = required_cap; \
        _capacity = next_capacity; \
        return ; \
    } \
    size_type construct_from_end = n_to_insert; \
    VDBG("ENOUGH CAP: " << _capacity); \
    VDBG("Construct from end: " << construct_from_end); \
    for (size_type i = 0; i < n_to_insert; i++) { \
        _allocator.construct(_c + _size + i, __RESOLVER2); \
    } \
    if (!is_collapsing && it_end != position) { \
        size_type to_move = it_end - position - construct_from_end; \
        VDBG("Collapse is(" << is_collapsing << ") N=" << to_move); \
        for (size_type i = 0; i < to_move; i++) { \
            *(_c + _size - (i + 1)) = *(_c + _size - (i + n_to_insert + 1)); \
        } \
    } \
    if (it_end != position) { \
        VDBG("Remaining is(" << remaining_to_insert); \
        for (size_type i = 0; i < n_to_insert - remaining_to_insert; i++) \
            *(_c + at + i) = __RESOLVER; \
    } \
    _size += n_to_insert;

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
                _c = _allocator.allocate(1);
            };
            explicit vector (
                size_type n,
                const value_type & val = value_type(),
                const allocator_type & alloc = allocator_type()
            ) : _size(0), _capacity(0), _allocator(alloc) {
                VDBG("Parametric Constructor: - N > " << n);
                VDBG("Size: " << _size);
                reserve(n);
                for (size_type i = 0; i < n; i++)
                    _allocator.construct(_c + i, val);
                _size = n;
                VDBG("End construct");
            }
            vector(const vector & x) {
                VDBG("Copy Constructor");
                clear();
                *this = x;
            };
            // template <class InputIterator>
            // vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
            ~vector(void) {
                VDBG("Destructor");
                _clean();
            };
            // Data access
            reference at(size_type position) {
                VDBG("At position " << position);
                if (!(position < size()))
                    throw std::out_of_range("out of range");
                return _c[position];
            }
            const_reference at(size_type position) const {
                VDBG("const At position " << position);
                if (!(position < size()))
                    throw std::out_of_range("out of range");
                return _c[position];
            }
            void push_back (const value_type & val) {
                // insert(end(), val);
            }
            void pop_back() {
                VDBG("Poping back");
                erase(end() - 1);
            }
            iterator insert (iterator position, const value_type & val) {
                difference_type at = position - begin();
                insert(position, 1, val);
                return (begin() + at + 1);
            }
            void insert (iterator position, size_type n_to_insert, const value_type & val) {
                __VECTOR_INSERT(val, val);
            }
            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last) {
                size_type n_to_insert = std::distance(first, last);
                __VECTOR_INSERT(*(first + i), *((is_collapsing && i < collapse_at) ? last - collapse_at + i : it_end - construct_from_end + i));
            }
            iterator erase (iterator position) {
                if (position < end())
                    erase(position, position + 1);
            }
            iterator erase (iterator first, iterator last) {
                iterator e          = end();
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
                    _allocator.destroy(&(*it));
                _size -= n;
                return first;
            }

            // will probably just call insert ??
            void resize (size_type n, value_type val = value_type()) {
                if (n < _size) {
                    VDBG("Resizing: deletion");
                    erase(begin() + n, end());
                } else if (n > _size) {
                    VDBG("Resizing: addition");
                    // do insert
                }
            }

            // getters
            allocator_type      get_allocator() const { return _allocator; }
            reference           operator[] (size_type position) { return _c[position]; }
            const_reference     operator[] (size_type position) const { return _c[position]; }
            pointer             data() { return _c; }
            const pointer       data() const { return _c; }
            reference           front() { return *_c; }
            const_reference     front() const { return *_c; }
            reference           back() { return _c[_size]; }
            const_reference     back() const { return _c[_size]; }
            size_type           size() const { return _size; }
            bool                empty() const { return _size == 0; }
            size_type           max_size() const { return _allocator.max_size(); }
            size_type           capacity() const { return _capacity; }
            
            /**
             * @brief 
             * Increase the capacity of the vector to a value that's greater or equal to new_cap. If new_cap is greater than the current capacity(), new storage is allocated, otherwise the function does nothing.
             * reserve() does not change the size of the vector.
             * If new_cap is greater than capacity(), all iterators, including the past-the-end iterator, and all references to the elements are invalidated. Otherwise, no iterators or references are invalidated.
             * @param new_cap 
             */
            void reserve(size_type new_cap) {
                if (new_cap > max_size()) {
                    throw std::length_error("Length error");
                } else if (new_cap > _capacity) {
                    size_type s = _size;
                    VDBG("Reallocating " << new_cap);
                    pointer tmp = _allocator.allocate(new_cap + 1);
                    for (size_type i = 0; i < _size; i++)
                        _allocator.construct(tmp + i, _c[i]);
                    _clean();
                    _c = tmp;
                    _size = s;
                    _capacity = new_cap;
                }
            }

            void clear(void) {
                VDBG("Clearing actual container");
                erase(begin(), end());
            }

            void swap (vector & x) {
                size_type   tmp_s   = _size;
                size_type   tmp_c   = _capacity;
                pointer     tmp_p   = _c;

                _size               = x._size;
                _capacity           = x._capacity;
                _c                  = x._c;

                x._size             = tmp_s;
                x._capacity         = tmp_c;
                x._c                = tmp_p;
            }

            iterator begin() {
                VDBG("Begin iterator");
                return iterator(_c);
            }
            const_iterator begin() const {
                return iterator(_c);
            }
            iterator end() {
                VDBG("End iterator");
                return iterator(_c + _size);
            }
            const_iterator end() const {
                return iterator(_c + _size);
            }

        private:
            size_type                   _size;
            size_type                   _capacity;
            allocator_type              _allocator;
            pointer                     _c;

            void _clean(void) {
                clear();
                _allocator.deallocate(_c, _capacity + 1);
                _capacity = 0;
            }
    };

    template <class T, class Alloc>
    void swap (vector<T, Alloc> & x, vector<T, Alloc> & y) {
        x.swap(y);
    }
}

#endif // !VECTOR_HPP