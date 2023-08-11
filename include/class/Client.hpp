/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:57:10 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/11 13:02:55 by tda-silv         ###   ########.fr       */
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

										Client(void);
										Client(Server &server);	// ! throw possible

		int								set_non_blocking_fd(void);
		std::string						ip_to_string(void);

		int								communication_fd;
		struct sockaddr_in				address;
		socklen_t						address_len;
		std::string						ipv4;
		in_port_t						port;
		pollfd							*poll_struct;
		std::vector<pollfd> :: iterator	it;

	protected:

	private:

};

#endif
