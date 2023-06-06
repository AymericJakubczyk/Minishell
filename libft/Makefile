# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajakubcz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 14:37:15 by ajakubcz          #+#    #+#              #
#    Updated: 2023/04/04 15:03:21 by ajakubcz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = libft.a

SRCS = 		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	   		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c      \
	   		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c  \
	   		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c   \
	   		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c       \
	   		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c     \
	   		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

BONUS = 	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c 	\
			ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c  \
			ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

GNL =		get_next_line.c get_next_line_utils.c

FT_PRINTF = ft_printf.c ft_printf_utils.c ft_printf_utils2.c

OBJS = 			$(SRCS:.c=.o)
OBJSBONUS =		$(BONUS:.c=.o)
OBJSGNL = 		$(GNL:.c=.o)
OBJSFT_PRINTF = $(FT_PRINTF:.c=.o)

CC = gcc
CFLAGS = -Werror -Wextra -Wall
RM = rm -rf
HEADERS = libft.h get_next_line.h ft_printf.h

#$(NAME) : $(OBJS)
#	ar rcs $(NAME) $(OBJS)

all : $(NAME)

$(NAME) : $(OBJS) $(OBJSBONUS) $(OBJSGNL) $(OBJSFT_PRINTF)
	ar rcs $(NAME) $(OBJS) $(OBJSBONUS) $(OBJGNL) $(OBJSFT_PRINTF)

%.o : %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -I ./

clean :
	$(RM) $(OBJS) $(OBJSBONUS) $(OBJSGNL) $(OBJSFT_PRINTF)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
