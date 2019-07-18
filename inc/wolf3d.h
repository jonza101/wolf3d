/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:33:53 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/18 11:28:50 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "mlx.h"
# include "../gnl/get_next_line.h"

# include "mac_keys.h"

# include <pthread.h>

# define THREAD 16

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>

# define W 1280
# define H 720

# define CEILING 0x383838
# define FLOOR 0x6b6f6e
# define IGNORE_COLOR 0x980088

# define PLAYER 'P'

# define TILES 13

# define SPACE '0'
# define BW1 '1'
# define BW2 '2'
# define CELL '#'
# define SCELL '$'
# define GB1 '3'
# define GB2 '4'
# define EAGLE 'E'
# define FLAG 'F'
# define GH 'G'
# define WW '5'
# define WEAGLE 'W'
# define WH 'H'
# define BUNKWALL '%'

# define OBJ 26

# define SKELETON 'S'
# define CLAMP 'L'
# define BONES 'B'
# define CHAND 'C'
# define TREE 'T'
# define PUDDLE 'V'
# define BARREL 'O'
# define TABLE 'I'
# define FWELL 'Z'
# define EWELL 'X'
# define DPOT 'U'
# define DEAD 'D'
# define KNIGHT 'K'
# define VASE '&'
# define TCHAIRS '-'
# define BUSH '^'
# define FLAMP '!'
# define FLAGPOLE 'i'
# define GBARREL 'o'
# define BUBBLER 'b'
# define S_SKELETON 's'
# define K_STUFF 'k'
# define B_BONES '@'
# define PILLAR 'p'
# define CAGE 'J'
# define S_CAGE 'j'

# define COBJ 8

# define AMMO 'A'
# define CROSS '+'
# define CUP '?'
# define CROWN 'Q'
# define CHEST '='
# define FOOD 'M'
# define DFOOD '_'
# define MEDKIT '*'

typedef	struct		s_img
{
	void			*img;
	int				w;
	int				h;
	int				*data;
	int				*dark_data;
	int				bpp;
	int				size_line;
	int				endian;
}					t_img;

typedef struct		s_cobj
{
	double			x;
	double			y;
	int				is;
	t_img			*img;
	struct s_cobj	*next_cobj;
}					t_cobj;

typedef struct		s_obj
{
	double			x;
	double			y;
	t_img			*img;
}					t_obj;

typedef struct		s_player
{
	double			x;
	double			y;
	double			start_x;
	double			start_y;
	double			pov;
	double			fov;
	int				ammo;
	int				score;
	int				hp;

	int				wsad[4];
	int				left;
	int				right;
}					t_player;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	int				*data;
	int				bpp;
	int				size_line;
	int				endian;

	double			depth;

	double			iter_angle;
	int				hit;
	double			dist_to_wall;
	double			sample_x;
	double			sample_y;
	double			eye_angle_x;
	double			eye_angle_y;
	int				p_x;
	int				p_y;
	double			block_mid_x;
	double			block_mid_y;
	double			point_x;
	double			point_y;
	double			txt_angle;
	double			ceiling;
	int				floor;

	double			vec_x;
	double			vec_y;
	double			dist_from_player;
	double			eye_x;
	double			eye_y;
	double			obj_angle;
	int				in_fov;
	double			obj_ceiling;
	double			obj_floor;
	double			obj_aspect_ratio;
	double			obj_h;
	double			obj_w;
	double			obj_middle;
	double			sample_ox;
	double			sample_oy;
	int				obj_color;
	int				obj_col;
	int				dark;
	int				dark_switch;
	int				color;

	char			**map;
	char			*map_file;

	char			*tiles[TILES];
	char			*dark_tiles[3];
	t_img			**textures;
	t_img			**textures_d;
	int				tile_index;

	int				obj_count;
	t_obj			**objs;
	char			*obj[OBJ];

	int				cobj_count;
	t_cobj			*cobjs;
	char			*cobj[COBJ];

	double			*depth_buff;

	char			*ammo_str;
	char			*score_str;
	char			*hp_str;
	char			*fov_str;
	char			*depth_str;

	int				mlx_index;

	int				row;
	int				col;

	int				*sprite_order;
	double			*sprite_dist;

	int				player_t;
	int				obj_c;
	int				cobj_c;
	int				cobj_f;
	int				cobj_index;
	int				ox;
	int				oy;

	int				read_i;

	t_player		*player;
}					t_mlx;

