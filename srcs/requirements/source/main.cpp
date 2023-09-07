/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:58:01 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/07 12:04:39 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

volatile sig_atomic_t	siginit_status = 0;

int	main(int argc, char **argv, char **env)
{
	LogFile		log_file;					// redirige cout et cerr vers le fichier log

	if (check_arg(argc, argv) == false)
		return (1);

	signal(SIGINT, handler);

	try
	{
		Server	server(8080);				// ! throw possible

		infinity_loop_poll(server, env);	// ! throw possible
	}
	catch(const std::exception &e)
	{
		return (1);
	}

	return (0);
}
