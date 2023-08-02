/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_and_wait_accept.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:45 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/02 14:25:58 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

int	listen_and_wait_accept(int server_fd)
{
	int					connexion_fd;
	struct sockaddr_in	client_adress;
	socklen_t			client_adress_len;

	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		return (1);
	}

	memset( (char *)&client_adress, 0, sizeof(client_adress) );
	client_adress_len = sizeof(client_adress);
	connexion_fd = accept(server_fd, (struct sockaddr *)&client_adress, &client_adress_len);

	if (connexion_fd < 0)
	{
		perror("accept");
		return (1);
	}

	return (0);
}
