/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castrayhor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:04:10 by mlektaib          #+#    #+#             */
/*   Updated: 2023/09/04 20:08:44 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	find_dy(t_hit *hhit)
{
	if (hhit->angle > 90 && hhit->angle < 270)
	{
		if (hhit->dy == floor(hhit->y))
			hhit->dy = floor(hhit->y) - 1;
		else
			hhit->dy = floor(hhit->y);
	}
	else
		hhit->dy = floor(hhit->y) + 1;
}

static void	find_dx(t_hit *hhit)
{
	if (hhit->angle != 90 && hhit->angle != 270)
		hhit->dx = hhit->x + (hhit->dy - hhit->y)
			* tanf(hhit->angle * M_PI / 180.0);
	else
	{
		hhit->dy = hhit->y;
		if (hhit->angle == 90)
			hhit->dx = floor(hhit->x) + 1;
		else if (hhit->dx != floor((hhit->x)))
			hhit->dx = floor(hhit->x);
		else
		{
			if (hhit->dx == floor(hhit->x))
				hhit->dx = floor(hhit->x) - 1;
			else
				hhit->dx = floor(hhit->x);
		}
	}
}

void	castrayhorizontal(t_hit *hhit, t_data *data)
{
	find_dy(hhit);
	find_dx(hhit);
	hhit->x = hhit->dx;
	hhit->y = hhit->dy;
	if (hhit->x <= 0 || hhit->x >= data->map.width || hhit->y <= 0
		|| hhit->y >= data->map.height)
	{
		hhit->hit = 1;
		return ;
	}
	if (hhit->angle > 90 && hhit->angle < 270)
		if (data->map.map[(int)hhit->dy - 1][(int)hhit->dx] == '1'
			|| data->map.map[(int)hhit->dy - 1][(int)hhit->dx] == '*')
			hhit->hit = 1;
	if (data->map.map[(int)hhit->dy][(int)hhit->dx] == '1'
		|| data->map.map[(int)hhit->dy][(int)hhit->dx] == '*')
		hhit->hit = 1;
	if (data->map.map[(int)hhit->y][(int)hhit->x] == 'D')
		add_back_to_doors(data, hhit->dx, hhit->dy, NS);
}
