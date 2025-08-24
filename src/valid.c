/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:06:44 by miaghabe          #+#    #+#             */
/*   Updated: 2025/08/24 16:38:09 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_filename(char *filename)
{
	char	*name;

	name = ft_strrchr(filename, '.');
	if (!name || ft_strcmp(name, ".cub") != 0)
	{
		printf("Invalid file name\n");
		return (0);
	}
	return (1);
}

static char *skip_ws(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return s;
}

int is_ws_only(char *s)
{
	size_t i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n')
		i++;
	return s[i] == '\0';
}

int	demi_6_toxy(char *line)
{
	char *s = skip_ws(line);

	return (
		(s[0] == 'N' && s[1] == 'O' && (s[2] == ' ' || s[2] == '\t')) ||
		(s[0] == 'S' && s[1] == 'O' && (s[2] == ' ' || s[2] == '\t')) ||
		(s[0] == 'W' && s[1] == 'E' && (s[2] == ' ' || s[2] == '\t')) ||
		(s[0] == 'E' && s[1] == 'A' && (s[2] == ' ' || s[2] == '\t')) ||
		(s[0] == 'F' && (s[1] == ' ' || s[1] == '\t')) ||
		(s[0] == 'C' && (s[1] == ' ' || s[1] == '\t'))
	);
}

int	parse_et_6_toxy(t_config *data, char *line)
{
	char *s = skip_ws(line);

	if (s[0] == 'N' && s[1] == 'O' && (s[2] == ' ' || s[2] == '\t'))
		return parse_texture(data, &data->no, s + 2, "NO");
	if (s[0] == 'S' && s[1] == 'O' && (s[2] == ' ' || s[2] == '\t'))
		return parse_texture(data, &data->so, s + 2, "SO");
	if (s[0] == 'W' && s[1] == 'E' && (s[2] == ' ' || s[2] == '\t'))
		return parse_texture(data, &data->we, s + 2, "WE");
	if (s[0] == 'E' && s[1] == 'A' && (s[2] == ' ' || s[2] == '\t'))
		return parse_texture(data, &data->ea, s + 2, "EA");
	if (s[0] == 'F' && (s[1] == ' ' || s[1] == '\t'))
		return parse_color(data, &data->f, s + 1, "F");
	if (s[0] == 'C' && (s[1] == ' ' || s[1] == '\t'))
		return parse_color(data, &data->c, s + 1, "C");
	return 0;
}

int	parse_texture(t_config *data, int *flag, char *after_key, char *type)
{
	char   **dest;
	char   *pos = skip_ws(after_key);
	char   *trimmed;

	if (*flag)
		return (printf("Error: Duplicate %s\n", type), 0);
	trimmed = ft_strtrim(pos, " \t\r\n");
	if (!trimmed)
		return 0;
	if (ft_strlen(trimmed) < 5 || ft_strcmp(trimmed + ft_strlen(trimmed) - 4, ".xpm") != 0)
	{
		free(trimmed);
		return (printf("Error: %s must be a .xpm file\n", type), 0);
	}
	if (ft_strcmp(type, "NO") == 0)
		dest = &data->no_path;
	else if (ft_strcmp(type, "SO") == 0)
		dest = &data->so_path;
	else if (ft_strcmp(type, "WE") == 0)
		dest = &data->we_path;
	else
		dest = &data->ea_path;
	*dest = trimmed;
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


int	parse_color(t_config *data, int *flag, char *after_key, char *type)
{
	char	*tmp = skip_ws(after_key);
	t_color	*color;

	if (*flag)
		return (printf("Error: Duplicate %s\n", type), 0);
	color = (type[0] == 'F') ? &data->floor : &data->ceiling;
	color->r = guyni_stugum(&tmp);
	if (*tmp++ != ',')
		return (printf("Error: Invalid %s format\n", type), 0);
	color->g = guyni_stugum(&tmp);
	if (*tmp++ != ',')
		return (printf("Error: Invalid %s format\n", type), 0);
	color->b = guyni_stugum(&tmp);
	while (*tmp == ' ' || *tmp == '\t')
		tmp++;
	// if (!(*tmp == '\0' || *tmp == '\n' || *tmp == '\r'))
	// 	return (printf("Error: Trailing characters in %s\n", type), 0);
	// if (color->r == -1 || color->g == -1 || color->b == -1)
	// 	return (printf("Error: %s values must be 0..255\n", type), 0);
	*flag = 1;
	return 1;
}

int	parse(t_config *data, char **lines, int *start_index)
{
	int	i;

	i = 0;
	while (lines[i] && !(data->no && data->so && data->we && data->ea && data->f && data->c))
	{
		if (is_ws_only(lines[i])) 
		{
			i++;
			continue;
		}
		if (!demi_6_toxy(lines[i]))
			break;
		if (!parse_et_6_toxy(data, lines[i]))
			return 0;
		i++;
	}
	if (!(data->no && data->so && data->we && data->ea && data->f && data->c))
		return (printf("Error: Missing texture or color.\n"), 0);
	while (lines[i] && is_ws_only(lines[i]))
		i++;
	*start_index = i;
	return 1;
}
