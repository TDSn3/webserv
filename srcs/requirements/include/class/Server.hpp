/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:57:10 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/14 16:49:31 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

class Client;

class Server
{
	public:
	
							Server(const int desired_port);		// ! throw possible
							~Server(void);

		int					give_connexion_fd(void);
		bool				new_connexion(void);
		pollfd				*add_fd_poll_struct(int fd, short events);

		const int			port;
		std::vector<Client>	clients;
		std::vector<pollfd>	poll_struct;

	protected:

	private:

		int					creat_socket(void);
		void				give_socket_name(void);

		int					_connexion_fd;
		struct sockaddr_in	_address;

};

#endif
