# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabra <sabra@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/29 17:35:52 by sabra             #+#    #+#              #
#    Updated: 2021/01/08 14:21:20 by sabra            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minirt

SRCS		= srcs/main.c \
		  srcs/pars_start.c \
		  srcs/pars_objects.c \

OBJS		= $(SRCS:.c=.o)

MINILIBX_DIR 	= minilibx-linux/
CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror
LIBFT_DIR	= ./libft/libft/
LIBS		= -L$(LIBFT_DIR) -lft -L$(MINILIBX_DIR) -lmlx -L/usr/lib -lX11 -lXext -lm
LIBS_MAC	= -L$(LIBFT_DIR) -lft -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
INCLUDES = -I./includes

all:		$(NAME)

$(NAME):	$(OBJS)
	make -C ./libft/libft
	$(CC) $(OBJS) $(LIBS) -o $(NAME) # Linux
	#$(CC) $(OBJS) $(LIBS_MAC) -o $(NAME)	# macOS
%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Iminlibx-linux -O3 -c $< -o $@ # Linux
	#$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@	# macOS

clean:
			$(RM) $(OBJS)
			make fclean -C ./libft/libft

fclean:		clean
			$(RM) $(NAME)
			make fclean -C ./libft/libft

re:			fclean $(NAME)

