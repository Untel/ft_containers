/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:18:01 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/21 20:36:16 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

    # include <sstream>
    #ifdef DEBUG
        #define VDBG(...) std::cerr << "<Vector> " << __VA_ARGS__ << std::endl
    #else
        #define VDBG(...)
        // #define DBG(...)
    #endif // DEBUG
    #define DBG(...) std::cerr << "<DEBUG> " << __VA_ARGS__ << std::endl

    template<class T>
    std::string toString(T el) {
        std::ostringstream sstream;
        sstream << el;
        return sstream.str();
    }

#endif // !UTILS_HPP