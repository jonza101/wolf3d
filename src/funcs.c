/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:28:38 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/06 18:46:22 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_usage(void)
{
	ft_putstr("Usage: ./wolf3d [map]\n");
	exit(0);
}

void	ft_reset_image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp,
		&mlx->size_line, &mlx->endian);
	mlx_clear_window(mlx->mlx, mlx->win);
}

int		ft_close(int i)
{
	i = 1;
	exit(0);
}

int		ft_game_loop(t_mlx *mlx)
{
	if (mlx->player->left)
		mlx->player->pov -= 0.04f;
	if (mlx->player->right)
		mlx->player->pov += 0.04f;
	ft_move_calc(mlx);
	ft_reset_image(mlx);
	ft_thread(mlx);
	return (0);
}

int		ft_texture_sampling(t_img *img, double sample_x, double sample_y)
{
	int sx;
	int sy;

	sx = sample_x * (double)img->w;
	sy = sample_y * (double)img->h;
	if (sx < 0 || sx > img->w || sy < 0 || sy > img->h)
		return (0x0);
	else
		return (img->data[sy * img->w + sx]);
}
