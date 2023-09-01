/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:58:36 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/01 20:10:19 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HPP
# define HEADER_HPP

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <sys/time.h>
# include <sys/types.h>
# include <poll.h>
# include <sys/socket.h>
# include <netdb.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <netinet/in.h>

# include <iostream>
# include <fstream>
# include <vector>
# include <queue>

# include "colors.hpp"
# include "enum.hpp"

# include "class/Server.hpp"
# include "class/Client.hpp"
# include "class/LogFile.hpp"
# include "class/HttpRequest.hpp"
# include "class/HttpResponse.hpp"

# define INDEX_FILE_NAME "card.html"
# define FAVICON_FILE_NAME "favicon.png"

extern volatile sig_atomic_t	siginit_status;

void	client_accept(Server &server);
void	handler(int sig);

#endif
