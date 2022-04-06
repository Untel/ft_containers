/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:05:28 by adda-sil          #+#    #+#             */
/*   Updated: 2022/04/06 22:17:41 by adda-sil         ###   ########.fr       */
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
			typedef typename Iterator::difference_type                   	difference_type;
			typedef typename Iterator::value_type                        	value_type;
			typedef typename Iterator::pointer                           	pointer;
			typedef typename Iterator::reference                         	reference;
			typedef typename Iterator::iterator_category                 	iterator_category;
	};

	template <class T>
	class iterator_traits<T *> {
		public:
			typedef ptrdiff_t                               				difference_type;
			typedef T                                       				value_type;
			typedef T *                                     				pointer;
			typedef T &                                     				reference;
			typedef std::random_access_iterator_tag         				iterator_category;
	};

	template <class T>
	class iterator_traits<const T *> {
		public:
			typedef ptrdiff_t                           					difference_type;
			typedef T                                   					value_type;
			typedef const T *                           					pointer;
			typedef const T &                           					reference;
			typedef std::random_access_iterator_tag     					iterator_category;
	};

	template <class Iterator>
	class reverse_iterator {
		public: 
			typedef	Iterator														iterator_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type         difference_type;
			typedef typename ft::iterator_traits<Iterator>::value_type              value_type;
			typedef typename ft::iterator_traits<Iterator>::pointer                 pointer;
			typedef typename ft::iterator_traits<Iterator>::reference               reference;
			typedef typename ft::iterator_traits<Iterator>::iterator_category       iterator_category;

			// default (1)	
			reverse_iterator() : _base(iterator_type()) {}
			// initialization (2)	
			explicit reverse_iterator (iterator_type it) : _base(it) {}
			// copy (3)	
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter> & rev_it) : _base(rev_it.base()) {}

			reverse_iterator & operator ++ (void) { --_base; return *this; }
			reverse_iterator operator ++ (int) { reverse_iterator tmp(*this); operator++(); return tmp; }
			reverse_iterator & operator -- (void) { ++_base; return *this; }	
			reverse_iterator operator -- (int) { reverse_iterator tmp(*this); operator--(); return tmp; }
			
			iterator_type base() const {
				return _base;
			}
			reference operator * () const {
				iterator_type b = _base;
				return *(--b);
			}
			pointer operator -> () const {
				iterator_type b = _base;
				return (--b).operator->();
			}
			reverse_iterator & operator += (difference_type n) {
				_base -= n;
				return (*this);
			}
			reverse_iterator operator + (difference_type n) const {
				return reverse_iterator(_base - n);
				
			}
			reverse_iterator operator - (difference_type n) const {
				return reverse_iterator(_base + n);
			}
			reverse_iterator & operator -= (difference_type n) {
				_base += n;
				return (*this);
			}

			// /*unspecified*/ said by cppreference
			// reference said by cplusplus.com
			reference operator [] (difference_type n) const {
				IDBG("rev op[" << -n - 1 << "] = " << base()[-n - 1]);
				return base()[-n - 1];
			}

		private:
			iterator_type	_base;
	};

    template<typename T>
    ft::reverse_iterator<T> operator + (
        typename ft::reverse_iterator<T>::difference_type lhs,
        const ft::reverse_iterator<T> & rhs
    ) {
        return (rhs + lhs);
    }

    template<typename T>
    typename ft::reverse_iterator<T>::difference_type operator - (
        const ft::reverse_iterator<T> & lhs,
        const ft::reverse_iterator<T> & rhs
    ) {
        return (rhs.base() - lhs.base());
    }

    template<typename T, typename U>
    typename ft::reverse_iterator<T>::difference_type operator - (
        const ft::reverse_iterator<T> & lhs,
        const ft::reverse_iterator<U> & rhs
    ) {
        return (rhs.base() - lhs.base());
    }

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