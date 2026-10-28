/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:09:00 by enschnei          #+#    #+#             */
/*   Updated: 2025/09/05 17:46:33 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_colors(t_cubed *cubed)
{
	cubed->pixel_data = ft_calloc(1, sizeof(t_pixel_data));
	if (!cubed->pixel_data)
		return (ft_printf(2, "Error\nMalloc pixel_data failed\n"),
			EXIT_FAILURE);
	cubed->pixel_data->floor_color = 0;
	cubed->pixel_data->ceiling_color = 0;
	return (EXIT_SUCCESS);
}

int	validate_rgb_value(int value)
{
	return (value >= 0 && value <= 255);
}

int	check_looong(char *str)
{
	while (*str == 'F' || *str == 'C')
		str++;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	if (ft_strlen(str) > 11)
		return (1);
	return (0);
}

static int	is_valid_rgb_component(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	parse_rgb(char *line, int *r, int *g, int *b)
{
	char	**components;
	int		i;

	line += 2;
	components = ft_split(line, ',');
	if (!components)
		return (EXIT_FAILURE);
	i = 0;
	while (components[i])
		i++;
	if (i != 3)
		return (ft_freetab(components), EXIT_FAILURE);
	if (!is_valid_rgb_component(components[0])
		|| !is_valid_rgb_component(components[1])
		|| !is_valid_rgb_component(components[2]))
		return (ft_freetab(components), EXIT_FAILURE);
	*r = ft_atoi(components[0]);
	*g = ft_atoi(components[1]);
	*b = ft_atoi(components[2]);
	if (!validate_rgb_value(*r) || !validate_rgb_value(*g)
		|| !validate_rgb_value(*b))
		return (ft_freetab(components), EXIT_FAILURE);
	ft_freetab(components);
	return (EXIT_SUCCESS);
}
