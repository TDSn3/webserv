/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _add_body.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:34:49 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/06 17:00:05 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

void	HttpResponse::_add_body(HttpRequest &request, char **env)
{
	std::ostringstream	oss;

	str_response += "Content-Length: ";

	if (request.request_line.method == GET)
	{
		if (request.request_line.uri == "/")
			str_body = _read_file_in_str(INDEX_FILE_NAME);							// ! throw possible
		else if (request.request_line.uri == "/favicon.ico")
			str_body = _read_file_in_str(FAVICON_FILE_NAME);						// ! throw possible
		else
		{
			if (request.request_line.parsed_url.path.find("cgi-bin/") != std::string::npos)
			{
				std::cout << COLOR_BOLD_CYAN << "CGI detected" << COLOR_RESET << std::endl;
				str_body = _exec_cgi(request.request_line.parsed_url.path, request, env);	// ! throw possible
			}
			else
				str_body = _read_file_in_str(request.request_line.parsed_url.path);	// ! throw possible
		}
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