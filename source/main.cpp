/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:58:01 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/02 16:12:26 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	int					server_fd;
	struct sockaddr_in	adress;
	const int			port = 8080;

	server_fd = creat_socket();
	if (server_fd < 0) 
		return (1);
	if (give_socket_name(&adress, port, server_fd)) 
		return (1);

	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		return (1);
	}

	std::cout << "Le serveur demarre sur le port " << port << std::endl;

	if (client_accept(server_fd) )
		return (1);

	return (0);
}

void	printSockAddrInInfo(const sockaddr_in &address)
{
	std::cout << "Address Family: " << address.sin_family << std::endl;
	std::cout << "Port: " << ntohs(address.sin_port) << std::endl;

	char ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(address.sin_addr), ip, INET_ADDRSTRLEN);
	std::cout << "IP Address: " << ip << std::endl;

	// Alternatively, you can use this to print the IP address in a more concise way:
	std::cout << "IP Address: " << inet_ntoa(address.sin_addr) << std::endl;
}
