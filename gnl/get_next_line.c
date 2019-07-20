/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 14:49:08 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/20 14:15:37 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strchr_(char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != (char)c && s[i] != 0)
		s++;
	if (s[i] == (char)c)
		s[i] = 0;
}

void	ft_strzero(char *input, int len)
{
	while (len--)
		input[len] = 0;
}

int		str_process(char *input, char **result)
{
	char		*tmp;
	char		*tmp2;

	if (ft_strrchr(input, '\n'))
	{
		tmp = ft_strdup(input);
		input = ft_strcpy(input, &ft_strchr(input, '\n')[1]);
		ft_strchr_(tmp, 10);
		tmp2 = *result;
		*result = ft_strjoin(*result, tmp);
		free(tmp);
		free(tmp2);
		return (1);
	}
	else
	{
		tmp = *result;
		*result = ft_strjoin(*result, input);
		free(tmp);
		ft_strzero(input, BUFF_SIZE);
		return (0);
	}
}

int		get_next_line(const int fd, char **line)
{
	static char	*buff[4096];
	int			ret;

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (!buff[fd])
		buff[fd] = ft_strnew(BUFF_SIZE);
	*line = ft_strnew(0);
	if (*buff[fd])
		if (str_process(buff[fd], line))
			return (1);
	ft_strzero(buff[fd], BUFF_SIZE);
	while ((ret = read(fd, buff[fd], BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		if (str_process(buff[fd], line))
			return (1);
	}
	if (**line == 0)
		return (0);
	return (1);
}
