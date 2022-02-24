/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   awesome.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:09:22 by adda-sil          #+#    #+#             */
/*   Updated: 2022/02/04 07:49:50 by adda-sil         ###   ########.fr       */
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
        int is_cpy;
        Awesome( void ) : _n(42), str("None tmtc"), is_cpy(0) {
            DBG("Awesome Construct");
            return;
        }
        Awesome( int n ) : _n(n), str(std::string("N=").append(toString(n))), is_cpy(0) {
            DBG("Awesome Construct By ints: " << n);

            return;
        }
        ~Awesome( void ) {
            DBG("Awesome Destruct");
            return;
        }
        Awesome( Awesome const &rhs ) : _n(rhs._n), str(rhs.str), is_cpy(1) {
            DBG("Awesome copy construco from " << rhs.str);
        }

		Awesome &operator=( const Awesome & rhs ) {
            this->_n = rhs._n;
            this->is_cpy = 1;
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
