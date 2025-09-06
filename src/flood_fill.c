/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 23:25:24 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/06 23:28:59 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	flood_fill_rec(char **map, int y, int x, int height, int width)
{
	if (y < 0 || y >= height || x < 0 || x >= width)
		return;
	if (map[y][x] == '1' || map[y][x] == ' ' || map[y][x] == '\t')
		return; 
	map[y][x] = 'F';
	flood_fill_rec(map, y + 1, x, height, width);
	flood_fill_rec(map, y - 1, x, height, width);
	flood_fill_rec(map, y, x + 1, height, width);
	flood_fill_rec(map, y, x - 1, height, width);
}

void	flood_fill(char **map, t_config start, int height, int width)
{
	if (!map)
		return;
	flood_fill_rec(map, start.player_y, start.player_x, height, width);
}
