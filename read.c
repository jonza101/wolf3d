/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 21:03:30 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/04/10 23:18:20 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_get_tile_index(char c)
{
	if (c == BW1)
		return (0);
	else if (c == BW2)
		return (1);
	else if (c == CELL)
		return (2);
	else if (c == SCELL)
		return (3);
	else if (c == GB1)
		return (4);
	else if (c == GB2)
		return (5);
	else if (c == EAGLE)
		return (6);
	else if (c == FLAG)
		return (7);
	else if (c == GH)
		return (8);
	else if (c == WW)
		return (9);
	else if (c == WEAGLE)
		return (10);
}

int		ft_get_obj_index(char c)
{
	if (c == SKELETON)
		return (0);
	else if (c == CLAMP)
		return (1);
	else if (c == BONES)
		return (2);
	else if (c == CHAND)
		return (3);
	else if (c == TREE)
		return (4);
	else if (c == PUDDLE)
		return (5);
	else if (c == BARREL)
		return (6);
	else if (c == TABLE)
		return (7);
	else if (c == FWELL)
		return (8);
	else if (c == EWELL)
		return (9);
	else if (c == DPOT)
		return (10);
	else if (c == DEAD)
		return (11);
}

int		ft_get_cobj_index(char c)
{
	if (c == AMMO)
		return (0);
	else if (c == CROSS)
		return (1);
	else if (c == CUP)
		return (2);
	else if (c == CROWN)
		return (3);
	else if (c == CHEST)
		return (4);
}

void	ft_on_item_check(t_mlx *mlx, int p_x, int p_y)
{
	if (mlx->map[p_y][p_x] == AMMO || mlx->map[p_y][p_x] == CROSS || mlx->map[p_y][p_x] == CUP ||
		mlx->map[p_y][p_x] == CROWN || mlx->map[p_y][p_x] == CHEST)
	{
		mlx->map[p_y][p_x] = SPACE;
		
		t_cobj *temp;

		if (mlx->cobjs && (int)mlx->cobjs->x == p_x && (int)mlx->cobjs->y == p_y)
		{
			if (mlx->cobjs->is_treasure == 0)
				mlx->ammo += 10;
			else
				mlx->score += 100;

			temp = mlx->cobjs;
			free(mlx->cobjs);
			mlx->cobjs = temp->next_cobj;
		}
		else
		{
			int i = 1;
			t_cobj *tmp;

			tmp = mlx->cobjs;
			while (mlx->cobjs->next_cobj && ((int)mlx->cobjs->next_cobj->x != p_x || (int)mlx->cobjs->next_cobj->y != p_y))
				mlx->cobjs = mlx->cobjs->next_cobj;

			if (mlx->cobjs->next_cobj->is_treasure == 0)
				mlx->ammo += 10;
			else
				mlx->score += 100;

			temp = mlx->cobjs->next_cobj;
			free(mlx->cobjs->next_cobj);
			mlx->cobjs->next_cobj = temp->next_cobj;
			mlx->cobjs = tmp;
		}
	}
}

int		ft_cobj_check(char c)
{
	if (c == AMMO || c == CROSS || c == CUP || c == CROWN || c == CHEST)
		return (1);
	return (0);
}

int		ft_is_obj_lamp(char c)
{
	if (c == CLAMP || c == CHAND)
		return (1);
	return (0);
}

int		ft_is_obj_phys(char c)
{
	if (c == TREE || c == BARREL || c == TABLE || c == FWELL || c == EWELL)
		return (1);
	return (0);
}

int		ft_obj_check_c(char c)
{
	if (c == SKELETON || c == CLAMP || c == BONES || c == CHAND || c == TREE || c == PUDDLE
		|| c == BARREL || c == TABLE || c == FWELL || c == EWELL || c == DPOT || c == DEAD)
		return (1);
	return (0);
}

void	ft_obj_check(t_mlx *mlx, char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == SKELETON || line[i] == CLAMP || line[i] == BONES || line[i] == CHAND || line[i] == TREE || line[i] == PUDDLE || line[i] == BARREL
			|| line[i] == TABLE || line[i] == FWELL || line[i] == EWELL || line[i] == DPOT || line[i] == DEAD)
			mlx->obj_count++;
		if (line[i] == AMMO || line[i] == CROSS || line[i] == CUP || line[i] == CROWN || line[i] == CHEST)
			mlx->cobj_count++;
		i++;
	}
}

int		ft_tiles_check(char **map, int p_x, int p_y)
{
	if (map[p_y][p_x] == SPACE || map[p_y][p_x] == TREE || map[p_y][p_x] == BARREL|| map[p_y][p_x] == TABLE || map[p_y][p_x] == FWELL
		|| map[p_y][p_x] == EWELL || map[p_y][p_x] == AMMO || map[p_y][p_x] == CROSS || map[p_y][p_x] == CUP || map[p_y][p_x] == CROWN
			|| map[p_y][p_x] == CHEST)
		return (0);
	return (1);
}

int		ft_walls_check(char **map, int player_x, int player_y)
{
	if (map[player_y][player_x] == SPACE || map[player_y][player_x] == AMMO || map[player_y][player_x] == CROSS
		|| map[player_y][player_x] == CUP || map[player_y][player_x] == CROWN || map[player_y][player_x] == CHEST)
		return (1);
	return (0);
}

