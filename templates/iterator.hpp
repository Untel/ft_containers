/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:05:28 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/19 21:45:33 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <iterator>

template < class Iterator >
class iterator_trait {
    typedef Iterator::difference_type                   difference_type;
    typedef Iterator::value_type                        value_type;
    typedef Iterator::pointer                           pointer;
    typedef Iterator::reference                         reference;
    typedef Iterator::iterator_category                 iterator_category;
};

template <class T>
class iterator_trait<T *> {
        typedef ptrdiff_t                               difference_type;
        typedef T                                       value_type;
        typedef T *                                     pointer;
        typedef T &                                     reference;
        typedef std::random_access_iterator_tag         iterator_category;
};

template <class T>
class iterator_trait<const T *> {
        typedef ptrdiff_t                               difference_type;
        typedef T                                       value_type;
        typedef const T *                               pointer;
        typedef const T &                               reference;
        typedef std::random_access_iterator_tag         iterator_category;
};

template <class Iterator>
class reverse_iterator {
	public: 
		typedef	Iterator														iterator_type
		typedef ft::iterator_trait<Iterator>::difference_type                   difference_type;
		typedef ft::iterator_trait<Iterator>::value_type                        value_type;
		typedef ft::iterator_trait<Iterator>::pointer                           pointer;
		typedef ft::iterator_trait<Iterator>::reference                         reference;
		typedef ft::iterator_trait<Iterator>::iterator_category                 iterator_category;

		// default (1)	
		reverse_iterator() : _base(iterator_type()) {}
		// initialization (2)	
		explicit reverse_iterator (iterator_type it) : _base(it) {}
		// copy (3)	
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>v & rev_it) { *this = rev_it; }

		reverse_iterator & operator++ (void) { --this->_base; return *this; }
		reverse_iterator operator++ (int) { reverse_iterator tmp(*this); operator++(); return tmp; }
		reverse_iterator & operator-- (void) { ++this->_base; return *this; }	
		reverse_iterator operator-- (int) { reverse_iterator tmp(*this); operator--(); return tmp; }
		
		template< class U >
		reverse_iterator &operator=( const reverse_iterator<U> &other) { this->_base = other._base }

		iterator_type base() const {
			return this->_base;
		}

		reference operator * () const {
			reference b = base;
			return *(--b);
		}
		// PEUT ETRE PAS BON CA
		pointer operator -> () const {
			pointer b = &_base;
			return (--b);
		}
	private:
		iterator_type	_base;
};

#endif