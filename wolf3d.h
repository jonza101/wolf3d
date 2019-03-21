/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:33:53 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/21 18:36:06 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

#include "mlx.h"
#include "gnl/get_next_line.h"

#include <bsd/string.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>

#define W 1280
#define H 720

#define WALL '#'

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

typedef struct	s_player
{
    double			x;
    double			y;
    double			pov;
	double			fov;
}						t_player;

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

typedef struct	s_mlx
{
    void			*mlx;
    void			*win;
    void			*img;
	int				*data;
	int				bpp;
	int				size_line;
	int				endian;

	int				proj_dist;
	double		ray_angle;
	double		iter_angle;

	double		depth;
	double		dist_inc;

	char			**map;

	t_img			*textures;

    t_player    *player;
	t_slider	*slider;
}						t_mlx;

void				ft_draw_line(t_mlx *mlx, int xo, int yo, int x, int y, int color);
void				ft_draw_circle(t_mlx *mlx, int xo, int yo, int color);
void				ft_draw_cross(t_mlx *mlx );

void				ft_image(t_mlx *mlx, int x, int y, int color);

void				ft_ray_cast(t_mlx *mlx);
void				ft_ray_start(t_mlx *mlx);

void				ft_read_textures(t_mlx *mlx);

int					ft_texture_sampling(t_img *img, double sample_x, double sample_y);

void				ft_slider_line(t_mlx *mlx, int mouse_x);

#endif
