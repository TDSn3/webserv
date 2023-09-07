/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_accept.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:45 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/07 09:22:17 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

static void check_clients_poll_struct(Server &server, char **env);
static void data_received(std::vector<Client> :: iterator &it, ssize_t ret, char **env);

void	client_accept(Server &server, char **env)	// ! throw possible
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

		check_clients_poll_struct(server, env);
		if (siginit_status)
			break ;
	}
}

static void	check_clients_poll_struct(Server &server, char **env)
{
	std::vector<Client> :: iterator	it = server.clients.begin();
	ssize_t							index_check;
	size_t							index;

	while (it != server.clients.end() )
	{
		index_check = give_index_fd_in_poll_struct(server.poll_struct, it->communication_fd);
		if (index_check == -1)
		{
			std::cout << COLOR_BOLD_MAGENTA << "STRANGE !" << COLOR_RESET << std::endl;	// TODO: à supprimer à la fin
			continue ;
		}
		index = static_cast<size_t>(index_check);

		if (server.poll_struct[ index ].revents & (POLLIN | POLLERR | POLLHUP) )
		{
			it->buffer_clear();
			
			ssize_t	ret;

			ret = recv(it->communication_fd, it->buffer, sizeof(it->buffer), 0);
			if (ret > 0)
				data_received(it, ret, env);
			else								// la connexion a été fermée par le client
			{
				std::cout << COLOR_RED << "Déconnexion de [" << it->ipv4 << ":" << it->port << "]" << COLOR_RESET << "\n" << std::endl;
				server.poll_struct.erase( server.poll_struct.begin() + static_cast<long>( index ) );
				it = server.clients.erase(it);	// supprime le Client de std::vector stockée dans Server
				continue ;
			}
		}
		if (server.poll_struct[ index ].revents & POLLOUT && it->response.status() == true)
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

static void	data_received(std::vector<Client> :: iterator &it, ssize_t ret, char **env)
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
			it->response.build(it->request, env);						// ! throw possible
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
