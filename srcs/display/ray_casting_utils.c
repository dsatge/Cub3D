/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:07:13 by dsatge            #+#    #+#             */
/*   Updated: 2025/09/03 16:12:34 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	orientation_color(t_cubed *cube)
{
	if (cube->ray->dda == VERTICAL && cube->ray->step_x == 1)
		return (EAST_C);
	else if (cube->ray->dda == VERTICAL && cube->ray->step_x == -1)
		return (WEST_C);
	else if (cube->ray->dda == HORIZONTAL && cube->ray->step_y == 1)
		return (SOUTH_C);
	else if (cube->ray->dda == HORIZONTAL && cube->ray->step_y == -1)
		return (NORTH_C);
	return (0);
}

int	angle_correction(float angle)
{
	if (angle < 0)
		angle = 360 + angle;
	else if (angle > 360)
		angle = angle - 360;
	return (angle);
}

int	get_texture_pixel(char *texture, int tex_x, int tex_y, int tex_width)
{
	int	pixel_index;

	if (tex_x < 0 || tex_x >= tex_width || tex_y < 0 || tex_y >= 64)
		return (0);
	pixel_index = (tex_y * tex_width + tex_x) * 4;
	return (*(int *)(texture + pixel_index));
}

char	*get_wall_texture(t_cubed *cube)
{
	if (cube->ray->dda == VERTICAL)
	{
		if (cube->ray->step_x == 1)
			return (cube->imgs->east_texture);
		else
			return (cube->imgs->west_texture);
	}
	else
	{
		if (cube->ray->step_y == 1)
			return (cube->imgs->south_texture);
		else
			return (cube->imgs->north_texture);
	}
}

void	put_texture(t_cubed *cube, char *texture, int tex_x, double tex_pos)
{
	int	x;
	int	y;
	int	tex_y;
	int	i;
	int	color;

	y = cube->imgs->draw_start;
	while (y <= cube->imgs->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= 64)
			tex_y = 63;
		color = get_texture_pixel(texture, tex_x, tex_y, 64);
		x = cube->imgs->x_start;
		while (x <= cube->imgs->x_end)
		{
			i = (y * cube->pixel_data->size_len_background)
				+ (x * (cube->pixel_data->bpp_background / 8));
			*(int *)(cube->pixel_data->background + i) = color;
			x++;
		}
		tex_pos += cube->imgs->tex_step;
		y++;
	}	
}
