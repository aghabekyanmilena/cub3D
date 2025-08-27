/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anush <anush@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:29:20 by atseruny          #+#    #+#             */
/*   Updated: 2025/08/27 17:38:48 by anush            ###   ########.fr       */
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
	int j=0;
	while (i<1000)
	{
		j=0;
		while(j<1800)
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

int	start_ray_casting(t_config *config)
{
	int	x;
	double wallX; //where exactly the wall was hit
	get_player_struct(config);
	put_back(&config->data);

	config->ray.hit = '0';
	while (1)
	{
		x = 0;
		while (x < WIDTH)
		{
			config->ray.camera_x = 2 * x / WIDTH - 1;
			config->ray.rayDir_x = config->player.dir_x + config->player.plane_x * config->ray.camera_x;
			config->ray.rayDir_y = config->player.dir_y + config->player.plane_y * config->ray.camera_x;
			if (config->ray.rayDir_x == 0 || config->ray.rayDir_x == 0)
				return (0);
			config->ray.deltaDist_x = fabs(1 / config->ray.rayDir_x);
			config->ray.deltaDist_y = fabs(1 / config->ray.rayDir_y);
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
				if (config->map[config->player.map_x][config->player.map_y] != '0')
					config->ray.hit = config->map[config->player.map_x][config->player.map_y];
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

			if (side == 0)
				wallX = config->player.pos_y + config->ray.wallDist * config->ray.rayDir_y;
			else
				wallX = config->player.pos_x + config->ray.wallDist * config->ray.rayDir_x;
			wallX -= floor((wallX));

			//x coordinate on the texture
			int texX = int(wallX * double(texWidth));
			if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
			if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

			// How much to increase the texture coordinate per screen pixel
			double step = 1.0 * texHeight / lineHeight;
			// Starting texture coordinate
			double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
			for(int y = drawStart; y<drawEnd; y++)
			{
				// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
				int texY = (int)texPos & (texHeight - 1);
				texPos += step;
				Uint32 color = texture[texNum][texWidth * texY + texX];
				//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
				if(side == 1) color = (color >> 1) & 8355711;
				buffer[y][x] = color;
			}


			
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
