/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:51:33 by atseruny          #+#    #+#             */
/*   Updated: 2025/09/22 15:05:02 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_ray_dir(t_ray *ray, t_player *player, int x)
{
	ray->camera_x = 2 * x / (double)LENGTH - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	player->map_x = (int)player->pos_x;
	player->map_y = (int)player->pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

void	get_step_player(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		player->step_x = -1;
		ray->side_dist_x = (player->pos_x - player->map_x) * ray->delta_dist_x;
	}
	else
	{
		player->step_x = 1;
		ray->side_dist_x = (player->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		player->step_y = -1;
		ray->side_dist_y = (player->pos_y - player->map_y) * ray->delta_dist_y;
	}
	else
	{
		player->step_y = 1;
		ray->side_dist_y = (player->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}

void	check_if_hit(t_ray *ray, t_player *player, char **map)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			player->map_x += player->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			player->map_y += player->step_y;
			ray->side = 1;
		}
		if (map[player->map_x][player->map_y] == '1')
			ray->hit = 1;
		else if (map[player->map_x][player->map_y] == 'C')
			ray->hit = 2;
		else if (map[player->map_x][player->map_y] == 'O')
			ray->hit = 3;
	}
	if (ray->side == 0)
		ray->wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

void	get_wall_size(t_ray *ray, t_player *player, t_wall *wall)
{
	double	wall_x;

	wall->line_height = (int)(WIDTH / ray->wall_dist);
	wall->draw_start = -wall->line_height / 2 + WIDTH / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = wall->line_height / 2 + WIDTH / 2;
	if (wall->draw_end >= WIDTH)
		wall->draw_end = WIDTH - 1;
	if (ray->side == 0)
		wall_x = player->pos_y + ray->wall_dist * ray->ray_dir_y;
	else
		wall_x = player->pos_x + ray->wall_dist * ray->ray_dir_x;
	wall_x -= floor((wall_x));
	wall->tex_x = (int)(wall_x * (double)TEX_H);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		wall->tex_x = TEX_H - wall->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		wall->tex_x = TEX_H - wall->tex_x - 1;
	wall->step = 1.0 * TEX_H / wall->line_height;
	wall->tex_pos = (wall->draw_start - WIDTH / 2
			+ wall->line_height / 2) * wall->step;
}

void	draw_wall(t_config *config, t_wall *wall, int x, int y)
{
	while (++y < wall->draw_end)
	{
		wall->tex_y = (int)wall->tex_pos & (TEX_H - 1);
		wall->tex_pos += wall->step;
		if (config->ray.hit == 2)
			my_pixel_put(&config->img, x, y,
				get_pixel(&config->close, wall->tex_x, wall->tex_y));
		else if (config->ray.hit == 3)
			my_pixel_put(&config->img, x, y,
				get_pixel(&config->open, wall->tex_x, wall->tex_y));
		else if (config->ray.side == 0 && config->ray.ray_dir_x > 0)
			my_pixel_put(&config->img, x, y,
				get_pixel(&config->south, wall->tex_x, wall->tex_y));
		else if (config->ray.side == 0 && config->ray.ray_dir_x < 0)
			my_pixel_put(&config->img, x, y,
				get_pixel(&config->north, wall->tex_x, wall->tex_y));
		else if (config->ray.side == 1 && config->ray.ray_dir_y > 0)
			my_pixel_put(&config->img, x, y,
				get_pixel(&config->east, wall->tex_x, wall->tex_y));
		else if (config->ray.side == 1 && config->ray.ray_dir_y < 0)
			my_pixel_put(&config->img, x, y,
				get_pixel(&config->west, wall->tex_x, wall->tex_y));
	}
}