int		ft_texture_sampling(t_img *img, double sample_x, double sample_y)
{
	int sx = sample_x * (double)img->w;
	int sy = sample_y * (double)img->h;
	if (sx < 0 || sx > img->w || sy < 0 || sy > img->h)
		return (0x0);
	else
		return (img->data[sy * img->w + sx]);
}

void	ft_lst_fill(t_mlx *mlx, t_cobj *root, double x, double y, int cobj_c, int cobj_index)
{
	int i;

	i = 0;
	if (!root)
		return ;
	while (i < cobj_c)
	{
		root = root->next_cobj;
		i++;
	}
	root->x = x;
	root->y = y;
	root->is_treasure = (cobj_index > 0) ? 1 : 0;

	root->img->img = mlx_xpm_file_to_image(mlx->mlx, mlx->cobj[cobj_index], &root->img->w, &root->img->h);
	root->img->data = (int*)mlx_get_data_addr(root->img->img, &root->img->bpp, &root->img->size_line, &root->img->endian);
}

void	ft_lst_add_img(t_cobj *root)
{
	if (!root)
		return ;
	while (root->next_cobj)
		root = root->next_cobj;

	root->next_cobj = (t_cobj*)malloc(sizeof(t_cobj));
	root = root->next_cobj;
	root->img = (t_img*)malloc(sizeof(t_img));
	root->img->w = 64;
	root->img->h = 64;
}

void	ft_init_cobjects(t_mlx *mlx)
{
	int i;

	i = 1;
	mlx->cobj[0] = ft_strdup("textures/cobj/ammo.xpm");
	mlx->cobj[1] = ft_strdup("textures/cobj/cross.xpm");
	mlx->cobj[2] = ft_strdup("textures/cobj/cup.xpm");
	mlx->cobj[3] = ft_strdup("textures/cobj/crown.xpm");
	mlx->cobj[4] = ft_strdup("textures/cobj/chest.xpm");

	mlx->cobjs = (t_cobj*)malloc(sizeof(t_cobj));
	mlx->cobjs->img = (t_img*)malloc(sizeof(t_img));
	mlx->cobjs->img->w = 64;
	mlx->cobjs->img->h = 64;

	if (mlx->cobj_count <= 1)
		return ;

	while (i < mlx->cobj_count)
	{
		ft_lst_add_img(mlx->cobjs);	
		i++;
	}
}

void	ft_init_objects(t_mlx *mlx)
{
	int i;
	mlx->obj[0] = ft_strdup("textures/obj/skeleton.xpm");
	mlx->obj[1] =  ft_strdup("textures/obj/ceiling_lamp.xpm");
	mlx->obj[2] =  ft_strdup("textures/obj/bones.xpm");
	mlx->obj[3] = ft_strdup("textures/obj/chandelier.xpm");
	mlx->obj[4] = ft_strdup("textures/obj/tree.xpm");
	mlx->obj[5] = ft_strdup("textures/obj/puddle.xpm");
	mlx->obj[6] = ft_strdup("textures/obj/barrel.xpm");
	mlx->obj[7] = ft_strdup("textures/obj/table.xpm");
	mlx->obj[8] = ft_strdup("textures/obj/f_well.xpm");
	mlx->obj[9] = ft_strdup("textures/obj/e_well.xpm");
	mlx->obj[10] = ft_strdup("textures/obj/dog_pot.xpm");
	mlx->obj[11] = ft_strdup("textures/obj/dead.xpm");

	i = 0;
	mlx->objs = (t_obj**)malloc(sizeof(t_obj*) * mlx->obj_count);
	while (i < mlx->obj_count)
	{
		mlx->objs[i] = (t_obj*)malloc(sizeof(t_obj));
		mlx->objs[i]->img = (t_img*)malloc(sizeof(t_img));
		mlx->objs[i]->img->w = 64;
		mlx->objs[i]->img->h = 64;
		i++;
	}
}

void	ft_init_textures(t_mlx *mlx)
{
	int i;
	char *tiles[TILES] = { "textures/blue_wall1.xpm", "textures/blue_wall2.xpm", "textures/blue_cell.xpm", "textures/blue_skeleton_cell.xpm",
		"textures/gray_brick1.xpm", "textures/gray_brick2.xpm", "textures/gray_eagle.xpm", "textures/gray_flag.xpm", "textures/gray_hit.xpm",
			"textures/wooden_wall.xpm", "textures/wooden_eagle.xpm" };

	i = 0;
	mlx->textures = (t_img**)malloc(sizeof(t_img*) * TILES);

	while (i < TILES)
	{
		mlx->textures[i] = (t_img*)malloc(sizeof(t_img));
		mlx->textures[i]->w = 64;
		mlx->textures[i]->h = 64;
		mlx->textures[i]->img = mlx_xpm_file_to_image(mlx->mlx, tiles[i], &mlx->textures[i]->w, &mlx->textures[i]->h);
		mlx->textures[i]->data = (int*)mlx_get_data_addr(mlx->textures[i]->img, &mlx->textures[i]->bpp, &mlx->textures[i]->size_line, &mlx->textures[i]->endian);
		i++;
	}
}