/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _make_response.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 09:52:55 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/06 17:45:41 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

static std::string	give_uri_extension_name(std::string uri);

void	HttpResponse::_make_response(HttpRequest &request, char **env)	// ! throw possible
{
	std::ostringstream	oss;

	(void) request;

	oss << status_line.code;

	str_response += status_line.version;
	str_response += " ";
	str_response += oss.str();
	str_response += " ";
	str_response += status_line.reason_phrase;
	str_response += "\r\n";

	_give_content_type(request);

	_add_body(request, env);		// ! throw possible
}

void	HttpResponse::_give_content_type(HttpRequest &request)
{
	if (request.request_line.method == GET)	// TODO: gérer POST et DELETE
	{
		if (request.request_line.uri == "/")
		{
			str_response += "Content-Type: text/html; charset=UTF-8\r\n";
		}
		else if (request.request_line.uri == "/favicon.ico")
		{
			str_response += "Content-Type: image/png; charset=UTF-8\r\n";
		}
		else
		{
			std::string	extension_name;
			
			str_response += "Content-Type: ";
			extension_name = give_uri_extension_name(request.request_line.uri);
			if (extension_name == "html" || extension_name == "css")
				str_response += "text/" + extension_name;
			else if (extension_name == "javascript" || extension_name == "js")
				str_response += "application/javascript";
/////////// ajouter d'autres types ici si besoin
			str_response += "; charset=UTF-8\r\n";
		}
	}
}

static std::string	give_uri_extension_name(std::string uri)
{
    size_t		dot_pos;
	std::string	extension_name;

	dot_pos = uri.rfind('.');
    if (dot_pos == std::string::npos)
	{
        return ("");
	}
	extension_name = uri.substr(dot_pos + 1);
	if (extension_name == "cgi")
		extension_name == "html";

	if (extension_name != "html"
		|| extension_name != "css"
		|| extension_name != "javascript"
		|| extension_name != "js"
		|| extension_name != "ico"
		|| extension_name != "png"
		|| extension_name != "cgi")
		return ("");
    return (extension_name);
}
