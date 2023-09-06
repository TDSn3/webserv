/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parse_request_line.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:28:11 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/06 12:31:11 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

static http_method	get_http_method(const std::string str);

void	HttpRequest::_parse_request_line(void)
{
	std::string			stock_line;
	std::istringstream	ss(str_request_line);
	char				i;

	i = 0;
	while(std::getline(ss, stock_line, ' ') && i < 127)
	{
		if (i == 0)
			request_line.method = get_http_method(stock_line);
		else if (i == 1)
		{
			request_line.uri = stock_line;
		}
		else if (i == 2)
		{
			while (!stock_line.empty() && get_character_type(stock_line[stock_line.size() - 1] ) & LWS)
				stock_line.erase(stock_line.size() - 1);
			request_line.version = stock_line;
		}
		i++;
	}

	try
	{
		_parse_url();				// ! throw possible
	}
	catch(const std::exception &e)
	{
		throw (StatusCode(400) );
	}
	_check_url_syntax();			// ! throw possible
	_print_parsing_url();

	if (i != 3)
		throw (StatusCode(400) );
}

static http_method	get_http_method(const std::string str)
{
	if (str == "EMPTY")
		return EMPTY;
	if (str == "GET")
		return GET;
	if (str == "POST")
		return POST;
	return EMPTY;
}
