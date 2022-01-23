/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   awesome.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:09:22 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/22 17:56:32 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AWESOME_HPP
# define AWESOME_HPP

# include <string>
# include <iostream>
# include "utils.hpp"

class Awesome
{
    public:
        int _n;
        std::string const str;
        int *_list;
        int is_cpy;
        Awesome( void ) : _n(42), str("None tmtc"), is_cpy(0) {
            DBG("Awesome Construct");
            // _list = new int[10]();
            // _list[1] = 666;
            // DBG("Awesome Construct" << *_list);
            // DBG("Awesome Construct" << _list[1]);
            // DBG("Awesome Construct" << _list[2]);

            return;
        }
        Awesome( int n ) : _n(n), str(std::string("N=").append(toString(n))), is_cpy(0) {
            DBG("Awesome Construct By ints: " << n);
            // _list = new int[10]();
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
        Awesome( Awesome const &rhs ) : _n(rhs._n), str(rhs.str), is_cpy(1) {
            DBG("Awesome copy const from " << rhs.str);
        }

		Awesome &operator=( Awesome const & rhs ) {
            this->_n = rhs._n;
            this->is_cpy = 1;
            // this->_list = rhs._list;
            DBG("Awesome Assignation Old: " << this->str << " New: " << rhs.str << " |  _n=" << this->_n);
            return (*this);
        }
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
extern std::ostream & operator << (std::ostream & o, Awesome const & a);

#endif
