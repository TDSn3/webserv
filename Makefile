# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/30 09:01:22 by tda-silv          #+#    #+#              #
#    Updated: 2023/08/03 09:49:15 by tda-silv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= webserv

SRC_DIR		= source/
OBJ_DIR		= object/
INC_DIR		= include/

CC			= c++

CFLAGS		= -Wall -Wextra -Wshadow -Wconversion -std=c++98

# **************************************************************************** #
#                                                                              #
#   -I   | Chemin du dossier où trouver un .h								   #
#   -L   | Chemin du dossier où trouver un .a								   #
#   -l   | Nom du .a sans le préfixe "lib"									   #
#                                                                              #
# **************************************************************************** #

I_HEADER	= -I $(INC_DIR)

HEADER		= $(shell find include/ -type f)

SEARCH_FILE	= $(shell find $(SRC_DIR) -name "*.cpp")
NAME_FILE	= $(SEARCH_FILE:$(SRC_DIR)/%.cpp=%)

SRC			= $(addsuffix .cpp, $(addprefix $(SRC_DIR), $(NAME_FILE)))
OBJ			= $(addsuffix .o, $(addprefix $(OBJ_DIR), $(NAME_FILE)))
DEPENDS		= $(addsuffix .d, $(addprefix $(OBJ_DIR), $(NAME_FILE)))

# **************************************************************************** #
#                                                                              #
#   $@   | Le nom de la cible												   #
#   $<   | Le nom de la première dépendance									   #
#   $^   | La liste des dépendances											   #
#   $?   | La liste des dépendances plus récentes que la cible				   #
#   $*   | Le nom du fichier sans suffixe									   #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#   Relink si les headers ou le Makfile sont changés                           #
#                                                                              #
# *****************************vvvvvvvvvvvvvvvvvv***************************** #

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(HEADER) Makefile
	@ mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(I_HEADER) -MMD -MP -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(I_HEADER) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPENDS)

.PHONY: all clean fclean re
