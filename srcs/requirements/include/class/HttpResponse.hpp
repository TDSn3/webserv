/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:43:46 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/01 19:22:23 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

# include <iostream>

class HttpRequest;

struct s_status_line
{
	std::string	version;
	int			code;
	std::string	reason_phrase;
};

/* ************************************************************************** */
/*                                                                            */
/*   status_line = HTTP-Version SP* Status-Code SP* Reason-Phrase CRLF* **    */
/*   status_line = HTTP/1.1 200 OK											  */
/*                                                                            */
/*   SP = Space																  */
/*   CR = Carriage Return (retour chariot)									  */
/*   LF = Line Feed	(saut de ligne)											  */
/*   CRLF = utilisée comme marqueur de fin de ligne pour tous les éléments	  */
/*   du protocole, sauf pour le body										  */
/*                                                                            */
/*   *	RFC 2616 - 2.2 Basic Rules											  */
/*   **	RFC 2616 - 6.1 Status-Line											  */
/*                                                                            */
/* ************************************************************************** */
class HttpResponse
{
	public:

		void	build(HttpRequest &request)
		{
			status_line.version = request.request_line.version;
			status_line.code = 200;
			status_line.reason_phrase = "OK";

			_make_response(request);
		};

		bool	status(void)
		{
			if (str_response.empty() )
				return (false);	// vide
			return (true);		// remplie
		};

		void	clear(void)
		{
			data.clear();
			str_header.clear();
			str_body.clear();

			status_line.version.clear();
			status_line.code = 0;
			status_line.reason_phrase.clear();

			str_response.clear();
		};

		std::string		data;

		s_status_line	status_line;
		std::string		str_header;
		std::string		str_body;

		std::string		str_response;

	protected:

	private:

		std::string		_read_file_in_str(std::string path);
		void			_make_response(HttpRequest &request);
		void			_give_content_type(HttpRequest &request);

};

#endif

