/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:14:36 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/14 00:03:38 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**copy_map(char **map)
{
	char	**copy;
	int		i;

	i = 0;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		// if (!copy[i])
		// 	return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	flood_fill_rec(char **map, int y, int x)
{
	if (y < 0 || x < 0 || map[y][x] == '\0')
		return 0;
	// printf("%c\n", map[y][x]);
	if (map[y][x] != '\0' && map[y][x] != '1' && map[y][x] != 'F')
		map[y][x] = 'F';
	else
		return 1;
	if (!flood_fill_rec(map, y + 1, x))
		return 0;
	if (!flood_fill_rec(map, y - 1, x))
		return 0;
	if (!flood_fill_rec(map, y, x + 1))
		return 0;
	if (!flood_fill_rec(map, y, x - 1))
		return 0;
	return (1);
}

void	flood_fill(char **map, int start_y, int start_x)
{
	if (!map)
		return;
	if (!flood_fill_rec(map, start_y, start_x))
		printf("Invalid\n");
}

void	free_temp_map(char **temp_map, int height)
{
	int	y = 0;
	while (y < height)
		free(temp_map[y++]);
	free(temp_map);
}

int	check_map_closed(t_config *config)
{
	char	**temp_map;
	int		i = 0;

	temp_map = (char **)malloc((config->height + 1) * sizeof(char *));
	if (!temp_map)
		return (0);
	temp_map = copy_map(config->map);
	if (!temp_map)
		return (0);
	// flood_fill(temp_map, config->player_y, config->player_x);
	while(temp_map[i])
	{
		printf("%s\n", temp_map[i]);
		i++;
	}
	free_temp_map(temp_map, config->height);
	return (1);
}
