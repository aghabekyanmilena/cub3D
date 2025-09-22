/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 20:26:32 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/22 15:30:52 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_lines(char **lines)
{
	int	i;

	i = 0;
	if (!lines)
		return ;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}

void	free_config(t_config *data)
{
	if (data->map)
		free_lines(data->map);
	data->map = NULL;
	free(data->no_path);
	free(data->so_path);
	free(data->we_path);
	free(data->ea_path);
	data->no_path = NULL;
	data->so_path = NULL;
	data->we_path = NULL;
	data->ea_path = NULL;
}

void	free_map_copy(char ***map, int height)
{
	int	i;

	if (!map || !*map)
		return ;
	i = 0;
	while (i < height)
	{
		free((*map)[i]);
		i++;
	}
	free(*map);
	*map = NULL;
}
