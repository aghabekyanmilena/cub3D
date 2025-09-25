/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:14:46 by atseruny          #+#    #+#             */
/*   Updated: 2025/09/25 17:34:12 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	fri(t_config *config)
{
	int	i;

	i = 0;
	if (config->south.img)
		mlx_destroy_image(config->data.mlx, config->south.img);
	if (config->east.img)
		mlx_destroy_image(config->data.mlx, config->east.img);
	if (config->west.img)
		mlx_destroy_image(config->data.mlx, config->west.img);
	if (config->north.img)
		mlx_destroy_image(config->data.mlx, config->north.img);
	mlx_destroy_image(config->data.mlx, config->open.img);
	mlx_destroy_image(config->data.mlx, config->close.img);
	while (i < 26)
		mlx_destroy_image(config->data.mlx, config->up_down[i++].img);
	free(config->up_down);
	if (config->data.win)
		mlx_destroy_window(config->data.mlx, config->data.win);
	mlx_destroy_display(config->data.mlx);
	free(config->data.mlx);
	free_config(config);
	free_lines(config->data.map);
	exit (0);
}

int	rgb_to_int(t_color c)
{
	return (((c.r & 0xFF) << 16) | ((c.g & 0xFF) << 8) | (c.b & 0xFF));
}

void	init_player_struct_sharunak(t_config *config)
{
	if (config->view == 'N')
	{
		config->player.dir_x = -1;
		config->player.plane_y = 0.7;
	}
	else if (config->view == 'S')
	{
		config->player.dir_x = 1;
		config->player.plane_y = -0.7;
	}
	else if (config->view == 'W')
	{
		config->player.dir_y = -1;
		config->player.plane_x = -0.7;
	}
	else
	{
		config->player.dir_y = 1;
		config->player.plane_x = 0.7;
	}
}

void	init_player_struct(t_config *config)
{
	config->player.pos_x = (double)config->pos_x + 0.5;
	config->player.pos_y = (double)config->pos_y + 0.5;
	config->player.prev_view = -1;
	config->player.prev_char = config->map[(int)config->player.pos_x]
	[(int)config->player.pos_y];
	config->player.dir_x = 0;
	config->player.dir_y = 0;
	config->player.plane_x = 0;
	config->player.plane_y = 0;
	init_player_struct_sharunak(config);
}
