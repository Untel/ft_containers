/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:22:03 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/07 16:38:43 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft {

	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( pair<T1,T2>(x,y) );
	}

    template <class T1, class T2>
    class pair {
        public:
            typedef typename T1     first_type;
            typedef typename T2     second_type;

            first_type              first;
            second_type             second;

            pair(void);
            template<class U, class V> pair (const pair<U,V>& pr)
                : first(pr.first), second(pr.second) {};
            pair (const first_type &a, const second_type &b)
                : first(a), second(b) {};
            pair & operator = (const pair & pr)
                : first(pr.first), second(pr.second) {};

            // void swap (pair & x) {
            //     size_type   tmp_first   = first;
            //     size_type   tmp_second  = second;

            //     first                   = x.first;
            //     second                  = x.second;

            //     x.first                 = tmp_first;
            //     x.second                = tmp_second;
            // }
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
}