/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_accept.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:45 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/10 10:21:24 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

static void	clients_poll_struct_check(Server &server);

int	client_accept(Server &server)
{
	std::cout << COLOR_GREEN << "\n+++++++ Waiting for new connection ++++++++\n" << COLOR_RESET << std::endl;

	while (1)
	{
		int		ret;

		ret = poll(server.poll_struct.data(), static_cast<nfds_t>(server.poll_struct.size() ), 0);
		if (ret == -1)
		{
			perror("poll");
			return (1);								// !!! Ajouter close()
		}

		if (server.new_connexion() )
		{
			Client	new_client;

			new_client.communication_fd = accept(server.give_connexion_fd(), (struct sockaddr *) &new_client.address, &new_client.address_len);
			if (new_client.communication_fd != -1)	// si une nouvelle connexion est arrivée
			{
				if (new_client.set_non_blocking_fd() )
					continue ;
				new_client.ipv4 = new_client.ip_to_string();
				new_client.port = new_client.address.sin_port;
				new_client.poll_struct = server.add_fd_poll_struct(new_client.communication_fd, POLLIN);
				new_client.it = server.poll_struct.end() - 1;
				server.clients.push_back(new_client);

				std::cout << "Connexion de " << COLOR_BOLD << new_client.ipv4 << COLOR_BLUE << ":" << new_client.port << COLOR_RESET << "\n" << std::endl;
			}	
		}

		clients_poll_struct_check(server);
	}

	close(server.give_connexion_fd());

	return (0);
}

static void	clients_poll_struct_check(Server &server)
{
	std::string						hello("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!");
	std::vector<Client> :: iterator it = server.clients.begin();

	while (it != server.clients.end() )
	{
		if (it->poll_struct && it->poll_struct->revents & (POLLIN | POLLERR | POLLHUP) )
		{
			char	buffer[3000] = {0};
			ssize_t	ret;

			ret = recv(it->communication_fd, buffer, sizeof(buffer), 0);
			if (ret > 0)
			{
				write(server.clients.back().communication_fd , hello.c_str() , strlen(hello.c_str() ) );
				std::cout << "[" << COLOR_BOLD << it->ipv4 << COLOR_BLUE << ":" << it->port << COLOR_RESET << "]\n" << buffer << std::endl;
			}
			else									// la connexion a été fermée par le client
			{
				std::cout << COLOR_RED << "Déconnexion de [" << it->ipv4 << ":" << it->port << "]" << COLOR_RESET << "\n" << std::endl;
				server.poll_struct.erase(it->it);
				it = server.clients.erase(it);
				continue ;
			}
		}
		it++;
	}
}
