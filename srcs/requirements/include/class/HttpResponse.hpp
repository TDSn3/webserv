/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:43:46 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/23 16:18:08 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

# include <iostream>


struct status_line
{
	std::string	version;
	int			code;
	std::string	reason_phrase;
};

/* ************************************************************************** */
/*                                                                            */
/*   status_line = HTTP-Version SP* Status-Code SP* Reason-Phrase CRLF* **	  */
/*   request_line = GET / HTTP/1.1											  */
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

		void	clear(void)
		{
			data.clear();
			s_status_line.clear();
			s_header.clear();
			s_body.clear();

			sl.version.clear();
			sl.code = 0;
			sl.reason_phrase.clear();
		};

		std::string	data;

		std::string	s_status_line;
		status_line	sl;
		std::string	s_header;
		std::string	s_body;

	protected:

	private:

};

#endif

