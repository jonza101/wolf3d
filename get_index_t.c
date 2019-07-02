/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_index_t.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:55:47 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/02 16:57:39 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
	return (-1);
}

int		ft_cobj_is(int index)
{
	if (index == 0)
		return (0);
	else if (index > 0 && index < 5)
		return (1);
	else if (index == 5)
		return (2);
	else if (index == 6)
		return (3);
	else if (index == 7)
		return (4);
	return (-1);
}
