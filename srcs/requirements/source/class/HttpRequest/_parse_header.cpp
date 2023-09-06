/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parse_header.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:30:41 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/06 12:31:07 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

void	HttpRequest::_parse_header(void)
{
	std::string			stock_line;
	std::istringstream	ss(str_header);
	size_t				i;
	char				j;

	while(std::getline(ss, stock_line) )
	{
		std::string			field_name;		// nom de champ		// <nom de champ>: <valeur de champ>	//  <nom de champ> ':' *LWS <valeur de champ>
		std::string			field_value;	// valeur de champ	//

		i = 0;
		j = 0;
		while(stock_line[i])
		{		
			if (stock_line[i] == ':' && j == 0)
			{
				i++;
				while (stock_line[i] && get_character_type(stock_line[i] ) & LWS)
					i++;
				j++;
				continue ;
			}
			if (j == 0)
				field_name += stock_line[i];
			else if (j == 1)
				field_value += stock_line[i];
			i++;
		}
		while (!field_value.empty() && get_character_type(field_value[field_value.size() - 1] ) & LWS)
			field_value.erase(field_value.size() - 1);
		if (!field_name.empty() )
			header[field_name] += field_value;
	}
}
