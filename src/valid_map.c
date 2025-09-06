/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:24:22 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/06 19:54:57 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int characker_check(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' ||
			c == 'E' || c == 'W' || c == 'D' || c == ' ' || c == '\t');
}

int parse_map(t_config *data, char **lines, int start_index)
{
	int	i = 0;
	int	player_count = 0;
	int	line_count = 0;
	int	j;

	int	k = start_index;
	while (lines[k])
	{
		if (!is_ws_only(lines[k]))
				line_count++;
		k++;
	}
	data->map = malloc(sizeof(char *) * (line_count + 1));
	if (!data->map)
		return (0);
	while (lines[start_index])
	{
		if (is_ws_only(lines[start_index]))
		{
			start_index++;
			continue;
		}
		j = 0;
		while (lines[start_index][j] && lines[start_index][j] != '\n' && lines[start_index][j] != '\r')
		{
			if (!characker_check(lines[start_index][j]))
			{
				printf("Error\ninvalid character in map\n");
				while (i > 0)
					free(data->map[--i]);
				free(data->map);
				return (0);
			}
			if (ft_strchr("NSEW", lines[start_index][j]))
				player_count++;
			j++;
		}
		data->map[i] = ft_strdup(lines[start_index]);
		if (!data->map[i])
		{
			while (i > 0)
				free(data->map[--i]);
			free(data->map);
			return (0);
		}
		i++;
		start_index++;
	}
	data->map[i] = NULL;
	data->height = line_count;
	data->player_count = player_count;
	if (player_count != 1)
		return (printf("Error\ninvalid number of players\n"), 0);
	return (1);
}
