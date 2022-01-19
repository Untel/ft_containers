/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   awesome.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:09:22 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/19 22:22:11 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AWESOME_HPP
# define AWESOME_HPP

# include <string>
# include <iostream>
# include "utils.hpp"

static int inc = 0;
class Awesome
{
    public:
        static int _count;
        int _n;
        int *_list;
        int is_cpy;
        Awesome( void ) : _n(42), is_cpy(0) {
            DBG("Awesome Construct");
            _list = new int[10]();
            _count++;
            // _list[1] = 666;
            // DBG("Awesome Construct" << *_list);
            // DBG("Awesome Construct" << _list[1]);
            // DBG("Awesome Construct" << _list[2]);

            return;
        }
        ~Awesome( void ) {
            DBG("Awesome Destruct");
            // DBG("Awesome Destruct" << _list[1]);

            // OMMMMMG
            // delete[] _list;
            return;
        }
        Awesome( Awesome const &rhs ) { *this = rhs; DBG("Awesome copy const"); }

		Awesome &operator=( Awesome const & rhs ) { this->_n = rhs._n; is_cpy = 1; this->_list = rhs._list; return (*this); }
		bool operator==( Awesome const & rhs ) const { return (this->_n == rhs._n); }
		bool operator!=( Awesome const & rhs ) const { return (this->_n != rhs._n); }
		bool operator>( Awesome const & rhs ) const { return (this->_n > rhs._n); }
		bool operator<( Awesome const & rhs ) const { return (this->_n < rhs._n); }
		bool operator>=( Awesome const & rhs ) const { return (this->_n >= rhs._n); }
		bool operator<=( Awesome const & rhs ) const { return (this->_n <= rhs._n); }
		void operator+=(int rhs){ _n += rhs; }
        int get(void) const { return this->_n; }
        void set(int v) { this->_n = v; }
};
// std::ostream & operator << (std::ostream & o, Awesome const & a){
//     o << "Awesome" << " N: " << a.get() << std::endl; 
//     for (int i = 0; i < 10; i++)
//         o << i << ": " << a._list[i] << ", ";
//     o << std::endl;
// 	return o;
// }
int Awesome::_count = 0;

#endif
