/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:57:28 by atseruny          #+#    #+#             */
/*   Updated: 2025/09/04 16:33:25 by atseruny         ###   ########.fr       */
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

void	init_player_struct(t_config *config)
{
	config->player.pos_x = (double)config->posX + 0.5;
	config->player.pos_y = (double)config->posY + 0.5;
	if (config->view == 'N')
	{
		config->player.dir_x = -1;
		config->player.dir_y = 0;
		config->player.plane_x = 0;
		config->player.plane_y = 0.66;
	}
	else if (config->view == 'S')
	{
		config->player.dir_x = 1;
		config->player.dir_y = 0;
		config->player.plane_x = 0;
		config->player.plane_y = -0.66;
	}
	else if (config->view == 'W')
	{
		config->player.dir_x = 0;
		config->player.dir_y = -1;
		config->player.plane_x = -0.66;
		config->player.plane_y = 0;
	}
	else
	{
		config->player.dir_x = 0;
		config->player.dir_y = 1;
		config->player.plane_x = 0.66;
		config->player.plane_y = 0;
	}
	config->player.prev_view = -1;
}

void	get_textures(t_config *config)
{
	int	texlen = texh;
	// printf("%s\n", config->no_path);
	config->south.img = mlx_xpm_file_to_image(config->data.mlx, config->so_path, &texlen, &texlen);
	config->south.ht = texlen;
	config->south.wd = texlen;
	config->south.addr = mlx_get_data_addr(config->south.img, &config->south.bits_per_pixel,
			&config->south.line_len, &config->south.endian);

	config->north.img = mlx_xpm_file_to_image(config->data.mlx, config->no_path, &texlen, &texlen);
	config->north.ht = texlen;
	config->north.wd = texlen;
	config->north.addr = mlx_get_data_addr(config->north.img, &config->north.bits_per_pixel,
			&config->north.line_len, &config->north.endian);

	config->west.img = mlx_xpm_file_to_image(config->data.mlx, config->we_path, &texlen, &texlen);
	config->west.ht = texlen;
	config->west.wd = texlen;
	config->west.addr = mlx_get_data_addr(config->west.img, &config->west.bits_per_pixel,
			&config->west.line_len, &config->west.endian);

	config->east.img = mlx_xpm_file_to_image(config->data.mlx, config->ea_path, &texlen, &texlen);
	config->east.ht = texlen;
	config->east.wd = texlen;
	config->east.addr = mlx_get_data_addr(config->east.img, &config->east.bits_per_pixel,
			&config->east.line_len, &config->east.endian);
}