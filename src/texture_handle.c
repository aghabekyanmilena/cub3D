/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:00:12 by miaghabe          #+#    #+#             */
/*   Updated: 2025/08/03 16:33:16 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_textures(t_config *config)
{
	config->graphics.texture_paths[0] = config->no_path;
	config->graphics.texture_paths[1] = config->so_path;
	config->graphics.texture_paths[2] = config->we_path;
	config->graphics.texture_paths[3] = config->ea_path;

	for (int i = 0; i < 4; i++)
	{
		config->graphics.textures[i] = mlx_xpm_file_to_image(
			config->graphics.mlx,
			config->graphics.texture_paths[i],
			&config->graphics.widths[i],
			&config->graphics.heights[i]
		);
		if (!config->graphics.textures[i])
		{
			printf("load failed: %s\n", config->graphics.texture_paths[i]);
			exit(1);
		}
	}
}

void	init_window_and_textures(t_config *config)
{
	config->graphics.mlx = mlx_init();
	if (!config->graphics.mlx)
	{
		perror("mlx_init");
		exit(1);
	}
	config->graphics.win = mlx_new_window(
		config->graphics.mlx,
		640, 480,
		"cub3D"
	);
	if (!config->graphics.win)
	{
		perror("mlx_new_window");
		exit(1);
	}
	load_textures(config);
}

void	draw_tile(t_data *data, int x, int y, void *img)
{
	mlx_put_image_to_window(data->mlx, data->win, img, x * TILE_SIZE, y * TILE_SIZE);
}

void	render_map(t_config *config)
{
	for (int y = 0; config->map[y]; y++)
	{
		for (int x = 0; config->map[y][x]; x++)
		{
			if (config->map[y][x] == '1')
				draw_tile(&config->graphics, x, y, config->graphics.textures[0]);
		}
	}
}

