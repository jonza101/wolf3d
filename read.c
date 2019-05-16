/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 21:03:30 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/16 19:34:39 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_mem_error()
{
	ft_putstr("Memory allocation error!\n");
	ft_usage();
}

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
	else if (c == WH)
		return (11);
	else if (c == BUNKWALL)
		return (12);
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
	else if (c == KNIGHT)
		return (12);
	else if (c == VASE)
		return (13);
	else if (c == TCHAIRS)
		return (14);
	else if (c == BUSH)
		return (15);
	else if (c == FLAMP)
		return (16);
	else if (c == FLAGPOLE)
		return (17);
	else if (c == GBARREL)
		return (18);
	else if (c == BUBBLER)
		return (19);
	else if (c == S_SKELETON)
		return (20);
	else if (c == K_STUFF)
		return (21);
	else if (c == B_BONES)
		return (22);
	else if (c == PILLAR)
		return (23);
	else if (c == CAGE)
		return (24);
	else if (c == S_CAGE)
		return (25);
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
	else if (c == FOOD)
		return (5);
	else if (c == DFOOD)
		return (6);
	else if (c == MEDKIT)
		return (7);
}

int		ft_cobj_is(int index)
{
	if (index == 0)
		return (0);
	else if (index > 0 && index < 5)
		return (1);
	else if (index == 5)
		return(2);
	else if (index == 6)
		return (3);
	else if (index == 7)
		return (4);
}

void	ft_on_item_check(t_mlx *mlx, int p_x, int p_y)
{
	if (ft_cobj_check(mlx->map[p_y][p_x]))
	{		
		t_cobj *temp;

		if (mlx->cobjs && (int)mlx->cobjs->x == p_x && (int)mlx->cobjs->y == p_y)
		{
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
			{
				if (mlx->cobjs->is == 2)
					mlx->player->hp += 10;
				else if (mlx->cobjs->is == 3)
					mlx->player->hp += 4;
				else if (mlx->cobjs->is == 4)
					mlx->player->hp += 25;
				(mlx->player->hp > 100) ? mlx->player->hp = 100 : 1;
				mlx->map[p_y][p_x] = SPACE;
			}
			else if (mlx->player->hp == 100)
				return ;

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

			if (mlx->cobjs->next_cobj->is == 0)
			{
				mlx->player->ammo += 5;
				mlx->map[p_y][p_x] = SPACE;
			}		
			else if (mlx->cobjs->next_cobj->is == 1)
			{
				mlx->player->score += 100;
				mlx->map[p_y][p_x] = SPACE;
			}
			else if (mlx->player->hp < 100)
			{
				if (mlx->cobjs->next_cobj->is == 2)
					mlx->player->hp += 10;
				else if (mlx->cobjs->next_cobj->is == 3)
					mlx->player->hp += 4;
				else if (mlx->cobjs->next_cobj->is == 4)
					mlx->player->hp += 25;
				(mlx->player->hp > 100) ? mlx->player->hp = 100 : 1;
				mlx->map[p_y][p_x] = SPACE;
			}
			else if (mlx->player->hp == 100)
			{
				mlx->cobjs = tmp;
				return ;
			}

			temp = mlx->cobjs->next_cobj;
			free(mlx->cobjs->next_cobj);
			mlx->cobjs->next_cobj = temp->next_cobj;
			mlx->cobjs = tmp;
		}
	}
}

int		ft_cobj_check(char c)
{
	if (c == AMMO || c == CROSS || c == CUP || c == CROWN || c == CHEST || c == FOOD || c == DFOOD || c == MEDKIT)
		return (1);
	return (0);
}

int		ft_is_obj_phys(char c)
{
	if (c == TREE || c == BARREL || c == TABLE || c == FWELL || c == EWELL || c == KNIGHT || c == VASE || c == TCHAIRS || c == BUSH
		|| c == FLAMP || c == FLAGPOLE || c == GBARREL || c == BUBBLER || c == S_SKELETON || c == PILLAR || c == CAGE || c == S_CAGE)
		return (1);
	return (0);
}

