/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:42:27 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/02 14:44:49 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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

void	ft_bounds_error(void)
{
	ft_putstr("Map boundaries Error!\n");
	ft_usage();
}

void	ft_player_error(void)
{
	ft_putstr("Player not found!\n");
	ft_usage();
}

void	ft_map_error(void)
{
	ft_putstr("Map Error!\n");
	ft_usage();
}
