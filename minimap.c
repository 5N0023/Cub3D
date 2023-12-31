/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:58:23 by mlektaib          #+#    #+#             */
/*   Updated: 2023/09/04 20:16:15 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_player_minimap(t_data *data, int size)
{
	int	i;
	int	j;
	int	newplayerx;
	int	newplayery;

	i = 0;
	newplayery = (size / 2) - 3;
	newplayerx = (size / 2) - 3;
	while (newplayerx + i < ((size / 2)) + 3)
	{
		j = 0;
		while (newplayery + j < ((size / 2)) + 3)
		{
			mlx_put_pixel(data->img, newplayerx + i, newplayery + j,
				0xFF0000FF);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_data *data, int size, double startx, double starty)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		startx = data->player.x - 5;
		while (j < size)
		{
			if (startx >= 0 && starty >= 0 && startx < data->map.width
				&& starty < data->map.height)
			{
				if (data->map.map[(int)starty][(int)startx] == '1')
					mlx_put_pixel(data->img, j, i, 0x998970FF);
				else if (data->map.map[(int)starty][(int)startx] == 'd'
					|| data->map.map[(int)starty][(int)startx] == 'D')
					mlx_put_pixel(data->img, j, i, 0x5d2906FF);
			}
			startx += 0.05;
			j++;
		}
		starty += 0.05;
		i++;
	}
}

void	draw_map(t_data *data, int size)
{
	double	startx;
	double	starty;

	startx = data->player.x - 5;
	starty = data->player.y - 5;
	draw_minimap(data, size, startx, starty);
	draw_player_minimap(data, size);
}
