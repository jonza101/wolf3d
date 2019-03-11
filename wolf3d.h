/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:33:53 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/11 19:53:14 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

#include "minilibx/mlx.h"
#include <stdlib.h>
#include <math.h>

#define W 1920
#define H 1080

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

    t_player    *player;
	t_slider	*slider;
}						t_mlx;

void				ft_draw_line(t_mlx *mlx, int xo, int yo, int x, int y, int color);
void				ft_draw_circle(t_mlx *mlx, int xo, int yo, int color);

void				ft_image(t_mlx *mlx, int x, int y, int color);

void				ft_ray_cast(t_mlx *mlx);
void				ft_ray_start(t_mlx *mlx);

void				ft_slider_line(t_mlx *mlx, int mouse_x);

#endif
