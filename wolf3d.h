/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:33:53 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/08 22:53:59 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

#include "minilibx/mlx.h"
#include <stdlib.h>
#include <math.h>

#define W 1920
#define H 1080

typedef struct	s_player
{
    double			x;
    double			y;
    double			pov;
	int					fov;
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

	char			**map;

    t_player    *player;
}						t_mlx;

void				ft_draw_line(t_mlx *mlx, int xo, int yo, int x, int y, int color);
void				ft_image(t_mlx *mlx, int x, int y, int color);

void				ft_ray_cast(t_mlx *mlx);
void				ft_ray_start(t_mlx *mlx);

#endif
