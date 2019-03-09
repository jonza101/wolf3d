/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:40:07 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/03/09 22:09:34 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#include <stdio.h>

void	ft_reset_image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int*)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);
	mlx_clear_window(mlx->mlx, mlx->win);
}

void	ft_fill_map(t_mlx *mlx)
{
	mlx->map[0] = "1111111111111111";
	mlx->map[1] = "1000000010000001";
	mlx->map[2] = "1000000010000001";
	mlx->map[3] = "1111100011100001";
	mlx->map[4] = "1000100000000001";
	mlx->map[5] = "1000000000000001";
	mlx->map[6] = "1000000000001001";
	mlx->map[7] = "1000000000011111";
	mlx->map[8] = "1110000000000001";
	mlx->map[9] = "1000000000000001";
	mlx->map[10] = "1111000000000001";
	mlx->map[11] = "1001000000110001";
	mlx->map[12] = "1001000000010001";
	mlx->map[13] = "1000000011110001";
	mlx->map[14] = "1000000001000001";
	mlx->map[15] = "1111111111111111";
}

void	ft_map(t_mlx *mlx)
{
	int i;
	i = 0;
	mlx->map = (char**)malloc(sizeof(char*) * 16);
	while (i  < 5)
	{
		mlx->map[i] = (char*)malloc(sizeof(char) * 16);
		i++;
	}
	ft_fill_map(mlx);
}

int		key_press(int keycode, t_mlx *mlx)
{
	printf("%d\n", keycode);
	(keycode == 65307) ? exit(0) : 1;
	
	if (keycode == 65361)
	{
		ft_reset_image(mlx);
		mlx->player->pov -= 0.1;
		printf("pov %d\n",  mlx->player->pov);
		ft_ray_cast(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}

	if (keycode == 65363)
	{
		ft_reset_image(mlx);
		mlx->player->pov += 0.1;
		printf("pov %d\n",  mlx->player->pov);
		ft_ray_cast(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}

	if (keycode == 1731 || keycode == 119)
	{
		ft_reset_image(mlx);
		mlx->player->x += sinf(mlx->player->pov) * 0.5;
		mlx->player->y += cosf(mlx->player->pov) * 0.5;
		if (mlx->map[(int)mlx->player->y][(int)mlx->player->x] == '1')
		{
			mlx->player->x -= sinf(mlx->player->pov) * 0.5;
			mlx->player->y -= cosf(mlx->player->pov) * 0.5;
		}
		ft_ray_cast(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}

	if (keycode == 1753 || keycode == 115)
	{
		ft_reset_image(mlx);
		mlx->player->x -= sinf(mlx->player->pov) * 0.5;
		mlx->player->y -= cosf(mlx->player->pov) * 0.5;
				if (mlx->map[(int)mlx->player->y][(int)mlx->player->x] == '1')
		{
			mlx->player->x += sinf(mlx->player->pov) * 0.5;
			mlx->player->y += cosf(mlx->player->pov) * 0.5;
		}
		ft_ray_cast(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}
	
	if (keycode == 1739)
	{
		ft_reset_image(mlx);
		ft_ray_start(mlx);
		ft_ray_cast(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}
	return (0);
}

int		main()
{
	t_mlx *mlx;
	
	mlx = (t_mlx*)malloc(sizeof(t_mlx));
	mlx->player = (t_player*)malloc(sizeof(t_player));

	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, W, H, "Wolf3D");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int*)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);

	ft_map(mlx);

	ft_ray_start(mlx);
	ft_ray_cast(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);

	mlx_hook(mlx->win, 2, 1, key_press, mlx);

	mlx_loop(mlx->mlx);
	return (0);
}