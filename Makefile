# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccoste <ccoste@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/20 19:19:20 by ccoste            #+#    #+#              #
#    Updated: 2023/04/29 13:26:48 by ccoste           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex
CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror
RM 				= rm -rf

HEADER_SRCS 	= pipex.h
HEADER_DIR 		= includes/
HEADER 			= $(addprefix $(HEADER_DIR), $(HEADER_SRCS))

SPATH_SRCS 		= error.c
				free.c \
				pipex.c
SPATH_DIR 		= sources/
SPATH 			= $(addprefix $(SPATH_DIR), $(SPATH_SRCS))
OBJ_M 			= $(SPATH:.c=.o)

FUNC_SRCS 		= ft_split.c \
				ft_strdup.c \
				ft_strjoi.c \
				ft_strncmp.c \
				ft_strlen.c
FUNC_DIR 		= functions/
FUNC 			= $(addprefix $(FUNC_DIR), $(FUNC_SRCS))
OBJ_F 			= $(FUNC:.c=.o)

O_PATH 			= objet_o/
OBJS	 		= $(addprefix $(O_PATH), $(OBJ_M), $(OBJ_F))
TOTAL_C 		= $(addprefix $(SPATH_DIR), $(FUNC_DIR))

$(O_PATH):
				mkdir $(O_PATH)

all : 			$(O_PATH) $(NAME)

$(O_PATH)%.o : 	$(TOTAL_C)%.c
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : 		$(OBJ_F) $(OBJ_M)
				$(CC) $(FLAGS) $(OBJ_M) $(OBJ_F) -o $(NAME)
				@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

clean :
				@$(RM) $(O_PATH)
				@$(RM) $(OBJ_M)
				@$(RM) $(OBJ_F)
				@echo -e "$(YELLOW)object files deleted!$(DEFAULT)"

fclean : 		clean
				@$(RM) $(NAME)
				@echo -e "$(RED)all deleted!$(DEFAULT)"

re : 			fclean all

.PHONY : 		all clean fclean re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m