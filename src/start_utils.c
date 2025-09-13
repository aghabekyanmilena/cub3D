/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:57:28 by atseruny          #+#    #+#             */
/*   Updated: 2025/09/13 15:38:01 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fri(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_lines(data->map);
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
}

void	get_textures(t_config *config)
{
	char	*hands_path = "./textures/camera.xpm";
	config->hands.ht = texh;
	config->hands.wd = texh;
	config->hands.img = mlx_xpm_file_to_image(config->data.mlx, hands_path, &config->hands.wd, &config->hands.ht);
	config->hands.addr = mlx_get_data_addr(config->hands.img, &config->hands.bits_per_pixel,
			&config->hands.line_len, &config->hands.endian);

	char	*closed_door_path= "./textures/closed_door.xpm";
	config->closed_door.ht = texh;
	config->closed_door.wd = texh;
	config->closed_door.img = mlx_xpm_file_to_image(config->data.mlx, closed_door_path, &config->closed_door.wd, &config->closed_door.ht);
	config->closed_door.addr = mlx_get_data_addr(config->closed_door.img, &config->closed_door.bits_per_pixel,
			&config->closed_door.line_len, &config->open_door.endian);

	config->south.ht = texh;
	config->south.wd = texh;
	config->south.img = mlx_xpm_file_to_image(config->data.mlx, config->so_path, &config->south.wd, &config->south.ht);
	config->south.addr = mlx_get_data_addr(config->south.img, &config->south.bits_per_pixel,
			&config->south.line_len, &config->south.endian);

	config->north.img = mlx_xpm_file_to_image(config->data.mlx, config->no_path, &config->north.wd, &config->north.ht);
	config->north.ht = texh;
	config->north.wd = texh;
	config->north.addr = mlx_get_data_addr(config->north.img, &config->north.bits_per_pixel,
			&config->north.line_len, &config->north.endian);

	config->west.img = mlx_xpm_file_to_image(config->data.mlx, config->we_path, &config->west.wd, &config->west.ht);
	config->west.ht = texh;
	config->west.wd = texh;
	config->west.addr = mlx_get_data_addr(config->west.img, &config->west.bits_per_pixel,
			&config->west.line_len, &config->west.endian);

	config->east.img = mlx_xpm_file_to_image(config->data.mlx, config->ea_path, &config->east.wd, &config->east.ht);
	config->east.ht = texh;
	config->east.wd = texh;
	config->east.addr = mlx_get_data_addr(config->east.img, &config->east.bits_per_pixel,
			&config->east.line_len, &config->east.endian);
}