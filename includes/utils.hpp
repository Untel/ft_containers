/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:18:01 by adda-sil          #+#    #+#             */
/*   Updated: 2022/01/18 15:38:06 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

    #ifdef DEBUG
        #define VDBG(...) std::cerr << "<Vector> " << __VA_ARGS__ << std::endl
    #else
        #define VDBG(...)
    #endif // DEBUG

#endif // !UTILS_HPP