/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:22:03 by adda-sil          #+#    #+#             */
/*   Updated: 2022/04/06 22:20:02 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft {
    template <class T1, class T2>
    class pair {
        public:
            typedef T1              first_type;
            typedef T2              second_type;

            first_type              first;
            second_type             second;

            pair(void) : first(0), second(0) {};
            template<class U, class V> pair (const pair<U,V>& pr)
                : first(pr.first), second(pr.second) {};
            pair (const first_type &a, const second_type &b)
                : first(a), second(b) {};
            pair & operator = (const pair & pr) {
                first = pr.first;
                second = pr.second;
                return *this;
            };
    };

    template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first==rhs.first && lhs.second==rhs.second; }

    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs==rhs); }

    template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(rhs<lhs); }

    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return rhs<lhs; }

    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs<rhs); }

    template <class T1,class T2>
	ft::pair<T1,T2> make_pair (T1 x, T2 y) {
		return ( pair<T1,T2>(x,y) );
	}

    #ifdef DEBUG
        template <class T1, class T2>
        std::ostream & operator << (std::ostream & o, ft::pair<T1, T2> const & pr){
            o << "(" << pr.first << ") " << pr.second; 
            return o;
        }
    #endif
}