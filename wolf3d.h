/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:33:53 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/04/10 23:17:56 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

#include "mlx.h"
#include "gnl/get_next_line.h"

#include "mac_keys.h"
#include "linux_keys.h" //!!!!!!!

#include <pthread.h>

#define THREAD 16

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>

#define W 1280
#define H 720

#define TILES 11

#define SPACE '0'
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

#define OBJ 12

#define SKELETON 'S'
#define CLAMP 'L'
#define BONES 'B'
#define CHAND 'C'
#define TREE 'T'
#define PUDDLE 'V'
#define BARREL 'O'
#define TABLE 'I'
#define FWELL 'Z'
#define EWELL 'X'
#define DPOT 'U'
#define DEAD 'D'

#define COBJ 5			// R ++ && G ++

#define AMMO 'A'
#define CROSS '+'
#define CUP '?'
#define CROWN 'Q'
#define CHEST '='

typedef	struct			s_img
{
	void					*img;
	int						w;
	int						h;
	int						*data;
	int						bpp;
	int						size_line;
	int						endian;
}							t_img;

typedef struct		s_cobj
{
	double				x;
	double				y;
	int						is_treasure;
	t_img				*img;
	struct s_cobj	*next_cobj;
}							t_cobj;

typedef struct		s_obj
{
	double				x;
	double				y;
	int						is_lamp;
	int						is_collectable;
	t_img				*img;
}							t_obj;

typedef struct		s_player
{
    double				x;
    double				y;
    double				pov;
	double				fov;
}							t_player;

typedef struct		s_mlx
{
    void				*mlx;
    void				*win;
    void				*img;
	int						*data;
	int						bpp;
	int						size_line;
	int						endian;

	double				iter_angle;

	double				depth;
	double				dist_inc;

	char				**map;

	t_img				**textures;
	int						tile_index;

	int						obj_count;
	t_obj				**objs;
	char				*obj[OBJ];

	int						cobj_count;
	t_cobj				*cobjs;
	char				*cobj[COBJ];

	int						ammo;
	int						score;

	//double				angles[W];

	double				*depth_buff;

	int						mlx_index;

	//int						keycode;

	//double				upper;

	int						row;
	int						col;

    t_player    		*player;
}							t_mlx;

void				ft_draw_line(t_mlx *mlx, int xo, int yo, int x, int y, int color);
void				ft_draw_cross(t_mlx *mlx );
void				ft_draw_interface(t_mlx *mlx);

void				ft_image(t_mlx *mlx, int x, int y, int color);

void				ft_ray_cast(t_mlx *mlx);
void				ft_ray_start(t_mlx *mlx);

void				ft_objs_draw(t_mlx *mlx);
void				ft_cobjs_draw(t_mlx *mlx);

void				ft_init_textures(t_mlx *mlx);
void				ft_init_objects(t_mlx *mlx);
void				ft_init_cobjects(t_mlx *mlx);

int					ft_texture_sampling(t_img *img, double sample_x, double sample_y);

int					ft_walls_check(char **map, int player_x, int player_y);
int					ft_tiles_check(char **map, int t_x, int t_y);
int					ft_get_tile_index(char c);

void				ft_obj_check(t_mlx *mlx, char *line);
int					ft_obj_check_c(char c);
int					ft_is_obj_phys(char c);
int					ft_is_obj_lamp(char c);
void				ft_read_obj(t_mlx *mlx);
int					ft_get_obj_index(char c);
int					ft_cobj_check(char c);
int					ft_get_cobj_index(char c);

void				ft_lst_fill(t_mlx *mlx, t_cobj *head, double x, double y, int cobj_c, int cobj_index);
void				ft_lst_del_elem(t_mlx *mlx, t_cobj *root, int x, int y);

void				ft_on_item_check(t_mlx *mlx, int p_x, int p_y);

void				ft_read_map(char *map, t_mlx *mlx);

void				ft_thread(t_mlx *mlx);

#endif
