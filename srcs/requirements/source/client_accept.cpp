/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_accept.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:45 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/06 12:38:54 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

static void check_clients_poll_struct(Server &server);
static void data_received(std::vector<Client> :: iterator &it, ssize_t ret);

void	client_accept(Server &server)	// ! throw possible
{
	std::cout << COLOR_GREEN << "\n+++++++ Waiting for new connection ++++++++\n" << COLOR_RESET << std::endl;

	while (1)
	{
		int	ret;

		ret = poll(server.poll_struct.data(), static_cast<nfds_t>(server.poll_struct.size() ), 0);	// poll() vérifie l'état de chaque socket
		if (ret == -1)
			my_perror_and_throw("poll error", std::exception() );

		if (server.new_connexion() )
		{
			try
			{
				Client	new_client(server);	// ! throw possible
			}
			catch(const std::exception &e)
			{
				continue ;
			}
		}

		check_clients_poll_struct(server);
		if (siginit_status)
			break ;
	}
}

static void	check_clients_poll_struct(Server &server)
{
	std::vector<Client> :: iterator	it = server.clients.begin();

	while (it != server.clients.end() )
	{
		if (server.poll_struct[ it->index_vector_poll_struct ].revents & (POLLIN | POLLERR | POLLHUP) )
		{
			it->buffer_clear();
			
			ssize_t	ret;

			ret = recv(it->communication_fd, it->buffer, sizeof(it->buffer), 0);
			if (ret > 0)
				data_received(it, ret);
			else								// la connexion a été fermée par le client
			{
				std::cout << COLOR_RED << "Déconnexion de [" << it->ipv4 << ":" << it->port << "]" << COLOR_RESET << "\n" << std::endl;
				server.poll_struct.erase( server.poll_struct.begin() + static_cast<long>(it->index_vector_poll_struct) );
				it = server.clients.erase(it);	// supprime le Client de std::vector stockée dans Server
				continue ;
			}
		}
		if (server.poll_struct[ it->index_vector_poll_struct ].revents & POLLOUT && it->response.status() == true)
		{
			size_t	to_send =  it->response.str_response.size();
			ssize_t	sended;
			
			std::cout << "[" << COLOR_BOLD_GREEN << "RESPONSE" << COLOR_RESET << "]\n" << it->response.str_response << std::endl;
			std::cout << "[" << COLOR_BOLD_RED << "END OF RESPONSE" << COLOR_RESET << "]\n" << std::endl;
			sended = send(it->communication_fd , it->response.str_response.c_str() , to_send, 0);
			if (sended < static_cast<ssize_t>(to_send) )
			{
				std::cout << COLOR_BOLD_RED << "RESPONSE WAS NOT COMPLETELY SEND !" << std::endl;	// TODO: gerer cela
			}
			it->response.clear();
		}
		it++;
	}
}

static void	data_received(std::vector<Client> :: iterator &it, ssize_t ret)
{
	it->request.data += it->buffer;

	std::cout << COLOR_BOLD_RED << "BUFFER : " << ret << " / " << BUFFER_CLIENT_SIZE << COLOR_RESET << std::endl;
	std::cout << "[" << COLOR_BOLD << it->ipv4 << COLOR_BLUE << ":" << it->port << COLOR_RESET << "]\n" << it->request.data << std::endl;

	try
	{
		it->request.parsing();										// ! throw possible 
	}
	catch (const StatusCode &e)
	{
		it->response.clear();
		it->response.build_error(it->request, e.status_code);		// ! throw possible
		it->request.clear();
		return ;
	}
	if (it->request.request_status == true)
	{
		try
		{
			it->response.build(it->request);						// ! throw possible
		}
		catch (const StatusCode &e)
		{
			it->response.clear();
			it->response.build_error(it->request, e.status_code);	// ! throw possible
			it->request.clear();
			return ;
		}
	}
	it->request.clear();
}
