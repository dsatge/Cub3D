/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:46:37 by dsatge            #+#    #+#             */
/*   Updated: 2025/09/05 17:45:10 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	fill_image_color(char *pix_char, int colour, int width, int height)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			i = y * (WIDTH * 4) + x * (BPP / 8);
			pix_char[i + 0] = color_convert(colour, BLUE);
			pix_char[i + 1] = color_convert(colour, GREEN);
			pix_char[i + 2] = color_convert(colour, RED);
			x++;
		}
		y++;
	}
}

int	display_floor_ceiling(t_cubed cube)
{
	int	bpp;
	int	width;
	int	endian;

	cube.pixel_data->ptr_background = mlx_new_image(cube.mlx, WIDTH, HEIGHT);
	if (cube.pixel_data->ptr_background == NULL)
		return (printf("Error\nMlx failure\n"), EXIT_FAILURE);
	cube.pixel_data->background
		= mlx_get_data_addr(cube.pixel_data->ptr_background,
			&bpp, &width, &endian);
	cube.pixel_data->bpp_background = bpp;
	cube.pixel_data->size_len_background = width;
	fill_image_color(cube.pixel_data->background, cube.pixel_data->floor_color,
		WIDTH, HEIGHT);
	fill_image_color(cube.pixel_data->background,
		cube.pixel_data->ceiling_color, WIDTH, HEIGHT / 2);
	cube.pixel_data->backgr_empty = malloc(HEIGHT
			* cube.pixel_data->size_len_background);
	if (!cube.pixel_data->backgr_empty)
		return (printf("Error\nMalloc failed\n"), EXIT_FAILURE);
	ft_memcpy(cube.pixel_data->backgr_empty, cube.pixel_data->background, HEIGHT
		* cube.pixel_data->size_len_background);
	mlx_put_image_to_window(cube.mlx, cube.win, cube.pixel_data->ptr_background,
		0, 0);
	return (0);
}
