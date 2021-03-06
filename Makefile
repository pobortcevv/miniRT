# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabra <sabra@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/29 17:35:52 by sabra             #+#    #+#              #
#    Updated: 2021/02/25 16:10:03 by sabra            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

SRCS		= srcs/main.c \
		  srcs/pars_start.c \
		  srcs/pars_objects.c \
		  srcs/parser_checks.c \
		  srcs/render.c \
		  srcs/plane.c \
		  srcs/square.c \
		  srcs/triangle.c \
		  srcs/vector.c \
		  srcs/vector2.c \
		  srcs/colors.c \
		  srcs/colors2.c \
		  srcs/lists_utils.c \
		  srcs/intersect_objects.c \
		  srcs/cylinder.c \
		  srcs/camera.c \
		  srcs/sphere.c \
		  srcs/math.c \
		  srcs/matrix.c \
		  srcs/hooks.c \
		  srcs/events.c \
		  srcs/create_bmp.c \
		  srcs/normal_exit.c \
		  srcs/cam_to_world.c \


OBJS		= $(SRCS:.c=.o)

.SILENT: $(NAME) clean fclean re

MINILIBX_DIR 	= minilibx-linux/
CC			= gcc 
RM			= rm -f
CFLAGS		= -Wall -Wextra -g -ggdb3
LIBFT_DIR	= ./libft/libft/
LIBS		= -L$(LIBFT_DIR) -lft -L$(MINILIBX_DIR) -lmlx -L/usr/lib -lX11 -lXext -lm
LIBS_MAC	= -L$(LIBFT_DIR) -lft -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit 
INCLUDES = -I./includes

all:		
	$(MAKE) $(NAME) -j4

$(NAME):	$(OBJS)
	make bonus -j4 -C ./libft/libft
	#$(CC) $(OBJS) $(LIBS) -o $(NAME) # Linux
	$(CC) $(OBJS) $(LIBS_MAC) -o $(NAME)	# macOS
	echo miniRT compiled!

%.o: %.c
	@#$(CC) $(CFLAGS) -I/usr/include -Iminlibx-linux -O3 -c $< -o $@ # Linux
	@$(CC) $(CFLAGS)  -Imlx -c $< -o $@	# macOS

clean:
			$(RM) $(OBJS)
			make clean -C ./libft/libft
			echo clean .o files

fclean:		clean
			$(RM) $(NAME)
			make fclean -C ./libft/libft
			echo miniRT deleted :\(

re:			fclean $(NAME)

