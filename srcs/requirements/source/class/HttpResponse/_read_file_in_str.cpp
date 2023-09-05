/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _read_file_in_str.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:12:26 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/05 20:23:25 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

std::string	HttpResponse::_read_file_in_str(std::string path)	// ! throw possible
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
		std::cerr << "Error: could not open file." << std::endl;	// TODO: gestion erreur avec la reponse
		file.close();

		throw (StatusCode(404) );	// ! throw possible
	}

    oss << file.rdbuf();
	str = oss.str();

	file.close();

	return (str);
}
