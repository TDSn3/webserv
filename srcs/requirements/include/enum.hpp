/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:49:59 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/25 13:15:03 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_HPP
# define ENUM_HPP

enum http_method
{
	EMPTY,
	GET,
	POST,
	DELETE
};

enum character_type
{
	OCTET	= 0b1111111111,			// séquence de 8 bits de données
	CHAR	= 0b0111111111,			// caractère US-ASCII (octets 0 - 127)
	UPALPHA	= 1 << 0,				// lettre majuscule "A" - "Z"
	LOALPHA	= 1 << 1,				// lettre minuscule "a" - "z"
	ALPHA	= UPALPHA | LOALPHA,	// majuscule ou minuscule
	DIGIT	= 1 << 2,				// chiffre "0" - "9"
	CTL		= 1 << 3,				// caractère de contrôle US-ASCII (octets 0 - 31) et DEL (127)
	CR		= 1 << 4,				// retour chariot (13)
	LF		= 1 << 5,				// saut à la ligne (10)
	SP		= 1 << 6,				// espace (32)
	HT		= 1 << 7,				// tabulation horizontale (9)
	QUOTE	= 1 << 8				// Guillemets (34)
};

enum rule
{
	LWS		= CR | LF | SP | HT,
	TEXT	= OCTET & ~CTL
};

#endif