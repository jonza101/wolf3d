/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 21:03:30 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/21 21:18:53 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_get_tile_index(char c)
{
	if (c == '1')
		return (0);
	if (c == '2')
		return (1);
	if (c == '#')
		return (2);
	//if (c == 'S')
	return (3);
}

int		ft_tiles_check(char **map, int t_x, int t_y)
{
	if (map[t_y][t_x] == BW1 || map[t_y][t_x] == BW2 || map[t_y][t_x] == CELL || map[t_y][t_x] == SCELL)
		return (1);
	return (0);
}

int		ft_walls_check(char **map, int player_x, int player_y)
{
	if (map[player_y][player_x] != BW1 && map[player_y][player_x] != BW2 && map[player_y][player_x] != CELL && map[player_y][player_x] != SCELL)
		return (1);
	return (0);
}

int		ft_texture_sampling(t_img *img, double sample_x, double sample_y)
{
	int sx = sample_x * (double)img->w;
	int sy = sample_y * (double)img->h;
	if (sx < 0 || sx > img->w || sy < 0 || sy > img->h)
		return (0x0);
	else
		return (img->data[sy * img->w + sx]);
}

void	ft_read_textures(t_mlx *mlx)
{
	int i;
	char *tiles[TILES] = { "textures/blue_wall1.xpm", "textures/blue_wall2.xpm", "textures/blue_cell.xpm", "textures/blue_skeleton_cell.xpm" };

	i = 0;
	mlx->textures = (t_img**)malloc(sizeof(t_img*) * TILES);

	while (i < TILES)
	{
		mlx->textures[i] = (t_img*)malloc(sizeof(t_img));
		mlx->textures[i]->w = 64;
		mlx->textures[i]->h = 64;
		mlx->textures[i]->img = mlx_xpm_file_to_image(mlx->mlx, tiles[i], &mlx->textures[i]->w, &mlx->textures[i]->h);
		mlx->textures[i]->data = (int*)mlx_get_data_addr(mlx->textures[i]->img, &mlx->textures[i]->bpp, &mlx->textures[i]->size_line, &mlx->textures[i]->endian);
		i++;
	}
}
