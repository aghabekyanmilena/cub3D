/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:24:22 by miaghabe          #+#    #+#             */
/*   Updated: 2025/08/23 14:54:01 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	characker_check(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' ||
			c == 'E' || c == 'W' || c == 'D' || c == ' ');
}

int	parse_map(t_config *data, char **lines, int start_index)
{
	int		i;
	int		line_count;
	int		player_count;
	char	*line;
	int		j;

	i = start_index;
	line_count = 0;
	player_count = 0;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) == 0)
		{
			printf("error, empty line\n");
			return (0);
		}
		line_count++;
		i++;
	}
	data->map = malloc(sizeof(char *) * (line_count + 1));
	if (!data->map)
		return (0);
	i = 0;
	while (i < line_count)
	{
		line = lines[start_index + i];
		j = 0;
		while(line[j])
		{
			if (!characker_check(line[j]))
			{
				printf("error, invalid character\n");
				return (0);
			}
			if (ft_strchr("NSEW", line[j]))
				player_count++;
			j++;
		}
		data->map[i] = ft_strdup(line);
		if (!data->map[i])
			return (0);
		i++;
	}
	data->map[i] = NULL;
	data->height = line_count;
	data->player_count = player_count;
	if (player_count != 1)
	{
		printf("error, too many players\n");
		return (0);
	}
	return (1);
}
