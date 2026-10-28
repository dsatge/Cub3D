/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:38:18 by dsatge            #+#    #+#             */
/*   Updated: 2025/09/02 19:12:24 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	pix_colour(double ray_x, double ray_y, int colour, t_cubed *cube)
{
	int	i;

	i = ((int)(cube->player->y_pos + (PLAYER_SIZE / 2) + ray_y)
			* cube->pixel_data->size_len) + ((int)(cube->player->x_pos
				+ (PLAYER_SIZE / 2) + ray_x) * (cube->pixel_data->bpp / 8));
	cube->pixel_data->minimap[i + 0] = color_convert(colour, BLUE);
	cube->pixel_data->minimap[i + 1] = color_convert(colour, GREEN);
	cube->pixel_data->minimap[i + 2] = color_convert(colour, RED);
}

void	change_pix(t_cubed *cube, int colour)
{
	double	rad;
	double	ray_x;
	double	ray_y;
	double	player_size;

	rad = 0;
	ray_x = 0;
	ray_y = 0;
	player_size = (sqrt(PLAYER_SIZE));
	while (player_size >= 0)
	{
		rad = 0;
		while (rad < (360 * (M_PI / 180)))
		{
			ray_x = (cos(rad) * player_size);
			ray_y = (sin(rad) * player_size);
			pix_colour(ray_x, ray_y, colour, cube);
			rad = rad + 1 * (M_PI / 180);
		}
		player_size--;
	}
}

void	angle(int dir, t_cubed *cube)
{
	int	angle_max;

	angle_max = 0;
	if (dir == KEY_LEFT)
	{
		cube->player->facing_pos -= ROTATE_SPEED;
		if (cube->player->facing_pos < 0)
		{
			angle_max = cube->player->facing_pos;
			cube->player->facing_pos = 360 + angle_max;
		}
	}
	if (dir == KEY_RIGHT)
	{
		cube->player->facing_pos += ROTATE_SPEED;
		if (cube->player->facing_pos > 360)
		{
			angle_max = cube->player->facing_pos;
			cube->player->facing_pos = angle_max - 360;
		}
	}
}

static int	check_path(int dir, t_cubed *cube)
{
	if (dir == KEY_W)
		move_player_forward(cube);
	if (dir == KEY_A || dir == KEY_D)
		move_player_side(cube, dir);
	if (dir == KEY_S)
		move_player_backward(cube);
	return (0);
}

int	loop_handler(t_cubed *cubed)
{
	if (cubed->keys[KEY_W])
		check_path(KEY_W, cubed);
	if (cubed->keys[KEY_S])
		check_path(KEY_S, cubed);
	if (cubed->keys[KEY_A])
		check_path(KEY_A, cubed);
	if (cubed->keys[KEY_D])
		check_path(KEY_D, cubed);
	if (cubed->keys[KEY_LEFT])
		angle(KEY_LEFT, cubed);
	else if (cubed->keys[KEY_RIGHT])
		angle(KEY_RIGHT, cubed);
	if (ray_vision(cubed) == EXIT_FAILURE)
		return (free_all(cubed), 1);
	mlx_put_image_to_window(cubed->mlx, cubed->win,
		cubed->pixel_data->ptr_minimap, 5, 5);
	return (0);
}
