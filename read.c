/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 21:03:30 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/13 23:08:25 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_texture_sampling(t_mlx *mlx, double sample_x, double sample_y)
{
	return (64 * 64 * sample_y * sample_x);
}

void	ft_read_textures(t_mlx *mlx)
{
	int x;
	int y;
	int file;
	char buff[1];

	x = 0;
	file = open("textures/blue_wall.png", O_RDONLY);
	mlx->textures = (int**)malloc(sizeof(int*) * 1);
	mlx->textures[0] = (int*)malloc(sizeof(int) * 64 * 64);
	// while (read(file, buff, 1))
	// {
	// 	mlx->textures[0][x] = (int)buff[0];
	// 	x++;
	// }
	while (x < 64)
	{
		y = 0;
		while (y < 64)
		{
			int ycolor = y * 256 / 64;
			mlx->textures[0][64 * y + x] = 65536 * ycolor; //red gradient
			y++;
		}
		x++;
	}
	close(file);
}
