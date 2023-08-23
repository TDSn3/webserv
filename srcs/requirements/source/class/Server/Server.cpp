/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:58:53 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/23 13:04:28 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

/* ************************************************************************** */
/*                                                                            */
/*   CONSTRUCTEUR															  */
/*                                                                            */
/*   Si une exception est levée dans le constructeur d'un objet,			  */
/*   son destructeur ne sera pas appelé,									  */
/*   car l'objet n'a pas été entièrement construit.							  */
/*                                                                            */
/* ************************************************************************** */
Server::Server(const int desired_port) : port(desired_port)
{
	creat_socket();									// Crée un socket pour ce connecter au serveur	// ! throw possible
	give_socket_name();								// Affecte un "nom" au socket crée				// ! throw possible

	if (listen(_connexion_fd, 3) < 0)				// Prépare le socket pour la connexion
	{
		this->~Server();
		perror("listen");
		throw (std::exception() );
	}

	if (fcntl(_connexion_fd, F_SETFL, O_NONBLOCK) )	// unique utilisation autorisé par le sujet
	{
		this->~Server();
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
