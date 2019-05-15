/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 20:02:51 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/15 15:42:27 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_usage()
{
	ft_putstr("Usage: ./wolf3d [map]\n");
	exit(0);
}

void	ft_map_value_error(char c, int row, int col)
{
	char *str;
	char *s_row;
	char *s_col;
	char *s_c;

	s_c = (char*)malloc(sizeof(char) * 2);
	s_c[0] = c;
	s_c[1] = '\0';
	s_row = ft_itoa(row);
	s_col = ft_itoa(col);
	str = ft_strdup("Row: ");
	str = ft_strjoin(str, s_row);
	str = ft_strjoin(str, "	Column: ");
	str = ft_strjoin(str, s_col);
	str = ft_strjoin(str, "\n");
	str = ft_strjoin(str, "Map value '");
	str = ft_strjoin(str, s_c);
	str = ft_strjoin(str, "' not found!\n");
	ft_putstr("Map Error!\n");
	ft_putstr(str);
	ft_usage();
}

void	ft_bounds_error()
{
	ft_putstr("Map boundaries Error!\n");
	ft_usage();
}

void	ft_player_error()
{
	ft_putstr("Player not found!\n");
	ft_usage();
}

void	ft_map_error()
{
	ft_putstr("Map Error!\n");
	ft_usage();
}

int		ft_is_wall(char c)
{
	if (c == BW1 || c == BW2 || c == CELL || c == SCELL || c == GB1 || c == GB2 || c == EAGLE || c == FLAG || c == GH
		|| c == WW || c == WEAGLE || c == WH)
			return (1);
	return (0);
}

int		ft_asd(t_mlx *mlx, int x, int y, int last_x, int last_y)
{
	if (mlx->map[y + 1][x] && ft_is_wall(mlx->map[y + 1][x]) && y + 1 != last_y)
		return (ft_asd(mlx, x, y + 1, x, y));
	if (mlx->map[y - 1][x] && ft_is_wall(mlx->map[y - 1][x]) && y - 1 != last_y)
		return ft_asd(mlx, x, y - 1, x, y);
	if (mlx->map[y][x + 1] && ft_is_wall(mlx->map[y][x + 1]) && x + 1 != last_x)
		return ft_asd(mlx, x + 1, y, x, y);
	if (mlx->map[y][x - 1] && ft_is_wall(mlx->map[y][x - 1]) && x - 1 != last_x)
		return ft_asd(mlx, x - 1, y, x, y);
	if (x == mlx->f_x && y == mlx->f_y && last_x != mlx->f_x && last_y != mlx->f_y)
		return (1);
	return (0);
}

int		ft_bound_check(t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	while (i < mlx->row)
	{
		j = 0;
		while (j < mlx->col)
		{
			if (!ft_is_wall(mlx->map[i][j]))
			{
				printf("%d		%d\n", i, j);
				j++;
			}
			else
			{
				mlx->f_x = j;
				mlx->f_y = i;
				return (ft_asd(mlx, j, i, 0, 0));
			}
		}
		i++;
	}
}

int		ft_map_value_check(char c)
{
	if (c == PLAYER)
		return (1);
	if (!ft_obj_check_c(c) && !ft_cobj_check(c) && c != SPACE && c != BW1 && c != BW2 && c != CELL && c != SCELL && c != GB1 && c != GB2 && c != EAGLE && c != FLAG
		&& c != GH && c != WW && c != WEAGLE && c != WH)
		return (0);
	return (1);
}

void	ft_read_obj(t_mlx *mlx)
{
	int i;
	int j;
	int obj_c;
	int cobj_c;
	int player;

	i = 0;
	obj_c = 0;
	cobj_c = 0;
	player = 0;
	while (i < mlx->row)
	{
		j = 0;
		while (j < mlx->col)
		{
			(!ft_map_value_check(mlx->map[i][j])) ? ft_map_value_error(mlx->map[i][j], i, j) : 1;
			if (mlx->map[i][j] == PLAYER)
			{
				mlx->player->start_x = j + 0.5;
				mlx->player->start_y = i + 0.5;
				mlx->map[i][j] = '0';
				player = 1;
			}
			if (ft_obj_check_c(mlx->map[i][j]) == 1)
			{
				int index = ft_get_obj_index(mlx->map[i][j]);
				mlx->objs[obj_c]->is_lamp = (ft_is_obj_lamp(mlx->map[i][j]) == 1) ? 1 : 0;
				mlx->objs[obj_c]->img->img = mlx_xpm_file_to_image(mlx->mlx, mlx->obj[index], &mlx->objs[obj_c]->img->w, &mlx->objs[obj_c]->img->h);
				mlx->objs[obj_c]->img->data = (int*)mlx_get_data_addr(mlx->objs[obj_c]->img->img, &mlx->objs[obj_c]->img->bpp, &mlx->objs[obj_c]->img->size_line, &mlx->objs[obj_c]->img->endian);
				(!ft_is_obj_phys(mlx->map[i][j])) ? mlx->map[i][j] = '0' : 1;
				mlx->objs[obj_c]->y = i + 0.5;
				mlx->objs[obj_c]->x = j + 0.5;
				obj_c++;
			}
			if (ft_cobj_check(mlx->map[i][j]) == 1)
			{
				ft_lst_fill(mlx, mlx->cobjs, j + 0.5, i + 0.5, cobj_c, ft_get_cobj_index(mlx->map[i][j]));
				cobj_c++;
			}
			j++;
		}
		i++;
	}
	(player == 0) ? ft_player_error() : 1;
	//printf("asd %d\n", ft_bound_check(mlx));
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
	mlx->cobj_count = 0;
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
	printf("row %d		col %d\n", mlx->row, mlx->col);
	printf("obj count %d\n", mlx->obj_count);
	printf("cobj count %d\n\n", mlx->cobj_count);
	close(fd);
}

