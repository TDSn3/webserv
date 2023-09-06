/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:10:13 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/06 12:45:11 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

static void unfolding(std::string &data);
static void delete_first_crlf(std::string &data);

int	HttpRequest::parsing(void)	// ! throw possible
{		
	_lexer();

	delete_first_crlf(data);
	unfolding(data);

	_fill_up_to_lf();

	if (request_line.status)
		_parse_request_line();	// ! throw possible
	if (header_status)
		_parse_header();
	
	return (0);
};

int	HttpRequest::_lexer(void)	// TODO: code lexer
{
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*   Les valeurs de champ d'en-tête peuvent être étalées sur plusieurs		  */
/*   lignes si chaque nouvelle ligne commence par une espace SP				  */
/*   ou une tabulation horizontale HT.										  */
/*                                                                            */
/* ************************************************************************** */
static void	unfolding(std::string &data)
{
	std::string :: iterator	it = data.begin();

	while (it != data.end() )
	{
		if (get_character_type(*it) == CR && it + 1 != data.end() && get_character_type( *(it + 1) ) == LF && it + 2 != data.end()
			&& ( get_character_type( *(it + 2) ) == SP || get_character_type( *(it + 2) ) == HT) )
		{
			data.erase(it, it + 2);
		}
		else if (get_character_type(*it) == LF && it + 1 != data.end()
			&& ( get_character_type( *(it + 1) ) == SP || get_character_type( *(it + 1) ) == HT) )
		{
			data.erase(it, it + 1);
		}
		++it;
	}
}

static void delete_first_crlf(std::string &data)
{
	std::string :: iterator	it = data.begin();

	while (it != data.end() && (get_character_type(*it) == CR || get_character_type(*it) == LF) )
		it = data.erase(it, it + 1);
}
