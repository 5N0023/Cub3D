/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:20:53 by mjarboua          #+#    #+#             */
/*   Updated: 2023/07/27 08:09:15 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

int find_player_pos(t_data *data)
{
	for(size_t i = 0;i < data->map.height; i++)
	{
		for(size_t j = 0; j < data->map.width; j++)
		{
			if (data->map.map[i][j] == 'N' || data->map.map[i][j] == 'S' || data->map.map[i][j] == 'E' || data->map.map[i][j] == 'W')
			{
				data->player.x = j+0.5;
				data->player.y = i + 0.5;
				if(data->map.map[i][j] == 'N')
					data->player.angle = 180;
				else if(data->map.map[i][j] == 'S')
					data->player.angle = 0;
				else if(data->map.map[i][j] == 'E')
					data->player.angle = 90;
				else if(data->map.map[i][j] == 'W')
					data->player.angle = 270;
				data->map.map[i][j] = '0';
				return (0);
			}
		}
	}
	return (1);
}

int	parser(int c, char **v, t_data *data)
{
	t_pars *pars;
	
	if (c == 1)
		return (printf("you will have to give the map path as an argument\n"), 1);
	pars = ft_map_parser(v[1]);
	if (!pars)
		return (1);
	data->map.map = pars->map.map;
	data->map.width = pars->map.width;
	data->map.height = pars->map.height;
	data->floorcolor = pars->floorcolor;
	data->ceilingcolor = pars->ceilingcolor;
	data->texture.sud = pars->south;
	data->texture.ouest = pars->west;
	data->texture.east = pars->east;
	data->texture.nord = pars->north;
	if(find_player_pos(data))
	{
		printf("no player found\n");
		ft_free_array(pars->map.map);
		free(pars->south);
		free(pars->west);
		free(pars->east);
		free(pars->north);
		free(pars);
		return (1);
	}
	free(pars);
	return (0);
}