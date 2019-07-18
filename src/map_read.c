/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 20:02:51 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/18 11:26:45 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

int		ft_is_wall(char c)
{
	if (c == BW1 || c == BW2 || c == CELL || c == SCELL ||
		c == GB1 || c == GB2 || c == EAGLE || c == FLAG || c == GH
			|| c == WW || c == WEAGLE || c == WH || c == BUNKWALL)
		return (1);
	return (0);
}

void	ft_bound_check(t_mlx *mlx)
{
	int i;

	i = -1;
	while (++i < mlx->col)
	{
		if (!ft_is_wall(mlx->map[0][i]) ||
				!ft_is_wall(mlx->map[mlx->row - 1][i]))
			ft_bounds_error();
	}
	i = -1;
	while (++i < mlx->row)
	{
		if (!ft_is_wall(mlx->map[i][0]) ||
				!ft_is_wall(mlx->map[i][mlx->col - 1]))
			ft_bounds_error();
	}
}

int		ft_map_value_check(char c)
{
	if (c == PLAYER)
		return (1);
	if (!ft_obj_check_c(c) && !ft_cobj_check(c) && c != SPACE && !ft_is_wall(c))
		return (0);
	return (1);
}

void	ft_read_obj(t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	mlx->obj_c = 0;
	mlx->cobj_c = 0;
	mlx->player_t = 0;
	ft_bound_check(mlx);
	while (i < mlx->row)
	{
		j = 0;
		while (j < mlx->col)
		{
			(!ft_map_value_check(mlx->map[i][j])) ?
				ft_map_value_error(mlx->map[i][j], i, j) : 1;
			ft_player_tmp(mlx, i, j);
			ft_obj_tmp(mlx, i, j);
			ft_cobj_tmp(mlx, i, j);
			j++;
		}
		i++;
	}
	(mlx->player_t == 0) ? ft_player_error() : 1;
}

void	ft_read_map(char *map, t_mlx *mlx)
{
	int		fd;
	char	*line;

	((fd = open(map, O_RDONLY)) < 0) ? ft_map_error() : 1;
	(get_next_line(fd, &line) <= 0) ? ft_map_error() : 1;
	ft_read_init(mlx, line);
	while (get_next_line(fd, &line) == 1)
	{
		((int)ft_strlen(line) != mlx->col) ? ft_map_error() : 1;
		ft_obj_check(mlx, line);
		mlx->row++;
		mlx->read_i++;
	}
	free(line);
	close(fd);
	mlx->read_i = -1;
	fd = open(map, O_RDONLY);
	mlx->map = (char**)malloc(sizeof(char*) * mlx->row);
	while (++mlx->read_i < mlx->row)
	{
		(get_next_line(fd, &line) != 1) ? ft_map_error() : 1;
		mlx->map[mlx->read_i] = ft_strdup(line);
	}
	close(fd);
}
