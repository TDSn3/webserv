/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_accept.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:45 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/23 15:45:58 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

static void	clients_poll_struct_check(Server &server);

void	client_accept(Server &server)
{
	std::cout << COLOR_GREEN << "\n+++++++ Waiting for new connection ++++++++\n" << COLOR_RESET << std::endl;

	while (1)
	{
		int				ret;

		ret = poll(server.poll_struct.data(), static_cast<nfds_t>(server.poll_struct.size() ), 0);
		if (ret == -1)
		{
			perror("poll");
			throw (std::exception() );
		}

		if (server.new_connexion() )
		{
			try
			{
				Client	new_client(server);
			}
			catch(const std::exception &e)
			{
				continue ;
			}
		}

		clients_poll_struct_check(server);
		if (siginit_status)
			break ;
	}
}

static void	clients_poll_struct_check(Server &server)
{
	std::string						hello("HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!");
	std::vector<Client> :: iterator it = server.clients.begin();

	while (it != server.clients.end() )
	{
		if (it->poll_struct && it->poll_struct->revents & (POLLIN | POLLERR | POLLHUP) )
		{
			it->buffer_clear();
			
			ssize_t					ret;

			ret = recv(it->communication_fd, it->buffer, sizeof(it->buffer), 0);
			if (ret > 0)
			{
				it->request.data += it->buffer;
				if (ret < BUFFER_CLIENT_SIZE)
				{
					std::cout << COLOR_BOLD_RED << "BUFFER : " << ret << " / " << BUFFER_CLIENT_SIZE << COLOR_RESET << std::endl;

					write(server.clients.back().communication_fd , hello.c_str() , strlen(hello.c_str() ) );
					std::cout << "[" << COLOR_BOLD << it->ipv4 << COLOR_BLUE << ":" << it->port << COLOR_RESET << "]\n" << it->request.data << std::endl;

					it->request.clear();
				}
				else
				{
					std::cout << COLOR_BOLD_RED << "BUFFER FULL : " << ret << " / " << BUFFER_CLIENT_SIZE << COLOR_RESET << std::endl;
				}
			}
			else	// la connexion a été fermée par le client
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