int		ft_obj_check_c(char c)
{
	if (c == SKELETON || c == CLAMP || c == BONES || c == CHAND || c == TREE || c == PUDDLE
		|| c == BARREL || c == TABLE || c == FWELL || c == EWELL || c == DPOT || c == DEAD || c == KNIGHT || c == VASE || c == TCHAIRS
			|| c == BUSH || c == FLAMP || c == FLAGPOLE || c == GBARREL || c == BUBBLER || c == S_SKELETON || c == K_STUFF || c == B_BONES
				|| c == PILLAR || c == CAGE || c == S_CAGE)
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
			|| line[i] == TABLE || line[i] == FWELL || line[i] == EWELL || line[i] == DPOT || line[i] == DEAD || line[i] == KNIGHT || line[i] == VASE
				|| line[i] == TCHAIRS || line[i] == BUSH || line[i] == FLAMP || line[i] == FLAGPOLE || line[i] == GBARREL || line[i] == BUBBLER
					|| line[i] == S_SKELETON || line[i] == K_STUFF || line[i] == B_BONES || line[i] == PILLAR || line[i] == CAGE || line[i] == S_CAGE)
			mlx->obj_count++;
		if (line[i] == AMMO || line[i] == CROSS || line[i] == CUP || line[i] == CROWN || line[i] == CHEST || line[i] == FOOD || line[i] == DFOOD
			|| line[i] == MEDKIT)
				mlx->cobj_count++;
		i++;
	}
}

int		ft_tiles_check(char **map, int p_x, int p_y)
{
	if (map[p_y][p_x] == SPACE || map[p_y][p_x] == TREE || map[p_y][p_x] == BARREL|| map[p_y][p_x] == TABLE || map[p_y][p_x] == FWELL
		|| map[p_y][p_x] == EWELL || map[p_y][p_x] == AMMO || map[p_y][p_x] == CROSS || map[p_y][p_x] == CUP || map[p_y][p_x] == CROWN
			|| map[p_y][p_x] == CHEST || map[p_y][p_x] == KNIGHT || map[p_y][p_x] == VASE || map[p_y][p_x] == TCHAIRS || map[p_y][p_x] == BUSH
				|| map[p_y][p_x] == FLAMP || map[p_y][p_x] == FLAGPOLE || map[p_y][p_x] == GBARREL || map[p_y][p_x] == FOOD
					|| map[p_y][p_x] == DFOOD || map[p_y][p_x] == MEDKIT || map[p_y][p_x] == BUBBLER || map[p_y][p_x] == S_SKELETON
						|| map[p_y][p_x] == PILLAR || map[p_y][p_x] == CAGE || map[p_y][p_x] == S_CAGE)
		return (0);
	return (1);
}

int		ft_walls_check(char **map, int player_x, int player_y)
{
	if (map[player_y][player_x] == SPACE || map[player_y][player_x] == AMMO || map[player_y][player_x] == CROSS
		|| map[player_y][player_x] == CUP || map[player_y][player_x] == CROWN || map[player_y][player_x] == CHEST
			|| map[player_y][player_x] == FOOD || map[player_y][player_x] == DFOOD || map[player_y][player_x] == MEDKIT)
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
	root->is = ft_cobj_is(cobj_index);

	root->img->img = mlx_xpm_file_to_image(mlx->mlx, mlx->cobj[cobj_index], &root->img->w, &root->img->h);
	root->img->data = (int*)mlx_get_data_addr(root->img->img, &root->img->bpp, &root->img->size_line, &root->img->endian);
}

