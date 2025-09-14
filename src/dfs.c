/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:14:36 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/14 22:47:36 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char **copy_map(t_config *data)
{
	int		i;
	char	**copy;

	copy = malloc(sizeof(char *) * (data->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < data->height)
	{
		copy[i] = ft_strdup(data->map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[data->height] = NULL;
	return (copy);
}

void free_map_copy(char ***map, int height)
{
	int i;

	if (!map || !*map)
		return;
	i = 0;
	while (i < height)
	{
		free((*map)[i]);
		i++;
	}
	free(*map);
	*map = NULL;
}

int is_spawn_or_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' ||
			c == 'E' || c == 'W' || c == 'D');
}

bool dfs_outside(char **map, int row, int col, t_config *data)
{
	if (row < 0 || col < 0 || row >= data->height || col >= data->width)
		return (true);
	if (map[row][col] == 'F' || map[row][col] == '1')
		return (true);
	if (is_spawn_or_walkable(map[row][col]))
		return (false);
	if (map[row][col] != '2')
		return (true);
	map[row][col] = 'F';
	if (!dfs_outside(map, row - 1, col, data))
		return (false);
	if (!dfs_outside(map, row + 1, col, data))
		return (false);
	if (!dfs_outside(map, row, col - 1, data))
		return (false);
	if (!dfs_outside(map, row, col + 1, data))
		return (false);
	return (true);
}

bool check_map_closed(t_config *data)
{
	char	**map_copy;
	int		r;
	int		c;

	map_copy = copy_map(data);
	if (!map_copy)
		return (printf("Error\nmalloc error\n"), false);
	r = 0;
	while (r < data->height)
	{
		if (is_spawn_or_walkable(map_copy[r][0])
			|| is_spawn_or_walkable(map_copy[r][data->width - 1]))
		{
			free_map_copy(&map_copy, data->height);
			return (false);
		}
		r++;
	}
	c = 0;
	while (c < data->width)
	{
		if (is_spawn_or_walkable(map_copy[0][c])
			|| is_spawn_or_walkable(map_copy[data->height - 1][c]))
		{
			free_map_copy(&map_copy, data->height);
			return (false);
		}
		c++;
	}
	r = 0;
	while (r < data->height)
	{
		if (map_copy[r][0] == '2' && !dfs_outside(map_copy, r, 0, data))
			return (free_map_copy(&map_copy, data->height), false);
		if (map_copy[r][data->width - 1] == '2'
			&& !dfs_outside(map_copy, r, data->width - 1, data))
			return (free_map_copy(&map_copy, data->height), false);
		r++;
	}
	c = 0;
	while (c < data->width)
	{
		if (map_copy[0][c] == '2' && !dfs_outside(map_copy, 0, c, data))
			return (free_map_copy(&map_copy, data->height), false);
		if (map_copy[data->height - 1][c] == '2'
			&& !dfs_outside(map_copy, data->height - 1, c, data))
			return (free_map_copy(&map_copy, data->height), false);
		c++;
	}
	free_map_copy(&map_copy, data->height);
	return (true);
}
