/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:55:10 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/23 15:45:14 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include <iostream>

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

		void	clear(void)
		{
			data.clear();
			request_line.clear();
			header.clear();
			body.clear();
		};

		std::string	data;
		std::string	request_line;
		std::string	header;
		std::string	body;

	protected:

	private:

};

#endif

