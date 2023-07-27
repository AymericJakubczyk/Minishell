# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cprojean <cprojean@42lyon.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 14:11:17 by ajakubcz          #+#    #+#              #
#    Updated: 2023/07/27 15:32:34 by cprojean         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


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
				$(DIR_PARSING)go_to_end_block.c \
				$(DIR_BUILTINS)builtins.c \
				$(DIR_BUILTINS)export.c \
				$(DIR_BUILTINS)export_utils.c \
				$(DIR_BUILTINS)export_utils2.c \
				$(DIR_BUILTINS)unset.c \
				$(DIR_BUILTINS)ft_exit.c \
				$(DIR_BUILTINS)ft_exit_utils.c \
				$(DIR_BUILTINS)ft_cd.c \
				$(DIR_BUILTINS)ft_getenv.c \
				$(DIR_BUILTINS)builtins_utils.c \
				$(DIR_BUILTINS)ft_atoll.c \
				$(DIR_COLLECTOR)ft_garb_addback.c \
				$(DIR_COLLECTOR)ft_garb_clear.c \
				$(DIR_COLLECTOR)ft_garb_last.c \
				$(DIR_COLLECTOR)ft_garb_new.c \
				$(DIR_EXEC)execution.c \
				$(DIR_EXEC)get_path_utils.c \
				$(DIR_EXEC)exec_utils.c \
				$(DIR_EXEC)heredoc/do_heredoc.c \
				$(DIR_EXEC)heredoc/get_heredoc.c \
				$(DIR_EXEC)heredoc/expand_heredoc.c \
				$(DIR_EXEC)heredoc/heredoc_utils.c \
				$(DIR_EXEC)single_cmd/single_cmd.c \
				$(DIR_EXEC)single_cmd/single_cmd_utils.c \
				$(DIR_EXEC)single_cmd/start_exec.c \
				$(DIR_EXEC)mult_cmd/exec_with_forks.c \
				$(DIR_EXEC)mult_cmd/exec_cmd.c \
				$(DIR_EXEC)mult_cmd/exec_fork_utils.c \
				$(DIR_EXEC)redirections/do_redirect.c \
				$(DIR_EXEC)redirections/check_redirect.c \
				$(DIR_EXEC)redirections/expand_redirect.c \
				$(DIR_EXEC)redirections/size_expand_redir.c \
				$(DIR_EXEC)redirections/fill_expanded_redir.c \
				$(DIR_EXEC)redirections/redirect_utils.c \
				$(DIR_EXEC)signals/signals.c \

OBJS =			$(patsubst %.c, $(DIR_OBJ)%.o, $(SRCS))

all :			makelib $(NAME)

$(DIR_OBJ)%.o: %.c $(LIB) $(HEADERS)
				@mkdir -p $(shell dirname $@)
				$(CC) $(CFLAGS) -I inc -c $< -o $@

$(NAME) :		$(LIB) $(OBJS)
				$(CC) $(OBJS) -o $(NAME) -L./libft -lft -lreadline -fsanitize=address

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
