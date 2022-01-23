/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iVector.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:57:08 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/23 15:26:57 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#ifndef IVECTOR_HPP
# define IVECTOR_HPP 1
namespace ft {
    template <class T, class Allocator = std::allocator<T> >
    class iVector {
        public:
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
            // 23.2.4.1 construct/copy/destroy:
            // virtual explicit iVector(const Allocator& = Allocator()) = 0;
            // virtual explicit iVector(size_type n, const T& value = T(), const Allocator& = Allocator()) = 0;
            // template <class InputIterator>
            // virtual iVector(InputIterator first, InputIterator last, const Allocator& = Allocator()) = 0;
            // virtual iVector(const iVector<T,Allocator>& x) = 0;
            virtual ~iVector() = 0;
            virtual iVector<T,Allocator>& operator=(const iVector<T,Allocator>& x) = 0;
            // template <class InputIterator>
            // virtual void assign(InputIterator first, InputIterator last) = 0;
            virtual void assign(size_type n, const T& u) = 0;
            virtual allocator_type get_allocator() const = 0;
            // iterators:
            virtual iterator begin() = 0;
            virtual const_iterator begin() const = 0;
            virtual iterator end() = 0;
            virtual const_iterator end() const = 0;
            virtual reverse_iterator rbegin() = 0;
            virtual const_reverse_iterator rbegin() const = 0;
            virtual reverse_iterator rend() = 0;
            virtual const_reverse_iterator rend() const = 0;
            // 23.2.4.2 capacity:
            virtual size_type size() const = 0;
            virtual size_type max_size() const = 0;
            virtual void resize(size_type sz, T c = T()) = 0;
            virtual size_type capacity() const = 0;
            virtual bool empty() const = 0;
            virtual void reserve(size_type n) = 0;
            // element access:
            virtual reference operator[](size_type n) = 0;
            virtual const_reference operator[](size_type n) const = 0;
            virtual const_reference at(size_type n) const = 0;
            virtual reference at(size_type n) = 0;
            virtual reference front() = 0;
            virtual const_reference front() const = 0;
            virtual reference back() = 0;
            virtual const_reference back() const = 0;
            // 23.2.4.3 modifiers:
            virtual void push_back(const T& x) = 0;
            virtual void pop_back() = 0;
            virtual iterator insert(iterator position, const T& x) = 0;
            virtual void insert(iterator position, size_type n, const T& x) = 0;
            // template <class InputIterator>
            // virtual void insert(iterator position, InputIterator first, InputIterator last) = 0;
            virtual iterator erase(iterator position) = 0;
            virtual iterator erase(iterator first, iterator last) = 0;
            virtual void swap(iVector<T,Allocator>&) = 0;
            virtual void clear() = 0;
    };
}
#endif