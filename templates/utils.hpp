/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:18:01 by adda-sil          #+#    #+#             */
/*   Updated: 2022/02/25 07:47:48 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP 1

# include <sstream>
# ifdef DEBUG
    #define VDBG(...) std::cerr << "<Vector> " << YELLOW << __VA_ARGS__ << RESET << std::endl
    #define IDBG(...) std::cerr << "<Iterator> " << YELLOW << __VA_ARGS__ << RESET << std::endl

# else
    #define VDBG(...)
    #define IDBG(...)
# endif // DEBUG

# define DBG(...) std::cout << "<DEBUG> " << __VA_ARGS__ << std::endl

template<class T>
std::string toString(T el) {
    std::ostringstream sstream;
    sstream << el;
    return sstream.str();
}

namespace ft {

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (
        InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2, InputIterator2 last2
    ) {
        while (first1 != last1)
        {
            if (first2 == last2 || *first2 < *first1) return false;
            else if (*first1 < *first2) return true;
            ++first1; ++first2;
        }
        return (first2 != last2);
    }

    template <class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare (
        InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2, InputIterator2 last2,
        Compare comp
    ) {
        while (first1 != last1) {
            if (first2 == last2 || comp(*first2, *first1)) return false;
            else if (comp(*first1, *first2)) return true;
            ++first1; ++first2;
        }
        return (first2 != last2);
    }
}


#endif // !UTILS_HPP