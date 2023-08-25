/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:58:53 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/25 10:03:35 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

/* ************************************************************************** */
/*                                                                            */
/*   CONSTRUCTEUR															  */
/*                                                                            */
/* ************************************************************************** */
Client::Client(void)
{
	buffer_clear();
	memset( (char *) &address, 0, sizeof(address) );
	address_len = sizeof(address);
	index_vector_poll_struct = 0;
}

Client::Client(Server &server)
{
	buffer_clear();
	memset( (char *) &address, 0, sizeof(address) );
	address_len = sizeof(address);

	communication_fd = accept(server.give_connexion_fd(), (struct sockaddr *) &address, &address_len);

	if (communication_fd != 1)				// si une nouvelle connexion est arrivée et donc qu'il y a un client a créer
	{
		set_non_blocking_fd();				// ! throw possible
		ipv4 = ip_to_string();
		port = address.sin_port;
		server.add_fd_poll_struct(communication_fd, POLLIN);
		index_vector_poll_struct =  server.poll_struct.size();
		if (index_vector_poll_struct > 1)	// [0] doit toujours être déjà attribué
			index_vector_poll_struct--;
		else
		{
			close(communication_fd);
			perror("poll_struct size");
			throw (std::exception() );
		}
		server.clients.push_back(*this);

		std::cout << "Connexion de " << COLOR_BOLD << ipv4 << COLOR_BLUE << ":" << port << COLOR_RESET << "\n" << std::endl;
	}
}

/*   COPY CONSTRUCTEUR   **************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*   DESTRUCTEUR															  */
/*                                                                            */
/* ************************************************************************** */

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

int			Client::set_non_blocking_fd(void)
{
	if (fcntl(communication_fd, F_SETFL, O_NONBLOCK) )	// unique utilisation autorisé par le sujet
	{
		close(communication_fd);
		perror("fcntl");
		throw (std::exception() );
		return (1);
	}
	return (0);
}

std::string	Client::ip_to_string(void)
{
	std::stringstream	ss;
	ss << static_cast<int>(address.sin_addr.s_addr & 0xFF) << '.'
		<< static_cast<int>( (address.sin_addr.s_addr >> 8) & 0xFF) << '.'
		<< static_cast<int>( (address.sin_addr.s_addr >> 16) & 0xFF) << '.'
		<< static_cast<int>( (address.sin_addr.s_addr >> 24) & 0xFF);

	return (ss.str() );
}

void	Client::buffer_clear(void)
{
	memset(buffer, 0, sizeof(buffer) );
}

/*   MÉTHODE PRIVATE   ****************************************************** */

/* ************************************************************************** */
