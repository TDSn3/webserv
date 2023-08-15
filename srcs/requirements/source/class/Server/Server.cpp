/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:58:53 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/15 15:16:56 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

/* ************************************************************************** */
/*                                                                            */
/*   CONSTRUCTEUR															  */
/*                                                                            */
/* ************************************************************************** */
Server::Server(const int desired_port) : port(desired_port)
{
	_connexion_fd = creat_socket();					// Crée un socket pour ce connecter au serveur	// ! throw possible
	give_socket_name();								// Affecte un "nom" au socket crée				// ! throw possible

	if (listen(_connexion_fd, 3) < 0)				// Prépare le socket pour la connexion
	{
		perror("listen");
		throw (std::exception() );
	}

	if (fcntl(_connexion_fd, F_SETFL, O_NONBLOCK) )	// unique utilisation autorisé par le sujet
	{
		perror("fcntl");
		throw (std::exception() );
	}

	add_fd_poll_struct(_connexion_fd, POLLIN);		// ajoute le socket à la struct de poll
}

/*   COPY CONSTRUCTEUR   **************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*   DESTRUCTEUR															  */
/*                                                                            */
/* ************************************************************************** */
Server::~Server(void)
{
	for (std::vector<Client> :: iterator it = clients.begin(); it != clients.end(); it++)
	{
		close(it->communication_fd);
		std::cout << "Server: Client: close: " << it->communication_fd << std::endl;
	}
	close(_connexion_fd);
	std::cout << "Server: close: " << _connexion_fd << std::endl;
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

int		Server::give_connexion_fd(void)
{
	return (_connexion_fd);
}

bool	Server::new_connexion(void)
{
	return (poll_struct[0].revents & POLLIN);
}

/*   MÉTHODE PRIVATE   ****************************************************** */

/* ************************************************************************** */
