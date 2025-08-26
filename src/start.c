/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:29:20 by atseruny          #+#    #+#             */
/*   Updated: 2025/08/23 18:44:12 by atseruny         ###   ########.fr       */
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

int	put_back(t_data *data)
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
	return 1;
}

void start(t_config *config, char **map)
{
	t_data data;

	(void)config;
	data.mlx = mlx_init();
	if (!data.mlx)
		return ;
	data.map = map;
	data.win = mlx_new_window(data.mlx, 1800, 1000, "Cub3D");
	if (!data.win)
	{
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		return ;
	}
	mlx_key_hook(data.win, check, &data);
	mlx_hook(data.win, 17, 0, fri, &data);
	mlx_loop_hook(data.mlx, put_back, &data);
	mlx_loop(data.mlx);
}