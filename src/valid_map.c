/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anush <anush@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:24:22 by miaghabe          #+#    #+#             */
/*   Updated: 2025/08/27 14:30:35 by anush            ###   ########.fr       */
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
	int		i = start_index;
	int		line_count = 0;
	int		player_count = 0;
	char	*line;
	int		j;

	while (lines[i])
	{
		if (!is_ws_only(lines[i]))
			line_count++;
		i++;
	}
	data->map = malloc(sizeof(char *) * (line_count + 1));
	if (!data->map)
		return (0);
	i = 0;
	while (lines[start_index])
	{
		line = lines[start_index];
		if (is_ws_only(line))
		{
			start_index++;
			continue;
		}
		j = 0;
		while (line[j] && line[j] != '\n' && line[j] != '\r')
		{
			if (!characker_check(line[j]))
			{
				printf("error, invalid character\n");
				return (0);
			}
			if (ft_strchr("NSEW", line[j]))
			{
				data->posX = i; //payer's position
				data->posY = j;
				data->view = line[j]; //vor koxm a nayum u positiony
				player_count++;
			}
			j++;
		}
		data->map[i] = ft_strtrim(line, " \t\r\n");
		if (!data->map[i])
			return (0);
		i++;
		start_index++;
	}
	data->map[i] = NULL;
	data->height = line_count;
	data->player_count = player_count;
	if (player_count != 1)
	{
		printf("error, invalid number of players\n");
		return 0;
	}
	return (1);
}
