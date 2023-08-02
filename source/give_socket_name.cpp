/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   give_socket_name.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:03:33 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/02 14:26:02 by tda-silv         ###   ########.fr       */
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
int	give_socket_name(struct sockaddr_in *adress, const int PORT, int server_fd)
{
	memset( (char *)adress, 0, sizeof(*adress) );
	adress->sin_family = AF_INET;
	adress->sin_addr.s_addr = htonl(INADDR_ANY); 
	adress->sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr *) adress, sizeof(*adress) ) < 0) 
	{
		perror("bind failed"); 
		return (1);
	}

	return (0);
}
