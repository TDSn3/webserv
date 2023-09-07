/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   give_index_fd_in_poll_struct.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 09:12:55 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/07 09:13:08 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

ssize_t	give_index_fd_in_poll_struct(std::vector<pollfd> &poll_struct, int fd)
{
	size_t	i;

	i = 0;
	while (i < poll_struct.size() )
	{
		if (poll_struct[i].fd == fd)
			return (static_cast<ssize_t>(i) );
		i++;
	}
	return (-1);
}
