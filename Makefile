SRC = main.c draw.c ray.c

all :
	gcc $(SRC) -lm -lmlx -lXext -lX11 -L minilibx/ -I minilibx/