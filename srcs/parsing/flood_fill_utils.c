/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:44:38 by enschnei          #+#    #+#             */
/*   Updated: 2025/09/05 14:59:28 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	copy_line(char **dest, char *src, int max_wid)
{
	int	j;

	*dest = ft_calloc(max_wid + 1, sizeof(char));
	if (!*dest)
		return (1);
	j = 0;
	while (j < max_wid)
	{
		if (j < (int)ft_strlen(src))
			(*dest)[j] = src[j];
		else
			(*dest)[j] = ' ';
		j++;
	}
	(*dest)[max_wid] = '\0';
	return (0);
}
