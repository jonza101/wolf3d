/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:47:22 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/02 12:44:35 by zjeyne-l         ###   ########.fr       */
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

	double		angle;
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

void	ft_draw_line(t_mlx *mlx, int xo, int yo, int x, int y, int color);

#endif