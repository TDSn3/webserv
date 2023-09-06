/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _assign_socket_name.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:03:33 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/23 12:56:18 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

/* ************************************************************************** */
/*                                                                            */
/*   htonl()	: convertit un entier  non  signé (par exemple une adresse)	  */
/*				  en une représentation réseau.								  */
/*   htons()	: convertit un entier court non  signé (par exemple port)	  */
/*				  en une représentation réseau.								  */
/*                                                                            */
/* ************************************************************************** */
void	Server::_assign_socket_name(void)
{
	memset( (char *) &_address, 0, sizeof(_address) );
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY; 
	_address.sin_port = htons(static_cast<uint16_t>(port) );

	if (bind(_connexion_fd, (struct sockaddr *) &_address, sizeof(_address) ) < 0) 
	{
		this->~Server();
		my_perror_and_throw("bind failed", std::exception() );
	}
}
