/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _read_file_in_str.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:12:26 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/31 12:17:29 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

std::string	HttpResponse::_read_file_in_str(std::string path)
{
	std::string			new_path;
	std::ifstream		file;
	std::ostringstream	oss;
	std::string			str;

	if (!path.empty() && path[0] == '/')
		new_path = "www" + path;
	else if (!path.empty() && path[0] != '/')
		new_path = "www/" + path;

	file.open(new_path.c_str() );
	if (!file.good() || !file.is_open() )
	{
		std::cerr << "Error: could not open file." << std::endl;	// !!! a gérer plus tard !!!	// gestion erreur avec la reponse
		file.close();

		return (str);
	}

    oss << file.rdbuf();
	str = oss.str();

	file.close();

	return (str);
}
