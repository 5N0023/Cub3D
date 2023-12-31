/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:11:16 by mlektaib          #+#    #+#             */
/*   Updated: 2023/09/04 20:11:17 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_cursor(t_data *data)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png("textures/cursor.png");
	if (!texture)
		exit(1);
	image = mlx_texture_to_image(data->mlx, texture);
	mlx_resize_image(image, 26, 26);
	data->mouse.cursor = image;
	mlx_delete_texture(texture);
}

void	draw_cursor(t_data *data)
{
	size_t	i;
	size_t	j;
	int		pixel;

	i = 0;
	while (i < data->mouse.cursor->width)
	{
		j = 0;
		while (j < data->mouse.cursor->height)
		{
			pixel = get_pixel(data->mouse.cursor, i, j);
			if (pixel)
				mlx_put_pixel(data->img, i + 500 - 13, WINDOWW / 2 + j + 202,
					pixel);
			j++;
		}
		i++;
	}
}
