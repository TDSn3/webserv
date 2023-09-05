/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _check_url_syntax.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:24:44 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/05 19:14:13 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

static int	check_port(std::string &port);

void	HttpRequest::_check_url_syntax(void)
{
	if (!request_line.parsed_url.scheme.empty() && request_line.parsed_url.scheme != "http")
		throw (StatusCode(400) );
	if (!request_line.parsed_url.port.empty() && check_port(request_line.parsed_url.port) )
		throw (StatusCode(400) );
}

static int	check_port(std::string &port)
{
	for (size_t i = 0; port[i]; i++)
		if (get_character_type(port[i]) != DIGIT)
			return (1);
	return (0);
}
