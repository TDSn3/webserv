/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:58:01 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/02 14:26:28 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	int					server_fd;
	struct sockaddr_in	adress;
	const int			PORT = 8080;

	server_fd = creat_socket();
	if (server_fd < 0) 
		return (1);
	if (give_socket_name(&adress, PORT, server_fd)) 
		return (1);
	if (listen_and_wait_accept(server_fd))
		return (1);

	return (0);
}
