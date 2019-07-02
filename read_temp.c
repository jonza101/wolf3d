/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_temp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:58:04 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/02 16:28:45 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_player_tmp(t_mlx *mlx, int i, int j)
{
	if (mlx->map[i][j] == PLAYER)
	{
		mlx->player->start_x = j + 0.5;
		mlx->player->start_y = i + 0.5;
		mlx->map[i][j] = '0';
		mlx->player_t = 1;
	}
}

void	ft_obj_tmp(t_mlx *mlx, int i, int j)
{
	int index;

	if (ft_obj_check_c(mlx->map[i][j]) == 1)
	{
		index = ft_get_obj_index(mlx->map[i][j]);
		mlx->objs[mlx->obj_c]->img->img = mlx_xpm_file_to_image(
										mlx->mlx, mlx->obj[index],
										&mlx->objs[mlx->obj_c]->img->w,
										&mlx->objs[mlx->obj_c]->img->h);
		mlx->objs[mlx->obj_c]->img->data = (int*)mlx_get_data_addr(
										mlx->objs[mlx->obj_c]->img->img,
										&mlx->objs[mlx->obj_c]->img->bpp,
										&mlx->objs[mlx->obj_c]->img->size_line,
										&mlx->objs[mlx->obj_c]->img->endian);
		(!ft_is_obj_phys(mlx->map[i][j])) ? mlx->map[i][j] = '0' : 1;
		mlx->objs[mlx->obj_c]->y = i + 0.5;
		mlx->objs[mlx->obj_c]->x = j + 0.5;
		mlx->obj_c++;
	}
}

void	ft_cobj_tmp(t_mlx *mlx, int i, int j)
{
	if (ft_cobj_check(mlx->map[i][j]) == 1)
	{
		mlx->cobj_index = ft_get_cobj_index(mlx->map[i][j]);
		ft_lst_fill(mlx, mlx->cobjs, j + 0.5, i + 0.5);
		mlx->cobj_c++;
	}
}

void	ft_read_init(t_mlx *mlx, char *line)
{
	mlx->read_i = 0;
	mlx->col = ft_strlen(line);
	mlx->row = 1;
	mlx->obj_count = 0;
	mlx->cobj_count = 0;
}
