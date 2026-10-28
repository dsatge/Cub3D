/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:06:04 by dsatge            #+#    #+#             */
/*   Updated: 2025/09/02 17:17:46 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	colour_check(t_cubed *cube, double pix_x, double pix_y)
{
	double	rad;
	double	ray_x;
	double	ray_y;
	int		ray;

	rad = 0;
	while (rad < 2 * M_PI)
	{
		ray_x = cos(rad) * (sqrt(PLAYER_SIZE) + 1);
		ray_y = sin(rad) * (sqrt(PLAYER_SIZE) + 1);
		ray = ((int)(cube->player->y_pos + (PLAYER_SIZE / 2) + ray_y + pix_y)
				* cube->pixel_data->size_len) + ((int)(cube->player->x_pos
					+ (PLAYER_SIZE / 2) + ray_x + pix_x)
				* (cube->pixel_data->bpp / 8));
		if (cube->pixel_data->minimap[ray + 0] == color_convert(WALL_MAP_C,
				BLUE) && cube->pixel_data->minimap[ray
				+ 1] == color_convert(WALL_MAP_C, GREEN)
			&& cube->pixel_data->minimap[ray + 2] == color_convert(WALL_MAP_C,
				RED))
			return (1);
		rad += (M_PI / 180);
	}
	return (0);
}

void	move_player_backward(t_cubed *cube)
{
	double	rad;
	double	angle;
	double	pix_x;
	double	pix_y;

	angle = (cube->player->facing_pos - 180);
	if (angle > 360)
		angle = angle - 360;
	if (angle < 0)
		angle = 360 + angle;
	rad = angle * (M_PI / 180.0);
	pix_x = (cos(rad) * STEP_LEN);
	pix_y = (sin(rad) * STEP_LEN);
	if (colour_check(cube, pix_x, pix_y) == 0)
	{
		change_pix(cube, FLOOR_MAP_C);
		cube->player->x_pos += pix_x;
		cube->player->y_pos += pix_y;
		change_pix(cube, PLAYER_C);
	}
}

void	move_player_side(t_cubed *cube, int dir)
{
	double	rad;
	double	angle;
	double	pix_y;
	double	pix_x;

	if (dir == KEY_A)
		angle = cube->player->facing_pos - 90;
	if (dir == KEY_D)
		angle = cube->player->facing_pos + 90;
	if (angle > 360)
		angle = angle - 360;
	if (angle < 0)
		angle = 360 + angle;
	rad = angle * (M_PI / 180.0);
	pix_x = (cos(rad) * STEP_LEN);
	pix_y = (sin(rad) * STEP_LEN);
	if (colour_check(cube, pix_x, pix_y) == 0)
	{
		change_pix(cube, FLOOR_MAP_C);
		cube->player->x_pos += pix_x;
		cube->player->y_pos += pix_y;
		change_pix(cube, PLAYER_C);
	}
}

void	move_player_forward(t_cubed *cube)
{
	double	rad;
	double	pix_x;
	double	pix_y;

	rad = cube->player->facing_pos * (M_PI / 180.0);
	pix_x = (cos(rad) * STEP_LEN);
	pix_y = (sin(rad) * STEP_LEN);
	if (colour_check(cube, pix_x, pix_y) == 0)
	{
		change_pix(cube, FLOOR_MAP_C);
		cube->player->x_pos += pix_x;
		cube->player->y_pos += pix_y;
		change_pix(cube, PLAYER_C);
	}
}