void				ft_draw_cross(t_mlx *mlx);
void				ft_draw_interface(t_mlx *mlx);

void				ft_image(t_mlx *mlx, int x, int y, int color);

void				ft_ray_cast(t_mlx *mlx);
void				ft_ray_start(t_mlx *mlx);

void				ft_objs_draw(t_mlx *mlx);
void				ft_cobjs_draw(t_mlx *mlx);

void				ft_init_textures(t_mlx *mlx);
void				ft_init_objects(t_mlx *mlx);
void				ft_init_cobjects(t_mlx *mlx);

int					ft_texture_sampling(t_img *img, double sample_x,
					double sample_y);

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

void				ft_lst_fill(t_mlx *mlx, t_cobj *head, double x, double y);
void				ft_lst_del_elem(t_mlx *mlx, t_cobj *root, int x, int y);

void				ft_on_item_check(t_mlx *mlx, int p_x, int p_y);

void				ft_read_map(char *map, t_mlx *mlx);

void				ft_thread(t_mlx *mlx);

void				ft_usage(void);

void				ft_mem_error(void);

void				ft_reset_image(t_mlx *mlx);
int					ft_close(int i);
int					ft_game_loop(t_mlx *mlx);

void				ft_map_value_error(char c, int row, int col);
void				ft_bounds_error(void);
void				ft_player_error(void);
void				ft_map_error(void);

void				ft_player_tmp(t_mlx *mlx, int i, int j);
void				ft_obj_tmp(t_mlx *mlx, int i, int j);
void				ft_cobj_tmp(t_mlx *mlx, int i, int j);
void				ft_read_init(t_mlx *mlx, char *line);

void				ft_init_obj_sprites(t_mlx *mlx);
void				ft_init_obj_sprites_t(t_mlx *mlx);
void				ft_init_tiles(t_mlx *mlx);
void				ft_init_dark(t_mlx *mlx);
void				ft_init_dark_tiles(t_mlx *mlx);
void				ft_init_cobj_sprites(t_mlx *mlx);

int					ft_get_tile_index(char c);
int					ft_get_tile_index_t(char c);
int					ft_get_dark_index(int index);

int					ft_get_obj_index(char c);
int					ft_get_obj_index_t(char c);
int					ft_get_obj_index_tmp(char c);

int					ft_cobj_is(int index);
int					ft_get_cobj_index(char c);

int					ft_cobj_check(char c);
int					ft_is_obj_phys(char c);
int					ft_obj_check_c(char c);

void				ft_obj_check(t_mlx *mlx, char *line);

int					ft_tiles_check(char **map, int p_x, int p_y);
int					ft_walls_check(char **map, int player_x, int player_y);

void				ft_lst_add_img(t_mlx *mlx);
void				ft_lst_fill(t_mlx *mlx, t_cobj *root, double x, double y);

void				ft_cobj_tmp_hp(t_mlx *mlx, int p_x, int p_y);
void				ft_cobj_t(t_mlx *mlx, int p_x, int p_y, t_cobj *tmp);

void				ft_ray_iter_init(t_mlx *mlx, int x);
void				ft_col_fill(t_mlx *mlx, int x);
void				ft_texturing_calc(t_mlx *mlx, int p_x, int p_y);
void				ft_hit_calc(t_mlx *mlx);

void				ft_sort(t_mlx *mlx);

void				ft_move_calc(t_mlx *mlx);

#endif
