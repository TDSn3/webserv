/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_accept.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:45 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/07 11:16:37 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

int test = 0;

int	client_accept(Server &server)
{
	std::cout << COLOR_GREEN << "\n+++++++ Waiting for new connection ++++++++\n" << COLOR_RESET << std::endl;

	while (1)
	{
		Client	new_client;
		
		new_client.communication_fd = accept(server.give_connexion_fd(), (struct sockaddr *) &new_client.address, &new_client.address_len);
		if (new_client.communication_fd != -1)	// si une nouvelle connexion est arrivée
		{
			try
			{
				new_client.set_non_blocking_fd();
			}
			catch (const std::exception &e)
			{
				close(new_client.communication_fd);
				continue ;
			}

			new_client.ipv4 = new_client.ip_to_string();
			new_client.port = new_client.address.sin_port;

			std::cout << "Connexion de " << COLOR_BOLD << new_client.ipv4 << COLOR_DIM << ":" << new_client.port << COLOR_RESET << std::endl;
			server.clients.push_back(new_client);
		}
		
		std::vector<Client> :: iterator it = server.clients.begin();
		
		while (it != server.clients.end() )
		{
			char	buffer[3000] = {0};
			ssize_t	ret;
			bool	disconnect;

			disconnect = false;
			ret = recv(it->communication_fd, buffer, sizeof(buffer), 0);
			if (ret > 0)
				std::cout << "[" << it->ipv4 << ":" << it->port << "]" << buffer << std::endl;
			else if (ret == 0)	// la connexion a été fermée par le client
				disconnect = true;
			else if (ret == -1 && errno != EWOULDBLOCK)
				disconnect = true;
			//else
			//{
			//	std::cout << (errno == EWOULDBLOCK) << std::endl;
			//}

			if (!test)
			{
				char	*hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
				char	buffer2[3000] = {0};
			
				write(new_client.communication_fd , hello , strlen(hello));
				//recv(new_client.communication_fd, buffer2, sizeof(buffer2), 0);
				//std::cout << buffer2 << std::endl;
				test++;
			}

			if (disconnect)
			{
				std::cout << "Déconnexion de [" << it->ipv4 << ":" << it->port << "]" << std::endl;
				it = server.clients.erase(it);
			}
			else
				it++;
		}
	}

	close(server.give_connexion_fd());

	return (0);
}
