/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:29:20 by atseruny          #+#    #+#             */
/*   Updated: 2025/09/13 15:34:43 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	put_miniback(t_config *config)
{
	int	i;
	int	j;
	int	k;
	int	m;
	int	n;
	int	c;

	j = 0;
	n = 0;
	while (config->map[j])
	{
		i = 0;
		while (i++ < 10)
		{
			k = 0;
			m = 0;
			while (config->map[j][k] != '\0')
			{
				while (ft_isspace(config->map[j][k]))
				{
					k++;
					m += 10;
				}
				if (config->map[j][k] == '\0')
					break;
				c = 0;
				while (c++ < 10)
					my_pixel_put(&config->img, m++, n, 0x404040);
				k++;
			}
			n++;
		}
		j++;
	}
}

void	minimap(t_config *config)
{
	int	i;
	int	j;
	int	k;
	int	m;
	int	n;
	int c;
	j = 0;
	n = 0;
	put_miniback(config);
	while (config->map[j])
	{
		i = 0;
		while (i < 10)
		{
			k = 0;
			m = 0;
			while (config->map[j][k] != '\0')
			{
				while (ft_isspace(config->map[j][k]))
				{
					k++;
					m += 10;
				}
				if (config->map[j][k] != '\0' && config->map[j][k] == '1')
				{
					c = 0;
					while (c < 10)
						my_pixel_put(&config->img, m + c++, n, 0x000000);
				}
				else if (config->map[j][k] != '\0' && config->map[j][k] == 'D')
				{
					c = 0;
					while (c < 10)
						my_pixel_put(&config->img, m + c++, n, 0x000090);
				}
				
				m += 10;
				k++;
			}
			c = 0;
			while (c < 6 && i < 6)
				my_pixel_put(&config->img, (config->player.pos_y * 10 + c++ - 3), (config->player.pos_x * 10 + i - 3), 0xF02020);
			i++;
			n++;
		}
		j++;
	}
}

// void	hands(t_config *config)
// {
// 	int	i = WIDTH - 768;
// 	int	j = (LENGTH - 768) / 2;
// 	int	k = 0;
// 	int	l;
// 	while (k < 768)
// 	{
// 		j = (LENGTH - 768) / 2;
// 		l = 0;
// 		while (l < 768)
// 		{
// 			if (get_pixel(&config->hands, l, k) >= 0xFDFDFD)
// 			{
// 				j++;
// 				l++;
// 				continue;
// 			}
// 			my_pixel_put(&config->img, j, i, get_pixel(&config->hands, l, k));
// 			j++;
// 			l++;
// 		}
// 		k++;
// 		i++;
// 	}
// }

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
		config->ray.hit = 0;

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
		while (config->ray.hit == 0)
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
				config->ray.hit = 1;
			else if (config->map[config->player.map_x][config->player.map_y] == 'D')
				config->ray.hit = 2;
			// if (config->map[config->player.map_x][config->player.map_y] == 'N' || 
			// config->map[config->player.map_x][config->player.map_y] == 'W' ||
			// config->map[config->player.map_x][config->player.map_y] == 'S' || 
			// config->map[config->player.map_x][config->player.map_y] == 'E')
			// 	config->ray.hit = 0;
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
			if (config->ray.side == 0 && config->ray.rayDir_x > 0)
				my_pixel_put(&config->img, x, y, get_pixel(&config->south, config->wall.tex_x, config->wall.tex_y));
			else if (config->ray.side == 0 && config->ray.rayDir_x < 0)
				my_pixel_put(&config->img, x, y, get_pixel(&config->north, config->wall.tex_x, config->wall.tex_y));
			else if (config->ray.side == 1 && config->ray.rayDir_y > 0)
				my_pixel_put(&config->img, x, y, get_pixel(&config->east, config->wall.tex_x, config->wall.tex_y));
			else if (config->ray.side == 1 && config->ray.rayDir_y < 0)
				my_pixel_put(&config->img, x, y, get_pixel(&config->west, config->wall.tex_x, config->wall.tex_y));
			else if (config->ray.hit == 2)
				my_pixel_put(&config->img, x, y, get_pixel(&config->closed, config->wall.tex_x, config->wall.tex_y));
		}
	}
	minimap(config);
	// hands(config);
	mlx_put_image_to_window(config->data.mlx, config->data.win, config->img.img, 0, 0);
	mlx_destroy_image(config->data.mlx, config->img.img);

	return (0);
}


// void	take_photo(t_config *config)
// {
// 	// static int	c;
// 	// int			k;
// 	// int			x = 0;
// 	// int			y = 0;

// 	// if (c == 300)
// 	// 	return ;
// 	// x = 0;

// 	unsigned int	*dst;
// 	unsigned int	i;

// 	dst = (unsigned int *) config->img.addr;
// 	i = LENGTH * WIDTH + 1;
// 	while (--i > 0)
// 		*dst++ = 0xFFFFFF;

// 	// c++;

// }


// int mouse_photo(int button, int x, int y, t_config *config)
// {
// 	(void)x;
// 	(void)y;
	
// 	if (button == 1)
// 		take_photo(config);
// 	return (0);
// }

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
	get_textures(config);
	mlx_hook(config->data.win, 2, (1L << 0), check, config);
	mlx_hook(config->data.win, 17, 0, fri, &config->data);
	// mlx_hook(config->data.win, 4, (1L << 2), mouse_photo, config);
	mlx_hook(config->data.win, 6, (1L << 6), mouse_motion, config);
	mlx_loop_hook(config->data.mlx, start_ray_casting, config);
	mlx_loop(config->data.mlx);
}
