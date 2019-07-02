/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:03:46 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/02 17:04:22 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_lst_fill(t_mlx *mlx, t_cobj *root, double x, double y)
{
	int i;

	i = -1;
	if (!root)
		return ;
	while (++i < mlx->cobj_c)
		root = root->next_cobj;
	root->x = x;
	root->y = y;
	root->is = ft_cobj_is(mlx->cobj_index);
	root->img->img = mlx_xpm_file_to_image(
							mlx->mlx, mlx->cobj[mlx->cobj_index],
							&root->img->w, &root->img->h);
	root->img->data = (int*)mlx_get_data_addr(
							root->img->img, &root->img->bpp,
							&root->img->size_line, &root->img->endian);
}

void	ft_lst_add_img(t_mlx *mlx)
{
	if (!mlx->cobjs)
		return ;
	(!(mlx->cobjs->next_cobj = (t_cobj*)malloc(sizeof(t_cobj))))
							? ft_mem_error() : 1;
	mlx->cobjs = mlx->cobjs->next_cobj;
	(!(mlx->cobjs->img = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
	mlx->cobjs->img->w = 64;
	mlx->cobjs->img->h = 64;
}
