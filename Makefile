# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/20 19:19:20 by ccoste            #+#    #+#              #
#    Updated: 2023/04/26 23:41:35 by ccoste           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror
RM 		= rm -rf

SRC_PATH = sources/
OBJ_PATH = objet_o/

SRC = ft_split.c \
	ft_strdup.c \
	ft_strjoi.c \
	ft_strncmp.c \
	pipex.c \
	ft_strlen.c \
	error.c

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))
INCS = -I ./includes/

all : $(OBJ_PATH) $(NAME)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -g -c $< -o $@ $(INCS)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

clean :
	@$(RM) $(OBJ_PATH)
	@echo -e "$(YELLOW)object files deleted!$(DEFAULT)"

fclean : clean
	@$(RM) $(NAME)
	@echo -e "$(RED)all deleted!$(DEFAULT)"

re : fclean all

.PHONY : all clean fclean re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m