/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:55:10 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/25 11:57:20 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include <iostream>

# include "../enum.hpp"

struct request_line
{
	http_method	method;
	std::string	uri;
	std::string	version;
};

/* ************************************************************************** */
/*                                                                            */
/*   request_line = Method SP* Request-URI SP* HTTP-Version CRLF* **		  */
/*   request_line = GET / HTTP/1.1											  */
/*                                                                            */
/*   SP = Space																  */
/*   CR = Carriage Return (retour chariot)									  */
/*   LF = Line Feed	(saut de ligne)											  */
/*   CRLF = utilisée comme marqueur de fin de ligne pour tous les éléments	  */
/*   du protocole, sauf pour le body										  */
/*                                                                            */
/*   *	RFC 2616 - 2.2 Basic Rules											  */
/*   **	RFC 2616 - 5.1 Request-Line											  */
/*                                                                            */
/* ************************************************************************** */
class HttpRequest
{
	public:

		HttpRequest(void)
		{
			content_length = -1;
		}
		
		void			clear(void)
		{
			data.clear();
			s_request_line.clear();
			s_header.clear();
			s_body.clear();
			
			rl.method = EMPTY;
			rl.uri.clear();
			rl.version.clear();
		};

		int				parsing(void);

		std::string		data;

		std::string		s_request_line;
		request_line	rl;
		std::string		s_header;
		std::string		s_body;

		int				content_length;

	protected:

	private:

		int	_lexer(void);

};

#endif

