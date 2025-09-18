/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:32:51 by miaghabe          #+#    #+#             */
/*   Updated: 2025/09/18 20:22:42 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_lines(char **lines)
{
	int	i;

	i = 0;
	if (!lines)
		return;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}

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
	char	*line = NULL;
	char	**lines = NULL;
	int		count = 0;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("open"), NULL);
	while ((line = get_next_line(fd)) != NULL)
	{
		lines = add_line(lines, line, count);
		if (!lines)
		{
			free(line);
			close(fd);
			return (NULL);
		}
		count++;
	}
	close(fd);
	return (lines);
}

int main(int argc, char **argv)
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
	ft_bzero(&config, sizeof(t_config));
	map_lines = read_map(argv[1]);
	if (!map_lines)
		return (printf("Error\nEmpty file\n"), 1);
	if (!parse(&config, map_lines, &map_start))
		return (free_lines(map_lines), 1);
	if (!parse_map(&config, map_lines, map_start))
		return (free_lines(map_lines), 1);
	if (!check_map(&config))
		return (printf("Error\nNo map found\n"), 1);
	if (!check_single_spawn(&config))
		return(1);
	if (!check_map_closed(&config))
	{
		free_lines(map_lines);
		return (printf("Error\nmap not enclosed\n"), 1);
	}
	free_lines(map_lines);
	return (0);
}
