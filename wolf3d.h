/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:47:22 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/01 16:17:31 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

#include "mlx.h"
#include <stdlib.h>
#include <math.h>

# define W 1920
# define H 1080

typedef	struct	s_points
{
	double		x;
	double		y;
}				t_points;

typedef	struct	s_player
{
	double		x;
	double		y;

	double		dir_xo;
	double		dir_yo;
	double		dir_x;
	double		dir_y;

	double		pov;
}				t_player;


typedef	struct	s_mlx
{
	void		*mlx;
	void		*win;

	void		*img;
	int			*data;
	int			bpp;
	int			size_line;
	int			endian;

	t_player	*player;
	t_points	*points;
}				t_mlx;

void			ft_draw_line(t_mlx *mlx, int xo, int yo, int x, int y, int color);
void			ft_image(t_mlx *mlx, int x, int y, int color);

void			ft_view_dir(t_mlx *mlx);
void			ft_rotate(t_mlx *mlx, int dir);

void			ft_view(t_mlx *mlx, int dir);
void			ft_player_move(t_mlx *mlx, int dir);

void			ft_reset_img(t_mlx *mlx);
void			ft_draw_all(t_mlx *mlx);

#endif