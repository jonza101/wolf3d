# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/11 19:33:51 by zjeyne-l          #+#    #+#              #
#    Updated: 2019/07/02 19:34:10 by zjeyne-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c draw.c ray.c read.c map_read.c thread.c funcs.c error.c read_temp.c init.c get_index.c get_index_t.c c_check.c c_check_t.c lst_f.c init_toc.c cobj_funcs.c ray_funcs.c obj_draw.c sort.c cobj_draw.c gnl/get_next_line.c gnl/libft/libft.a

all :
	gcc -Ofast $(SRC) -lmlx -framework OpenGL -framework AppKit