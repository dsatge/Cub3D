/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_size_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:27:51 by enschnei          #+#    #+#             */
/*   Updated: 2025/09/05 17:46:42 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_size_map(t_cubed *cubed)
{
	int	line_length;
	int	i;

	line_length = ft_strlen(cubed->map[cubed->start_map]);
	if (line_length > 35)
	{
		free_texture_names(cubed->imgs);
		return (ft_printf(2, "Error\nMap is too big\n"), EXIT_FAILURE);
	}
	i = cubed->start_map;
	while (cubed->map[i])
	{
		if (i > 35)
		{
			free_texture_names(cubed->imgs);
			return (ft_printf(2, "Error\nMap is too big\n"), EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
