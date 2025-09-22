/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:24:22 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/22 17:16:04 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	hashvel(char **lines, int start, int *h, int *w)
{
	int	k;
	int	len;
	int	j;

	*h = 0;
	*w = 0;
	k = start;
	while (lines[k])
	{
		len = 0;
		j = 0;
		while (lines[k][j] && lines[k][j] != '\n' && lines[k][j] != '\r')
		{
			if (lines[k][j] == '\t')
				len += 4;
			else
				len++;
			j++;
		}
		if (len > *w)
			*w = len;
		(*h)++;
		k++;
	}
}

static void	fill_empty_line(char *dst, int max_width)
{
	int	i;

	i = 0;
	while (i < max_width)
	{
		dst[i] = '2';
		i++;
	}
	dst[i] = '\0';
}

static int	handle_char(char c, char *dst, int *syun, int max_width)
{
	int	t;

	if (!characker_check(c))
		return (ft_putendl_fd("Error", 2), 0);
	if (c == '\t')
	{
		t = 0;
		while (t++ < 4 && *syun < max_width)
			dst[(*syun)++] = '2';
	}
	else if (c == ' ')
		dst[(*syun)++] = '2';
	else
		dst[(*syun)++] = c;
	return (1);
}

static int	copy_line(t_config *data, char *src, int i, int max_width)
{
	int	j;
	int	syun;

	j = 0;
	syun = 0;
	if (is_ws_only(src))
		return (fill_empty_line(data->map[i], max_width), 1);
	while (src[j] && src[j] != '\n' && src[j] != '\r')
	{
		if (!handle_char(src[j], data->map[i], &syun, max_width))
			return (0);
		j++;
	}
	while (syun < max_width)
		data->map[i][syun++] = '2';
	data->map[i][syun] = '\0';
	return (1);
}

int	parse_map(t_config *data, char **lines, int start_index)
{
	int	i;

	hashvel(lines, start_index, &data->height, &data->width);
	data->map = malloc(sizeof(char *) * (data->height + 1));
	if (!data->map)
		return (0);
	i = 0;
	while (lines[start_index])
	{
		data->map[i] = malloc(data->width + 1);
		if (!data->map[i])
			return (free_half(data, i - 1), 0);
		if (!copy_line(data, lines[start_index], i, data->width))
			return (free_half(data, i), 0);
		i++;
		start_index++;
	}
	data->map[i] = NULL;
	data->is_open = 0;
	return (1);
}
