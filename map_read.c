/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 20:02:51 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/04/04 00:33:21 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_map_error()
{
	ft_putstr("Map error!\nUsage: ./wolf3d [map]\n");
	exit(1);
}

void	ft_read_obj(t_mlx *mlx)
{
	int i;
	int j;
	int obj_c;

	i = 0;
	obj_c = 0;
	while (i < mlx->row)
	{
		j = 0;
		while (j < mlx->col)
		{
			if (ft_obj_check_c(mlx->map[i][j]) == 1)
			{
				int index = ft_get_obj_index(mlx->map[i][j]);
				mlx->objs[obj_c]->img->img = mlx_xpm_file_to_image(mlx->mlx, mlx->obj[index], &mlx->objs[obj_c]->img->w, &mlx->objs[obj_c]->img->h);
				mlx->objs[obj_c]->img->data = (int*)mlx_get_data_addr(mlx->objs[obj_c]->img->img, &mlx->objs[obj_c]->img->bpp, &mlx->objs[obj_c]->img->size_line, &mlx->objs[obj_c]->img->endian);
				mlx->map[i][j] = '0';
				mlx->objs[obj_c]->y = i + 0.5;
				mlx->objs[obj_c]->x = j + 0.5;
				obj_c++;
			}
			j++;
		}
		i++;
	}
}

void	ft_read_map(char *map, t_mlx *mlx)
{
	int fd;
	char *line;
	char **temp;
	int i;

	i = 0;
	fd = open(map, O_RDONLY);
	get_next_line(fd, &line);
	mlx->col = ft_strlen(line);
	mlx->row = 1;
	mlx->obj_count = 0;
	while (get_next_line(fd, &line) == 1)
	{
		(ft_strlen(line) != mlx->col) ? ft_map_error() : 1;
		ft_obj_check(mlx, line);
		mlx->row++;
		i++;
	}
	i = 0;
	close(fd);
	fd = open(map, O_RDONLY);
	mlx->map = (char**)malloc(sizeof(char*) * mlx->row);
	while (i < mlx->row)
	{
		(get_next_line(fd, &line) != 1) ? ft_map_error() : 1;
		mlx->map[i] = (char*)malloc(sizeof(char) * mlx->col);
		mlx->map[i] = ft_strncpy(mlx->map[i], line, mlx->col);
		i++;
	}
	printf("obj count %d\n", mlx->obj_count);
	close(fd);
}
