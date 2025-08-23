/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:32:51 by miaghabe          #+#    #+#             */
/*   Updated: 2025/08/23 14:53:32 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_lines(char **lines)
{
	int i = 0;
	if (!lines)
		return;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}

static char **add_line(char **lines, char *line, int count)
{
	char **new_lines;
	int i;

	new_lines = malloc(sizeof(char *) * (count + 2));
	if (!new_lines)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_lines[i] = lines[i];
		i++;
	}
	new_lines[i++] = line;
	new_lines[i] = NULL;
	free(lines);
	return (new_lines);
}

char **read_map(const char *filename)
{
	int fd = open(filename, O_RDONLY);
	char *line = NULL;
	char **lines = NULL;
	int count = 0;

	if (fd < 0)
	{
	perror("open");
	return NULL;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
	lines = add_line(lines, line, count);
	if (!lines)
	{
	free(line);
	close(fd);
	return NULL;
	}
	count++;
	}
	close(fd);
	return lines;
}

int main(int argc, char **argv)
{
	t_config config;
	char **map_lines = NULL;
	int map_start = 0;

	if (argc != 2)
		return (printf("Usage: %s <map.cub>\n", argv[0]), 1);
	if (!check_filename(argv[1]))
		return (1);

	ft_bzero(&config, sizeof(t_config));
	map_lines = read_map(argv[1]);
	if (!map_lines)
		return (1);
	if (!parse(&config, map_lines, &map_start))
		return (free_lines(map_lines), 1);
	if (!parse_map(&config, map_lines, map_start))
		return (free_lines(map_lines), 1);

	// if (!validate_closure(&config))
	// 	return (free_lines(map_lines), 1);
	
	init_window_and_textures(&config);
	render_map(&config);
	mlx_loop(config.graphics.mlx);
	free_lines(map_lines);
	return (0);
}

/* uremn vabshe inch em arel, validacian karelia asel arel uxxaki
vonc vor shat andur kod lini ayspes asac tqac kpcrac, pordzel em
grel mapy kardalu pahy mi qich ban man, bayc normal chi linum */