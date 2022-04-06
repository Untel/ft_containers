/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:18:01 by adda-sil          #+#    #+#             */
/*   Updated: 2022/04/06 22:04:43 by adda-sil         ###   ########.fr       */
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
    #define MAP_PRINT(m) m.print()

# else
    #define VDBG(...)
    #define IDBG(...)
    #define MDBG(...)
    #define MAP_PRINT(x)

# endif // DEBUG

# define DBG(...) std::cout << "<DEBUG> " << __VA_ARGS__ << std::endl

template<class T>
std::string toString(T el) {
    std::ostringstream sstream;
    sstream << el;
    return sstream.str();
}

#endif // !UTILS_HPP