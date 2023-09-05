/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_character_type.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:34:06 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/05 16:34:37 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

/* ************************************************************************** */
/*                                                                            */
/*   SP Espaces, HT tabulations, LF sauts de ligne et CR retours chariot	  */
/*   peuvent être remplacé par un seul SP espaces pour le parsing.			  */
/*                                                                            */
/* ************************************************************************** */
rule	get_character_type(const char c)
{
	unsigned char	u_c = static_cast<unsigned char>(c);

	if (u_c == 13)
		return CR;
	if (u_c == 10)
		return LF;
	if (u_c == 32)
		return SP;
	if (u_c == 9)
		return HT;
	if (u_c == 34)
		return QUOTE;
	if (u_c >= 'A' && u_c <= 'Z')
		return UPALPHA;
	if (u_c >= 'a' && u_c <= 'z')
		return LOALPHA;
	if (u_c >= '0' && u_c <= '9')
		return DIGIT;
	if (u_c < 32 || u_c == 127)
		return CTL;
	if (u_c < 128)
		return CHAR;
	return OCTET; // Tout autre octet
}
