/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_socket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:48:34 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/10 10:25:17 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

/* ************************************************************************** */
/*                                                                            */
/*   AF_INET		: IPv4.													  */
/*   SOCK_STREAM	: flux d'octets full-duplex.							  */
/*                                                                            */
/* ************************************************************************** */
int	Server::creat_socket(void)
{
	int	server_fd;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0) 
	{
		perror("cannot create socket");
		throw (std::exception() );
	}

	return (server_fd);
}
