/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _add_body.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:34:49 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/05 20:23:41 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

void	HttpResponse::_add_body(HttpRequest &request)
{
	std::ostringstream	oss;

	str_response += "Content-Length: ";

	if (request.request_line.method == GET)
	{
		if (request.request_line.uri == "/")
			str_body = _read_file_in_str(INDEX_FILE_NAME);			// ! throw possible
		else if (request.request_line.uri == "/favicon.ico")
			str_body = _read_file_in_str(FAVICON_FILE_NAME);		// ! throw possible
		else
			str_body = _read_file_in_str(request.request_line.uri);	// ! throw possible
	}

	oss << str_body.size();

	str_response += oss.str();
	str_response += "\r\n";

	str_response += "\r\n";

	str_response += str_body;
}

void	HttpResponse::_add_body(std::string path)
{
	std::ostringstream	oss;

	str_response += "Content-Length: ";

	str_body = _read_file_in_str(path);								// ! throw possible

	oss << str_body.size();

	str_response += oss.str();
	str_response += "\r\n";

	str_response += "\r\n";

	str_response += str_body;
}