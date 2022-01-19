#ifndef AWESOME_HPP
# define AWESOME_HPP

# include <string>
# include <iostream>
# include "utils.hpp"

class Awesome
{
    public:
        int _n;
        int *_list;
        Awesome( void ) : _n(42), _list(new int[10]()) {
            DBG("Construct");
            return;
        }
        ~Awesome( void ) {
            delete [] _list;
            DBG("Destruct");
            return;
        }
        int get(void) const { return this->_n; }
        void set(int v) { this->_n = v; }
};
std::ostream & operator<<(std::ostream & o, Awesome const & a){
    o << "Awesome" << " N: " << a.get() << std::endl; 
    for (int i = 0; i < 10; i++)
        o << i << ": " << a._list[i] << ", ";
    o << std::endl;
	return o;
}
#endif