/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:47:19 by atseruny          #+#    #+#             */
/*   Updated: 2025/09/22 14:22:23 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_image_put(t_config *config, int i)
{
	int				x;
	int				y;
	unsigned int	pixel;

	x = 0;
	while (x < config->up_down[i].wd)
	{
		y = 0;
		while (y < config->up_down[i].ht - 66)
		{
			pixel = get_pixel(&config->up_down[i], x, y + 66);
			if (pixel != 0x76BBD0)
				my_pixel_put(&config->img, x + 250, y, pixel);
			y++;
		}
		x++;
	}
}

void	spider_anim(t_config *config)
{
	static int	c;

	my_image_put(config, c / 3);
	c++;
	if (c == 78)
		c = 54;
}

void	open_the_door(t_config *config)
{
	double	next_x;
	double	next_y;
	double	len;

	len = sqrt(config->player.dir_x * config->player.dir_x
			+ config->player.dir_y * config->player.dir_y);
	next_x = config->player.pos_x + config->player.dir_x / len * STEP * 10;
	next_y = config->player.pos_y + config->player.dir_y / len * STEP * 10;
	if (config->map[(int)next_x][(int)next_y] == 'C')
		config->map[(int)next_x][(int)next_y] = 'O';
	else if (config->map[(int)next_x][(int)next_y] == 'O')
		config->map[(int)next_x][(int)next_y] = 'C';
}

void	rotate_view(t_config *config, double angle)
{
	double	sa;
	double	ca;
	double	tmp;

	ca = cos(angle);
	sa = sin(angle);
	tmp = config->player.dir_x;
	config->player.dir_x = config->player.dir_x * ca
		- config->player.dir_y * sa;
	config->player.dir_y = tmp * sa + config->player.dir_y * ca;
	tmp = config->player.plane_x;
	config->player.plane_x = config->player.plane_x * ca
		- config->player.plane_y * sa;
	config->player.plane_y = tmp * sa + config->player.plane_y * ca;
}

int	mouse_motion(int x, int y, t_config *config)
{
	int	delta_rot;

	if (config->player.prev_view != -1)
	{
		delta_rot = x - config->player.prev_view;
		if (delta_rot < 0)
			rotate_view(config, (double)(SPEED));
		else
			rotate_view(config, (double)(-SPEED));
	}
	config->player.prev_view = x;
	(void)y;
	return (0);
}
