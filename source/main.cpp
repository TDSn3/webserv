/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:58:01 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/09 11:27:20 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	try
	{
		Server	server(8080);

		std::cout << "\nLe serveur démarre sur le port " << COLOR_BOLD_BLUE << server.port << COLOR_RESET << std::endl;

		if (client_accept(server) )
			return (1);
	}
	catch(const std::exception &e) {
		return (1); }

	return (0);
}
