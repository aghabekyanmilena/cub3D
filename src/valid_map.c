/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:24:22 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/14 00:04:09 by miaghabe         ###   ########.fr       */
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
	int	i;
	int	j;
	int	k = start_index;
	int line_count = 0;
	int max_width = 0;

	while (lines[k])
	{
		if (!is_ws_only(lines[k]))
		{
			int len = 0;
			int j = 0;
			while (lines[k][j] && lines[k][j] != '\n' && lines[k][j] != '\r')
			{
				if (lines[k][j] == '\t')
					len += 4;
				else
					len++;
				j++;
			}
			if (len > max_width)
				max_width = len;
			line_count++;
		}
		k++;
	}
	data->height = line_count;
	data->width = max_width;
	data->map = malloc(sizeof(char *) * (line_count + 1));
	if (!data->map)
		return (0);
	i = 0;
	while (lines[start_index])
	{
		if (is_ws_only(lines[start_index]))
		{
			start_index++;
			continue;
		}
		data->map[i] = malloc(max_width + 1);
		if (!data->map[i])
			return (0);
		j = 0;
		int syun = 0;
		while (lines[start_index][j] && lines[start_index][j] != '\n' && lines[start_index][j] != '\r')
		{
			if (!characker_check(lines[start_index][j]))
				return (printf("Error\ninvalid character in map\n"), 0);

			if (lines[start_index][j] == '\t')
			{
				for (int t = 0; t < 4 && syun < max_width; t++)
					data->map[i][syun++] = '2';
			}
			else if (lines[start_index][j] == ' ')
			{
				data->map[i][syun++] = '2';
			}
			else
				data->map[i][syun++] = lines[start_index][j];
			j++;
		}
		while (syun < max_width)
			data->map[i][syun++] = '2';
		data->map[i][syun] = '\0';
		i++;
		start_index++;
	}
	data->map[i] = NULL;
	// int boo = 0;
	// while(lines[boo])
	// {
	// 	printf("%s", lines[boo]);
	// 	boo++;
	// }
	return (1);
}
