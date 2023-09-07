/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinity_loop_poll.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:45 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/07 12:06:58 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

void	infinity_loop_poll(Server &server, char **env)	// ! throw possible
{
	std::cout << COLOR_GREEN << "\n+++++++ Waiting for new connection ++++++++\n" << COLOR_RESET << std::endl;

	while (1)
	{
		int	ret;

		ret = poll(server.poll_struct.data(), static_cast<nfds_t>(server.poll_struct.size() ), 0);	// poll() vérifie l'état de chaque socket
		if (ret == -1)
			my_perror_and_throw("poll error", std::exception() );

		if (server.new_connexion() )
		{
			try
			{
				Client	new_client(server);	// ! throw possible
			}
			catch(const std::exception &e)
			{
				continue ;
			}
		}

		check_clients_poll_struct(server, env);
		if (siginit_status)
			break ;
	}
}
