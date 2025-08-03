/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:14:36 by miaghabe          #+#    #+#             */
/*   Updated: 2025/08/03 14:19:35 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**copy_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	is_invalid_tile(char c)
{
	return (c == ' ' || c == '\0');
}

int	qaylelu_tex(char c)
{
	return (c == '0' || c == 'N' ||
		c == 'S' || c == 'E' || c == 'W' || c == 'D');
}

// Recursive DFS
int	dfs(char **map, int x, int y, int max_y)
{
	int	row_len;

	if (y < 0 || y >= max_y)
		return (0);
	row_len = ft_strlen(map[y]);
	if (x < 0 || x >= row_len)
		return (0);
	if (is_invalid_tile(map[y][x]))
		return (0);
	if (!qaylelu_tex(map[y][x]))
		return (1);
	map[y][x] = 'x';
	if (!dfs(map, x + 1, y, max_y))
		return (0);
	if (!dfs(map, x - 1, y, max_y))
		return (0);
	if (!dfs(map, x, y + 1, max_y))
		return (0);
	if (!dfs(map, x, y - 1, max_y))
		return (0);
	return (1);
}
