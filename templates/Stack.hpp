/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 12:01:27 by adda-sil          #+#    #+#             */
/*   Updated: 2022/04/06 22:05:55 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP 1

#include "vector.hpp"

namespace ft {
	template <class T, class Container = ft::vector<T> >
	class stack {
	    public:
            typedef T			                            value_type;
            typedef Container	                            container_type;
            typedef typename Container::size_type           size_type;

            explicit stack (const container_type &cT = container_type()) : c(cT) {}
            bool empty() const { return (c.empty()); }
            size_type size() const { return (c.size()); }
            value_type & top() { return (c.back()); }
            const value_type & top() const { return (c.back()); }
            void push (const value_type &el) { c.push_back(el); }
            void pop() { c.pop_back(); }

            template <class _T, class _Container>
            friend bool operator== (const ft::stack<_T, _Container> &lhs, const ft::stack<_T, _Container> &rhs);
            template <class _T, class _Container>
            friend bool operator!= (const ft::stack<_T, _Container> &lhs, const ft::stack<_T, _Container> &rhs);
            template <class _T, class _Container>
            friend bool operator< (const ft::stack<_T, _Container> &lhs, const ft::stack<_T, _Container> &rhs);
            template <class _T, class _Container>
            friend bool operator<= (const ft::stack<_T, _Container> &lhs, const ft::stack<_T, _Container> &rhs);
            template <class _T, class _Container>
            friend bool operator> (const ft::stack<_T, _Container> &lhs, const ft::stack<_T, _Container> &rhs);
            template <class _T, class _Container>
            friend bool operator>= (const ft::stack<_T, _Container> &lhs, const ft::stack<_T, _Container> &rhs);

        protected:
            Container   c;
	};

    template <class T, class Container>
	bool operator == (const stack<T,Container> &lhs, const stack<T,Container> &rhs) {
		return (lhs.c == rhs.c);
	}
	template <class T, class Container>
	bool operator != (const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return (!(lhs == rhs));
	}
	template <class T, class Container>
	bool operator <= (const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return (!(rhs < lhs));
	}
	template <class T, class Container>
	bool operator >= (const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return (!(lhs < rhs));
	}
	template <class T, class Container>
	bool operator < (const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return (lhs.c < rhs.c);
	}
	template <class T, class Container>
	bool operator > (const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
		return (rhs < lhs);
	}
}

#endif // !STACK_HPP