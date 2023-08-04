/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 08:57:10 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/04 15:32:18 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

class Server;

class Client
{
	public:

		Client(void)
		{
			memset( (char *) &adress, 0, sizeof(adress) );
			adress_len = sizeof(adress);
		}

		void	set_non_blocking_fd(void)
		{
			if (fcntl(communication_fd, F_SETFL, O_NONBLOCK) )	// unique utilisation autorisé par le sujet
			{
				perror("fcntl");
				throw (std::exception() );
			}			
		}

		int					communication_fd;
		struct sockaddr_in	adress;
		socklen_t			adress_len;

	protected:

	private:

};

#endif
