/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:57:10 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/07 09:23:35 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <sstream>

# include "HttpRequest.hpp"
# include "HttpResponse.hpp"

# define BUFFER_CLIENT_SIZE 4096

class Server;

class Client
{
	public:

										Client(void);
										Client(Server &server);	// ! throw possible

		int								set_non_blocking_fd(void);
		std::string						ip_to_string(void);
		void							buffer_clear(void);

		int								communication_fd;
		struct sockaddr_in				address;
		socklen_t						address_len;
		std::string						ipv4;
		in_port_t						port;
		char							buffer[BUFFER_CLIENT_SIZE];
		HttpRequest						request;
		HttpResponse					response;

	protected:

	private:

};

#endif
