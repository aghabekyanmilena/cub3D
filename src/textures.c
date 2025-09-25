/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:15:04 by atseruny          #+#    #+#             */
/*   Updated: 2025/09/22 15:05:07 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_animation_textures(t_config *config)
{
	int		i;
	char	*name;
	char	*num;

	config->up_down = (t_img *)malloc(26 * sizeof(t_img));
	if (!config->up_down)
		return ;
	i = 0;
	while (i < 26)
	{
		name = ft_itoa(i + 1);
		num = ft_strjoin("./textures/animation/New_Project_", name);
		free(name);
		name = ft_strjoin(num, ".xpm");
		free(num);
		config->up_down[i].ht = 1393;
		config->up_down[i].wd = 548;
		config->up_down[i].img = mlx_xpm_file_to_image(config->data.mlx,
				name, &config->up_down[i].wd, &config->up_down[i].ht);
		config->up_down[i].addr = mlx_get_data_addr(config->up_down[i].img,
				&config->up_down[i].bits_per_pixel,
				&config->up_down[i].line_len, &config->open.endian);
		i++;
		free(name);
	}
}

void	get_door_textures(t_config *config)
{
	char	*open_path;
	char	*close_path;

	close_path = "./textures/closed_door.xpm";
	open_path = "./textures/open_door.xpm";
	config->close.ht = TEX_H;
	config->close.wd = TEX_H;
	config->close.img = mlx_xpm_file_to_image(config->data.mlx, close_path,
			&config->close.wd, &config->close.ht);
	config->close.addr = mlx_get_data_addr(config->close.img,
			&config->close.bits_per_pixel,
			&config->close.line_len, &config->close.endian);
	config->open.ht = TEX_H;
	config->open.wd = TEX_H;
	config->open.img = mlx_xpm_file_to_image(config->data.mlx, open_path,
			&config->open.wd, &config->open.ht);
	config->open.addr = mlx_get_data_addr(config->open.img,
			&config->open.bits_per_pixel,
			&config->open.line_len, &config->open.endian);
}

void	get_textures_sharunak(t_config *config)
{
	config->west.img = mlx_xpm_file_to_image(config->data.mlx, config->we_path,
			&config->west.wd, &config->west.ht);
	config->west.ht = TEX_H;
	config->west.wd = TEX_H;
	config->west.addr = mlx_get_data_addr(config->west.img,
			&config->west.bits_per_pixel,
			&config->west.line_len, &config->west.endian);
	config->east.img = mlx_xpm_file_to_image(config->data.mlx, config->ea_path,
			&config->east.wd, &config->east.ht);
	config->east.ht = TEX_H;
	config->east.wd = TEX_H;
	config->east.addr = mlx_get_data_addr(config->east.img,
			&config->east.bits_per_pixel,
			&config->east.line_len, &config->east.endian);
}

void	get_textures(t_config *config)
{
	get_animation_textures(config);
	get_door_textures(config);
	config->south.ht = TEX_H;
	config->south.wd = TEX_H;
	config->south.img = mlx_xpm_file_to_image(config->data.mlx, config->so_path,
			&config->south.wd, &config->south.ht);
	config->south.addr = mlx_get_data_addr(config->south.img,
			&config->south.bits_per_pixel,
			&config->south.line_len, &config->south.endian);
	config->north.img = mlx_xpm_file_to_image(config->data.mlx, config->no_path,
			&config->north.wd, &config->north.ht);
	config->north.ht = TEX_H;
	config->north.wd = TEX_H;
	config->north.addr = mlx_get_data_addr(config->north.img,
			&config->north.bits_per_pixel,
			&config->north.line_len, &config->north.endian);
	get_textures_sharunak(config);
}
