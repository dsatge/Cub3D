/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:37:46 by enschnei          #+#    #+#             */
/*   Updated: 2025/09/05 17:44:30 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_string_textures(t_imgs *imgs)
{
	imgs->east_texture = NULL;
	imgs->west_texture = NULL;
	imgs->north_texture = NULL;
	imgs->south_texture = NULL;
	imgs->imgs = NULL;
	return (EXIT_SUCCESS);
}

void	init_null(t_cubed *cubed)
{
	cubed->imgs->ptr_east = NULL;
	cubed->imgs->ptr_west = NULL;
	cubed->imgs->ptr_north = NULL;
	cubed->imgs->ptr_south = NULL;
}

int	fill_ptr_texture(t_cubed *cubed)
{
	int	w;
	int	h;

	init_null(cubed);
	cubed->imgs->ptr_east = mlx_xpm_file_to_image(cubed->mlx,
			cubed->imgs->east_texture, &w, &h);
	cubed->imgs->ptr_west = mlx_xpm_file_to_image(cubed->mlx,
			cubed->imgs->west_texture, &w, &h);
	cubed->imgs->ptr_north = mlx_xpm_file_to_image(cubed->mlx,
			cubed->imgs->north_texture, &w, &h);
	cubed->imgs->ptr_south = mlx_xpm_file_to_image(cubed->mlx,
			cubed->imgs->south_texture, &w, &h);
	if (!cubed->imgs->ptr_east || !cubed->imgs->ptr_west
		|| !cubed->imgs->ptr_north || !cubed->imgs->ptr_south)
	{
		free_texture_names(cubed->imgs);
		cleanup_textures(cubed);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_textures(t_cubed *cubed)
{
	int	bpp;
	int	size_line;
	int	endian;

	if (!cubed->imgs)
		return (ft_printf(2, "Error\nImgs not initialized\n"), EXIT_FAILURE);
	if (fill_ptr_texture(cubed) == EXIT_FAILURE)
	{
		free_imgs_error_pars(cubed);
		return (ft_printf(2, "Error\nFailed to load textures\n"), EXIT_FAILURE);
	}
	free_texture_names(cubed->imgs);
	init_string_textures(cubed->imgs);
	cubed->imgs->east_texture = mlx_get_data_addr(cubed->imgs->ptr_east, &bpp,
			&size_line, &endian);
	cubed->imgs->west_texture = mlx_get_data_addr(cubed->imgs->ptr_west, &bpp,
			&size_line, &endian);
	cubed->imgs->north_texture = mlx_get_data_addr(cubed->imgs->ptr_north, &bpp,
			&size_line, &endian);
	cubed->imgs->south_texture = mlx_get_data_addr(cubed->imgs->ptr_south, &bpp,
			&size_line, &endian);
	return (EXIT_SUCCESS);
}

int	init_mlx(t_cubed *cubed)
{
	cubed->mlx = mlx_init();
	if (!cubed->mlx)
		return (ft_printf(2, "Error\nMlx_init failed\n"), free(cubed->imgs),
			free(cubed->pixel_data), EXIT_FAILURE);
	cubed->win = mlx_new_window(cubed->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!cubed->win)
	{
		ft_printf(2, "Error\nMlx_new_window failed\n");
		if (!cubed->mlx)
			return (EXIT_FAILURE);
		free(cubed->mlx);
		#ifdef __linux__
			mlx_destroy_display(cubed->mlx);
		#endif
		return (EXIT_FAILURE);
	}
	if (init_textures(cubed) == EXIT_FAILURE)
	{
		mlx_destroy_window(cubed->mlx, cubed->win);
		#ifdef __linux__
			mlx_destroy_display(cubed->mlx);
		#endif
		return (free(cubed->mlx), free(cubed->pixel_data), EXIT_FAILURE);
	}
	cubed->ray = ft_calloc(1, sizeof(t_ray));
	if (!cubed->ray)
	{
		mlx_destroy_window(cubed->mlx, cubed->win);
		#ifdef __linux__
			mlx_destroy_display(cubed->mlx);
		#endif
		free(cubed->mlx);
		return (ft_printf(2, "Error\nRay allocation failed\n"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
