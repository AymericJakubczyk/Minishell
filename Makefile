# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 14:11:17 by ajakubcz          #+#    #+#              #
#    Updated: 2023/06/11 18:48:49 by cprojean         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -g3 #Werror

LIB = libft/libft.a

RM = $(RM) -f

HEADERS = $(DIR_INCLUDES)minishell.h $(DIR_INCLUDES)error.h

MKDIR = mkdir -p

RM = rm -rf

DIR_OBJ = ./.obj/

DIR_SRCS = ./srcs/

DIR_INCLUDES = ./inc/

SRCS =			$(DIR_SRCS)main.c \
				$(DIR_SRCS)parse_and_exec.c \
				$(DIR_SRCS)parse_errors.c \
				$(DIR_SRCS)next_parse_errors.c \
				$(DIR_SRCS)get_prompt.c \
				$(DIR_SRCS)ft_error.c \
				$(DIR_SRCS)check_syntax.c \
				$(DIR_SRCS)first_parse.c \
				$(DIR_SRCS)second_parse.c \
				$(DIR_SRCS)parse_utils.c \
				$(DIR_SRCS)utils.c \
				$(DIR_SRCS)print.c \

OBJS = $(SRCS:$(DIR_SRCS)%.c=$(DIR_OBJ)%.o)

all :			makelib $(NAME)

$(DIR_OBJ):
				mkdir $@

$(DIR_OBJ)%.o: $(DIR_SRCS)%.c $(LIB) $(HEADERS) | $(DIR_OBJ)
				$(CC) $(CFLAGS) -I inc -c $< -o $@

$(NAME) :		$(LIB) $(OBJS)
				$(CC) $(OBJS) -o $(NAME) -L./libft -lft -lreadline

makelib:
				$(MAKE) -C libft

clean :
				$(MAKE) clean -C libft
				$(RM) $(OBJS)

fclean :		clean
				$(MAKE) fclean -C libft
				@$(RM) $(DIR_OBJ)
				$(RM) $(NAME)

re :			fclean all

rebonus :		fclean bonus
