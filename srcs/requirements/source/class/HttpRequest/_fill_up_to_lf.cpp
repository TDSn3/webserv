/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _fill_up_to_lf.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:25:16 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/06 13:48:15 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

void	HttpRequest::_fill_up_to_lf(void)
{
	for(size_t i = 0; data[i] && request_status == false ; i++)
	{
		if (!request_line.status)
		{
			str_request_line += data[i];
			if (get_character_type(data[i]) == LF)
				request_line.status = true;
		}
		else if(!header_status)
		{
			if ( (get_character_type(data[i]) == CR && data[i + 1] && data[i + 2]
					&& get_character_type(data[i + 2]) == LF && !data[i + 3] )
				|| (get_character_type(data[i]) == LF && !data[i + 1] ) )			// no header
			{
				request_status = true;
				return ;
			}

			str_header += data[i];
			
			if (get_character_type(data[i]) == LF
				&& data[i + 1] && get_character_type(data[i + 1]) == CR
				&& data[i + 2] && get_character_type(data[i + 2]) == LF)
			{
				i += 2;
				header_status = true;
			}
		}
		else
		{
			str_body += data[i];
		}

		if (header_status == true && header.find("Content-Length") != header.end() )
		{
			std::istringstream	iss(header["Content-Length"]);
			size_t				stock;

			iss >> stock;
			if (str_body.size() == stock)
			{
				request_status = true;
				return ;
			}
		}
		else if (header_status == true)
		{
			str_body.clear();
			request_status = true;
			return ;
		}
	}
}
