/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 21:42:26 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/22 18:02:05 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_border_rows_cols(t_config *data, char **map_copy)
{
	int	r;
	int	c;

	r = 0;
	while (r < data->height)
	{
		if (is_spawn_or_walkable(map_copy[r][0])
			|| is_spawn_or_walkable(map_copy[r][data->width - 1]))
			return (ft_putendl_fd("Error", 2), false);
		r++;
	}
	c = 0;
	while (c < data->width)
	{
		if (is_spawn_or_walkable(map_copy[0][c])
			|| is_spawn_or_walkable(map_copy[data->height - 1][c]))
			return (ft_putendl_fd("Error", 2), false);
		c++;
	}
	return (true);
}

static bool	check_dfs_edges(t_config *data, char **map_copy)
{
	int	r;
	int	c;

	r = 0;
	while (r < data->height)
	{
		if ((map_copy[r][0] == '2' && !dfs_outside(map_copy, r, 0, data))
			|| (map_copy[r][data->width - 1] == '2'
				&& !dfs_outside(map_copy, r, data->width - 1, data)))
			return (ft_putendl_fd("Error", 2), false);
		r++;
	}
	c = 0;
	while (c < data->width)
	{
		if ((map_copy[0][c] == '2' && !dfs_outside(map_copy, 0, c, data))
			|| (map_copy[data->height - 1][c] == '2'
				&& !dfs_outside(map_copy, data->height - 1, c, data)))
			return (ft_putendl_fd("Error", 2), false);
		c++;
	}
	return (true);
}

static bool	check_dfs_inside(t_config *data, char **map_copy)
{
	int	r;
	int	c;

	r = 0;
	while (r < data->height)
	{
		c = 0;
		while (c < data->width)
		{
			if (map_copy[r][c] == '2' && !dfs_outside(map_copy, r, c, data))
				return (ft_putendl_fd("Error", 2), false);
			c++;
		}
		r++;
	}
	return (true);
}

bool	check_map_closed(t_config *data)
{
	char	**map_copy;

	map_copy = copy_map(data);
	if (!map_copy)
		return (ft_putendl_fd("Error", 2), false);
	if (!check_door(map_copy, data))
		return (free_map_copy(&map_copy, data->height),
			ft_putendl_fd("Error", 2), false);
	if (!check_border_rows_cols(data, map_copy)
		|| !check_dfs_edges(data, map_copy)
		|| !check_dfs_inside(data, map_copy))
	{
		free_map_copy(&map_copy, data->height);
		return (false);
	}
	free_map_copy(&map_copy, data->height);
	return (true);
}

bool	check_map(t_config *data)
{
	if (!data->map || data->height == 0 || data->width == 0)
		return (false);
	return (true);
}
