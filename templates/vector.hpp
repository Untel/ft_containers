/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:01:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/07 17:39:48 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP 1

# include <iostream>
# include <stdexcept>
# include "utils.hpp"
# include "array_iterator.hpp"
# include "iterator.hpp"
# include "tester.hpp"

#define __VECTOR_INSERT(__RESOLVER, __RESOLVER2) \
    size_type required_cap = _size + n_to_insert; \
    size_type at = std::distance(begin(), position); \
    iterator it_end = end(); \
    bool is_collapsing = (it_end != position && ((position + n_to_insert) > it_end)); \
    size_type collapse_at = is_collapsing ? (it_end - position) : at; \
    size_type remaining_to_insert = is_collapsing ? n_to_insert - (collapse_at - at) : n_to_insert; \
    (void)collapse_at; \
    VDBG("INSERTING at: " << at << " length: " << n_to_insert << " actual_size: " << _size); \
    if (required_cap > _capacity) { \
        VDBG("NOT ENOUGH CAP "); \
        VDBG(CYAN << "remaining_to_insert " << remaining_to_insert << std::endl); \
        VDBG(RED << "collpase " << is_collapsing << std::endl); \
        VDBG(MAGENTA << "collapse_at " << collapse_at << std::endl); \
        VDBG(YELLOW << "at " << at << std::endl << RESET); \
        size_type s = _size; \
        size_type next_capacity = (required_cap > (_capacity * 2) \
            ? required_cap \
            : _capacity * 2 \
        ); \
        VDBG("Alloc = " << next_capacity); \
        pointer tmp = _allocator.allocate(next_capacity + 1); \
        VDBG("Copying length" << at); \
        for (size_type i = 0; i < at; i++) {\
            VDBG("Copying " << _c[i] << " at " << i); \
            _allocator.construct(tmp + i, _c[i]); \
        } \
        VDBG("Constructing length" << n_to_insert); \
        for (size_type i = 0; i < n_to_insert; i++) { \
            VDBG("Constructing " << __RESOLVER << " at " << at + i); \
            _allocator.construct(tmp + at + i, __RESOLVER); \
        } \
        VDBG("Collapsing length" << remaining_to_insert); \
            for (size_type i = 0; i < remaining_to_insert; i++) { \
                VDBG("Collapsing " << *(_c + s - remaining_to_insert + i) << " at " <<  at + n_to_insert + i); \
                _allocator.construct(tmp + at + n_to_insert + i, *(_c + s - remaining_to_insert + i)); \
            } \
        _clean(); \
        _c = tmp; \
        _size = required_cap; \
        _capacity = next_capacity; \
        return ; \
    } \
    size_type construct_from_end = n_to_insert - collapse_at; \
    VDBG("ENOUGH CAP: " << _capacity); \
    VDBG("Construct from end: " << construct_from_end); \
    for (size_type i = 0; i < construct_from_end; i++) { \
        _allocator.construct(_c + _size + i, __RESOLVER2); \
    } \
    VDBG(YELLOW << "Construct from actual list: " << RESET << n_to_insert - construct_from_end); \
    for (size_type i = 0; i < n_to_insert - construct_from_end; i++) { \
        _allocator.construct(_c + _size + i + construct_from_end, *(_c + _size - construct_from_end + i)); \
    } \
    if (is_collapsing && it_end > position) { \
        size_type to_move = it_end - position - construct_from_end; \
        VDBG(CYAN << "Moving if collapsing: " << RESET << to_move); \
        VDBG("Collapse is(" << is_collapsing << ") N=" << to_move); \
        for (size_type i = 0; i < to_move; i++) { \
            *(_c + _size - (i + 1)) = *(_c + _size - (i + n_to_insert + 1)); \
        } \
    } else if (!is_collapsing && it_end != position) { \
        size_type to_move = n_to_insert; \
        VDBG(MAGENTA << "Moving if not collapsing: " << RESET << to_move << " at " << at << " size: " << _size << " n " << n_to_insert); \
        for (size_type i = 0; i < to_move; i++) { \
            *(_c + at + n_to_insert + to_move - (i + 1)) = *(_c + to_move + at - (i + 1)); \
        } \
    } \
    VDBG(BLUE << "Remaining is " << RESET << remaining_to_insert); \
    if (position != it_end) \
        for (size_type i = 0; i < remaining_to_insert; i++) \
            *(_c + at + i) = __RESOLVER; \
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
            typedef T                                                               value_type;
            typedef Allocator                                                       allocator_type;
            typedef typename allocator_type::reference                              reference;
            typedef typename allocator_type::pointer                                pointer;
            typedef typename allocator_type::const_reference                        const_reference;
            typedef typename allocator_type::const_pointer                          const_pointer;
            typedef typename allocator_type::size_type                              size_type;
            typedef typename ft::array_iterator< value_type >::iterator             iterator;
            typedef typename ft::array_iterator<const value_type >::const_iterator  const_iterator;
            // typedef typename ft::array_iterator< value_type >                       iterator;
            // typedef typename ft::array_iterator< const value_type >                 const_iterator;
            typedef typename ft::reverse_iterator< iterator >                       reverse_iterator;
            typedef typename ft::reverse_iterator< const_iterator >                 const_reverse_iterator;
            typedef typename ft::iterator_traits<iterator>::difference_type         difference_type;

            // Member functions
            vector (const allocator_type& alloc = allocator_type()) :
                _size(0), _capacity(0), _allocator(alloc), _c(_allocator.allocate(1))
            {
                VDBG("Default Constructor");
            };
            vector (
                size_type n,
                const value_type & val = value_type(),
                const allocator_type & alloc = allocator_type()
            ) : _size(0), _capacity(0), _allocator(alloc), _c(_allocator.allocate(1)) {
                insert(begin(), n, val);
            }

            vector(const vector & cpy) {
                VDBG(RED << "COPY CONST OLD REF:" << cpy._c << BLUE << " NEW REF " << _c << RESET);
                *this = cpy;
            }
            vector & operator = ( const vector &cpy) {
                VDBG(RED << "ASSIGNING OLD REF:" << cpy._c << BLUE << " NEW REF " << _c << RESET);
                _size = cpy._size;
                _capacity = cpy._capacity;
                _allocator = cpy._allocator;
                _c = _allocator.allocate(_capacity + 1);
                for (size_type i = 0; i < _size; i++)
                    _allocator.construct(_c + i, cpy._c[i]);
                return *this;
            }

            template <class InputIterator>
            vector (
                InputIterator first,
                typename enable_if <!is_integral <InputIterator>::value, InputIterator >::type last,
                const allocator_type& alloc = allocator_type()
            ) : _size(0), _capacity(0), _allocator(alloc), _c(_allocator.allocate(1)) {
                insert(begin(), first, last);
            }
            ~vector(void) {
                VDBG("Destructor _c ref " << _c);
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
                insert(end(), 1, val);
            }
            void pop_back() {
                VDBG("Poping back");
                erase(end() - 1);
            }
            iterator insert (iterator position, const value_type & val) {
                difference_type at = position - begin();
                insert(position, 1, val);
                return (begin() + at);
            }

            void insert (iterator position, size_type n_to_insert, const value_type& val) {
                VDBG(GREEN << "Insert by val n(" << n_to_insert << ") val(" << val << ")" << RESET);
                size_type at = std::distance(begin(), position);
                _buildMemoryHole(n_to_insert, position);
                for (size_type i = 0; i < n_to_insert; i++)
                    _allocator.construct(_c + at + i, val);
                // __VECTOR_INSERT(val, val);
            }
            
            template <class InputIterator>
            void insert (
                iterator position,
                InputIterator first,
                typename enable_if <!is_integral <InputIterator>::value, InputIterator >::type last
            ) {
                VDBG(BLUE << "Insert by range" << RESET);
                size_type at = std::distance(begin(), position);
                size_type n_to_insert = std::distance(first, last);
                _buildMemoryHole(n_to_insert, position);
                for (size_type i = 0; i < n_to_insert; i++)
                    _allocator.construct(_c + at + i, *(first++));
                // __VECTOR_INSERT(*(first + i), *((is_collapsing && i < collapse_at) ? last - collapse_at + i : it_end - construct_from_end + i));
            }
            iterator erase (iterator position) {
                return erase(position, position + 1);
            }
            iterator erase (iterator first, iterator last) {
                iterator e          = end();
                size_type at        = std::distance(begin(), first);
                // Nombre d'el a remove
                size_type n         = std::distance(first, last);
                VDBG("Erasing " << n << " elements");

                // Iterer entre iterator last et iterator end(), car on déplace ce qu'il y a après last a l'endroit mémoire qu'on erase
                // Cf. problème de memset dans libft (gauche a droite et pas droite a gauche)
                iterator it = first + n;
                for (; it != e; it++) {
                    VDBG("Erasing " << *it << " with " << *(it - n) );
                    *(it - n) = *(it); // assigner de n elements vers la gauche
                }
                it = end();
                // détruire les n éléments en partant du iterator end()
                // on ne détruit pas les éléments qu'on a érase, mais ceux a la fin du ctn, qui on été réassigné a la boucle précédente
                for (; it != end(); it++) {
                    VDBG("Destroying " << *it);
                    _allocator.destroy(&(*it));
                }
                _size -= n;
                return iterator(_c + at);
            }

            // will probably just call insert ??
            void resize (size_type n, value_type val = value_type()) {
                if (n < _size) {
                    VDBG("Resizing: deletion");
                    erase(begin() + n, end());
                } else {
                    VDBG("Resizing: addition");
                    insert(end(), n - _size, val);
                }
            }

            template <class InputIterator>
            void assign (
                InputIterator first,
                typename enable_if <!is_integral <InputIterator>::value, InputIterator >::type last
            ) {
                clear();
                insert(begin(), first, last);
            }
            void assign (size_type n, const value_type& val) {
                clear();
                insert(begin(), n, val);
            }
            // getters
            allocator_type      get_allocator() const { return _allocator; }
            reference           operator[] (size_type position) { return _c[position]; }
            const_reference     operator[] (size_type position) const { return _c[position]; }
            pointer             data() { return _c; }
            const pointer       data() const { return _c; }
            reference           front() { return *_c; }
            const_reference     front() const { return *_c; }
            reference           back() { return _c[_size - 1]; }
            const_reference     back() const { return _c[_size - 1]; }
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
                return const_iterator(_c);
            }
            iterator end() {
                VDBG("End iterator");
                return iterator(_c + _size);
            }
            const_iterator end() const {
                VDBG("Const End iterator");
                return const_iterator(_c + _size);
            }

            reverse_iterator rbegin() {
                VDBG("Begin reverse_iterator");
                return reverse_iterator(end());
            }
            const_reverse_iterator rbegin() const {
                return const_reverse_iterator(end());
            }
            reverse_iterator rend() {
                VDBG("End reverse_iterator");
                return reverse_iterator(begin());
            }
            const_reverse_iterator rend() const {
                VDBG("Const End reverse_iterator");
                return const_reverse_iterator(begin());
            }

        private:
            size_type                   _size;
            size_type                   _capacity;
            allocator_type              _allocator;
            pointer                     _c;

            void _clean(void) {
                VDBG(MAGENTA << "CLEARING " << _c << RESET);
                clear();
                _allocator.deallocate(_c, _capacity + 1);
                _capacity = 0;
            }

            void _buildMemoryHole(size_type additional, iterator position) {
                size_type required_cap = _size + additional;
                pointer ref = _c;
                size_type to_move = end() - position;
                size_type at = position - begin();
                size_type old_capacity = _capacity;
                bool is_capacity_changing = _capacity < required_cap;
                at = at > 0 ? at : 0;
                if (is_capacity_changing) {
                    size_type next_capacity = (required_cap > (_capacity * 2)
                        ? required_cap
                        : _capacity * 2
                    );
                    ref = _allocator.allocate(next_capacity + 1);
                    _capacity = next_capacity;
                    for (size_type i = 0; i < at; i++) {
                        _allocator.construct(ref + i, _c[i]);
                        _allocator.destroy(_c + i);
                    }
                }
                for (int i = to_move; i >= 0; i--) {
                    _allocator.construct(ref + at + i + additional, _c[at + i]);
                }
                if (is_capacity_changing)
                    _allocator.deallocate(_c, old_capacity + 1);
                _c = ref;
                _size += additional;
            }
    };

    template <class T, class Alloc>
    bool operator == (const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs) {
        VDBG("lhs == rhs");
        if (lhs.size() != rhs.size())
            return false;
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    template <class T, class Alloc>
    bool operator != (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        VDBG("lhs != rhs");
        return (!(lhs == rhs));
    }
    template <class T, class Alloc>
    bool operator < (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template <class T, class Alloc>
    bool operator > (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return (rhs < lhs);
    }
    template <class T, class Alloc>
    bool operator <= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(rhs < lhs);
    }
    template <class T, class Alloc>
    bool operator >= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(lhs < rhs);
    }

    template <class T, class Alloc>
    void swap (vector<T, Alloc> & x, vector<T, Alloc> & y) {
        x.swap(y);
    }
}

#endif // !VECTOR_HPP