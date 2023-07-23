# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 14:11:17 by ajakubcz          #+#    #+#              #
#    Updated: 2023/07/23 02:03:20 by cprojean         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# .SILENT :

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g3

LIB = libft/libft.a

RM = $(RM) -f

HEADERS =	$(DIR_INCLUDES)minishell.h \
			$(DIR_INCLUDES)error.h \
			$(DIR_INCLUDES)collector.h \
			$(DIR_INCLUDES)builtins.h \
			$(DIR_INCLUDES)parsing.h \

MKDIR = mkdir -p

RM = rm -rf

DIR_OBJ = ./.obj/

DIR_SRCS = srcs/

DIR_PARSING = $(DIR_SRCS)parsing/

DIR_BUILTINS = $(DIR_SRCS)builtins/

DIR_COLLECTOR = $(DIR_SRCS)collector/

DIR_EXEC = $(DIR_SRCS)exec/

DIR_EXEC_WITH_FORK = $(DIR_EXEC)with_fork/

DIR_INCLUDES = ./inc/

SRCS =			$(DIR_SRCS)main.c \
				$(DIR_PARSING)parse_and_exec.c \
				$(DIR_PARSING)parse_errors.c \
				$(DIR_PARSING)next_parse_errors.c \
				$(DIR_PARSING)get_prompt.c \
				$(DIR_PARSING)ft_error.c \
				$(DIR_PARSING)check_syntax.c \
				$(DIR_PARSING)first_parse.c \
				$(DIR_PARSING)second_parse.c \
				$(DIR_PARSING)parse_utils.c \
				$(DIR_PARSING)expand.c \
				$(DIR_PARSING)get_expand_size.c \
				$(DIR_PARSING)fill_expand.c \
				$(DIR_PARSING)expand_utils.c \
				$(DIR_PARSING)utils.c \
				$(DIR_PARSING)print.c \
				$(DIR_BUILTINS)builtins.c \
				$(DIR_BUILTINS)export.c \
				$(DIR_BUILTINS)export_utils.c \
				$(DIR_BUILTINS)export_utils2.c \
				$(DIR_BUILTINS)unset.c \
				$(DIR_BUILTINS)ft_exit.c \
				$(DIR_BUILTINS)ft_getenv.c \
				$(DIR_BUILTINS)builtins_utils.c \
				$(DIR_BUILTINS)ft_atoll.c \
				$(DIR_COLLECTOR)ft_garb_addback.c \
				$(DIR_COLLECTOR)ft_garb_clear.c \
				$(DIR_COLLECTOR)ft_garb_last.c \
				$(DIR_COLLECTOR)ft_garb_new.c \
				$(DIR_EXEC)start_exec.c \
				$(DIR_EXEC)exec_utils.c \
				$(DIR_EXEC)execution.c \
				$(DIR_EXEC)do_heredoc.c \
				$(DIR_EXEC)expand_heredoc.c \
				$(DIR_EXEC)heredoc_utils.c \
				$(DIR_EXEC)single_cmd.c \
				$(DIR_EXEC)single_cmd_utils.c \
				$(DIR_EXEC)check_redirect.c \
				$(DIR_EXEC_WITH_FORK)exec_with_forks.c \
				$(DIR_EXEC_WITH_FORK)do_redirect.c \
				$(DIR_EXEC_WITH_FORK)exec_fork_utils.c \

OBJS =			$(patsubst %.c, $(DIR_OBJ)%.o, $(SRCS))

all :			makelib $(NAME)

$(DIR_OBJ)%.o: %.c $(LIB) $(HEADERS)
				@mkdir -p $(shell dirname $@)
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