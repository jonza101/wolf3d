/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 21:03:30 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/22 16:39:25 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_get_tile_index(char c)
{
	if (c == BW1)
		return (0);
	else if (c == BW2)
		return (1);
	else if (c == CELL)
		return (2);
	else if (c == SCELL)
		return (3);
	else if (c == GB1)
		return (4);
	else if (c == GB2)
		return (5);
	else if (c == EAGLE)
		return (6);
	else if (c == FLAG)
		return (7);
	else if (c == GH)
		return (8);
}

int		ft_tiles_check(char **map, int p_x, int p_y)
{
	if (map[p_y][p_x] == BW1 || map[p_y][p_x] == BW2 || map[p_y][p_x] == CELL || map[p_y][p_x] == SCELL || map[p_y][p_x] == GB1
		|| map[p_y][p_x] == GB2 || map[p_y][p_x] == EAGLE || map[p_y][p_x] == FLAG || map[p_y][p_x] == GH)
		return (1);
	return (0);
}

int		ft_walls_check(char **map, int player_x, int player_y)
{
	if (map[player_y][player_x] != BW1 && map[player_y][player_x] != BW2 && map[player_y][player_x] != CELL && map[player_y][player_x] != SCELL
		&& map[player_y][player_x] != GB1 && map[player_y][player_x] != GB2 && map[player_y][player_x] != EAGLE && map[player_y][player_x] != FLAG
			&& map[player_y][player_x] != GH)
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
	char *tiles[TILES] = { "textures/blue_wall1.xpm", "textures/blue_wall2.xpm", "textures/blue_cell.xpm", "textures/blue_skeleton_cell.xpm",
		"textures/gray_brick1.xpm", "textures/gray_brick2.xpm", "textures/gray_eagle.xpm", "textures/gray_flag.xpm", "textures/gray_hit.xpm" };

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
