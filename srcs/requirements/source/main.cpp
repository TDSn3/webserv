/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:58:01 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/02 07:40:36 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

volatile sig_atomic_t	siginit_status = 0;

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	signal(SIGINT, handler);

	//LogFile		log_file;

	try
	{
		Server	server(8080);

		std::cout << "\nLe serveur démarre sur le port " << COLOR_BOLD_BLUE << server.port << COLOR_RESET << std::endl;

		client_accept(server);
	}
	catch(const std::exception &e)
	{
		return (1);
	}

	return (0);
}
