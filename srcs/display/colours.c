/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:22:51 by dsatge            #+#    #+#             */
/*   Updated: 2025/09/03 18:48:38 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	color_convert(int colour, int name_colour)
{
	int	res;

	if (name_colour == RED)
		res = colour >> 16 & 0xFF;
	if (name_colour == GREEN)
		res = colour >> 8 & 0xFF;
	if (name_colour == BLUE)
		res = colour & 0xFF;
	return (res);
}

void	wall_colour(int x, int y, t_cubed *cube)
{
	int	i;
	int	tmp_y;
	int	tmp_x;

	tmp_y = y;
	tmp_x = x;
	while (tmp_y < y + 10)
	{
		tmp_x = x;
		while (tmp_x < x + 10)
		{
			i = tmp_y * cube->pixel_data->size_len + tmp_x
				* (cube->pixel_data->bpp / 8);
			cube->pixel_data->minimap[i + 0] = color_convert(WALL_MAP_C, BLUE);
			cube->pixel_data->minimap[i + 1] = color_convert(WALL_MAP_C, GREEN);
			cube->pixel_data->minimap[i + 2] = color_convert(WALL_MAP_C, RED);
			cube->pixel_data->minimap[i + 3] = 0;
			tmp_x++;
		}
		tmp_y++;
	}
}

void	walk_colour(int x, int y, t_cubed *cube)
{
	int	i;
	int	tmp_y;
	int	tmp_x;

	tmp_y = y;
	tmp_x = x;
	while (tmp_y < y + 10)
	{
		tmp_x = x;
		while (tmp_x < x + 10)
		{
			i = tmp_y * cube->pixel_data->size_len + tmp_x
				* (cube->pixel_data->bpp / 8);
			cube->pixel_data->minimap[i + 0] = color_convert(FLOOR_MAP_C, BLUE);
			cube->pixel_data->minimap[i + 1] = color_convert(FLOOR_MAP_C,
					GREEN);
			cube->pixel_data->minimap[i + 2] = color_convert(FLOOR_MAP_C, RED);
			tmp_x++;
		}
		tmp_y++;
	}
}

static void	init_orientation(t_cubed *cube, int x, int y)
{
	if (cube->map_formated[y / 10][x / 10] == 'E')
		cube->player->facing_pos = 0;
	if (cube->map_formated[y / 10][x / 10] == 'S')
		cube->player->facing_pos = 90;
	if (cube->map_formated[y / 10][x / 10] == 'W')
		cube->player->facing_pos = 180;
	if (cube->map_formated[y / 10][x / 10] == 'N')
		cube->player->facing_pos = 270;
}

void	player_colour(int x, int y, t_cubed *cube)
{
	double	ray_y;
	double	ray_x;
	double	player_size;
	double	rad;

	player_size = (sqrt(PLAYER_SIZE));
	walk_colour(x, y, cube);
	cube->pixel_data->play_pix_x = x;
	cube->pixel_data->play_pix_y = y;
	cube->player->x_pos = (double)x + (BLOC_LEN / 2);
	cube->player->y_pos = (double)y + (BLOC_LEN / 2);
	init_orientation(cube, x, y);
	ray_vision(cube);
	while (player_size >= 0)
	{
		rad = 0;
		while (rad < (360 * (M_PI / 180)))
		{
			ray_x = (cos(rad) * player_size);
			ray_y = (sin(rad) * player_size);
			pix_colour(ray_x, ray_y, PLAYER_C, cube);
			rad = rad + 1 * (M_PI / 180);
		}
		player_size--;
	}
}
