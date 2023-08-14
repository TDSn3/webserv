# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 16:32:49 by tda-silv          #+#    #+#              #
#    Updated: 2023/08/14 16:35:14 by tda-silv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@docker-compose -f ./srcs/docker-compose.yml up -d --build

ps:
	docker image ls
	@echo ""
	docker ps
	@echo ""
	docker volume ls	

start:
	@docker-compose -f ./srcs/docker-compose.yml start

stop: 
	@docker-compose -f ./srcs/docker-compose.yml stop

down: 
	@docker-compose -f ./srcs/docker-compose.yml down

clean:
	@docker-compose -f ./srcs/docker-compose.yml kill
	@echo ""
	@docker system prune -a -f
	@if [ $$(docker volume ls -q | wc -l) -gt 0 ]; then	\
		docker volume rm $$(docker volume ls -q);		\
	fi

re: clean all

#-----------------------#

.PHONY: all ps start stop down clean re
