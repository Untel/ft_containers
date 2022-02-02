/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 02:13:44 by adda-sil          #+#    #+#             */
/*   Updated: 2022/02/02 02:13:45 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP 1
# include <iterator>
# include <cstddef>

namespace ft {

	template <class Iterator>
	class iterator_traits {
		public:
			typedef typename Iterator::difference_type                   difference_type;
			typedef typename Iterator::value_type                        value_type;
			typedef typename Iterator::pointer                           pointer;
			typedef typename Iterator::reference                         reference;
			typedef typename Iterator::iterator_category                 iterator_category;
	};

	template <class T>
	class iterator_traits<T *> {
		public:
			typedef ptrdiff_t                               	difference_type;
			typedef T                                       	value_type;
			typedef T *                                     	pointer;
			typedef T &                                     	reference;
			typedef std::random_access_iterator_tag         	iterator_category;
	};

	template <class T>
	class iterator_traits<const T *> {
		public:
			typedef ptrdiff_t                           	difference_type;
			typedef T                                   	value_type;
			typedef const T *                           	pointer;
			typedef const T &                           	reference;
			typedef std::random_access_iterator_tag     	iterator_category;
	};

	template <class Iterator>
	class reverse_iterator {
		public: 
			typedef	Iterator														iterator_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type          difference_type;
			typedef typename ft::iterator_traits<Iterator>::value_type               value_type;
			typedef typename ft::iterator_traits<Iterator>::pointer                  pointer;
			typedef typename ft::iterator_traits<Iterator>::reference                reference;
			typedef typename ft::iterator_traits<Iterator>::iterator_category        iterator_category;

			// default (1)	
			reverse_iterator() : _base(iterator_type()) {}
			// initialization (2)	
			explicit reverse_iterator (iterator_type it) : _base(it) {}
			// copy (3)	
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter> & rev_it) { *this = rev_it; }

			reverse_iterator & operator ++ (void) { --this->_base; return *this; }
			reverse_iterator operator ++ (int) { reverse_iterator tmp(*this); operator++(); return tmp; }
			reverse_iterator & operator -- (void) { ++this->_base; return *this; }	
			reverse_iterator operator -- (int) { reverse_iterator tmp(*this); operator--(); return tmp; }
			
			/**
			 * @brief cppreference.com ask tparams U
			 * cplusplus.com say to dont implement this operator
			 * @todo check if possible in cpp98
			 */
			template< class U >
			reverse_iterator & operator = ( const reverse_iterator<U> &other) { this->_base = other._base; }
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
				return --b;
			}
			reverse_iterator & operator += (difference_type n) {
				return this->_base -= n;
			}

			reverse_iterator operator + (difference_type n) const {
				return this->_base - n;
			}

			reverse_iterator operator - (difference_type n) const {
				return this->_base + n;
			}

			// /*unspecified*/ said by cppreference
			// reference said by cplusplus.com
			reference operator [] (difference_type n) const {
				return this->_base[-n - 1];
			}

		private:
			iterator_type	_base;
	};

	/**
	 * @brief cppreference.com ask for 2 tparams
	 * cplusplus.com ask for one
	 * @todo check if comparison between 2 differents iterators is possible. It could be problematic if it is
	 */
	template <class Iterator, class Iterator2>
	bool operator == (const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator2> & rhs) {
		return lhs.base() == rhs.base();
	}
	template <class Iterator, class Iterator2>
	bool operator != (const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator2> & rhs) {
		return !(lhs == rhs);
	}
	template <class Iterator, class Iterator2>
	bool operator < (const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator2> & rhs) {
		return !(lhs >= rhs);
	}
	template <class Iterator, class Iterator2>
	bool operator > (const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator2> & rhs) {
		return !(lhs <= rhs);
	}
	template <class Iterator, class Iterator2>
	bool operator <= (const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator2> & rhs) {
		return lhs.base() >= rhs.base();
	}
	template <class Iterator, class Iterator2>
	bool operator >= (const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator2> & rhs) {
		return lhs.base() <= rhs.base();
	}
}

#endif