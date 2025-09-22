/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:29:20 by atseruny          #+#    #+#             */
/*   Updated: 2025/09/21 18:06:35 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_pixel(t_img *tex, int x, int y)
{
	char	*dst;

	if (x >= 0 && x < tex->wd && y >= 0 && y < tex->ht)
	{
		dst = tex->addr + (y * tex->line_len + x * (tex->bits_per_pixel / 8));
		return (*(unsigned int *)dst);
	}
	return (0);
}

void	put_back(t_config *config)
{
	unsigned int	*dst;
	unsigned int	i;

	dst = (unsigned int *) config->img.addr;
	i = LENGTH * WIDTH / 2 + 1;
	while (--i > 0)
		*dst++ = rgb_to_int(config->floor);
	i = LENGTH * WIDTH / 2 + 1;
	while (--i > 0)
		*dst++ = rgb_to_int(config->ceiling);
}

int	start_ray_casting(t_config *config)
{
	int		x;

	config->img.img = mlx_new_image(config->data.mlx, LENGTH, WIDTH);
	config->img.addr = mlx_get_data_addr(config->img.img,
			&config->img.bits_per_pixel,
			&config->img.line_len, &config->img.endian);
	put_back(config);
	x = -1;
	while (++x < LENGTH)
	{
		get_ray_dir(&config->ray, &config->player, x);
		get_step_player(&config->ray, &config->player);
		check_if_hit(&config->ray, &config->player, config->map);
		get_wall_size(&config->ray, &config->player, &config->wall);
		draw_wall(config, &config->wall, x, config->wall.draw_start - 1);
	}
	minimap(config, 0, 0);
	spider_anim(config);
	mlx_put_image_to_window(config->data.mlx, config->data.win,
		config->img.img, 0, 0);
	mlx_destroy_image(config->data.mlx, config->img.img);
	return (0);
}

void	start(t_config *config, char **map)
{
	init_player_struct(config);
	config->data.mlx = mlx_init();
	if (!config->data.mlx)
		return ;
	config->data.map = map;
	config->data.win = mlx_new_window(config->data.mlx, LENGTH, WIDTH, "Cub3D");
	if (!config->data.win)
	{
		mlx_destroy_display(config->data.mlx);
		free(config->data.mlx);
		return ;
	}
	get_textures(config);
	mlx_hook(config->data.win, 2, (1L << 0), check, config);
	mlx_hook(config->data.win, 17, 0, fri, config);
	mlx_hook(config->data.win, 6, (1L << 6), mouse_motion, config);
	mlx_loop_hook(config->data.mlx, start_ray_casting, config);
	mlx_loop(config->data.mlx);
}
