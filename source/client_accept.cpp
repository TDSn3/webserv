/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_accept.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:45 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/02 16:24:05 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

int	client_accept(int server_fd)
{
	int					communication_fd;	// socket de communication
	struct sockaddr_in	client_adress;
	socklen_t			client_adress_len;

	memset( (char *) &client_adress, 0, sizeof(client_adress) );
	client_adress_len = sizeof(client_adress);
	communication_fd = accept(server_fd, (struct sockaddr *) &client_adress, &client_adress_len);

	if (communication_fd < 0)
	{
		perror("accept");
		return (1);
	}

	char		buff[INET6_ADDRSTRLEN] = {0};
	std::string	client_address( inet_ntop(client_adress.sin_family, (void*)&(client_adress.sin_addr), buff, INET6_ADDRSTRLEN) );

	std::cout << "Connexion de " << client_address << std::endl;

	return (0);
}
