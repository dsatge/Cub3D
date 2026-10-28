/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:37:00 by enschnei          #+#    #+#             */
/*   Updated: 2025/09/05 17:46:27 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_double_txt(t_imgs *imgs)
{
	if (imgs->east_texture && imgs->west_texture && imgs->north_texture
		&& imgs->south_texture)
	{
		if (ft_strcmp(imgs->east_texture, imgs->west_texture) == 0
			|| ft_strcmp(imgs->east_texture, imgs->north_texture) == 0
			|| ft_strcmp(imgs->east_texture, imgs->south_texture) == 0
			|| ft_strcmp(imgs->west_texture, imgs->north_texture) == 0
			|| ft_strcmp(imgs->west_texture, imgs->south_texture) == 0
			|| ft_strcmp(imgs->north_texture, imgs->south_texture) == 0)
			return (free_texture_names(imgs), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	check_format_texture(t_imgs *imgs)
{
	if (imgs->east_texture && !ends_with_xpm(imgs->east_texture))
		return (ft_printf(2, "Error\nEast texture must be .xpm\n"),
			EXIT_FAILURE);
	if (imgs->west_texture && !ends_with_xpm(imgs->west_texture))
		return (ft_printf(2, "Error\nWest texture must be .xpm\n"),
			EXIT_FAILURE);
	if (imgs->north_texture && !ends_with_xpm(imgs->north_texture))
		return (ft_printf(2, "Error\nNorth texture must be .xpm\n"),
			EXIT_FAILURE);
	if (imgs->south_texture && !ends_with_xpm(imgs->south_texture))
		return (ft_printf(2, "Error\nSouth texture must be .xpm\n"),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parsing_textures(t_cubed *cubed)
{
	cubed->imgs = malloc(sizeof(t_imgs));
	if (!cubed->imgs)
		return (ft_printf(2, "Error\nMalloc imgs failed\n"), EXIT_FAILURE);
	init_string_textures(cubed->imgs);
	if (stack_name_txt(cubed) == EXIT_FAILURE)
	{
		free(cubed->imgs);
		return (ft_printf(2, "Error\nStack name texture failed\n"),
			EXIT_FAILURE);
	}
	if (cubed->imgs->east_texture == NULL || cubed->imgs->west_texture == NULL
		|| cubed->imgs->north_texture == NULL
		|| cubed->imgs->south_texture == NULL)
	{
		free_texture_names(cubed->imgs);
		free(cubed->imgs);
		return (ft_printf(2, "Error\nMissing texture\n"), EXIT_FAILURE);
	}
	if (check_double_txt(cubed->imgs) == EXIT_FAILURE)
		return (free(cubed->imgs), ft_printf(2, "Error\nSame texture\n"),
			EXIT_FAILURE);
	if (check_format_texture(cubed->imgs) == EXIT_FAILURE)
		return (free_texture_names(cubed->imgs), free(cubed->imgs),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	count_coma(t_cubed *cubed, int i)
{
	int	coma;
	int	j;

	coma = 0;
	j = 0;
	while (cubed->map[i][j])
	{
		if (cubed->map[i][j] == ',')
			coma++;
		j++;
	}
	if (coma > 2)
		return (free_texture_names(cubed->imgs),
			ft_printf(2, "Error\nToo many colors\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parsing_nbr_colors(t_cubed *cubed)
{
	int	i;

	i = 0;
	while (i < cubed->start_map)
	{
		if (ft_strncmp(cubed->map[i], "F ", 2) == 0)
		{
			if (count_coma(cubed, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (ft_strncmp(cubed->map[i], "C ", 2) == 0)
		{
			if (count_coma(cubed, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
