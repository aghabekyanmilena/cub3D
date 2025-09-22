/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:32:51 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/22 15:24:25 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**add_line(char **lines, char *line, int count)
{
	char	**new_lines;
	int		i;

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

char	**read_map(const char *filename)
{
	int		fd;
	char	*line;
	char	**lines;
	int		count;

	count = 0;
	line = NULL;
	lines = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putendl_fd("Error", 2), NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines = add_line(lines, line, count);
		if (!lines)
		{
			free(line);
			close(fd);
			return (ft_putendl_fd("Error", 2), NULL);
		}
		line = get_next_line(fd);
		count++;
	}
	return (close(fd), lines);
}

int	validation(t_config *config, char **map_lines, int map_start)
{
	if (!parse(config, map_lines, &map_start))
		return (free_lines(map_lines), free_config(config), 0);
	if (!parse_map(config, map_lines, map_start))
		return (free_lines(map_lines), free_config(config), 0);
	if (!check_map(config))
		return (free_lines(map_lines), free_config(config),
			ft_putendl_fd("Error", 2), 0);

	if (!check_single_spawn(config))
		return (free_lines(map_lines), free_config(config), 0);
	if (!check_map_closed(config))
		return (free_lines(map_lines), free_config(config), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_config	config;
	char		**map_lines;
	int			map_start;

	map_start = 0;
	map_lines = NULL;
	if (argc != 2)
		return (printf("Error\nUsage: %s <map.cub>\n", argv[0]), 1);
	if (!check_filename(argv[1]))
		return (1);
	map_lines = read_map(argv[1]);
	if (!map_lines)
		return (ft_putendl_fd("Error", 2), 1);
	ft_bzero(&config, sizeof(t_config));
	if (!validation(&config, map_lines, map_start))
		return (1);
	start(&config, map_lines);
	free_lines(map_lines);
	free_config(&config);
	return (0);
}
