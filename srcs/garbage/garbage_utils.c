/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:42:13 by enschnei          #+#    #+#             */
/*   Updated: 2025/09/05 15:00:12 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_texture_names(t_imgs *imgs)
{
	free(imgs->east_texture);
	free(imgs->west_texture);
	free(imgs->north_texture);
	free(imgs->south_texture);
}

void	destroy_textures(t_cubed *cubed)
{
	if (!cubed || !cubed->imgs || !cubed->mlx)
		return ;
	if (cubed->imgs->ptr_east)
	{
		mlx_destroy_image(cubed->mlx, cubed->imgs->ptr_east);
		cubed->imgs->ptr_east = NULL;
	}
	if (cubed->imgs->ptr_west)
	{
		mlx_destroy_image(cubed->mlx, cubed->imgs->ptr_west);
		cubed->imgs->ptr_west = NULL;
	}
	if (cubed->imgs->ptr_north)
	{
		mlx_destroy_image(cubed->mlx, cubed->imgs->ptr_north);
		cubed->imgs->ptr_north = NULL;
	}
	if (cubed->imgs->ptr_south)
	{
		mlx_destroy_image(cubed->mlx, cubed->imgs->ptr_south);
		cubed->imgs->ptr_south = NULL;
	}
}

void	free_imgs_error_pars(t_cubed *cubed)
{
	if (cubed->imgs)
	{
		free(cubed->imgs);
		cubed->imgs = NULL;
	}
}
