/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:48:57 by dsatge            #+#    #+#             */
/*   Updated: 2025/09/03 17:41:45 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ray_hit_calc(t_cubed *cube)
{
	if (cube->ray->dda == VERTICAL)
	{
		cube->ray->x_hit = cube->ray->move_spot_x;
		cube->ray->y_hit = cube->ray->player_pos_y + (cube->ray->dist_line_x
				* cube->ray->ray_rad_y);
		cube->ray->ray_len_hit = cube->ray->dist_line_x - cube->ray->delta_x;
	}
	if (cube->ray->dda == HORIZONTAL)
	{
		cube->ray->y_hit = cube->ray->move_spot_y;
		cube->ray->x_hit = cube->ray->player_pos_x + (cube->ray->dist_line_y
				* cube->ray->ray_rad_x);
		cube->ray->ray_len_hit = cube->ray->dist_line_y - cube->ray->delta_y;
	}
	cube->ray->ray_lenx_hit = cube->ray->player_pos_x + cube->ray->ray_len_hit
		* cube->ray->ray_rad_x;
	cube->ray->ray_leny_hit = cube->ray->player_pos_y + cube->ray->ray_len_hit
		* cube->ray->ray_rad_y;
}

void	dist_line_calc(t_cubed *cube)
{
	if (cube->ray->ray_rad_x > 0)
	{
		cube->ray->dist_line_x = (cube->ray->move_spot_x + 1.0
				- cube->ray->player_pos_x) * cube->ray->delta_x;
		cube->ray->step_x = 1;
	}
	else
	{
		cube->ray->dist_line_x = (cube->ray->player_pos_x
				- cube->ray->move_spot_x) * cube->ray->delta_x;
		cube->ray->step_x = -1;
	}
	if (cube->ray->ray_rad_y > 0)
	{
		cube->ray->dist_line_y = (cube->ray->move_spot_y + 1.0
				- cube->ray->player_pos_y) * cube->ray->delta_y;
		cube->ray->step_y = 1;
	}
	else
	{
		cube->ray->dist_line_y = (cube->ray->player_pos_y
				- cube->ray->move_spot_y) * cube->ray->delta_y;
		cube->ray->step_y = -1;
	}
}

void	init_dda(t_cubed *cube)
{
	cube->ray->player_pos_x = cube->player->x_pos / BLOC_LEN;
	cube->ray->player_pos_y = cube->player->y_pos / BLOC_LEN;
	cube->ray->ray_rad_x = cos(cube->ray->rad);
	cube->ray->ray_rad_y = sin(cube->ray->rad);
	cube->ray->move_spot_x = cube->ray->player_pos_x;
	cube->ray->move_spot_y = cube->ray->player_pos_y;
	if (cube->ray->ray_rad_x == 0.0)
		cube->ray->delta_x = 1e30;
	else
		cube->ray->delta_x = fabs(1.0 / cube->ray->ray_rad_x);
	if (cube->ray->ray_rad_y == 0.0)
		cube->ray->delta_y = 1e30;
	else
		cube->ray->delta_y = fabs(1.0 / cube->ray->ray_rad_y);
	dist_line_calc(cube);
}

void	dda(t_cubed *cube)
{
	int	hit;

	init_dda(cube);
	hit = 0;
	while (hit == 0)
	{
		if (cube->ray->dist_line_x < cube->ray->dist_line_y)
		{
			cube->ray->dist_line_x += cube->ray->delta_x;
			cube->ray->move_spot_x += cube->ray->step_x;
			cube->ray->dda = VERTICAL;
		}
		else
		{
			cube->ray->dist_line_y += cube->ray->delta_y;
			cube->ray->move_spot_y += cube->ray->step_y;
			cube->ray->dda = HORIZONTAL;
		}
		if (cube->map_formated[cube->ray->move_spot_y][cube->ray->move_spot_x]
			== '1')
			hit = 1;
	}
	ray_hit_calc(cube);
}
