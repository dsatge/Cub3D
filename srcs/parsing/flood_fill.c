/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:00:13 by enschnei          #+#    #+#             */
/*   Updated: 2025/09/05 17:45:32 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	cpy_map(t_cubed *cubed)
{
	int	i;
	int	y;

	i = 0;
	while (is_map(cubed, i) == false)
		i++;
	cubed->cpy_map = ft_calloc(cubed->max_hei + 1, sizeof(char *));
	if (!cubed->cpy_map)
		return (ft_printf(2, "Error\nMalloc cpy_map failed\n"), EXIT_FAILURE);
	y = 0;
	while (cubed->map[i])
	{
		if (copy_line(&cubed->cpy_map[y], cubed->map[i], cubed->max_wid) != 0)
			return (ft_freetab(cubed->cpy_map), EXIT_FAILURE);
		i++;
		y++;
	}
	cubed->cpy_map[y] = NULL;
	return (EXIT_SUCCESS);
}

static void	find_spawn_in_cpy(t_cubed *cubed)
{
	int	i;
	int	j;

	i = 0;
	while (cubed->cpy_map[i])
	{
		j = 0;
		while (cubed->cpy_map[i][j])
		{
			if (ft_strchr("NSEW", cubed->cpy_map[i][j]))
			{
				cubed->spwn_x = i;
				cubed->spwn_y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

static int	flood_fill(t_cubed *cubed, int x, int y)
{
	if (x < 0 || y < 0 || x >= cubed->max_hei || y >= cubed->max_wid)
		return (EXIT_FAILURE);
	if ((x == 0 || x == cubed->max_hei - 1 || y == 0 || y == cubed->max_wid - 1)
		&& (cubed->cpy_map[x][y] == '0' || cubed->cpy_map[x][y] == ' '
			|| ft_strchr("NSEW", cubed->cpy_map[x][y])))
		return (EXIT_FAILURE);
	if (cubed->cpy_map[x][y] == '1' || cubed->cpy_map[x][y] == 'F')
		return (EXIT_SUCCESS);
	if (cubed->cpy_map[x][y] != '0' && cubed->cpy_map[x][y] != ' '
		&& !ft_strchr("NSEW", cubed->cpy_map[x][y]))
		return (EXIT_SUCCESS);
	cubed->cpy_map[x][y] = 'F';
	if (flood_fill(cubed, x + 1, y) == EXIT_FAILURE || flood_fill(cubed, x - 1,
			y) == EXIT_FAILURE || flood_fill(cubed, x, y + 1) == EXIT_FAILURE
		|| flood_fill(cubed, x, y - 1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_unreachable_areas(t_cubed *cubed)
{
	int	x;
	int	y;

	x = 0;
	while (x < cubed->max_hei)
	{
		y = 0;
		while (y < cubed->max_wid)
		{
			if (cubed->cpy_map[x][y] == '0' || ft_strchr("NSEW",
					cubed->cpy_map[x][y]))
			{
				if (flood_fill(cubed, x, y) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			y++;
		}
		x++;
	}
	return (EXIT_SUCCESS);
}

int	check_flood_fill(t_cubed *cubed)
{
	check_max(cubed->start_map, cubed);
	if (cpy_map(cubed) == EXIT_FAILURE)
		return (ft_printf(2, "Error\nCopy map failed\n"), EXIT_FAILURE);
	find_spawn_in_cpy(cubed);
	if (flood_fill(cubed, cubed->spwn_x, cubed->spwn_y) == EXIT_FAILURE
		|| check_unreachable_areas(cubed) == EXIT_FAILURE)
	{
		ft_printf(2, "Error\nThe map is not surrounded by a wall\n");
		ft_freetab(cubed->cpy_map);
		free_texture_names(cubed->imgs);
		return (EXIT_FAILURE);
	}
	ft_freetab(cubed->cpy_map);
	return (EXIT_SUCCESS);
}
