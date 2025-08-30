/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:06:43 by miaghabe          #+#    #+#             */
/*   Updated: 2025/08/11 17:08:19 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_config(t_config *config)
{
	int i;

	i = 0;
	ft_bzero(config, sizeof(t_config));
	config->no_path = NULL;
	config->so_path = NULL;
	config->we_path = NULL;
	config->ea_path = NULL;

	config->floor.r = -1;
	config->floor.g = -1;
	config->floor.b = -1;
	config->ceiling.r = -1;
	config->ceiling.g = -1;
	config->ceiling.b = -1;

	config->no = 0;
	config->so = 0;
	config->we = 0;
	config->ea = 0;
	config->f = 0;
	config->c = 0;

	config->map = NULL;
	config->height = 0;
	config->player_count = 0;
	config->graphics.mlx = NULL;
	config->graphics.win = NULL;

	while (i < 4)
	{
		config->graphics.texture_paths[i] = NULL;
		config->graphics.textures[i] = NULL;
		config->graphics.widths[i] = 0;
		config->graphics.heights[i] = 0;
		i++;
	}
}
