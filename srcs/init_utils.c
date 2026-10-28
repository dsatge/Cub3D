/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:47:00 by enschnei          #+#    #+#             */
/*   Updated: 2025/09/03 16:58:29 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cleanup_textures(t_cubed *cubed)
{
	if (cubed->imgs->ptr_east)
		mlx_destroy_image(cubed->mlx, cubed->imgs->ptr_east);
	if (cubed->imgs->ptr_west)
		mlx_destroy_image(cubed->mlx, cubed->imgs->ptr_west);
	if (cubed->imgs->ptr_north)
		mlx_destroy_image(cubed->mlx, cubed->imgs->ptr_north);
	if (cubed->imgs->ptr_south)
		mlx_destroy_image(cubed->mlx, cubed->imgs->ptr_south);
	cubed->imgs->ptr_east = NULL;
	cubed->imgs->ptr_west = NULL;
	cubed->imgs->ptr_north = NULL;
	cubed->imgs->ptr_south = NULL;
}
