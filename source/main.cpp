/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:58:01 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/03 17:17:12 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	Server				server(8080);

	std::cout << "Le serveur demarre sur le port " << server.port << std::endl;

	if (client_accept(server.give_fd() ) )
		return (1);

	return (0);
}

