/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:24:22 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/20 19:18:36 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int characker_check(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' ||
			c == 'E' || c == 'W' || c == 'O' || c == ' ' ||
			c == '\t' || c == 'C');
}

int	parse_map(t_config *data, char **lines, int start_index)
{
	int i, j, k = start_index;
	int line_count = 0;
	int max_width = 0;

	while (lines[k])
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
	    data->map[i] = malloc(max_width + 1);
	    if (!data->map[i])
	        return (0);
	    if (is_ws_only(lines[start_index]))
	    {
	        int syun = 0;
	        while (syun < max_width)
	            data->map[i][syun++] = '2';
	        data->map[i][syun] = '\0';
	        i++;
	        start_index++;
	        continue;
	    }	
	    j = 0;
	    int syun = 0;
	    while (lines[start_index][j] &&
	           lines[start_index][j] != '\n' &&
	           lines[start_index][j] != '\r')
	    {
	        if (!characker_check(lines[start_index][j]))
	            return (printf("Error\nInvalid character in map\n"), 0);
	        if (lines[start_index][j] == '\t')
	        {
	            for (int t = 0; t < 4 && syun < max_width; t++)
	                data->map[i][syun++] = '2';
	        }
	        else if (lines[start_index][j] == ' ')
	            data->map[i][syun++] = '2';
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
	data->is_open = 0;
	return (1);
}

