/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _creat_socket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:48:34 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/23 12:56:34 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

/* ************************************************************************** */
/*                                                                            */
/*   AF_INET		: IPv4.													  */
/*   SOCK_STREAM	: flux d'octets full-duplex.							  */
/*                                                                            */
/* ************************************************************************** */
void	Server::_creat_socket(void)
{
	_connexion_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_connexion_fd < 0) 
	{
		this->~Server();
		my_perror_and_throw("cannot create socket", std::exception() );
	}
}
