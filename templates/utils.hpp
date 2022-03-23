/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:18:01 by adda-sil          #+#    #+#             */
/*   Updated: 2022/03/22 02:22:28 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP 1

# include <sstream>
# include "term.hpp"
# ifdef DEBUG
    #define VDBG(...) std::cerr << "<Vector> " << YELLOW << __VA_ARGS__ << RESET << std::endl
    #define IDBG(...) std::cerr << "<Iterator> " << CYAN << __VA_ARGS__ << RESET << std::endl
    #define MDBG(...) std::cerr << "<Map> " << BOLDCYAN << __VA_ARGS__ << RESET << std::endl

# else
    #define VDBG(...)
    #define IDBG(...)
    #define MDBG(...)
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

    template <class InputIterator1, class InputIterator2>
    bool equal (
        InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2
    ) {
        while (first1!=last1) {
            if (!(*first1 == *first2))
                return false;
            ++first1; ++first2;
        }
        return true;
    }

    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal (
        InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2,
        BinaryPredicate pred
    ) {
        while (first1!=last1) {
            if ((!pred(*first1,*first2)))
                return false;
            ++first1; ++first2;
        }
        return true;
    }

    struct false_type { static const bool value = false; };
    struct true_type { static const bool value = true; };

    template <class T> struct is_integral : public false_type {};
    template <> struct is_integral<int> : public true_type {};
    template <> struct is_integral<unsigned int> : public true_type {};
    template <> struct is_integral<bool> : public true_type {};
    template <> struct is_integral<char> : public true_type {};
    template <> struct is_integral<unsigned char> : public true_type {};
    template <> struct is_integral<signed char> : public true_type {};
    template <> struct is_integral<short> : public true_type {};
    template <> struct is_integral<unsigned short> : public true_type {};
    template <> struct is_integral<long> : public true_type {};
    template <> struct is_integral<unsigned long> : public true_type {};
    template <> struct is_integral<long long> : public true_type {};
    template <> struct is_integral<unsigned long long> : public true_type {};

    template<bool B, typename T = void>
        struct enable_if {};

    template<typename T>
    struct enable_if<true, T> { typedef T type; };
}


#endif // !UTILS_HPP