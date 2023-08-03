/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:58:36 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/03 17:05:21 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HPP
# define HEADER_HPP

# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <sys/time.h>
# include <sys/types.h>
# include <poll.h>
# include <sys/event.h>
# include <sys/socket.h>
# include <netdb.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <netinet/in.h>

# include <iostream>

# include "colors.hpp"

# include "class/Server.hpp"

int	client_accept(int server_fd);

#endif
