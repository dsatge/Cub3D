/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:23:48 by enschnei          #+#    #+#             */
/*   Updated: 2025/09/05 17:47:34 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_map_line(const char *line)
{
	if (!line)
		return (0);
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (0);
	if (*line == '\0' || *line == '\n')
		return (0);
	while (*line)
	{
		if (*line == '1' || *line == '0' || *line == 'N' || *line == 'S'
			|| *line == 'E' || *line == 'W' || *line == ' ')
			return (1);
		line++;
	}
	return (0);
}

void	start_map(t_cubed *cubed)
{
	int	i;

	i = 0;
	while (cubed->map[i])
	{
		if (is_map_line(cubed->map[i]))
		{
			cubed->start_map = i;
			return ;
		}
		i++;
	}
}

int	parsing_floor_color(t_pixel_data *pixel_data, char *line)
{
	int	red;
	int	green;
	int	blue;

	if (check_looong(line) == 1)
		return (ft_printf(2, "Error\nRGB values too long\n"), EXIT_FAILURE);
	if (parse_rgb(line, &red, &green, &blue) == EXIT_FAILURE)
	{
		ft_printf(2, "Error\nInvalid floor RGB values\n");
		return (EXIT_FAILURE);
	}
	pixel_data->floor_color = (red << 16) | (green << 8) | blue;
	return (EXIT_SUCCESS);
}

int	parsing_ceiling_color(t_pixel_data *pixel_data, char *line)
{
	int	red;
	int	green;
	int	blue;

	if (check_looong(line) == 1)
		return (ft_printf(2, "Error\nRGB values too long\n"), EXIT_FAILURE);
	if (parse_rgb(line, &red, &green, &blue) == EXIT_FAILURE)
	{
		ft_printf(2, "Error\nInvalid floor RGB values\n");
		return (EXIT_FAILURE);
	}
	pixel_data->ceiling_color = (red << 16) | (green << 8) | blue;
	return (EXIT_SUCCESS);
}

int	ends_with_xpm(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (strcmp(filename + len - 4, ".xpm") == 0);
}
