/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:54:13 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/07 14:24:52 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_init_cobj_sprites(t_mlx *mlx)
{
	mlx->cobj[0] = ft_strdup("textures/cobj/ammo.xpm");
	mlx->cobj[1] = ft_strdup("textures/cobj/cross.xpm");
	mlx->cobj[2] = ft_strdup("textures/cobj/cup.xpm");
	mlx->cobj[3] = ft_strdup("textures/cobj/crown.xpm");
	mlx->cobj[4] = ft_strdup("textures/cobj/chest.xpm");
	mlx->cobj[5] = ft_strdup("textures/cobj/food.xpm");
	mlx->cobj[6] = ft_strdup("textures/cobj/dog_food.xpm");
	mlx->cobj[7] = ft_strdup("textures/cobj/medkit.xpm");
}

void	ft_init_obj_sprites_t(t_mlx *mlx)
{
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
}

void	ft_init_obj_sprites(t_mlx *mlx)
{
	mlx->obj[0] = ft_strdup("textures/obj/skeleton.xpm");
	mlx->obj[1] = ft_strdup("textures/obj/ceiling_lamp.xpm");
	mlx->obj[2] = ft_strdup("textures/obj/bones.xpm");
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
	ft_init_obj_sprites_t(mlx);
}

void	ft_init_tiles(t_mlx *mlx)
{
	mlx->tiles[0] = ft_strdup("textures/blue_wall1.xpm");
	mlx->tiles[1] = ft_strdup("textures/blue_wall2.xpm");
	mlx->tiles[2] = ft_strdup("textures/blue_cell.xpm");
	mlx->tiles[3] = ft_strdup("textures/blue_skeleton_cell.xpm");
	mlx->tiles[4] = ft_strdup("textures/gray_brick1.xpm");
	mlx->tiles[5] = ft_strdup("textures/gray_brick2.xpm");
	mlx->tiles[6] = ft_strdup("textures/gray_eagle.xpm");
	mlx->tiles[7] = ft_strdup("textures/gray_flag.xpm");
	mlx->tiles[8] = ft_strdup("textures/gray_hit.xpm");
	mlx->tiles[9] = ft_strdup("textures/wooden_wall.xpm");
	mlx->tiles[10] = ft_strdup("textures/wooden_eagle.xpm");
	mlx->tiles[11] = ft_strdup("textures/wood_hit.xpm");
	mlx->tiles[12] = ft_strdup("textures/bunker_wall.xpm");
}

void	ft_init_dark_tiles(t_mlx *mlx)
{
	mlx->dark_tiles[0] = ft_strdup("textures/gray_brick1_s.xpm");
	mlx->dark_tiles[1] = ft_strdup("textures/gray_brick2_s.xpm");
	mlx->dark_tiles[2] = ft_strdup("textures/wooden_wall_s.xpm");
}
