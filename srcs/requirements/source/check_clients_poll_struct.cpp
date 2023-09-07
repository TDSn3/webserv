/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_clients_poll_struct.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:06:11 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/07 12:49:12 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

static void data_received(std::vector<Client> :: iterator &it, ssize_t ret, char **env);
static bool give_and_check_index(std::vector<Client> :: iterator &it, Server &server, size_t &index);
static bool rec_data_or_del_client(std::vector<Client> :: iterator &it, Server &server, char **env, size_t index);
static void send_data(std::vector<Client> :: iterator &it);

void	check_clients_poll_struct(Server &server, char **env)
{
	std::vector<Client> :: iterator	it = server.clients.begin();
	size_t							index;

	while (it != server.clients.end() )
	{
		if (give_and_check_index(it, server, index) == false)
			continue ;

		if (server.poll_struct[ index ].revents & (POLLIN | POLLERR | POLLHUP) )
			if (rec_data_or_del_client(it, server, env, index) == false)
				continue ;

		if (server.poll_struct[ index ].revents & POLLOUT && it->response.status() == true)
			send_data(it);

		it++;
	}
}

static bool	give_and_check_index(std::vector<Client> :: iterator &it, Server &server, size_t &index)
{
	ssize_t	index_check;
	
	index_check = give_index_fd_in_poll_struct(server.poll_struct, it->communication_fd);
	if (index_check == -1)
	{
		std::cout << COLOR_BOLD_MAGENTA << "STRANGE !" << COLOR_RESET << std::endl;	// TODO: à supprimer à la fin
		return (false);
	}
	index = static_cast<size_t>(index_check);
	return (true);
}

static bool	rec_data_or_del_client(std::vector<Client> :: iterator &it, Server &server, char **env, size_t index)
{
	ssize_t	ret;
	
	it->buffer_clear();
	ret = recv(it->communication_fd, it->buffer, sizeof(it->buffer), 0);
	if (ret > 0)
		data_received(it, ret, env);
	else								// la connexion a été fermée par le client
	{
		std::cout << COLOR_RED << "Déconnexion de [" << it->ipv4 << ":" << it->port << "]" << COLOR_RESET << "\n" << std::endl;
		server.poll_struct.erase( server.poll_struct.begin() + static_cast<long>( index ) );
		it = server.clients.erase(it);	// supprime le Client de std::vector stockée dans Server
		return (false);
	}
	return (true);
}

static void	data_received(std::vector<Client> :: iterator &it, ssize_t ret, char **env)
{
	it->request.data += it->buffer;

	std::cout << COLOR_BOLD_RED << "BUFFER : " << ret << " / " << BUFFER_CLIENT_SIZE << COLOR_RESET << std::endl;
	std::cout << "[" << COLOR_BOLD << it->ipv4 << COLOR_BLUE << ":" << it->port << COLOR_RESET << "]\n" << it->request.data << std::endl;

	try
	{
		it->request.parsing();
	}
	catch (const StatusCode &e)
	{
		e.build_response_error(it);
		return ;
	}

	if (it->request.request_status == true)	// toute la request a été reçue
	{
		try
		{
			it->response.build(it->request, env);
		}
		catch (const StatusCode &e)
		{
			e.build_response_error(it);
			return ;
		}
	}

	it->request.clear();
}

static void	send_data(std::vector<Client> :: iterator &it)
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
