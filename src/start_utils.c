/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anush <anush@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:57:28 by atseruny          #+#    #+#             */
/*   Updated: 2025/09/17 16:14:35 by anush            ###   ########.fr       */
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
	mlx_destroy_image(config->data.mlx, config->south.img);
	mlx_destroy_image(config->data.mlx, config->east.img);
	mlx_destroy_image(config->data.mlx, config->west.img);
	mlx_destroy_image(config->data.mlx, config->north.img);
	mlx_destroy_image(config->data.mlx, config->open_door.img);
	mlx_destroy_image(config->data.mlx, config->closed_door.img);
	while (i < 26)
		mlx_destroy_image(config->data.mlx, config->up_down[i++].img);
	mlx_destroy_window(config->data.mlx, config->data.win);
	mlx_destroy_display(config->data.mlx);
	free(config->up_down);
	free(config->data.mlx);
	free_lines(config->map);
	free_lines(config->data.map);
	exit (0);
}

int	rgb_to_int(t_color c)
{
	return ((c.r & 0xFF) << 16) | ((c.g & 0xFF) << 8) | (c.b & 0xFF);
}

unsigned int get_pixel(t_img *tex, int x, int y)
{
	char *dst;

	if (x >= 0 && x < tex->wd && y >= 0 && y < tex->ht)
	{
		dst = tex->addr + (y * tex->line_len + x * (tex->bits_per_pixel / 8));
		return (*(unsigned int *)dst);
	}
	return (0);
}

void	init_player_struct(t_config *config)
{
	config->player.pos_x = (double)config->posX + 0.5;
	config->player.pos_y = (double)config->posY + 0.5;
	if (config->view == 'N')
	{
		config->player.dir_x = -1;
		config->player.dir_y = 0;
		config->player.plane_x = 0;
		config->player.plane_y = 0.7;
	}
	else if (config->view == 'S')
	{
		config->player.dir_x = 1;
		config->player.dir_y = 0;
		config->player.plane_x = 0;
		config->player.plane_y = -0.7;
	}
	else if (config->view == 'W')
	{
		config->player.dir_x = 0;
		config->player.dir_y = -1;
		config->player.plane_x = -0.7;
		config->player.plane_y = 0;
	}
	else
	{
		config->player.dir_x = 0;
		config->player.dir_y = 1;
		config->player.plane_x = 0.7;
		config->player.plane_y = 0;
	}
	config->player.prev_view = -1;
	config->player.prev_char = config->map[(int)config->player.pos_x][(int)config->player.pos_y];
}
