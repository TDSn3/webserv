/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   give_socket_name.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:03:33 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/07 10:34:33 by tda-silv         ###   ########.fr       */
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
int	Server::give_socket_name(struct sockaddr_in *address, const int PORT, int server_fd)
{
	memset( (char *) address, 0, sizeof(*address) );
	address->sin_family = AF_INET;
	address->sin_addr.s_addr = INADDR_ANY; 
	address->sin_port = htons(static_cast<uint16_t>(PORT) );

	if (bind(server_fd, (struct sockaddr *) address, sizeof(*address) ) < 0) 
	{
		perror("bind failed"); 
		return (1);
	}

	return (0);
}
