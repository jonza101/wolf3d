/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 21:03:30 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/21 18:45:37 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
	mlx->textures = (t_img*)malloc(sizeof(t_img) * 1);

	mlx->textures->w = 64;
	mlx->textures->h = 64;
	mlx->textures->img = mlx_xpm_file_to_image(mlx->mlx, "textures/blue_wall.xpm", &mlx->textures->w, &mlx->textures->h);
	mlx->textures->data = (int*)mlx_get_data_addr(mlx->textures->img, &mlx->textures->bpp, &mlx->textures->size_line, &mlx->textures->endian);
}
