/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:01:19 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/03 13:00:38 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_sort(t_mlx *mlx)
{
	int		i;
	int		j;
	int		tmp;
	double	temp;

	i = 0;
	while (i < mlx->obj_count - 1)
	{
		j = i + 1;
		while (j < mlx->obj_count)
		{
			if (mlx->sprite_dist[i] < mlx->sprite_dist[j])
			{
				tmp = mlx->sprite_order[i];
				mlx->sprite_order[i] = mlx->sprite_order[j];
				mlx->sprite_order[j] = tmp;
				temp = mlx->sprite_dist[i];
				mlx->sprite_dist[i] = mlx->sprite_dist[j];
				mlx->sprite_dist[j] = temp;
			}
			j++;
		}
		i++;
	}
}
