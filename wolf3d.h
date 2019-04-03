/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:33:53 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/04/04 00:50:51 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

#include "mlx.h"
#include "gnl/get_next_line.h"

#include "mac_keys.h"
#include "linux_keys.h" //!!!!!!!

#include <pthread.h>

#define THREAD 2

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>

#define W 1280
#define H 720

#define TILES 11

#define BW1 '1'
#define BW2 '2'
#define CELL '#'
#define SCELL '$'
#define GB1 '3'
#define GB2 '4'
#define EAGLE 'E'
#define FLAG 'F'
#define GH 'G'
#define WW '5'
#define WEAGLE 'W'

#define OBJ 5

#define SKELETON 'S'
#define CLAMP 'L'
#define BONES 'B'
#define CHAND 'C'
#define TREE 'T'

typedef struct	s_slider
{
	int					xo;
	int					x;
	int					y;
	int					radius;
	int					len;
	int					height;
	int					lmb_hold;
	int					is_grabbed;
}						t_slider;

typedef	struct	s_img
{
	void			*img;
	int				w;
	int				h;
	int				*data;
	int				bpp;
	int				size_line;
	int				endian;
}						t_img;

typedef struct	s_obj
{
	double			x;
	double			y;
	t_img			*img;
}						t_obj;

typedef struct	s_player
{
    double			x;
    double			y;
    double			pov;
	double			fov;
}						t_player;

typedef struct	s_mlx
{
    void			*mlx;
    void			*win;
    void			*img;
	int				*data;
	int				bpp;
	int				size_line;
	int				endian;

	//int				keycode;

	double		iter_angle;

	double		depth;
	double		dist_inc;

	char			**map;

	t_img			**textures;
	int					tile_index;

	int				obj_count;
	t_obj			**objs;
	char			*obj[OBJ];

	double		*depth_buff;

	int				keycode;

	double		upper;

	int				row;
	int				col;

    t_player    *player;
	t_slider	*slider;
}						t_mlx;

void				ft_draw_line(t_mlx *mlx, int xo, int yo, int x, int y, int color);
void				ft_draw_circle(t_mlx *mlx, int xo, int yo, int color);
void				ft_draw_cross(t_mlx *mlx );

void				ft_image(t_mlx *mlx, int x, int y, int color);

void				ft_ray_cast(t_mlx *mlx);
void				ft_ray_start(t_mlx *mlx);

void				ft_init_textures(t_mlx *mlx);
void				ft_init_objects(t_mlx *mlx);

int					ft_texture_sampling(t_img *img, double sample_x, double sample_y);

int					ft_walls_check(char **map, int player_x, int player_y);
int					ft_tiles_check(char **map, int t_x, int t_y);
int					ft_get_tile_index(char c);

void				ft_obj_check(t_mlx *mlx, char *line);
int					ft_obj_check_c(char c);
void				ft_read_obj(t_mlx *mlx);
int					ft_get_obj_index(char c);

void				ft_read_map(char *map, t_mlx *mlx);

void				*ft_realloc(void *ptr, size_t size);

void				ft_slider_line(t_mlx *mlx, int mouse_x);

#endif
