/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _make_response.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 09:52:55 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/01 13:55:22 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

void	HttpResponse::_make_response(HttpRequest &request)
{
	std::ostringstream	oss;
	std::string			body;

	(void) request;

	oss << status_line.code;

	str_response += status_line.version;
	str_response += " ";
	str_response += oss.str();
	str_response += " ";
	str_response += status_line.reason_phrase;
	str_response += "\r\n";

	if (request.request_line.method == GET && request.request_line.uri == "/")	// !!! a gérer plus tard !!!	// parser le type de doc envoyé
		str_response += "Content-Type: text/html; charset=UTF-8\r\n";
	else if (request.request_line.method == GET)
		str_response += "Content-Type: text/css; charset=UTF-8\r\n";

	str_response += "Content-Length: ";

	if (request.request_line.method == GET && request.request_line.uri == "/")
		body = _read_file_in_str(INDEX_FILE_NAME);
	else if (request.request_line.method == GET)
		body = _read_file_in_str(request.request_line.uri);

	oss.str("");
	oss.clear();
	oss << body.size();

	str_response += oss.str();
	str_response += "\r\n";

	str_response += "\r\n";

	str_response += body;
	
	//str_response += "Hello world!";
}
