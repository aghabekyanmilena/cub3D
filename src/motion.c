/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:47:19 by atseruny          #+#    #+#             */
/*   Updated: 2025/09/01 16:47:20 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_view(t_config *config, double angle)
{
	double	sa;
	double	ca;
	double	tmp;

	ca = cos(angle);
	sa = sin(angle);
	tmp = config->player.dir_x;
	config->player.dir_x = config->player.dir_x * ca - config->player.dir_y * sa;
	config->player.dir_y = tmp * sa + config->player.dir_y * ca;

	tmp = config->player.plane_x;
	config->player.plane_x = config->player.plane_x * ca - config->player.plane_y * sa;
	config->player.plane_y = tmp * sa + config->player.plane_y * ca;

}

int	mouse_motion(int x, int y, t_config *config)
{
	int	delta_rot;

	if (config->player.prev_view != -1)
	{
		delta_rot = x - config->player.prev_view;
		if (delta_rot < 0)
			rotate_view(config, (double)(SPEED));
		else
			rotate_view(config, (double)(-SPEED));
	}
	config->player.prev_view = x;
	(void)y;
	return (0);
}
