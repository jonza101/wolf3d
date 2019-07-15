/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 21:03:30 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/15 18:54:44 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_mem_error(void)
{
	ft_putstr("Memory allocation error!\n");
	ft_usage();
}

void	ft_on_item_tail(t_mlx *mlx, int p_x, int p_y)
{
	int		i;
	t_cobj	*temp;
	t_cobj	*tmp;
	t_cobj	*asd;

	i = 1;
	mlx->cobj_f = 0;
	tmp = mlx->cobjs;
	while (mlx->cobjs->next_cobj && ((int)mlx->cobjs->next_cobj->x != p_x
			|| (int)mlx->cobjs->next_cobj->y != p_y))
		mlx->cobjs = mlx->cobjs->next_cobj;
	asd = mlx->cobjs;
	mlx->cobjs = mlx->cobjs->next_cobj;
	ft_cobj_t(mlx, p_x, p_y, tmp);
	if (mlx->cobj_f)
		return ;
	temp = mlx->cobjs->next_cobj;
	free(mlx->cobjs);
	asd->next_cobj = temp;
	mlx->cobjs = tmp;
}

void	ft_on_item_head(t_mlx *mlx, int p_x, int p_y)
{
	t_cobj	*temp;

	temp = mlx->cobjs;
	if (mlx->cobjs->is == 0)
	{
		mlx->player->ammo += 5;
		mlx->map[p_y][p_x] = SPACE;
	}
	else if (mlx->cobjs->is == 1)
	{
		mlx->player->score += 100;
		mlx->map[p_y][p_x] = SPACE;
	}
	else if (mlx->player->hp < 100)
		ft_cobj_tmp_hp(mlx, p_x, p_y);
	else if (mlx->player->hp == 100)
		return ;
	free(mlx->cobjs);
	mlx->cobjs = temp->next_cobj;
}

void	ft_on_item_check(t_mlx *mlx, int p_x, int p_y)
{
	if (!mlx->cobjs)
		return ;
	if (ft_cobj_check(mlx->map[p_y][p_x]))
	{
		if ((int)mlx->cobjs->x == p_x && (int)mlx->cobjs->y == p_y)
			ft_on_item_head(mlx, p_x, p_y);
		else
			ft_on_item_tail(mlx, p_x, p_y);
	}
}
