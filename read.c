/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 21:03:30 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/04/01 20:09:02 by zjeyne-l         ###   ########.fr       */
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
	else if (c == WW)
		return (9);
	else if (c == WEAGLE)
		return (10);
}

int		ft_tiles_check(char **map, int p_x, int p_y)
{
	if (map[p_y][p_x] == '0')
		return (0);
	return (1);
}

int		ft_walls_check(char **map, int player_x, int player_y)
{
	if (map[player_y][player_x] == '0')
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

void	ft_init_objects(t_mlx *mlx)
{
	int i;
	char *obj[OBJ] = { "textures/obj/skeleton.xpm" };

	i = 0;
	mlx->objs = (t_obj**)malloc(sizeof(t_obj*) * OBJ);
	while (i < OBJ)
	{
		mlx->objs[i] = (t_obj*)malloc(sizeof(t_obj));
		mlx->objs[i]->img = (t_img*)malloc(sizeof(t_img));
		mlx->objs[i]->img->w = 64;
		mlx->objs[i]->img->h = 64;
		mlx->objs[i]->x = 23;
		mlx->objs[i]->y = 24.5;
		mlx->objs[i]->img->img = mlx_xpm_file_to_image(mlx->mlx, obj[i], &mlx->objs[i]->img->w, &mlx->objs[i]->img->h);
		mlx->objs[i]->img->data = (int*)mlx_get_data_addr(mlx->objs[i]->img->img, &mlx->objs[i]->img->bpp, &mlx->objs[i]->img->size_line, &mlx->objs[i]->img->endian);
		i++;
	}
}

void	ft_init_textures(t_mlx *mlx)
{
	int i;
	char *tiles[TILES] = { "textures/blue_wall1.xpm", "textures/blue_wall2.xpm", "textures/blue_cell.xpm", "textures/blue_skeleton_cell.xpm",
		"textures/gray_brick1.xpm", "textures/gray_brick2.xpm", "textures/gray_eagle.xpm", "textures/gray_flag.xpm", "textures/gray_hit.xpm",
			"textures/wooden_wall.xpm", "textures/wooden_eagle.xpm" };

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

