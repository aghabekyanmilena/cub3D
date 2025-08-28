/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anush <anush@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:29:20 by atseruny          #+#    #+#             */
/*   Updated: 2025/08/28 12:32:28 by anush            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_map(char **map)
{
	int i=0;
	while(map[i])
		free(map[i++]);
	free(map);
}


int	fri(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_map(data->map);
	exit (0);
}

int	check(int keycode, t_data *data)
{
	if (keycode == XK_ESCAPE)
		fri(data);
	return (0);
}

void	get_player_struct(t_config *config)
{
	config->player.pos_x = config->posX + 0.5;
	config->player.pos_y = config->posY + 0.5;
	
	//check
	config->player.plane_x = 0;
	config->player.plane_y = 0.66;
	config->player.dir_x = -1;
	config->player.dir_y = 0;


	config->player.map_x = config->posX;
	config->player.map_y = config->posY;

}

void	put_back(t_data *data)
{
	int i=0;
	int j;
	while (i<WIDTH)
	{
		j=0;
		while(j<LENGTH)
		{
			if (i>500)
				mlx_pixel_put(data->mlx, data->win, j, i, 0x000000);
			else
				mlx_pixel_put(data->mlx, data->win, j, i, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

int rgb_to_int(t_color c)
{
	return ((c.r & 0xFF) << 16) | ((c.g & 0xFF) << 8) | (c.b & 0xFF);
}

void	draw_buf(t_data *data, int buffer[WIDTH][LENGTH])
{
	int i=0;
	int j;
	while (i<LENGTH)
	{
		j = 0;
		while(j<WIDTH)
		{
			mlx_pixel_put(data->mlx, data->win, j, i, buffer[j][i]);
			j++;
		}
		i++;
	}
}

int	start_ray_casting(t_config *config)
{
	int		x;
	int		y;
	double	wallX; //where exactly the wall was hit

	// int buffer[LENGTH][WIDTH];
	get_player_struct(config);
	// put_back(&config->data);
	while (1)
	{
		x = 0;
		while (x < WIDTH)
		{
			config->ray.hit = '0';
			config->ray.camera_x = 2 * x / (double)WIDTH - 1;
			config->ray.rayDir_x = config->player.dir_x + config->player.plane_x * config->ray.camera_x;
			config->ray.rayDir_y = config->player.dir_y + config->player.plane_y * config->ray.camera_x;

			config->ray.deltaDist_x = (config->ray.rayDir_x == 0) ? 1e30 : fabs(1 / config->ray.rayDir_x);
			config->ray.deltaDist_y = (config->ray.rayDir_y == 0) ? 1e30 : fabs(1 / config->ray.rayDir_y);

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
			// printf("%c\n", config->ray.hit);
			while (config->ray.hit == '0')
			{
				printf("%c\n", config->map[config->player.map_x][config->player.map_y]);

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
			config->wall.line_height = (int)(h / config->ray.wallDist);
			config->wall.draw_start = config->wall.line_height / 2 + h / 2;
			if (config->wall.draw_start < 0)
				config->wall.draw_start = 0;
			config->wall.draw_end = config->wall.line_height / 2 + h / 2;
			if(config->wall.draw_end >= h)
				config->wall.draw_end = h - 1;

			if (config->ray.side == 0)
				wallX = config->player.pos_y + config->ray.wallDist * config->ray.rayDir_y;
			else
				wallX = config->player.pos_x + config->ray.wallDist * config->ray.rayDir_x;
			wallX -= floor((wallX));

			config->wall.tex_x = (int)(wallX * (double)h);
			if (config->ray.side == 0 && config->ray.rayDir_x > 0)
				config->wall.tex_x = h - config->wall.tex_x - 1; // h=texWidth?
			if (config->ray.side == 1 && config->ray.rayDir_y < 0)
				config->wall.tex_x = h - config->wall.tex_x - 1;

			// How much to increase the texture coordinate per screen pixel
			config->wall.step = 1.0 * h / config->wall.line_height;
			// Starting texture coordinate
			config->wall.tex_pos = (config->wall.draw_start - h / 2 + config->wall.line_height / 2) * config->wall.step;
			
			
			y = config->wall.draw_start;
			while (y < config->wall.draw_end)
			{
				// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
				config->wall.tex_y = (int)config->wall.tex_pos & (h - 1);
				config->wall.tex_pos += config->wall.step;
				// t_color c;
				// c.r =128;
				// c.g =128;
				// c.b =128;

				// printf("aaaa\n");
				mlx_pixel_put(config->data.mlx, config->data.win, y, x, 0x0000FF);
				

				//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
				// if (config->ray.side == 1)
				// 	c = (t_color){80, 80, 80};
				// buffer[y][x] = rgb_to_int(c);
				
				// printf("%d\n",rgb_to_int(buffer[y][x]) );
				y++;
			}

			
			// draw_buf(&config->data, buffer);
			x++;
		}
	}
	return (1);
}

void start(t_config *config, char **map)
{
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
	mlx_key_hook(config->data.win, check, &config->data);
	mlx_hook(config->data.win, 17, 0, fri, &config->data);
	mlx_loop_hook(config->data.mlx, start_ray_casting, config);
	mlx_loop(config->data.mlx);
}
