/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_accept.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:45 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/07 09:25:09 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

int	client_accept(Server &server)
{
	std::cout << COLOR_GREEN << "\n+++++++ Waiting for new connection ++++++++\n" << COLOR_RESET << std::endl;

	while (1)
	{
		Client	new_client;
		
		new_client.communication_fd = accept(server.give_connexion_fd(), (struct sockaddr *) &new_client.adress, &new_client.adress_len);
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

			char		buff[INET6_ADDRSTRLEN] = {0};
			std::string	client_ip( inet_ntop(new_client.adress.sin_family, (void*)&(new_client.adress.sin_addr), buff, INET6_ADDRSTRLEN) );

			std::cout << "Connexion de " << COLOR_BOLD << client_ip << COLOR_DIM << ":" << new_client.adress.sin_port << COLOR_RESET << std::endl;
			server.clients.push_back(new_client);

			char	*hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
			char	buffer[3000] = {0};
		
			recv(new_client.communication_fd, buffer, sizeof(buffer), 0);
			std::cout << buffer << std::endl;
			write(new_client.communication_fd , hello , strlen(hello));
		}
		
		std::vector<Client> :: iterator it = server.clients.begin();
		
		while (it != server.clients.end() )
		{
			char	buffer[3000] = {0};
			ssize_t	ret;
			// bool	disconnect;

			// disconnect = false;
			ret = recv(it->communication_fd, buffer, sizeof(buffer), 0);
			if (ret == -1)
			{
				
			}
			// if (ret == 0)
			// 	disconnect = true;
			// else if (ret == -1 && errno == EWOULDBLOCK)
			// {
			// 	EWOULDBLOCK;
			// }
			it++;
		}
	}

	close(server.give_connexion_fd());

	return (0);
}
