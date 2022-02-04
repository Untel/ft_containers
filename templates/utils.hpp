/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:18:01 by adda-sil          #+#    #+#             */
/*   Updated: 2022/02/04 08:40:11 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <sstream>
# ifdef DEBUG
    #define VDBG(...) std::cerr << "<Vector> " << __VA_ARGS__ << std::endl
# else
    #define VDBG(...)
    // #define DBG(...)
# endif // DEBUG
# define DBG(...) std::cout << "<DEBUG> " << __VA_ARGS__ << std::endl

template<class T>
std::string toString(T el) {
    std::ostringstream sstream;
    sstream << el;
    return sstream.str();
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

#endif // !UTILS_HPP