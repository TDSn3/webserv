/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:57:10 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/03 17:13:49 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

class Server
{
	public:
	
		Server(void);			
		Server(const int port);
		Server(const Server &src);
		~Server(void);

		int					give_fd(void);

		const int			port;

	protected:

	private:

		int					creat_socket(void);
		int					give_socket_name(struct sockaddr_in *adress, const int PORT, int server_fd);

		int					_fd;		// socket de connexion
		struct sockaddr_in	_adress;

};

#endif
