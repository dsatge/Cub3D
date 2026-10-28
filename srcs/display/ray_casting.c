/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:39:00 by dsatge            #+#    #+#             */
/*   Updated: 2025/09/03 17:42:16 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_textured_wall(t_cubed *cube, double wall_hit, int wall_height)
{
	char	*texture;
	int		tex_x;
	double	tex_pos;

	texture = get_wall_texture(cube);
	if (!texture)
		return ;
	tex_x = (int)(wall_hit * 64);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= 64)
		tex_x = 63;
	if ((cube->ray->dda == VERTICAL && cube->ray->step_x == -1)
		|| (cube->ray->dda == HORIZONTAL && cube->ray->step_y == 1))
		tex_x = 64 - tex_x - 1;
	cube->imgs->tex_step = 64.0 / wall_height;
	tex_pos = (cube->imgs->draw_start - (-wall_height + HEIGHT) / 2)
		* cube->imgs->tex_step;
	put_texture(cube, texture, tex_x, tex_pos);
}

void	draw_projection(t_cubed *cube, double perp_dist)
{
	int		wall_height;
	double	wall_hit;

	wall_height = (int)(HEIGHT / perp_dist);
	cube->imgs->draw_start = (-wall_height + HEIGHT) / 2;
	cube->imgs->draw_end = (wall_height + HEIGHT) / 2;
	if (cube->imgs->draw_start < 0)
		cube->imgs->draw_start = 0;
	if (cube->imgs->draw_end >= HEIGHT)
		cube->imgs->draw_end = HEIGHT - 1;
	if (cube->ray->dda == VERTICAL)
		wall_hit = cube->ray->ray_leny_hit - floor(cube->ray->ray_leny_hit);
	else
		wall_hit = cube->ray->ray_lenx_hit - floor(cube->ray->ray_lenx_hit);
	draw_textured_wall(cube, wall_hit, wall_height);
}

void	pix_projection_column(int screen_x, int ray_width, double perp_dist,
		t_cubed *cube)
{
	if (perp_dist < 1e-6)
		perp_dist = 1e-6;
	cube->imgs->x_start = screen_x * ray_width;
	cube->imgs->x_end = cube->imgs->x_start + ray_width - 1;
	if (cube->imgs->x_start < 0)
		cube->imgs->x_start = 0;
	if (cube->imgs->x_end >= WIDTH)
		cube->imgs->x_end = WIDTH - 1;
	draw_projection(cube, perp_dist);
}

void	ray_cast(t_cubed *cube, int screen_x)
{
	double	perp_dist;

	dda(cube);
	if (cube->ray->dda == VERTICAL)
		perp_dist = (cube->ray->move_spot_x - cube->ray->player_pos_x + (1.0
					- cube->ray->step_x) * 0.5) / cube->ray->ray_rad_x;
	else
		perp_dist = (cube->ray->move_spot_y - cube->ray->player_pos_y + (1.0
					- cube->ray->step_y) * 0.5) / cube->ray->ray_rad_y;
	if (cube->ray->dda == VERTICAL)
		perp_dist = cube->ray->dist_line_x - cube->ray->delta_x;
	if (cube->ray->dda == HORIZONTAL)
		perp_dist = cube->ray->dist_line_y - cube->ray->delta_y;
	perp_dist = perp_dist * cos(cube->ray->rad
			- (angle_correction(cube->player->facing_pos) * (M_PI / 180.0)));
	if (perp_dist < 1e-6)
		perp_dist = 1e-6;
	pix_projection_column(screen_x, RAY_PER_PIX, perp_dist, cube);
}

int	ray_vision(t_cubed *cube)
{
	double	fov_rad;
	int		ray;
	double	angle_step;
	double	base_angle;

	fov_rad = (VISION_WIDE * M_PI) / 180.0;
	angle_step = fov_rad / (double)(WIDTH - 1);
	base_angle = (angle_correction(cube->player->facing_pos) * (M_PI / 180.0))
		- (fov_rad / 2.0);
	ft_memcpy(cube->pixel_data->background, cube->pixel_data->backgr_empty,
		HEIGHT * cube->pixel_data->size_len_background);
	ray = -1;
	while (++ray < WIDTH)
	{
		cube->ray->rad = base_angle + (ray * angle_step);
		if (ray % RAY_PER_PIX == 0)
			ray_cast(cube, ray / RAY_PER_PIX);
	}
	mlx_put_image_to_window(cube->mlx, cube->win,
		cube->pixel_data->ptr_background, 0, 0);
	return (0);
}
