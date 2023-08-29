/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:55:10 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/29 19:19:33 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include <iostream>
# include <map>

# include "../enum.hpp"

struct s_request_line
{
	bool		status;
	http_method	method;
	std::string	uri;
	std::string	version;
	int			major_version;
	int			minor_version;
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
			request_line.status = false;
			request_line.method = EMPTY;
			request_line.major_version = 0;
			request_line.minor_version = 0;

			header_status = false;

			content_read = 0;
			content_length = 0;
			request_status = false;
		}
		
		void			clear(void)
		{
			data.clear();

			str_request_line.clear();
			request_line.status = false;
			request_line.method = EMPTY;
			request_line.uri.clear();
			request_line.version.clear();
			request_line.major_version = 0;
			request_line.minor_version = 0;

			str_header.clear();
			header_status = false;
			header.clear();

			str_body.clear();

			content_read = 0;
			content_length = 0;
			request_status = false;
		};

		int									parsing(void);
		void								parse_request_line(void);
		void								parse_header(void);
		void								parse_body(void);



		std::string							data;

		std::string							str_request_line;
		s_request_line						request_line;
	
		std::string							str_header;
		bool								header_status;
		std::map<std::string, std::string>	header;

		std::string							str_body;

		size_t								content_read;
		size_t								content_length;
		bool								request_status;

	protected:

	private:

		int									_lexer(void);

};

#endif

