/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_toc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:06:11 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/20 14:26:57 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_free_toc(t_mlx *mlx)
{
	int i;

	i = -1;
	while (++i < TILES)
		free(mlx->tiles[i]);
	i = -1;
	while (++i < OBJ)
		free(mlx->obj[i]);
	i = -1;
	while (++i < COBJ)
		free(mlx->cobj[i]);
	i = -1;
	while (++i < 3)
		free(mlx->dark_tiles[i]);
}

void	ft_init_cobjects(t_mlx *mlx)
{
	int		i;
	t_cobj	*temp;

	i = 0;
	if (mlx->cobj_count <= 0)
		return ;
	ft_init_cobj_sprites(mlx);
	(!(mlx->cobjs = (t_cobj*)malloc(sizeof(t_cobj)))) ? ft_mem_error() : 1;
	(!(mlx->cobjs->img = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
	mlx->cobjs->img->w = 64;
	mlx->cobjs->img->h = 64;
	temp = mlx->cobjs;
	while (++i < mlx->cobj_count)
		ft_lst_add_img(mlx);
	mlx->cobjs = temp;
}

void	ft_init_objects(t_mlx *mlx)
{
	int i;

	i = -1;
	ft_init_obj_sprites(mlx);
	(!(mlx->objs = (t_obj**)malloc(sizeof(t_obj*)
							* mlx->obj_count))) ? ft_mem_error() : 1;
	while (++i < mlx->obj_count)
	{
		(!(mlx->objs[i] = (t_obj*)malloc(sizeof(t_obj))))
							? ft_mem_error() : 1;
		(!(mlx->objs[i]->img = (t_img*)malloc(sizeof(t_img))))
							? ft_mem_error() : 1;
		mlx->objs[i]->img->w = 64;
		mlx->objs[i]->img->h = 64;
	}
}

void	ft_init_dark(t_mlx *mlx)
{
	int i;

	i = -1;
	ft_init_dark_tiles(mlx);
	(!(mlx->textures_d = (t_img**)malloc(sizeof(t_img*)
							* 3))) ? ft_mem_error() : 1;
	while (++i < 3)
	{
		(!(mlx->textures_d[i] = (t_img*)malloc(sizeof(t_img))))
							? ft_mem_error() : 1;
		mlx->textures_d[i]->w = 64;
		mlx->textures_d[i]->h = 64;
		mlx->textures_d[i]->img = mlx_xpm_file_to_image(
							mlx->mlx, mlx->dark_tiles[i],
							&mlx->textures_d[i]->w,
							&mlx->textures_d[i]->h);
		mlx->textures_d[i]->data = (int*)mlx_get_data_addr(
							mlx->textures_d[i]->img,
							&mlx->textures_d[i]->bpp,
							&mlx->textures_d[i]->size_line,
							&mlx->textures_d[i]->endian);
	}
}

void	ft_init_textures(t_mlx *mlx)
{
	int i;

	i = -1;
	ft_init_tiles(mlx);
	(!(mlx->textures = (t_img**)malloc(sizeof(t_img*)
							* TILES))) ? ft_mem_error() : 1;
	while (++i < TILES)
	{
		(!(mlx->textures[i] = (t_img*)malloc(sizeof(t_img))))
							? ft_mem_error() : 1;
		mlx->textures[i]->w = 64;
		mlx->textures[i]->h = 64;
		mlx->textures[i]->img = mlx_xpm_file_to_image(
							mlx->mlx, mlx->tiles[i],
							&mlx->textures[i]->w,
							&mlx->textures[i]->h);
		mlx->textures[i]->data = (int*)mlx_get_data_addr(
							mlx->textures[i]->img,
							&mlx->textures[i]->bpp,
							&mlx->textures[i]->size_line,
							&mlx->textures[i]->endian);
	}
}
