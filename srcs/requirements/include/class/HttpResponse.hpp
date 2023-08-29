/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:43:46 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/29 12:18:44 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

# include <iostream>


struct s_status_line
{
	std::string	version;
	int			code;
	std::string	reason_phrase;
};

/* ************************************************************************** */
/*                                                                            */
/*   s_status_line = HTTP-Version SP* Status-Code SP* Reason-Phrase CRLF* **	  */
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
			str_status_line.clear();
			str_header.clear();
			str_body.clear();

			sl.version.clear();
			sl.code = 0;
			sl.reason_phrase.clear();
		};

		std::string	data;

		std::string	str_status_line;
		s_status_line	sl;
		std::string	str_header;
		std::string	str_body;

	protected:

	private:

};

#endif

