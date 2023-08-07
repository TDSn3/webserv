/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:57:10 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/07 10:34:16 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

class Client;

class Server
{
	public:
	
		Server(const int port);
		Server(const Server &src);
		~Server(void);

		int					give_connexion_fd(void);

		const int			port;
		std::vector<Client>	clients;

	protected:

	private:

		int					creat_socket(void);
		int					give_socket_name(struct sockaddr_in *address, const int PORT, int server_fd);

		int					_connexion_fd;
		struct sockaddr_in	_address;

};

#endif
