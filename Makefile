# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/11 19:33:51 by zjeyne-l          #+#    #+#              #
#    Updated: 2019/08/17 16:47:05 by zjeyne-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

# PATHS TO C SOURCE FILES
SRC_PATH = $(wildcard $(SRC_DIR)/*.c)
SRC_PATH += gnl/get_next_line.c

# PATHS TO OBJECTS
OBJ_PATH = $(SRC_PATH:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# PATH TO LIBFT
LIB_NAME = libft.a
LIB_PATH = gnl/libft
LIB = -lft

# MLX INFO
MLX = -lpthread -lmlx -framework OpenGL -framework AppKit

# COMPILATION RULES
FLAGS =  -std=c99 -Ofast
NAME = wolf3d

.PHONY: all clean fclean re

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ_PATH) $(LIB_PATH)/$(LIB_NAME)
	gcc $(FLAGS) $(OBJ_PATH) -o $@ -I$(INC_DIR) -I$(LIB_PATH)/$(INC_DIR) -L$(LIB_PATH) $(LIB) $(MLX) 

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	gcc $(FLAGS) -o $@ -c $< -I$(INC_DIR) -I$(LIB_PATH)/$(INC_DIR)

$(LIB_PATH)/$(LIB_NAME):
	make -C $(LIB_PATH)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIB_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIB_PATH) fclean

re: fclean all
