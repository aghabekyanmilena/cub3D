/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:14:36 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/21 21:46:41 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_spawn_or_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == 'C' || c == 'O');
}

bool	dfs_outside(char **map, int row, int col, t_config *data)
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

bool	check_single_spawn(t_config *data)
{
	int	r;
	int	c;
	int	spawn_count;

	r = 0;
	spawn_count = 0;
	while (r < data->height)
	{
		c = 0;
		while (data->map[r][c])
		{
			if (data->map[r][c] == 'N' || data->map[r][c] == 'S' ||
				data->map[r][c] == 'E' || data->map[r][c] == 'W')
			{
				data->posX = r;
				data->posY = c;
				data->view = data->map[r][c];
				spawn_count++;
			}
			c++;
		}
		r++;
	}
	if (spawn_count != 1)
		return (printf("Error\nWrong number of characters\n"), false);
	return (true);
}

int	check_door(char **lines)
{
	int	k;
	int	j;

	k = 0;
	while (lines[k])
	{
		j = 0;
		while (lines[k][j])
		{
			if (lines[k][j] && (lines[k][j] == 'C' || lines[k][j] == 'O'))
			{
				if (lines[k][j + 1] && lines[k][j - 1] && lines[k][j + 1] == '1' && lines[k][j - 1] == '1'
					&& (lines[k + 1][j] && lines[k - 1][j] && lines[k - 1][j] != '1' && lines[k + 1][j] != '1'))
					return (1);
				else if ((lines[k + 1][j] && lines[k - 1][j] && lines[k - 1][j] == '1' && lines[k + 1][j] == '1') &&
					(lines[k][j + 1] && lines[k][j - 1] && lines[k][j + 1] != '1' && lines[k][j - 1] != '1'))
					return (1);
				else
					return (0);
			}
			j++;
		}
		k++;
	}
	return (1);
}

bool	check_map(t_config *data)
{
	if (!data->map || data->height == 0 || data->width == 0)
		return (false);
	return (true);
}
