/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:27:58 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/03 13:00:41 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_thread_tmp(t_mlx *mlx)
{
	pthread_t	o_threads[2];
	t_mlx		*o_mlx_cpy[2];

	o_mlx_cpy[0] = (t_mlx*)malloc(sizeof(t_mlx));
	o_mlx_cpy[1] = (t_mlx*)malloc(sizeof(t_mlx));
	o_mlx_cpy[0] = ft_memcpy((void*)o_mlx_cpy[0], (void*)mlx, sizeof(t_mlx));
	o_mlx_cpy[1] = ft_memcpy((void*)o_mlx_cpy[1], (void*)mlx, sizeof(t_mlx));
	pthread_create(&o_threads[0], NULL,
				(void*)ft_objs_draw, (void*)o_mlx_cpy[0]);
	pthread_create(&o_threads[1], NULL,
				(void*)ft_cobjs_draw, (void*)o_mlx_cpy[1]);
	pthread_join(o_threads[0], NULL);
	pthread_join(o_threads[1], NULL);
	ft_memdel((void*)&o_mlx_cpy[0]);
	ft_memdel((void*)&o_mlx_cpy[1]);
}

void	ft_thread(t_mlx *mlx)
{
	int			i;
	pthread_t	threads[THREAD];
	t_mlx		*mlx_cpy[THREAD];

	i = -1;
	while (++i < THREAD)
	{
		mlx_cpy[i] = (t_mlx*)malloc(sizeof(t_mlx));
		mlx_cpy[i] = ft_memcpy((void*)mlx_cpy[i], (void*)mlx, sizeof(t_mlx));
		mlx_cpy[i]->mlx_index = i;
		pthread_create(&threads[i], NULL,
					(void*)ft_ray_cast, (void*)mlx_cpy[i]);
	}
	i = -1;
	while (++i < THREAD)
		pthread_join(threads[i], NULL);
	i = -1;
	while (++i < THREAD)
		ft_memdel((void*)&mlx_cpy[i]);
	ft_thread_tmp(mlx);
	ft_draw_cross(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	ft_draw_interface(mlx);
}
