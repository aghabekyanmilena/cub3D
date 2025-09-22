/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:22:42 by atseruny          #+#    #+#             */
/*   Updated: 2025/09/22 14:31:57 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	change_map(t_config *config, int next_x, int next_y)
{
	char	p;

	p = config->map[(int)config->player.pos_x][(int)config->player.pos_y];
	config->map[(int)config->player.pos_x][(int)config->player.pos_y]
		= config->player.prev_char;
	config->player.prev_char = config->map[(int)next_x][(int)next_y];
	config->map[(int)next_x][(int)next_y] = p;
}

void	put_ten_pixels(t_config *config, int x, int y, char map)
{
	int	c;

	c = 0;
	if (map != '2')
		while (c < 10)
			my_pixel_put(&config->img, x + c++, y, 0x404040);
	c = 0;
	if (map == '1')
		while (c < 10)
			my_pixel_put(&config->img, x + c++, y, 0x000000);
	else if (map == 'C' || map == 'O')
		while (c < 10)
			my_pixel_put(&config->img, x + c++, y, 0x404090);
}

void	minimap(t_config *config, int j, int n)
{
	int	i;
	int	k;
	int	c;

	while (config->map[j])
	{
		i = -1;
		while (++i < 10)
		{
			k = 0;
			while (config->map[j][k] != '\0')
			{
				put_ten_pixels(config, 10 * k, n, config->map[j][k]);
				k++;
			}
			c = 0;
			while (c < 6 && i < 6)
				my_pixel_put(&config->img, (config->player.pos_y * 10 + c++
						- 3), (config->player.pos_x * 10 + i - 3), 0xF04040);
			n++;
		}
		j++;
	}
}
