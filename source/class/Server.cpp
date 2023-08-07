/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:58:53 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/07 10:35:00 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

/* ************************************************************************** */
/*                                                                            */
/*   CONSTRUCTEUR															  */
/*                                                                            */
/* ************************************************************************** */
Server::Server(const int port) : port(port)
{
	_connexion_fd = creat_socket();							// Crée un socket pour ce connecter au serveur
	if (_connexion_fd < 0) 
		throw (std::exception() );

	if (give_socket_name(&_address, port, _connexion_fd))	// Affecte un "nom" au socket crée
		throw (std::exception() );

	if (listen(_connexion_fd, 3) < 0)						// Prépare le socket pour la connexion
	{
		perror("listen");
		throw (std::exception() );
	}

	if (fcntl(_connexion_fd, F_SETFL, O_NONBLOCK) )			// unique utilisation autorisé par le sujet
	{
		perror("fcntl");
		throw (std::exception() );
	}
}

/*   COPY CONSTRUCTEUR   **************************************************** */

Server::Server(const Server &src) : port(src.port)
{
	(void) src;
}

/* ************************************************************************** */
/*                                                                            */
/*   DESTRUCTEUR															  */
/*                                                                            */
/* ************************************************************************** */
Server::~Server(void)
{
	for (std::vector<Client> :: iterator it = clients.begin(); it != clients.end(); it++)
		close(it->communication_fd);
	close(_connexion_fd);
}

/* ************************************************************************** */
/*                                                                            */
/*   OPÉRATEUR																  */
/*                                                                            */
/* ************************************************************************** */

/*   OPÉRATEUR INTERNE   **************************************************** */

/*   OPÉRATEUR EXTERNE   **************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*   MÉTHODE																  */
/*                                                                            */
/* ************************************************************************** */

/*   MÉTHODE PUBLIC   ******************************************************* */

int	Server::give_connexion_fd(void)
{
	return (_connexion_fd);
}

/*   MÉTHODE PRIVATE   ****************************************************** */

/* ************************************************************************** */