void	ft_lst_add_img(t_mlx *mlx)
{
	if (!mlx->cobjs)
		return ;
	
	(!(mlx->cobjs->next_cobj = (t_cobj*)malloc(sizeof(t_cobj)))) ? ft_mem_error() : 1;
	mlx->cobjs = mlx->cobjs->next_cobj;
	(!(mlx->cobjs->img = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;	
	mlx->cobjs->img->w = 64;
	mlx->cobjs->img->h = 64;
}

void	ft_init_cobjects(t_mlx *mlx)
{
	int i;
	t_cobj *temp;

	i = 1;
	mlx->cobj[0] = ft_strdup("textures/cobj/ammo.xpm");
	mlx->cobj[1] = ft_strdup("textures/cobj/cross.xpm");
	mlx->cobj[2] = ft_strdup("textures/cobj/cup.xpm");
	mlx->cobj[3] = ft_strdup("textures/cobj/crown.xpm");
	mlx->cobj[4] = ft_strdup("textures/cobj/chest.xpm");
	mlx->cobj[5] = ft_strdup("textures/cobj/food.xpm");
	mlx->cobj[6] = ft_strdup("textures/cobj/dog_food.xpm");
	mlx->cobj[7] = ft_strdup("textures/cobj/medkit.xpm");

	if (mlx->cobj_count < 0)
		return ;
	
	(!(mlx->cobjs = (t_cobj*)malloc(sizeof(t_cobj)))) ? ft_mem_error() : 1;
	(!(mlx->cobjs->img = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
	mlx->cobjs->img->w = 64;
	mlx->cobjs->img->h = 64;
	temp = mlx->cobjs;

	while (i < mlx->cobj_count)
	{
		ft_lst_add_img(mlx);
		i++;
	}
	mlx->cobjs = temp;
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
	mlx->obj[12] = ft_strdup("textures/obj/knight.xpm");
	mlx->obj[13] = ft_strdup("textures/obj/vase.xpm");
	mlx->obj[14] = ft_strdup("textures/obj/t_chairs.xpm");
	mlx->obj[15] = ft_strdup("textures/obj/bush.xpm");
	mlx->obj[16] = ft_strdup("textures/obj/floor_lamp.xpm");
	mlx->obj[17] = ft_strdup("textures/obj/flagpole.xpm");
	mlx->obj[18] = ft_strdup("textures/obj/g_barrel.xpm");
	mlx->obj[19] = ft_strdup("textures/obj/bubbler.xpm");
	mlx->obj[20] = ft_strdup("textures/obj/suspended_skeleton.xpm");
	mlx->obj[21] = ft_strdup("textures/obj/kitchen_stuff.xpm");
	mlx->obj[22] = ft_strdup("textures/obj/blood_bones.xpm");
	mlx->obj[23] = ft_strdup("textures/obj/pillar.xpm");
	mlx->obj[24] = ft_strdup("textures/obj/cage.xpm");
	mlx->obj[25] = ft_strdup("textures/obj/skeleton_cage.xpm");

	i = 0;
	(!(mlx->objs = (t_obj**)malloc(sizeof(t_obj*) * mlx->obj_count))) ? ft_mem_error() : 1;
	while (i < mlx->obj_count)
	{
		(!(mlx->objs[i] = (t_obj*)malloc(sizeof(t_obj)))) ? ft_mem_error() : 1;
		(!(mlx->objs[i]->img = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
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
			"textures/wooden_wall.xpm", "textures/wooden_eagle.xpm", "textures/wood_hit.xpm", "textures/bunker_wall.xpm" };

	i = 0;
	(!(mlx->textures = (t_img**)malloc(sizeof(t_img*) * TILES))) ? ft_mem_error() : 1;

	while (i < TILES)
	{
		(!(mlx->textures[i] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
		mlx->textures[i]->w = 64;
		mlx->textures[i]->h = 64;
		mlx->textures[i]->img = mlx_xpm_file_to_image(mlx->mlx, tiles[i], &mlx->textures[i]->w, &mlx->textures[i]->h);
		mlx->textures[i]->data = (int*)mlx_get_data_addr(mlx->textures[i]->img, &mlx->textures[i]->bpp, &mlx->textures[i]->size_line, &mlx->textures[i]->endian);
		i++;
	}
}
