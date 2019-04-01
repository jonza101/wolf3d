# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/11 19:33:51 by zjeyne-l          #+#    #+#              #
#    Updated: 2019/04/01 20:00:56 by zjeyne-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c draw.c ray.c slider.c read.c gnl/libft/libft.a

all :
	gcc $(SRC) -lm -lpthread -lmlx -lXext -lX11 -L minilibx/ -I minilibx/