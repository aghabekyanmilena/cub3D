/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:22:51 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/04 23:32:51 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// static int	char_valid(char c)
// {
// 	return (c == '0' || c == '1'
// 		|| c == 'N' || c == 'S'
// 		|| c == 'E' || c == 'W'
// 		|| ft_isspace((unsigned char)c));
// }

static int	char_valid(char c)
{
	return (c == '0' || c == '1'
		|| c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

static void	set_player(t_config *cfg, int y, int x, char dir)
{
	cfg->x = x;
	cfg->y = y;
	cfg->direct = dir;
}

// static int	copy_map_line(t_config *cfg, char *line, int row, int width)
// {
// 	int		x;
// 	char	*dst;

// 	dst = (char *)ft_calloc(width + 1, sizeof(char));
// 	if (!dst)
// 		return (0);
// 	x = 0;
// 	while (line[x])
// 	{
// 		if (!char_valid(line[x]))
// 		{
// 			printf("Error\nInvalid character in map: '%c'\n", line[x]);
// 			return (free(dst), 0);
// 		}
// 		dst[x] = line[x];
// 		if (line[x] == 'N' || line[x] == 'S'
// 			|| line[x] == 'E' || line[x] == 'W')
// 			set_player(cfg, row, x, line[x]);
// 		x++;
// 	}
// 	while (x < width)
// 		dst[x++] = ' ';
// 	cfg->map[row] = dst;
// 	return (1);
// }

static int	copy_map_line(t_config *cfg, char *line, int row, int width)
{
	int		x;
	char	*dst;

	dst = (char *)ft_calloc(width + 1, sizeof(char));
	if (!dst)
		return (0);
	x = 0;
	while (line[x])
	{
		if (!char_valid(line[x]))
		{
			printf("Error\nInvalid character in map: '%c'\n", line[x]);
			return (free(dst), 0);
		}
		if (line[x] == ' ')
			dst[x] = '1';
		else
			dst[x] = line[x];

		if (line[x] == 'N' || line[x] == 'S'
			|| line[x] == 'E' || line[x] == 'W')
			set_player(cfg, row, x, line[x]);
		x++;
	}
	while (x < width)
		dst[x++] = '1';
	cfg->map[row] = dst;
	return (1);
}


int	parse_map(t_config *cfg, char **lines, int start_index)
{
	int	i;
	int	h;
	int	w;

	h = 0;
	w = 0;
	while (lines[start_index + h])
	{
		if ((int)ft_strlen(lines[start_index + h]) > w)
			w = ft_strlen(lines[start_index + h]);
		h++;
	}
	cfg->map = (char **)ft_calloc(h + 1, sizeof(char *));
	if (!cfg->map)
		return (0);
	cfg->height = h;
	cfg->width = w;
	i = 0;
	while (i < h)
	{
		if (!copy_map_line(cfg, lines[start_index + i], i, w))
			return (0);
		i++;
	}
	return (1);
}
