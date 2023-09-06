/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:58:36 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/06 10:22:11 by tda-silv         ###   ########.fr       */
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

# include <string>
# include <iostream>
# include <sstream>
# include <fstream>
# include <vector>
# include <queue>
# include <map>
# include <exception>

# include "colors.hpp"
# include "enum.hpp"

# include "class/Server.hpp"
# include "class/Client.hpp"
# include "class/LogFile.hpp"
# include "class/HttpRequest.hpp"
# include "class/HttpResponse.hpp"
# include "class/StatusCode.hpp"

# define INDEX_FILE_NAME "card.html"
# define FAVICON_FILE_NAME "favicon.png"

extern volatile sig_atomic_t	siginit_status;

bool	check_arg(const int argc, const char * const *argv);
void	handler(int sig);
void	client_accept(Server &server);
rule	get_character_type(const char c);

#endif
