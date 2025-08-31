/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anush <anush@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:29:20 by atseruny          #+#    #+#             */
/*   Updated: 2025/08/31 12:35:56 by anush            ###   ########.fr       */
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

int rgb_to_int(t_color c)
{
	return ((c.r & 0xFF) << 16) | ((c.g & 0xFF) << 8) | (c.b & 0xFF);
}

int	check(int keycode, t_config *config)
{
	if (keycode == XK_ESCAPE)
		fri(&config->data);
	else if (keycode == XK_UP || keycode == XK_W || keycode == XK_WL)
		printf("Going up: dir_x %f dir_y %f\n", config->player.dir_x, config->player.dir_y); // >0.5 == 1 so yst dra uxxutyuny voroshum enq 
	else if (keycode == XK_DOWN || keycode == XK_S || keycode == XK_SL)
		printf("Going down\n");
	else if (keycode == XK_RIGHT || keycode == XK_D || keycode == XK_DL)
		printf("Going right\n");
	else if (keycode == XK_LEFT || keycode == XK_A || keycode == XK_AL)
		printf("Going left\n");
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

void	my_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}


int	start_ray_casting(t_config *config)
{
	int		x;
	int		y;
	double	wallX;

	config->img.img = mlx_new_image(config->data.mlx, LENGTH, WIDTH);
	config->img.addr = mlx_get_data_addr(config->img.img, &config->img.bits_per_pixel,
			&config->img.line_len, &config->img.endian);
	put_back(config);
	x = -1;
	while (++x < LENGTH)
	{
		config->ray.camera_x = 2 * x / (double)LENGTH - 1;
		config->ray.rayDir_x = config->player.dir_x + config->player.plane_x * config->ray.camera_x;
		config->ray.rayDir_y = config->player.dir_y + config->player.plane_y * config->ray.camera_x;

		config->player.map_x = (int)config->player.pos_x;
		config->player.map_y = (int)config->player.pos_y;

		
		config->ray.deltaDist_x = (config->ray.rayDir_x == 0) ? 1e30 : fabs(1 / config->ray.rayDir_x);
		config->ray.deltaDist_y = (config->ray.rayDir_y == 0) ? 1e30 : fabs(1 / config->ray.rayDir_y);
		config->ray.hit = '0';

		if (config->ray.rayDir_x < 0)
		{
			config->player.step_x = -1;
			config->ray.sideDist_x = (config->player.pos_x - config->player.map_x) * config->ray.deltaDist_x;
		}
		else
		{
			config->player.step_x = 1;
			config->ray.sideDist_x = (config->player.map_x + 1.0 - config->player.pos_x) * config->ray.deltaDist_x;
		}
		if (config->ray.rayDir_y < 0)
		{
			config->player.step_y = -1;
			config->ray.sideDist_y = (config->player.pos_y - config->player.map_y) * config->ray.deltaDist_y;
		}
		else
		{
			config->player.step_y = 1;
			config->ray.sideDist_y = (config->player.map_y + 1.0 - config->player.pos_y) * config->ray.deltaDist_y;
		}
		while (config->ray.hit == '0')
		{
			if (config->ray.sideDist_x < config->ray.sideDist_y)
			{
				config->ray.sideDist_x += config->ray.deltaDist_x;
				config->player.map_x += config->player.step_x;
				config->ray.side = 0;
			}
			else
			{
				config->ray.sideDist_y += config->ray.deltaDist_y;
				config->player.map_y += config->player.step_y;
				config->ray.side = 1;
			}
			if (config->map[config->player.map_x][config->player.map_y] == '1')
				config->ray.hit = '1';
		}

		if (config->ray.side == 0)
			config->ray.wallDist = (config->ray.sideDist_x - config->ray.deltaDist_x);
		else
			config->ray.wallDist = (config->ray.sideDist_y - config->ray.deltaDist_y);
		config->wall.line_height = (int)(WIDTH / config->ray.wallDist);
		config->wall.draw_start = -config->wall.line_height / 2 + WIDTH / 2;
		if (config->wall.draw_start < 0)
			config->wall.draw_start = 0;
		config->wall.draw_end = config->wall.line_height / 2 + WIDTH / 2;
		if(config->wall.draw_end >= WIDTH)
			config->wall.draw_end = WIDTH - 1;

		if (config->ray.side == 0)
			wallX = config->player.pos_y + config->ray.wallDist * config->ray.rayDir_y;
		else
			wallX = config->player.pos_x + config->ray.wallDist * config->ray.rayDir_x;
		wallX -= floor((wallX));

		config->wall.tex_x = (int)(wallX * (double)texh);
		if (config->ray.side == 0 && config->ray.rayDir_x > 0)
			config->wall.tex_x = texh - config->wall.tex_x - 1;
		if (config->ray.side == 1 && config->ray.rayDir_y < 0)
			config->wall.tex_x = texh - config->wall.tex_x - 1;

		config->wall.step = 1.0 * texh / config->wall.line_height;
		config->wall.tex_pos = (config->wall.draw_start - WIDTH / 2 + config->wall.line_height / 2) * config->wall.step;
		
		
		y = config->wall.draw_start - 1;
		while (++y < config->wall.draw_end)
		{
			config->wall.tex_y = (int)config->wall.tex_pos & (texh - 1);
			config->wall.tex_pos += config->wall.step;
			if (config->ray.side == 0)
				my_pixel_put(&config->img,  x, y, 0x626570);
			else
				my_pixel_put(&config->img, x, y, 0x4E5159);
		}
	}
	mlx_put_image_to_window(config->data.mlx, config->data.win, config->img.img, 0, 0);
	mlx_destroy_image(config->data.mlx, config->img.img);

	return (0);
}


void start(t_config *config, char **map)
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
	mlx_hook(config->data.win, 2, 1L << 0, check, config);
	mlx_hook(config->data.win, 17, 0, fri, &config->data);
	mlx_hook(config->data.win, 6, (1L << 6), mouse_motion, config);
	mlx_loop_hook(config->data.mlx, start_ray_casting, config);
	mlx_loop(config->data.mlx);
}
