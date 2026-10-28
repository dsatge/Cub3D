/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:09:44 by dsatge            #+#    #+#             */
/*   Updated: 2025/09/05 17:45:15 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	fill_map_colour(t_cubed *cube)
{
	int	map_x;
	int	map_y;
	int	pix_x;
	int	pix_y;

	map_y = -1;
	pix_x = 0;
	pix_y = 0;
	while (++map_y < cube->max_hei)
	{
		map_x = -1;
		while (++map_x < cube->max_wid)
		{
			pix_x = map_x * BLOC_LEN;
			pix_y = map_y * BLOC_LEN;
			if (cube->map_formated[map_y][map_x] == '1')
				wall_colour(pix_x, pix_y, cube);
			else if (cube->map_formated[map_y][map_x] == '0')
				walk_colour(pix_x, pix_y, cube);
			else if (is_player_pos(cube->map_formated[map_y][map_x]) == true)
				player_colour(pix_x, pix_y, cube);
			else
				break ;
		}
	}
}

int	minimap(t_cubed *cube)
{
	char	*minimap;
	int		size_line;
	int		bpp;
	int		endian;

	cube->pixel_data->ptr_minimap = mlx_new_image(cube->mlx, (cube->max_wid
				* 10), (cube->max_hei * 10));
	if (cube->pixel_data->ptr_minimap == NULL)
		return (ft_printf(2, "Error\nMlx failure\n"), EXIT_FAILURE);
	minimap = mlx_get_data_addr(cube->pixel_data->ptr_minimap, &bpp, &size_line,
			&endian);
	cube->pixel_data->minimap = (unsigned char *)minimap;
	if (!cube->pixel_data->minimap)
		return (EXIT_FAILURE);
	cube->pixel_data->bpp = bpp;
	cube->pixel_data->size_len = size_line;
	fill_map_colour(cube);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->pixel_data->ptr_minimap,
		5, 5);
	return (EXIT_SUCCESS);
}
