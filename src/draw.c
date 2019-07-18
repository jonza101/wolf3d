/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:20:31 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/18 11:24:41 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_image(t_mlx *mlx, int x, int y, int color)
{
	if (x >= 0 && x < W && y >= 0 && y < H && color != IGNORE_COLOR
			&& color != 0x1F978B && color != 0x179797 && color != 0x007FA7)
		mlx->data[x + y * W] = mlx_get_color_value(mlx->mlx, color);
}

void	ft_draw_cross(t_mlx *mlx)
{
	int i;

	i = W / 2 - 2;
	while (i <= W / 2 + 2)
	{
		ft_image(mlx, i, H / 2, 0xFFFFFF);
		i++;
	}
	i = H / 2 - 2;
	while (i <= H / 2 + 2)
	{
		ft_image(mlx, W / 2, i, 0xFFFFFF);
		i++;
	}
}

void	ft_putstr_win(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->win, 20, H - 60, 0xFFFFFF, mlx->ammo_str);
	mlx_string_put(mlx->mlx, mlx->win, 20, H - 40, 0xFFFFFF, mlx->score_str);
	mlx_string_put(mlx->mlx, mlx->win, 20, H - 80, 0xFFFFFF, mlx->hp_str);
	mlx_string_put(mlx->mlx, mlx->win, 20, H - 120, 0xFFFFFF, mlx->fov_str);
	mlx_string_put(mlx->mlx, mlx->win, 20, H - 100, 0xFFFFFF, mlx->depth_str);
}

void	ft_free(t_mlx *mlx)
{
	free(mlx->ammo_str);
	free(mlx->score_str);
	free(mlx->hp_str);
	free(mlx->fov_str);
	free(mlx->depth_str);
}

void	ft_draw_interface(t_mlx *mlx)
{
	char *ammo;
	char *score;
	char *hp;
	char *fov;
	char *depth;

	ammo = ft_itoa(mlx->player->ammo);
	score = ft_itoa(mlx->player->score);
	hp = ft_itoa(mlx->player->hp);
	fov = ft_itoa(mlx->player->fov * 180 / 3.14159);
	depth = ft_itoa(mlx->depth);
	mlx->ammo_str = ft_strjoin("Ammo: ", ammo);
	mlx->score_str = ft_strjoin("Score: ", score);
	mlx->hp_str = ft_strjoin("Health: ", hp);
	mlx->fov_str = ft_strjoin("FOV: ", fov);
	mlx->depth_str = ft_strjoin("Render Distance: ", depth);
	ft_putstr_win(mlx);
	free(ammo);
	free(score);
	free(hp);
	free(fov);
	free(depth);
	ft_free(mlx);
}
