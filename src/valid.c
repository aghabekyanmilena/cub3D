/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:06:44 by miaghabe          #+#    #+#             */
/*   Updated: 2025/08/23 17:24:18 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_filename(char *filename)
{
	char	*name;

	name = ft_strchr(filename, '.');
	if (!name || ft_strcmp(name, ".cub") != 0 || ft_strlen(name) != 4)
	{
		printf("Invalid file name\n");
		return (0);
	}
	return (1);
}

int	demi_6_toxy(char *line)
{
	return (
		ft_strcmp(line, "NO ") == 0 ||
		ft_strcmp(line, "SO ") == 0 ||
		ft_strcmp(line, "WE ") == 0 ||
		ft_strcmp(line, "EA ") == 0 ||
		ft_strcmp(line, "F ") == 0 ||
		ft_strcmp(line, "C ") == 0
	);
}

int	parse_et_6_toxy(t_config *data, char *line)
{
	if (ft_strcmp(line, "NO ") == 0)
		return (parse_texture(&data->no_path, &data->no, line + 3, "NO"));
	if (ft_strcmp(line, "SO ") == 0)
		return (parse_texture(&data->so_path, &data->so, line + 3, "SO"));
	if (ft_strcmp(line, "WE  ") == 0)
		return (parse_texture(&data->we_path, &data->we, line + 3, "WE"));
	if (ft_strcmp(line, "EA ") == 0)
		return (parse_texture(&data->ea_path, &data->ea, line + 3, "EA"));
	if (ft_strcmp(line, "F ") == 0)
		return (parse_color(&data->floor, &data->f, line + 2, "F"));
	if (ft_strcmp(line, "C ") == 0)
		return (parse_color(&data->ceiling, &data->c, line + 2, "C"));
	return (0);
}

int	parse(t_config *data, char **lines, int *start_index)
{
	int	i = 0;
	while (lines[i])
	{
		if (demi_6_toxy(lines[i]))
		{
			if (!parse_et_6_toxy(data, lines[i]))
				return (0);
		}
		else if (*lines[i] != '\0' && *lines[i] != '\n')
			break;
		i++;
	}
	// if (!data->no || !data->so || !data->we || !data->ea ||
	// 	  !data->f || !data->c)
	// {
	// 	printf("Error: Missing texture or color.\n");
	// 	return (0);
	// }
	*start_index = i;
	return (1);
}

int	parse_texture(char **dest, int *flag, char *path, char *type)
{
	(void)type;
	if (*flag)
	{
		printf("Error: Duplicate\n");
		return (0);
	}
	while (ft_isspace(*path))
		path++;
	if (ft_strlen(path) < 5 || ft_strcmp(path + ft_strlen(path) - 4, ".xpm") != 0)
	{
		printf("error, must be .xpm\n");
		return (0);
	}
	*dest = ft_strdup(path);
	if (!*dest)
		return (0);
	*flag = 1;
	return (1);
}

static int	guyni_stugum(char **str)
{
	int	val;

	val = 0;
	while (**str == ' ')
		(*str)++;
	if (!ft_isdigit(**str))
		return (-1);
	while (ft_isdigit(**str))
		val = val * 10 + *((*str)++) - '0';
	if (val < 0 || val > 255)
		return (-1);
	return (val);
}

int	parse_color(t_color *color, int *flag, char *line, char *type)
{
	(void)type;
	char *tmp = line;
	if (*flag)
	{
		printf("Error: Duplicate\n");
		return (0);
	}
	color->r = guyni_stugum(&tmp);
	if (*tmp++ != ',')
	{
		printf("Error: Invalid format.\n");
		return (0);
	}
	color->g = guyni_stugum(&tmp);
	if (*tmp++ != ',')
	{
		printf("Error: Invalid format.\n");
		return (0);
	}
	color->b = guyni_stugum(&tmp);
	while (*tmp == ' ') tmp++;
	if (color->r == -1 || color->g == -1 || color->b == -1)
	{
		printf("Error:\n");
		return (0);
	}
	*flag = 1;
	return (1);
}
