/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:45:19 by dsatge            #+#    #+#             */
/*   Updated: 2025/09/05 15:15:30 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	is_white_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
				|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f'))
			return (false);
		i++;
	}
	return (true);
}

int	is_whitespace(char c)
{
	if (!c)
		return (false);
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v'
		|| c == '\f')
		return (true);
	return (false);
}

int	is_line_empty(char *content, int start, int end)
{
	int	j;

	j = start;
	while (j < end)
	{
		if (content[j] != ' ' && content[j] != '\t')
			return (0);
		j++;
	}
	return (1);
}

int	is_map(t_cubed *cube, int i)
{
	if (ft_strncmp(cube->map[i], "F", 1) == 0)
		return (false);
	if (ft_strncmp(cube->map[i], "C", 1) == 0)
		return (false);
	if (ft_strncmp(cube->map[i], "EA", 2) == 0)
		return (false);
	if (ft_strncmp(cube->map[i], "WE", 2) == 0)
		return (false);
	if (ft_strncmp(cube->map[i], "NO", 2) == 0)
		return (false);
	if (ft_strncmp(cube->map[i], "SO", 2) == 0)
		return (false);
	if (is_white_line(cube->map[i]) == true)
		return (false);
	return (true);
}

void	check_max(int i, t_cubed *cube)
{
	int	x;
	int	y;

	y = i;
	x = 0;
	cube->max_wid = 0;
	cube->max_hei = 0;
	while (cube->map[y])
	{
		x = ft_strlen(cube->map[y]);
		if (x > cube->max_wid)
			cube->max_wid = x;
		y++;
	}
	cube->max_hei = y - i;
}
