/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:57:10 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/09 09:02:55 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <sstream>

class Server;

class Client
{
	public:

		Client(void)
		{
			memset( (char *) &address, 0, sizeof(address) );
			address_len = sizeof(address);
			poll_struct = NULL;
		}

		void	set_non_blocking_fd(void)
		{
			if (fcntl(communication_fd, F_SETFL, O_NONBLOCK) )	// unique utilisation autorisé par le sujet
			{
				perror("fcntl");
				throw (std::exception() );
			}			
		}

		std::string	ip_to_string(void)
		{
			std::stringstream	ss;
			ss << static_cast<int>(address.sin_addr.s_addr & 0xFF) << '.'
				<< static_cast<int>( (address.sin_addr.s_addr >> 8) & 0xFF) << '.'
				<< static_cast<int>( (address.sin_addr.s_addr >> 16) & 0xFF) << '.'
				<< static_cast<int>( (address.sin_addr.s_addr >> 24) & 0xFF);

			//char		buff[INET6_ADDRSTRLEN] = {0};
			//std::string	str( inet_ntop(address.sin_family, (void*) &(address.sin_addr), buff, INET6_ADDRSTRLEN) );

			//return (str);

			return (ss.str() );
		}

		int					communication_fd;
		struct sockaddr_in	address;
		socklen_t			address_len;
		std::string			ipv4;
		in_port_t			port;
		pollfd				*poll_struct;

	protected:

	private:

};

#endif
