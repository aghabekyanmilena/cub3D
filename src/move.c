/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:59:08 by atseruny          #+#    #+#             */
/*   Updated: 2025/09/06 20:21:32 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	change_map(t_config *config, int next_x, int next_y)
{
	char	p;

	p = config->map[(int)config->player.pos_x][(int)config->player.pos_y];
	config->map[(int)config->player.pos_x][(int)config->player.pos_y] = '0';
	config->map[(int)next_x][(int)next_y] = p;
	
}

void	go_forward(t_config *config)
{
	double	next_x;
	double	next_y;
	double	len;

	len = sqrt(config->player.dir_x*config->player.dir_x + config->player.dir_y*config->player.dir_y);
	next_x = config->player.pos_x + config->player.dir_x / len * STEP;
	next_y = config->player.pos_y + config->player.dir_y / len * STEP;
	if (config->map[(int)next_x][(int)next_y] != '1')
	{
		change_map(config, (int)next_x, (int)next_y);
		config->player.pos_x = next_x;
		config->player.pos_y = next_y;
	}
}

void	go_back(t_config *config)
{
	double	next_x;
	double	next_y;
	double	len;

	len = sqrt(config->player.dir_x*config->player.dir_x + config->player.dir_y*config->player.dir_y);
	next_x = config->player.pos_x - config->player.dir_x / len * STEP;
	next_y = config->player.pos_y - config->player.dir_y / len * STEP;
	if (config->map[(int)next_x][(int)next_y] != '1')
	{
		change_map(config, (int)next_x, (int)next_y);

		config->player.pos_x = next_x;
		config->player.pos_y = next_y;
	}
}

void	go_right(t_config *config)
{
	double	next_x;
	double	next_y;
	double	len;

	len = sqrt(config->player.dir_x*config->player.dir_x + config->player.dir_y*config->player.dir_y);
	next_x = config->player.pos_x + config->player.dir_y / len * STEP;
	next_y = config->player.pos_y - config->player.dir_x / len * STEP;
	if (config->map[(int)next_x][(int)next_y] != '1')
	{
		change_map(config, (int)next_x, (int)next_y);

		config->player.pos_x = next_x;
		config->player.pos_y = next_y;
	}
}

void	go_left(t_config *config)
{
	double	next_x;
	double	next_y;
	double	len;

	len = sqrt(config->player.dir_x*config->player.dir_x + config->player.dir_y*config->player.dir_y);
	next_x = config->player.pos_x - config->player.dir_y / len * STEP;
	next_y = config->player.pos_y + config->player.dir_x / len * STEP;
	if (config->map[(int)next_x][(int)next_y] != '1')
	{
		change_map(config, (int)next_x, (int)next_y);

		config->player.pos_x = next_x;
		config->player.pos_y = next_y;
	}
}

int	check(int keycode, t_config *config)
{
	if (keycode == XK_ESCAPE)
		fri(&config->data);
	else if (keycode == XK_W || keycode == XK_WL)
		go_forward(config);
	else if (keycode == XK_S || keycode == XK_SL)
		go_back(config);
	else if (keycode == XK_D || keycode == XK_DL)
		go_right(config);
	else if (keycode == XK_A || keycode == XK_AL)
		go_left(config);
	else if (keycode == XK_LEFT)
		rotate_view(config, (double)(SPEED));
	else if (keycode == XK_RIGHT)
		rotate_view(config, (double)(-SPEED));
	return (0);
}
